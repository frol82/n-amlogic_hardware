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
#include <pthread.h>
#include <time.h>
#include <cutils/properties.h>

#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"
//#include "utils.h"
#include "bt_mtk.h"


/**************************************************************************
 *                  G L O B A L   V A R I A B L E S                       *
***************************************************************************/

BT_INIT_VAR_T btinit[1];
BT_INIT_CB_T  btinit_ctrl;

static uint16_t wOpCode;
static HCI_CMD_STATUS_T cmd_status;
extern bt_vendor_callbacks_t *bt_vnd_cbacks;

static BOOL fgGetEFUSE = FALSE;
static UCHAR ucDefaultAddr[6];
static UCHAR ucZeroAddr[6];

VOID thread_exit(INT32 signo)
{
    pthread_t tid = pthread_self();
    LOG_DBG("Thread %lu is forced to exit...\n", tid);
    if (pthread_mutex_unlock(&btinit_ctrl.mutex) != 0) {
        LOG_ERR("pthread_mutex_unlock error\n");
    }
    pthread_mutexattr_destroy(&btinit_ctrl.attr);
    pthread_mutex_destroy(&btinit_ctrl.mutex);
    pthread_cond_destroy(&btinit_ctrl.cond);
    pthread_exit(0);
}

VOID *GORM_FW_Init_Thread(VOID *ptr)
{
    INT32 i = 0;
    HC_BT_HDR  *p_buf = NULL;
    bt_vendor_op_result_t ret = BT_VND_OP_RESULT_FAIL;

    LOG_DBG("FW init thread starts\n");

    pthread_mutexattr_init(&btinit_ctrl.attr);
    pthread_mutexattr_settype(&btinit_ctrl.attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&btinit_ctrl.mutex, &btinit_ctrl.attr);
    pthread_cond_init(&btinit_ctrl.cond, NULL);
	ret = BT_VND_OP_RESULT_SUCCESS;

exit:
    pthread_mutexattr_destroy(&btinit_ctrl.attr);
    pthread_mutex_destroy(&btinit_ctrl.mutex);
    pthread_cond_destroy(&btinit_ctrl.cond);

    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->fwcfg_cb(ret);
    }

    btinit_ctrl.worker_thread_running = FALSE;
    return NULL;
}

VOID *GORM_SCO_Init_Thread(VOID *ptr)
{
    INT32 i = 0;
    HC_BT_HDR  *p_buf = NULL;
    bt_vendor_op_result_t ret = BT_VND_OP_RESULT_FAIL;

    LOG_DBG("SCO init thread starts\n");

    pthread_mutexattr_init(&btinit_ctrl.attr);
    pthread_mutexattr_settype(&btinit_ctrl.attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&btinit_ctrl.mutex, &btinit_ctrl.attr);
    pthread_cond_init(&btinit_ctrl.cond, NULL);
    
    ret = BT_VND_OP_RESULT_SUCCESS;

    pthread_mutexattr_destroy(&btinit_ctrl.attr);
    pthread_mutex_destroy(&btinit_ctrl.mutex);
    pthread_cond_destroy(&btinit_ctrl.cond);

    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->scocfg_cb(ret);
    }

    btinit_ctrl.worker_thread_running = FALSE;
    return NULL;
}

