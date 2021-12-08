/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2014. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <cutils/properties.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <poll.h>
#include "cutils/log.h"
#include "cutils/memory.h"
#include "cutils/misc.h"

#include "private/android_filesystem_config.h"


#include "bt_mtk.h"
#include "upio.h"
/*add for ZTE set sdio power*/
#include <asm/ioctl.h>


//0: power on
//!0: power off
/*end*/
#ifndef UPIO_DBG
#define UPIO_DBG TRUE
#endif
#if (UPIO_DBG == TRUE)
#define UPIODBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define UPIODBG(param, ...) {}
#endif
static char *rfkill_state_path = NULL;
static int rfkill_id = -1;
static int bt_emul_enable = 0;
#define msleep(x) usleep(x*1000) 

/**************************************************************************
 *                  G L O B A L   V A R I A B L E S                       *
***************************************************************************/

bt_vendor_callbacks_t *bt_vnd_cbacks = NULL;
static int  bt_fd = -1;

/**************************************************************************
 *              F U N C T I O N   D E C L A R A T I O N S                 *
***************************************************************************/

extern BOOL BT_InitDevice(
    UINT32  chipId,
    PUCHAR  pucNvRamData,
    UINT32  u4Baud,
    UINT32  u4HostBaud,
    UINT32  u4FlowControl,
    SETUP_UART_PARAM_T setup_uart_param
);

extern BOOL BT_InitSCO(VOID);
extern BOOL BT_DeinitDevice(VOID);
extern VOID BT_Cleanup(VOID);


/*******************add for ZTE SDIO*********************************/

static const char DRIVER_PROP_NAME[]    = "bluetooth.btdriver.mtk";
//static const char DRIVER_PROP_NAME2[]    = "mtkbt";
//static const char DRIVER_PROP_NAME_INSMOD[]    = "bluetooth.btdriver.insmod";

/*****************************************************************************
**   Bluetooth On/Off Static Functions
*****************************************************************************/
static int is_emulator_context(void)
{
    char value[PROPERTY_VALUE_MAX];

    property_get("ro.kernel.qemu", value, "0");
    UPIODBG("is_emulator_context : %s", value);
    if (strcmp(value, "1") == 0) {
        return 1;
    }
    return 0;
}

static int is_rfkill_disabled(void)
{
    char value[PROPERTY_VALUE_MAX];

    property_get("ro.rfkilldisabled", value, "0");
    UPIODBG("is_rfkill_disabled ? [%s]", value);

    if (strcmp(value, "1") == 0) {
        return UPIO_BT_POWER_ON;
    }

    return UPIO_BT_POWER_OFF;
}

static int init_rfkill()
{
    char path[64];
    char buf[16];
    int fd, sz, id;

    if (is_rfkill_disabled())
        return -1;

    for (id = 0; ; id++)
    {
        snprintf(path, sizeof(path), "/sys/class/rfkill/rfkill%d/type", id);
        fd = open(path, O_RDONLY);
        if (fd < 0)
        {
            ALOGE("init_rfkill : open(%s) failed: %s (%d)\n", \
                 path, strerror(errno), errno);
            return -1;
        }

        sz = read(fd, &buf, sizeof(buf));
        close(fd);

        if (sz >= 9 && memcmp(buf, "bluetooth", 9) == 0)
        {
            rfkill_id = id;
            break;
        }
    }

    asprintf(&rfkill_state_path, "/sys/class/rfkill/rfkill%d/state", rfkill_id);
    return 0;
}


