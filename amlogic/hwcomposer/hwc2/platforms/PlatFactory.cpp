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

#include <HwcTrace.h>
#include <PrimaryDevice.h>
//#include <ExternalDevice.h>
#include <VirtualDevice.h>
#include <Hwcomposer.h>
#include <PlatFactory.h>
#include <GE2DComposer.h>

namespace android {
namespace amlogic {

PlatFactory::PlatFactory()
{
    CTRACE();
}

PlatFactory::~PlatFactory()
{
    CTRACE();
}

IDisplayDevice* PlatFactory::createDisplayDevice(int disp)
{
    CTRACE();
    //when createDisplayDevice is called, Hwcomposer has already finished construction.
    Hwcomposer &hwc = Hwcomposer::getInstance();

    class PlatDeviceControlFactory: public DeviceControlFactory {
    public:
        virtual IComposer* createComposer(IDisplayDevice& disp)       {return new GE2DComposer(disp);}
    };

    switch (disp) {
        case IDisplayDevice::DEVICE_PRIMARY:
            return new PrimaryDevice(hwc, new PlatDeviceControlFactory());
        case IDisplayDevice::DEVICE_VIRTUAL:
            return new VirtualDevice(hwc);
        case IDisplayDevice::DEVICE_EXTERNAL:
            // return new ExternalDevice(hwc, new PlatDeviceControlFactory());
        default:
            WTRACE("invalid display device %d", disp);
            return NULL;
    }
}

Hwcomposer* Hwcomposer::createHwcomposer()
{
    CTRACE();
    Hwcomposer *hwc = new Hwcomposer(new PlatFactory());
    return hwc;
}

} //namespace amlogic
} //namespace android
