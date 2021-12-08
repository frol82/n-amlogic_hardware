/*
// Copyright (c) 2016 Amlogic
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
*/

#ifndef HWC_FENCE_H
#define HWC_FENCE_H

#include <stdint.h>
#include <sys/types.h>

#include <utils/String8.h>
#include <utils/Timers.h>
#include <utils/StrongPointer.h>
#include <utils/RefBase.h>


namespace android {
namespace amlogic {


// ===========================================================================
// HwcFenceControl
// ===========================================================================

class HwcFenceControl
    : public LightRefBase<HwcFenceControl>
{
public:
    static const sp<HwcFenceControl> NO_FENCE;

    // TIMEOUT_NEVER may be passed to the wait method to indicate that it
    // should wait indefinitely for the fence to signal.
    enum { TIMEOUT_NEVER = -1 };

    // Construct a new Fence object with an invalid file descriptor.  This
    // should be done when the Fence object will be set up by unflattening
    // serialized data.
    HwcFenceControl();

    // Construct a new Fence object to manage a given fence file descriptor.
    // When the new Fence object is destructed the file descriptor will be
    // closed.
    HwcFenceControl(int32_t fenceFd);

    // Check whether the Fence has an open fence file descriptor. Most Fence
    // methods treat an invalid file descriptor just like a valid fence that
    // is already signalled, so using this is usually not necessary.
    bool isValid() const { return mFenceFd != -1; }

    // wait waits for up to timeout milliseconds for the fence to signal.  If
    // the fence signals then NO_ERROR is returned. If the timeout expires
    // before the fence signals then -ETIME is returned.  A timeout of
    // TIMEOUT_NEVER may be used to indicate that the call should wait
    // indefinitely for the fence to signal.
    static status_t wait(int32_t fence, int32_t timeout);

    // waitForever is a convenience function for waiting forever for a fence to
    // signal (just like wait(TIMEOUT_NEVER)), but issuing an error to the
    // system log and fence state to the kernel log if the wait lasts longer
    // than a warning timeout.
    // The logname argument should be a string identifying
    // the caller and will be included in the log message.
    status_t waitForever(const char* logname);

    // fence.
    static int32_t createFenceTimeline();
    static int32_t createFence(int32_t syncTimelineFd,char* str, uint32_t val);
    static status_t syncTimelineInc(int32_t syncTimelineFd);
    static status_t traceFenceInfo(int32_t fence);

    static inline void closeFd(int32_t fence) {
        if (fence > -1) {
            close(fence);
        }
    }
    static inline void waitAndCloseFd(int32_t fence, int32_t timeout) {
        if (fence > -1) {
            wait(fence, timeout);
            close(fence);
        }
    }

    // merge combines two Fence objects, creating a new Fence object that
    // becomes signaled when both f1 and f2 are signaled (even if f1 or f2 is
    // destroyed before it becomes signaled).  The name argument specifies the
    // human-readable name to associated with the new Fence object.
    static int32_t merge(const String8& name, const int32_t& f1,
            const int32_t& f2);

    static int32_t dupFence(int32_t fence);

private:
    // Only allow instantiation using ref counting.
    friend class LightRefBase<HwcFenceControl>;
    ~HwcFenceControl();

    // Disallow copying
    HwcFenceControl(const HwcFenceControl& rhs);
    HwcFenceControl& operator = (const HwcFenceControl& rhs);
    const HwcFenceControl& operator = (const HwcFenceControl& rhs) const;

    int32_t mFenceFd;
};

}; // namespace amlogic
}; // namespace android


#endif // ANDROID_FENCE_H