/*******************************************************************************
**
** Function        upio_set_bluetooth_power
**
** Description     Interact with low layer driver to set Bluetooth power
**                 on/off.
**
** Returns         0  : SUCCESS or Not-Applicable
**                 <0 : ERROR
**
*******************************************************************************/
int upio_set_bluetooth_power(int on)
{
    int sz;
    int fd = -1;
    int ret = -1;
    char buffer = '0';
	ALOGE("amlogic-upio_set_bluetooth_power on:%d",on);
    switch(on)
    {
        case UPIO_BT_POWER_OFF:
            buffer = '0';
            break;

        case UPIO_BT_POWER_ON:
            buffer = '1';
            break;
    }

    if (is_emulator_context())
    {
        /* if new value is same as current, return -1 */
        if (bt_emul_enable == on)
            return ret;

        UPIODBG("set_bluetooth_power [emul] %d", on);

        bt_emul_enable = on;
        return 0;
    }

    /* check if we have rfkill interface */
    if (is_rfkill_disabled())
        return 0;

    if (rfkill_id == -1)
    {
        if (init_rfkill())
        	{
        		ALOGE("#####INIT rfkill fail");
            	return ret;
}
    }

    fd = open(rfkill_state_path, O_WRONLY);
	ALOGE("#######open rfkill fd=%d",fd);
    if (fd < 0)
    {
        ALOGE("set_bluetooth_power : open(%s) for write failed: %s (%d)",
            rfkill_state_path, strerror(errno), errno);
        return ret;
    }

    sz = write(fd, &buffer, 1);
	ALOGE("####write rfkill sz=%d",sz);
    if (sz < 0) {
        ALOGE("set_bluetooth_power : write(%s) failed: %s (%d)",
            rfkill_state_path, strerror(errno),errno);
    }
    else
        ret = 0;

    if (fd >= 0)
        close(fd);

    return ret;
}


int bt_load_driver()
{
	char driver_status[PROPERTY_VALUE_MAX];
	int count = 0; 
   //int ins;
    sleep(1);
   //upio_set_bluetooth_power(UPIO_BT_POWER_ON);
   //ALOGE("set sdio power on success\n");
   //msleep(200);
   //sdio_reinit();
    if(upio_set_bluetooth_power(UPIO_BT_POWER_ON)==0)
   	{
   		ALOGE("set sdio power on success\n");
   	}
   	else
   	{
   	    ALOGE("set sdio power on failed\n");
   	}
	property_get(DRIVER_PROP_NAME, driver_status, "mtkdrunkown");
	ALOGD("check loading bt driver whether ok ####000 driver_status = %s ", driver_status);
	if(strcmp("true",driver_status) == 0)
	   return 1;
	ALOGD("check loading bt driver whether ok driver_status = %s ", driver_status);
	property_set(DRIVER_PROP_NAME,"true");
	sleep(3);
	
  return 1;
}

/**************************************************************************
 *                          F U N C T I O N S                             *
***************************************************************************/

static BOOL is_memzero(unsigned char *buf, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (*(buf+i) != 0) return FALSE;
    }
    return TRUE;
}

/* Register callback functions to libbt-hci.so */
void set_callbacks(const bt_vendor_callbacks_t *p_cb)
{
    bt_vnd_cbacks = p_cb;
}

/* Cleanup callback functions previously registered */
void clean_callbacks(void)
{
    bt_vnd_cbacks = NULL;
}

/* Initialize UART port */
int init_uart(void)
{
    LOG_TRC();
    int i=6;
    /*insmod bt driver*/
    if(bt_load_driver())
    	{
    		ALOGD("insmod bt driver ok\n");
			do{
    			bt_fd = open("/dev/stpbt", O_RDWR | O_NOCTTY | O_NONBLOCK);
				if (bt_fd < 0) {
					LOG_ERR("Can't open serial port\n");
					i--;
					msleep(300);
				}
				else{
					ALOGD("open stpbt ok!\n");
					break;
					}
			}while(i>0);
    	}
    	else
    	{
    		LOG_ERR("inmod bt driver error");	
    		bt_fd = -1;
    	}
    /*end*/
    return bt_fd;
}

/* Close UART port previously opened */
void close_uart(void)
{
    if (bt_fd >= 0) 
    close(bt_fd);
    bt_fd = -1;
    
  /*set sdio off*/
   property_set(DRIVER_PROP_NAME,"false");
   sleep(2);
   upio_set_bluetooth_power(UPIO_BT_POWER_OFF);
}

static int bt_get_combo_id(unsigned int *pChipId)
{
    int  chipId_ready_retry = 0;
    char chipId_val[PROPERTY_VALUE_MAX];

    do {
        if (property_get("persist.mtk.wcn.combo.chipid", chipId_val, NULL) &&
            0 != strcmp(chipId_val, "-1")) {
            *pChipId = (unsigned int)strtoul(chipId_val, NULL, 16);
            break;
        }
        else {
            chipId_ready_retry ++;
            usleep(500000);
        }
    } while(chipId_ready_retry < 10);

    LOG_DBG("Get combo chip id retry %d\n", chipId_ready_retry);
    if (chipId_ready_retry >= 10) {
        LOG_DBG("Invalid combo chip id!\n");
        return -1;
    }
    else {
        LOG_DBG("Combo chip id %x\n", *pChipId);
        return 0;
    }
}

