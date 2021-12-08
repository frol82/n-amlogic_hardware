/*
// Copyright (c) 2014 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This file is modified by Amlogic, Inc. 2017.01.17.
*/

#ifndef PRIMARY_DEVICE_H
#define PRIMARY_DEVICE_H

#include <utils/KeyedVector.h>
#include <PhysicalDevice.h>
#include <IComposerFactory.h>

namespace android {
namespace amlogic {


class PrimaryDevice : public PhysicalDevice {
public:
    PrimaryDevice(Hwcomposer& hwc, DeviceControlFactory *composer);
    virtual ~PrimaryDevice();
public:
    virtual bool initialize();
    virtual void deinitialize();
    virtual int32_t createVirtualDisplay(uint32_t width, uint32_t height, int32_t* format, hwc2_display_t* outDisplay){ return HWC2_ERROR_NONE; }
    virtual int32_t destroyVirtualDisplay(hwc2_display_t display) { return HWC2_ERROR_NONE; }
    virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) { return HWC2_ERROR_NONE; }

private:
    static void hotplugEventListener(void *data, bool status);
    void hotplugListener(bool connected);
};

}
}

#endif /* PRIMARY_DEVICE_H */
