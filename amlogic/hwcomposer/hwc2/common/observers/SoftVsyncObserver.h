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

#ifndef SOFT_VSYNC_OBSERVER_H
#define SOFT_VSYNC_OBSERVER_H

#include <SimpleThread.h>

namespace android {
namespace amlogic {

class IDisplayDevice;

class SoftVsyncObserver {
public:
    SoftVsyncObserver(IDisplayDevice& disp);
    virtual ~SoftVsyncObserver();

public:
    virtual bool initialize();
    virtual void deinitialize();
    virtual void setRefreshPeriod(nsecs_t period);
    virtual bool control(bool enabled);
    virtual nsecs_t getRefreshPeriod() const { return mRefreshPeriod; }

private:
    IDisplayDevice& mDisplayDevice;
    int  mDevice;
    bool mEnabled;
    nsecs_t mRefreshPeriod;
    mutable Mutex mLock;
    Condition mCondition;
    mutable nsecs_t mNextFakeVSync;
    bool mExitThread;
    bool mInitialized;

private:
    DECLARE_THREAD(VsyncEventPollThread, SoftVsyncObserver);
};

} // namespace amlogic
} // namespace android



#endif /* SOFT_VSYNC_OBSERVER_H */