/* MTK specific chip initialize process */
int mtk_fw_cfg(void)
{
    unsigned int chipId = 0x7662;
    unsigned char ucNvRamData[64] = {0};
    unsigned int speed, flow_control;
    SETUP_UART_PARAM_T uart_setup_callback = NULL;

    LOG_TRC();

    LOG_WAN("[BDAddr %02x-%02x-%02x-%02x-%02x-%02x][Voice %02x %02x][Codec %02x %02x %02x %02x] \
            [Radio %02x %02x %02x %02x %02x %02x][Sleep %02x %02x %02x %02x %02x %02x %02x][BtFTR %02x %02x] \
            [TxPWOffset %02x %02x %02x][CoexAdjust %02x %02x %02x %02x %02x %02x]\n",
            ucNvRamData[0], ucNvRamData[1], ucNvRamData[2], ucNvRamData[3], ucNvRamData[4], ucNvRamData[5],
            ucNvRamData[6], ucNvRamData[7],
            ucNvRamData[8], ucNvRamData[9], ucNvRamData[10], ucNvRamData[11],
            ucNvRamData[12], ucNvRamData[13], ucNvRamData[14], ucNvRamData[15], ucNvRamData[16], ucNvRamData[17],
            ucNvRamData[18], ucNvRamData[19], ucNvRamData[20], ucNvRamData[21], ucNvRamData[22], ucNvRamData[23], ucNvRamData[24],
            ucNvRamData[25], ucNvRamData[26],
            ucNvRamData[27], ucNvRamData[28], ucNvRamData[29],
            ucNvRamData[30], ucNvRamData[31], ucNvRamData[32], ucNvRamData[33], ucNvRamData[34], ucNvRamData[35]);


    return (BT_InitDevice(
              chipId,
              ucNvRamData,
              speed,
              speed,
              flow_control,
              uart_setup_callback) == TRUE ? 0 : -1);
}

/* MTK specific SCO/PCM configuration */
int mtk_sco_cfg(void)
{
    return (BT_InitSCO() == TRUE ? 0 : -1);
}

/* MTK specific deinitialize process */
int mtk_prepare_off(void)
{
    /*
    * On KK, BlueDroid adds BT_VND_OP_EPILOG procedure when BT disable:
    *   - 1. BT_VND_OP_EPILOG;
    *   - 2. In vendor epilog_cb, send EXIT event to bt_hc_worker_thread;
    *   - 3. Wait for bt_hc_worker_thread exit;
    *   - 4. userial close;
    *   - 5. vendor cleanup;
    *   - 6. Set power off.
    * On L, the disable flow is modified as below:
    *   - 1. userial Rx thread exit;
    *   - 2. BT_VND_OP_EPILOG;
    *   - 3. Write reactor->event_fd to trigger bt_hc_worker_thread exit
    *        (not wait to vendor epilog_cb and do nothing in epilog_cb);
    *   - 4. Wait for bt_hc_worker_thread exit;
    *   - 5. userial close;
    *   - 6. Set power off;
    *   - 7. vendor cleanup.
    *
    * It seems BlueDroid does not expect Tx/Rx interaction with chip during
    * BT_VND_OP_EPILOG procedure, and also does not need to do it in a new
    * thread context (NE may occur in __pthread_start if bt_hc_worker_thread
    * has already exited).
    * So BT_VND_OP_EPILOG procedure may be not for chip deinitialization,
    * do nothing, just notify success.
    *
    * [FIXME!!]How to do if chip deinit is needed?
    */
    //return (BT_DeinitDevice() == TRUE ? 0 : -1);
    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->epilog_cb(BT_VND_OP_RESULT_SUCCESS);
    }
    return 0;
}

/* Cleanup driver resources, e.g thread exit */
void clean_resource(void)
{
    BT_Cleanup();
}
