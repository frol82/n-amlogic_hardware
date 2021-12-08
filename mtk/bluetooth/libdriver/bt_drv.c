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

#include "bt_vendor_lib.h"
#include "bt_mtk.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cutils/sockets.h>

//===============        V A R I A B L E S       =======================
static unsigned int remaining_length = 0; // the remaing data length
static uint8_t data_buffer[1024]; // store the hci event
static uint8_t* remaining_data_buffer = NULL; // pointer to current data position
static uint8_t* current_pos = NULL;
static void whole_chip_reset(void);

//===============        P R I V A T E  A P I      =======================
void _mtk_bt_handle_voice_search_data(const uint8_t *buf, const unsigned int buf_len)
{
    if ( (buf_len == 13 || buf_len == 32) &&
         buf[0] == 0x02 && buf[1] == 0x00 && buf[2] == 0x22 &&
         (buf[3] == 0x08 || buf[3] == 0x1b) && buf[4] == 0x00 &&
         buf[9] == 0x1b && buf[10] == 0x35 && buf[11] == 0x00 )
    {
        int i;
        int ret;

        // GATT data pattern for key code (len = 4):
        //          Key Press           : 4b 00 00 0x
        //          Key Release         : 4b 00 00 00
        //          Voice key press     : 4b 00 00 07
        //          Voice key release   : 4b 00 00 00
        // GATT data pattern for voice data :
        //          Frist       : 35 00 04
        //          Second      : 35 00 xx xx xx (total 22Byte)
        static int g_connection_created = FALSE;
        static int g_voice_sockfd;
        static struct sockaddr_un g_voice_sockaddr;
        static socklen_t g_voice_sockaddr_len;
        static const char* const serverAddr="voice.source.address";
        int err;
#ifdef BT_DRV_PRINT_DBG_LOG
    if ( buf_len == 13 )
        LOG_DBG("full:hci_event(%d):%02X\n", buf_len, buf[12]);
    else
        LOG_DBG("full:hci_event(%d):%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", 
                buf_len,
                buf[12],
                buf[13],
                buf[14],
                buf[15],
                buf[16],
                buf[17],
                buf[18],
                buf[19],
                buf[20],
                buf[21],
                buf[22],
                buf[23],
                buf[24],
                buf[25],
                buf[26],
                buf[27],
                buf[28],
                buf[29],
                buf[30],
                buf[31]);
#endif
        if ( buf_len == 13 && buf[12] == 0x04 && g_connection_created == TRUE && g_voice_sockfd )
        {
            LOG_DBG("%s : close existing socket\n", __FUNCTION__);
            close(g_voice_sockfd);
            g_connection_created = FALSE;
        }

        if ( g_connection_created == FALSE )
        {
            //extern int socket_make_sockaddr_un(const char *name, int ns_id, struct sockaddr_un *p_addr, socklen_t *alen);
            err = 1;//socket_make_sockaddr_un(serverAddr,
                    //                      ANDROID_SOCKET_NAMESPACE_ABSTRACT,
                    //                      &g_voice_sockaddr, &g_voice_sockaddr_len);
            if ( err )
            {
                LOG_ERR("%s : Create socket failed.", __FUNCTION__);
                return;
            }

            g_voice_sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
            if (g_voice_sockfd < 0)
            {
                LOG_ERR("%s : Create server socket failed.", __FUNCTION__);
                return;
            }
            g_connection_created = TRUE;
        }

    	err = sendto(g_voice_sockfd, buf+12, buf_len-12 , MSG_DONTWAIT , (struct sockaddr*) &g_voice_sockaddr, g_voice_sockaddr_len) ;
        if ( err < 0 )
        {
            static int counter=0;
            counter++;
            if ( counter == 100 )
            {
                LOG_ERR("%s : send FAILED (%s:%d) x 100\n", __FUNCTION__, strerror(errno), errno);
                counter = 0;
            }
        }
    }
}

//===============        I N T E R F A C E S      =======================

int mtk_bt_init(const bt_vendor_callbacks_t* p_cb, unsigned char *local_bdaddr)
{
    (void)local_bdaddr;
    LOG_TRC();
    set_callbacks(p_cb);
	remaining_data_buffer = data_buffer;
    return 0;
}

