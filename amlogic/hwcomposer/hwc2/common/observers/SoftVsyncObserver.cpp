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
#include <SoftVsyncObserver.h>
#include <IDisplayDevice.h>

extern "C" int clock_nanosleep(clockid_t clock_id, int flags,
                           const struct timespec *request,
                           struct timespec *remain);


namespace android {
namespace amlogic {

SoftVsyncObserver::SoftVsyncObserver(IDisplayDevice& disp)
    : mDisplayDevice(disp),
      mEnabled(false),
      mRefreshPeriod(0),
      mLock(),
      mCondition(),
      mNextFakeVSync(0),
      mExitThread(false),
      mInitialized(false)
{
}

SoftVsyncObserver::~SoftVsyncObserver()
{
    WARN_IF_NOT_DEINIT();
}

bool SoftVsyncObserver::initialize()
{
    if (mInitialized) {
        WTRACE("object has been initialized");
        return true;
    }

    mExitThread = false;
    mEnabled = false;
    mRefreshPeriod = nsecs_t(1e9 / 60);
    mThread = new VsyncEventPollThread(this);
    if (!mThread.get()) {
        DEINIT_AND_RETURN_FALSE("failed to create vsync event poll thread.");
    }
    mThread->run("SoftVsyncObserver", PRIORITY_URGENT_DISPLAY);
    mInitialized = true;
    return true;
}

void SoftVsyncObserver::deinitialize()
{
    if (mEnabled) {
        WTRACE("soft vsync is still enabled");
        control(false);
    }

    mExitThread = true;
    mCondition.signal();

    if (mThread.get()) {
        mThread->requestExitAndWait();
        mThread = NULL;
    }
    mInitialized = false;
}

void SoftVsyncObserver::setRefreshPeriod(nsecs_t period)
{
    Mutex::Autolock _l(mLock);

    if (period <= 0) {
        WTRACE("invalid refresh period %lld", period);
    } else if (mRefreshPeriod != period) {
        mRefreshPeriod = period;
        if (mEnabled) {
            mNextFakeVSync = systemTime(CLOCK_MONOTONIC) + mRefreshPeriod;
        }
    }
}

bool SoftVsyncObserver::control(bool enabled)
{
    Mutex::Autolock _l(mLock);

    if (enabled == mEnabled) {
        WTRACE("vsync state %d is not changed", enabled);
        return true;
    }

    if (enabled) {
        mNextFakeVSync = systemTime(CLOCK_MONOTONIC) + mRefreshPeriod;
    }
    mEnabled = enabled;
    mCondition.signal();
    return true;
}

bool SoftVsyncObserver::threadLoop()
{
    { // scope for lock
        Mutex::Autolock _l(mLock);
        while (!mEnabled) {
            mCondition.wait(mLock);
            if (mExitThread) {
                ITRACE("exiting thread loop");
                return false;
            }
        }
    }

    const nsecs_t period = mRefreshPeriod;
    const nsecs_t now = systemTime(CLOCK_MONOTONIC);
    nsecs_t next_vsync = mNextFakeVSync;
    nsecs_t sleep = next_vsync - now;
    //DTRACE("Softvync (%lld), refresh (%lld)", period, nsecs_t(1e9/period));
    if (sleep < 0) {
        // we missed, find where the next vsync should be
        sleep = (period - ((now - next_vsync) % period));
        next_vsync = now + sleep;
    }
    mNextFakeVSync = next_vsync + period;

    struct timespec spec;
    spec.tv_sec  = next_vsync / 1000000000;
    spec.tv_nsec = next_vsync % 1000000000;

    int err;
    do {
        err = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &spec, NULL);
    } while (err < 0 && errno == EINTR);


    if (err == 0) {
        mDisplayDevice.onVsync(next_vsync);
    }

    return true;
}

} // namespace amlogic
} // namesapce android

