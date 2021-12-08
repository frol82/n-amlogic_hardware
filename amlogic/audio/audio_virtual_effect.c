/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "audio_virtual_effect"

#include <cutils/log.h>
#include <cutils/properties.h>
#include <pthread.h>
#include <stdlib.h>

#include "LVCS.h"
#include "InstAlloc.h"
#include "LVCS_Private.h"

#include "audio_virtual_effect.h"

LVCS_Handle_t           hCSInstance = LVM_NULL; /* Concert Sound instance handle */
LVCS_Instance_t         CS_Instance;        /* Concert Soun= d instance */

LVCS_MemTab_t           CS_MemTab;          /* Memory table */
LVCS_Capabilities_t     CS_Capabilities;    /* Initial capabilities */

static pthread_mutex_t audio_vir_mutex = PTHREAD_MUTEX_INITIALIZER;

int Virtualizer_init(void) {
    LVCS_ReturnStatus_en    LVCS_Status;
    LVCS_Params_t *CS_Params = &CS_Instance.Params;
    int i = 0;

    pthread_mutex_lock(&audio_vir_mutex);

    CS_Capabilities.MaxBlockSize = 2048;
    CS_Capabilities.pBundleInstance = (void*)hCSInstance;

    LVCS_Status = LVCS_Memory(LVM_NULL,
                              &CS_MemTab,
                              &CS_Capabilities);

    CS_MemTab.Region[LVCS_MEMREGION_PERSISTENT_SLOW_DATA].pBaseAddress = &CS_Instance;

    /* Allocate memory */
    for (i = 0; i < LVM_NR_MEMORY_REGIONS; i++) {
        if (CS_MemTab.Region[i].Size != 0) {
            CS_MemTab.Region[i].pBaseAddress = malloc(CS_MemTab.Region[i].Size);

            if (CS_MemTab.Region[i].pBaseAddress == LVM_NULL) {
                ALOGV("\tLVM_ERROR :LvmBundle_init CreateInstance Failed to allocate %"
                      " bytes for region %u\n", CS_MemTab.Region[i].Size, i );
                return LVCS_NULLADDRESS;
            } else {
                ALOGV("\tLvmBundle_init CreateInstance allocated %"
                      " bytes for region %u at %p\n",
                      CS_MemTab.Region[i].Size, i, CS_MemTab.Region[i].pBaseAddress);
            }
        }
    }

    hCSInstance = LVM_NULL;
    LVCS_Status = LVCS_Init(&hCSInstance,
                            &CS_MemTab,
                            &CS_Capabilities);

    CS_Params->OperatingMode = LVCS_OFF;
    CS_Params->CompressorMode = LVM_MODE_ON;
    CS_Params->SourceFormat = LVCS_STEREO;
    CS_Params->SpeakerType = LVCS_HEADPHONES;
    CS_Params->SampleRate  = LVM_FS_48000;
    CS_Params->ReverbLevel = 100;
    CS_Params->EffectLevel = 0; /* 0~32767 */

    pthread_mutex_unlock(&audio_vir_mutex);
    return LVCS_Status;
}

int Virtualizer_release(void) {
    int i;
    pthread_mutex_lock(&audio_vir_mutex);
    for (i = 0; i < LVM_NR_MEMORY_REGIONS; i++) {
        if (CS_MemTab.Region[i].pBaseAddress != 0) {
            free(CS_MemTab.Region[i].pBaseAddress);
            CS_MemTab.Region[i].pBaseAddress = NULL;
        }
    }
    hCSInstance = LVM_NULL;
    pthread_mutex_unlock(&audio_vir_mutex);
    return 0;
}

// enable: 1; disable:0, EffectLevel:0~100
int Virtualizer_control(int enable, int EffectLevel) {

    LVCS_ReturnStatus_en        CS_Status;
    LVCS_Params_t               *CS_Params = &CS_Instance.Params;

    if (hCSInstance == LVM_NULL)
        return LVCS_NULLADDRESS;

    pthread_mutex_lock(&audio_vir_mutex);
    if (enable == 1)
        CS_Params->OperatingMode    = LVCS_ON;
    else
        CS_Params->OperatingMode    = LVCS_OFF;

    if (EffectLevel > 100)
        CS_Params->EffectLevel    = 32700;
    else if (EffectLevel < 0)
        CS_Params->EffectLevel    = 0;
    else
        CS_Params->EffectLevel    = EffectLevel * 327;

    CS_Status = LVCS_Control(hCSInstance,
                             CS_Params);

    pthread_mutex_unlock(&audio_vir_mutex);
    return CS_Status;
}

int Virtualizer_process(int16_t *pInData, int16_t *pOutData, uint16_t NumSamples) {
    LVCS_ReturnStatus_en        CS_Status;

    if (hCSInstance == LVM_NULL)
        return LVCS_NULLADDRESS;

    pthread_mutex_lock(&audio_vir_mutex);
    CS_Status =  LVCS_Process(hCSInstance,
                              pInData,
                              pOutData,
                              NumSamples);
    pthread_mutex_unlock(&audio_vir_mutex);
    return CS_Status;
}
