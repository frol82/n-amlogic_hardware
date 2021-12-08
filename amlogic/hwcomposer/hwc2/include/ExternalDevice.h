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

#ifndef EXTERNAL_DEVICE_H
#define EXTERNAL_DEVICE_H

#include <PhysicalDevice.h>
#include <IHdcpControl.h>
#include <SimpleThread.h>

#include <DisplayHdmi.h>

namespace android {
namespace amlogic {


class ExternalDevice : public PhysicalDevice {

public:
    ExternalDevice(Hwcomposer& hwc, DeviceControlFactory* controlFactory);
    virtual ~ExternalDevice();
public:
    virtual bool initialize();
    virtual void deinitialize();
    virtual bool setDrmMode(drmModeModeInfo& value);
    virtual void setRefreshRate(int hz);
    virtual int  getActiveConfig();
    virtual bool setActiveConfig(int index);
    int getRefreshRate();
    DisplayHdmi* getDisplayHdmi()  const { return mDisplayHdmi; };

private:
    static void HdcpLinkStatusListener(bool success, void *userData);
    void HdcpLinkStatusListener(bool success);
    void setDrmMode();
protected:
    IHdcpControl *mHdcpControl;

private:
    static void hotplugEventListener(void *data);
    void hotplugListener();

private:
    Condition mAbortModeSettingCond;
    drmModeModeInfo mPendingDrmMode;
    bool mHotplugEventPending;
    int mExpectedRefreshRate;
    DisplayHdmi* mDisplayHdmi;

private:
    DECLARE_THREAD(ModeSettingThread, ExternalDevice);
};

}
}

#endif /* EXTERNAL_DEVICE_H */