int mtk_bt_op(bt_vendor_opcode_t opcode, void *param)
{
    int ret = 0;

    switch(opcode)
    {
      case BT_VND_OP_POWER_CTRL:
        LOG_DBG("BT_VND_OP_POWER_CTRL %d\n", *((int*)param));
        /* DO NOTHING on combo chip */
        break;

      case BT_VND_OP_USERIAL_OPEN:
        LOG_DBG("BT_VND_OP_USERIAL_OPEN\n");

        ((int*)param)[0] = init_uart();
        ret = 1; // CMD/EVT/ACL-In/ACL-Out via the same fd
        break;

      case BT_VND_OP_USERIAL_CLOSE:
        LOG_DBG("BT_VND_OP_USERIAL_CLOSE\n");
        close_uart();
        break;

      case BT_VND_OP_FW_CFG:
        LOG_DBG("BT_VND_OP_FW_CFG\n");
        ret = mtk_fw_cfg();
        break;

      case BT_VND_OP_SCO_CFG:
        LOG_DBG("BT_VND_OP_SCO_CFG\n");
        ret = mtk_sco_cfg();
        break;

      case BT_VND_OP_GET_LPM_IDLE_TIMEOUT:
        LOG_DBG("BT_VND_OP_GET_LPM_IDLE_TIMEOUT\n");
        *((uint32_t*)param) = 5000; //ms
        break;

      case BT_VND_OP_LPM_SET_MODE:
        LOG_DBG("BT_VND_OP_LPM_SET_MODE %d\n", *((uint8_t*)param));
        break;

      case BT_VND_OP_LPM_WAKE_SET_STATE:
        break;

      case BT_VND_OP_EPILOG:
        LOG_DBG("BT_VND_OP_EPILOG\n");
        ret = mtk_prepare_off();
        break;

      default:
        LOG_DBG("Unknown operation %d\n", opcode);
        break;
    }

    return ret;
}

void mtk_bt_cleanup()
{
    LOG_TRC();
	remaining_data_buffer = NULL;
    clean_resource();
    clean_callbacks();
    return;
}

void mtk_bt_notify_hci_cmd(const uint8_t* buf, const unsigned int buf_len)
{
	LOG_DBG("send HCI CMD, length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x",
		buf_len, buf[0], buf[1], buf[2], buf[3]);
	return;
}

void mtk_bt_handle_acl(const uint8_t *buf, const unsigned int buf_len)
{
    _mtk_bt_handle_voice_search_data(buf, buf_len);
}

void mtk_bt_handle_event(const uint8_t *buf, const unsigned int buf_len)
{
    (void)buf;
    (void)buf_len;
}

