/*
 * Copyright (C) 2012 The Android Open Source Project
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
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_TAG "PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>
#define DEBUG 0

struct private_power_module {
    power_module_t base;
    int fp;
};

static void power_init(struct power_module *module)
{
}

static void power_set_interactive(struct power_module *module, int on)
{
}

static void power_hint(struct power_module *module, power_hint_t hint,
                       void *data) {

    struct private_power_module *pm = (struct private_power_module *) module;

    const char *val = "preheat";
    static int bytes = 7;

    if (pm->fp == -1) {
        pm->fp = open("/sys/class/mpgpu/mpgpucmd", O_RDWR, 0644);
        if (DEBUG) {
            ALOGD("open file /sys/class/mpgpu/mpgpucmd,fd is %d", pm->fp);
        }
    }

    switch (hint) {
    case POWER_HINT_INTERACTION:
        if (pm->fp >= 0) {
            int len = write(pm->fp, val, bytes);
            if (DEBUG) {
                ALOGD("%s: write sucessfull, fd is %d\n", __FUNCTION__, pm->fp);
            }

            if (len != bytes)
                ALOGE("write preheat faile");
        }
        break;

    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct private_power_module HAL_MODULE_INFO_SYM = {
    .base = {
        .common = {
            .tag = HARDWARE_MODULE_TAG,
            .module_api_version = POWER_MODULE_API_VERSION_0_2,
            .hal_api_version = HARDWARE_HAL_API_VERSION,
            .id = POWER_HARDWARE_MODULE_ID,
            .name = "Default Power HAL",
            .author = "The Android Open Source Project",
            .methods = &power_module_methods,
        },
        .init = power_init,
        .setInteractive = power_set_interactive,
        .powerHint = power_hint,
    },
    .fp = -1,
};
