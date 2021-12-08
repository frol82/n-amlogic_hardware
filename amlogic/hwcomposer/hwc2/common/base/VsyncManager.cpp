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
#include <Hwcomposer.h>
#include <VsyncManager.h>
#include <IDisplayDevice.h>


namespace android {
namespace amlogic {

VsyncManager::VsyncManager(Hwcomposer &hwc)
     :mHwc(hwc),
      mInitialized(false),
      mEnableDynamicVsync(true),
      mEnabled(false),
      mVsyncSource(IDisplayDevice::DEVICE_COUNT),
      mLock()
{
}

VsyncManager::~VsyncManager()
{
    WARN_IF_NOT_DEINIT();
}

bool VsyncManager::initialize()
{

    mEnabled = false;
    mVsyncSource = IDisplayDevice::DEVICE_COUNT;
    mEnableDynamicVsync = !scUsePrimaryVsyncOnly;
    mInitialized = true;
    return true;
}

void VsyncManager::deinitialize()
{
    if (mEnabled) {
        WTRACE("vsync is still enabled");
    }

    mVsyncSource = IDisplayDevice::DEVICE_COUNT;
    mEnabled = false;
    mEnableDynamicVsync = !scUsePrimaryVsyncOnly;
    mInitialized = false;
}

int32_t VsyncManager::handleVsyncControl(int disp, bool enabled)
{
    Mutex::Autolock l(mLock);

    /*if (disp != IDisplayDevice::DEVICE_PRIMARY) {
        WTRACE("vsync control on non-primary device %d", disp);
        return false;
    }*/

    if (disp > IDisplayDevice::DEVICE_VIRTUAL || disp < IDisplayDevice::DEVICE_PRIMARY) {
        WTRACE("vsync control on invalid device %d", disp);
        return HWC2_ERROR_BAD_DISPLAY;
    }

    if (disp == IDisplayDevice::DEVICE_VIRTUAL) {
        WTRACE("vsync control on virtual device %d", disp);
        return HWC2_ERROR_NONE;
    }

    if (mEnabled == enabled) {
        WTRACE("vsync state %d is not changed", enabled);
        return HWC2_ERROR_NONE;
    }

    if (!enabled) {
        disableVsync();
        mEnabled = false;
    } else {
        mEnabled = enableVsync(getCandidate());
        if (!mEnabled) return HWC2_ERROR_BAD_PARAMETER;
    }

    return HWC2_ERROR_NONE;
}

void VsyncManager::resetVsyncSource()
{
    Mutex::Autolock l(mLock);

    if (!mEnableDynamicVsync) {
        ITRACE("dynamic vsync source switch is not supported");
        return;
    }

    if (!mEnabled) {
        return;
    }

    int vsyncSource = getCandidate();
    if (vsyncSource == mVsyncSource) {
        return;
    }

    disableVsync();
    enableVsync(vsyncSource);
}

int VsyncManager::getVsyncSource()
{
    return mVsyncSource;
}

void VsyncManager::enableDynamicVsync(bool enable)
{
    Mutex::Autolock l(mLock);
    if (scUsePrimaryVsyncOnly) {
        WTRACE("dynamic vsync is not supported");
        return;
    }

    mEnableDynamicVsync = enable;

    if (!mEnabled) {
        return;
    }

    int vsyncSource = getCandidate();
    if (vsyncSource == mVsyncSource) {
        return;
    }

    disableVsync();
    enableVsync(vsyncSource);
}

IDisplayDevice* VsyncManager::getDisplayDevice(int dispType ) {
    return mHwc.getDisplayDevice(dispType);
}

int VsyncManager::getCandidate()
{
    if (!mEnableDynamicVsync) {
        return IDisplayDevice::DEVICE_PRIMARY;
    }

    IDisplayDevice *device = NULL;
    // use HDMI vsync when connected
    device = getDisplayDevice(IDisplayDevice::DEVICE_EXTERNAL);
    if (device && device->isConnected()) {
        return IDisplayDevice::DEVICE_EXTERNAL;
    }

    return IDisplayDevice::DEVICE_PRIMARY;
}

bool VsyncManager::enableVsync(int candidate)
{
    if (mVsyncSource != IDisplayDevice::DEVICE_COUNT) {
        WTRACE("vsync has been enabled on %d", mVsyncSource);
        return true;
    }

    IDisplayDevice *device = getDisplayDevice(candidate);
    if (!device) {
        ETRACE("invalid vsync source candidate %d", candidate);
        return false;
    }

    if (device->vsyncControl(true)) {
        mVsyncSource = candidate;
        return true;
    }

    if (candidate != IDisplayDevice::DEVICE_PRIMARY) {
        WTRACE("failed to enable vsync on display %d, fall back to primary", candidate);
        device = getDisplayDevice(IDisplayDevice::DEVICE_PRIMARY);
        if (device && device->vsyncControl(true)) {
            mVsyncSource = IDisplayDevice::DEVICE_PRIMARY;
            return true;
        }
    }
    ETRACE("failed to enable vsync on the primary display");
    return false;
}

void VsyncManager::disableVsync()
{
    if (mVsyncSource == IDisplayDevice::DEVICE_COUNT) {
        WTRACE("vsync has been disabled");
        return;
    }

    IDisplayDevice *device = getDisplayDevice(mVsyncSource);
    if (device && !device->vsyncControl(false)) {
        WTRACE("failed to disable vsync on device %d", mVsyncSource);
    }
    mVsyncSource = IDisplayDevice::DEVICE_COUNT;
}

} // namespace amlogic
} // namespace android