void mtk_bt_notify_hci_event(const uint8_t* buf, const unsigned int buf_len)
{
	unsigned int length = buf_len;

	uint8_t* buffer = (uint8_t*)buf;
	BT_HDR_T hdr = 0x00;
	unsigned int size = 0;
#ifdef BT_DRV_PRINT_DBG_LOG
	LOG_DBG("enter");
#endif
	unsigned char reset_event[] = {0x04, 0xFF, 0x04, 0x00, 0x01, 0xFF, 0xFF};

	// handle reset condition
	if (buf_len == 7 && buf[1] == 0xFF && buf[0] == 0x04 && buf[2] == 0x04 && buf[3] == 0x00
		&& buf[4] == 0x01 && buf[5] == 0xFF && buf[6] == 0xFF) {
		LOG_DBG("kill self to trigger reset");
		whole_chip_reset();
	}

	while(length > 0) {
		// only remaining_length is zero, we can use buffer[0] to know data type
		if (remaining_length == 0) {
			switch (buffer[0])
			{
				case BT_ACL:
					size = 1*(buffer[3]&0x0f) + 16*((buffer[3]&0xf0)>>4)
					+ 256*((buffer[4]&0x0f)) + 4096*((buffer[4]&0xf0)>>4);

					if ((length-5) >= size) {
						// the received ACL data is complete
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full:%d, receive com-ACL, full length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, size+5, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
#endif
						// deliver the data pointer to handle
						mtk_bt_handle_acl(buffer, size+5);

						// move buffer
						length = length - size - 5;
						if(length > 0)
							buffer = buffer + size + 5;

						// reset values
						remaining_data_buffer = data_buffer;
						remaining_length = 0;
					} else {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full:%d, receive incom-ACL, remaining length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, size+5);

						// there is remaining ACL data in next packet, update related variables
						remaining_length = size - length + 5; // (header:1 byte + handle: 2 bytes + size: 2 bytes)
						remaining_data_buffer = remaining_data_buffer + size + 5;
						length = 0;
					}
					break;
				case BT_HCI_EVENT:
					size = buffer[2];
					// the received HCI event is complete
					if ((length-3) >= size) {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full len:%d, receive comp-hci, length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, size, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
#endif
						// deliver the data pointer to handle
						mtk_bt_handle_event(buffer, size+3);

						// move buffer
						length = length-size-3; // length subtract hci event (hdr + status + length + payload)
						if(length > 0)
							buffer = buffer + size + 3;

						// reset values
						remaining_length = 0;
						remaining_data_buffer = data_buffer;
						
					} else {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full len:%d, receive incom-hci, remaining length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
				    		buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, size+3);
						
						// there is remaining event data in next packet, update related variables
						remaining_length = size - length + 3; // 2(header:1 byte + status: 1 byte + size: 1 byte)
						remaining_data_buffer = remaining_data_buffer + size + 3;
						length = 0;
					}
					break;
				default:
					LOG_ERR("Unknown header:0x%02x, reset all flags", buffer[0]);
					unsigned int i;
					for(i = 0; i < buf_len; i++){
						LOG_ERR("content:0x%02x", buf[i]);
					}
					// reset all log checking flags
					remaining_length = 0;
					remaining_data_buffer = data_buffer;
					length = 0;
					break;
			}
		} else {
			int data_length = 0;
			switch (data_buffer[0])
			{
				case BT_ACL:
					if(remaining_length > buf_len) {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full:%d, receive incom-ACL, remaining len:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
			    			buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, buf_len);

						// update values
						remaining_data_buffer += buf_len;
						remaining_length -= buf_len;
						length = 0;
					} else if (remaining_length == buf_len) {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full:%d, receive last ACL:%d, remaining len:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, data_length+5, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, buf_len);

						// deliver the data pointer to handle
						data_length = 1*(data_buffer[3]&0x0f) + 16*((data_buffer[3]&0xf0)>>4)
							+ 256*((data_buffer[4]&0x0f)) + 4096*((data_buffer[4]&0xf0)>>4);
						mtk_bt_handle_acl(data_buffer, data_length+5);

						// update values
						remaining_data_buffer = data_buffer;
						remaining_length -= buf_len;
						length = 0;
					} else {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full:%d, receive last ACL:%d and other event, remaining len:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
		    				buf_len, data_length+5, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, remaining_length);

						// deliver the data pointer to handle
						data_length = 1*(data_buffer[3]&0x0f) + 16*((data_buffer[3]&0xf0)>>4)
							+ 256*((data_buffer[4]&0x0f)) + 4096*((data_buffer[4]&0xf0)>>4);
						mtk_bt_handle_acl(data_buffer, data_length+5);

						// update values
						remaining_data_buffer = data_buffer;
						remaining_length = 0;
						length -= remaining_length;
						buffer += remaining_length;
					}
					break;
				case BT_HCI_EVENT:
					if(remaining_length > buf_len) {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full len:%d, receive second incom-HCI, remaining length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, buf_len);

						// update values
						remaining_data_buffer += buf_len;
						remaining_length -= buf_len;
						length = 0;
					} else if (remaining_length == buf_len) {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full len:%d, receive last HCI, remaining length:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, buf_len);

						// deliver the data pointer to handle
						data_length = data_buffer[2];
						mtk_bt_handle_event(data_buffer, data_length+3);

						// update values
						remaining_data_buffer = data_buffer;
						remaining_length -= buf_len;
						length = 0;
					} else {
#ifdef BT_DRV_PRINT_DBG_LOG
						LOG_DBG("full len:%d, receive last HCI and other event, remaining len:%d, content:0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x", 
    						buf_len, remaining_length, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
#endif
						// copy data to buffer
						memcpy(remaining_data_buffer, buf, remaining_length);

						// deliver the data pointer to handle
						data_length = data_buffer[2];
						mtk_bt_handle_event(data_buffer, data_length+3);

						// update values
						remaining_data_buffer = data_buffer;
						remaining_length = 0;
						length -= remaining_length;
						buffer += remaining_length;
					}
					break;
				default:
					LOG_ERR("Unknown header:0x%02x, reset all flags", data_buffer[0]);
					unsigned int i;
					for(i = 0; i < buf_len; i++){
						LOG_ERR("content:0x%02x", buf[i]);
					}
					// reset all log checking flags
					remaining_length = 0;
					remaining_data_buffer = data_buffer;
					length = 0;
					break;
			}
		}
	}
#ifdef BT_DRV_PRINT_DBG_LOG
	LOG_DBG("leave the loop");
#endif
	return;
}

const bt_vendor_interface_t BLUETOOTH_VENDOR_LIB_INTERFACE = {
    sizeof(bt_vendor_interface_t),
    mtk_bt_init,
    mtk_bt_op,
    mtk_bt_cleanup,
    mtk_bt_notify_hci_cmd,
    mtk_bt_notify_hci_event,
};   

static void whole_chip_reset(void)
{    
	ALOGE("whole_chip_reset Restarting BT process");    
	usleep(10000); /* 10 milliseconds */    
	/* Killing the process to force a restart as part of fault tolerance */    
	kill(getpid(), SIGKILL);
}