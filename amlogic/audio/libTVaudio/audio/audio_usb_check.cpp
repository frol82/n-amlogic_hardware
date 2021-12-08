/*
 * Copyright (C) 2010 Amlogic Corporation.
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



#define LOG_TAG "aml_audio"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <cutils/log.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <media/AudioSystem.h>
#include <media/AudioParameter.h>
#include <cutils/properties.h>

#include "audio_usb_check.h"
#include "aml_audio.h"

namespace android {

unsigned int deviceID = 0;
extern "C" unsigned int GetUsbAudioCheckFlag(void) {
    return deviceID;
}

static float last_vol = 1.0;
extern "C" float get_android_stream_volume() {
    return last_vol;
}

extern "C" int set_parameters(char parameters[], char parm_key[]) {

    AudioParameter param = AudioParameter();
    String8 value = String8(parameters);
    String8 key = String8(parm_key);
    param.add(key, value);

    String8 keyValuePairs = param.toString();
    //ALOGI("%s\n", param.toString().string());

    audio_io_handle_t handle = -1;
    handle = AudioSystem::getOutput(AUDIO_STREAM_MUSIC,
                                48000,
                                AUDIO_FORMAT_PCM_16_BIT,
                                AUDIO_CHANNEL_OUT_STEREO,
                                AUDIO_OUTPUT_FLAG_PRIMARY
                                );
    if (handle > 0) {
        if (AudioSystem::setParameters(handle, keyValuePairs) != NO_ERROR) {
            ALOGI("Set audio Parameters failed!\n");
            return -1;
        }
    } else {
        ALOGI("get output handle failed\n");
        return -1;
    }
    param.remove(key);
    return 0;
}

static int GetDeviceID(void) {
    deviceID = AudioSystem::getDevicesForStream(AUDIO_STREAM_MUSIC);
    return 0;
}

static int GetStreamVolume(void) {
    float vol = last_vol;
    unsigned int sr = 0;
    AudioSystem::getOutputSamplingRate(&sr, AUDIO_STREAM_MUSIC);
    if (sr > 0) {
        audio_io_handle_t handle = -1;
        handle = AudioSystem::getOutput(AUDIO_STREAM_MUSIC,
                                    48000,
                                    AUDIO_FORMAT_PCM_16_BIT,
                                    AUDIO_CHANNEL_OUT_STEREO,
                                    AUDIO_OUTPUT_FLAG_PRIMARY
        );
        if (handle > 0) {
            if (AudioSystem::getStreamVolume(AUDIO_STREAM_MUSIC,&vol,handle) == NO_ERROR) {
                last_vol = vol;
            } else
                ALOGI("get stream volume failed\n");
        }else
            ALOGI("get output handle failed\n");
    }
    return 0;
}

static int SetAudioDelay(void) {
    char value[PROPERTY_VALUE_MAX];
    if (property_get("media.TV.audio.delay", value, NULL) > 0) {
        int delay = atoi(value);
        if (delay > 0 && get_audio_delay() != delay)
            set_audio_delay(delay);
    }
    return 0;
}

}

static int running_flag = 0;
void* android_check_threadloop(void *data __unused) {
    ALOGI("Start thread loop for android audio check!\n");
	prctl(PR_SET_NAME, (unsigned long)"aml_audio_check");
    while (running_flag) {
        android::GetStreamVolume();
        android::GetDeviceID();
        android::SetAudioDelay();
        usleep(100*1000);
    }
    ALOGI("Exit thread loop for android audio check!\n");
    return ((void *) 0);
}

extern "C" int creat_pthread_for_android_check
                    (pthread_t *android_check_ThreadID) {
    pthread_attr_t attr;
    struct sched_param param;
    int ret;

    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    //param.sched_priority = sched_get_priority_max(SCHED_RR);
    param.sched_priority = 50;
    pthread_attr_setschedparam(&attr, &param);
	running_flag = 1;
    ret = pthread_create(android_check_ThreadID, &attr,
            &android_check_threadloop, NULL);
    pthread_attr_destroy(&attr);
    if (ret != 0) {
        ALOGE("%s, Create thread fail!\n", __FUNCTION__);
        return -1;
    }
    //ALOGI("Creat thread ID: %u!\n", *android_check_ThreadID);
    return 0;
}

extern "C" int exit_pthread_for_android_check
                    (pthread_t android_check_ThreadID) {
    running_flag = 0;
    //ALOGI("Exit thread ID: %u!\n", android_check_ThreadID);
    pthread_join(android_check_ThreadID, NULL);
    return 0;
}

