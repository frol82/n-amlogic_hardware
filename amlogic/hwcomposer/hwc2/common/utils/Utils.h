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

#ifndef UTILS_H_
#define UTILS_H_

#include <gralloc_priv.h>
#if WITH_LIBPLAYER_MODULE
#include <Amavutils.h>
#endif
#include <hardware/hwcomposer_defs.h>

#define DISPLAY_HPD_STATE               "/sys/class/amhdmitx/amhdmitx0/hpd_state"
#define DISPLAY_HDMI_EDID               "/sys/class/amhdmitx/amhdmitx0/disp_cap"
#define SYSFS_AMVIDEO_CURIDX            "/sys/module/amvideo/parameters/cur_dev_idx"
#define SYSFS_DISPLAY_MODE                "/sys/class/display/mode"
#define SYSFS_DISPLAY1_MODE              "/sys/class/display/mode"
#define SYSFS_DISPLAY2_MODE              "/sys/class/display2/mode"
#define SYSFS_FB0_FREE_SCALE              "/sys/class/graphics/fb0/free_scale"
#define SYSFS_FB1_FREE_SCALE              "/sys/class/graphics/fb1/free_scale"
#define SYSFS_VIDEO_AXIS                      "/sys/class/video/axis"
#define SYSFS_VIDEOBUFUSED                 "/sys/class/amstream/videobufused"
#define SYSFS_WINDOW_AXIS               "/sys/class/graphics/fb0/window_axis"

namespace android {
namespace amlogic {

class Utils {
public:
    Utils();
    ~Utils();

    static int get_int_prop(const char* prop);
    static bool get_bool_prop(const char* prop);

    static int getSysfsInt(const char* syspath, int def);
    static int getSysfsStr(const char* syspath, char *valstr, int size,
        bool needOriginalData = false);
    static int setSysfsStr(const char *path, const char *val);

    static bool checkBoolProp(const char* prop);
    static int32_t checkIntProp(const char* prop);
    static int32_t checkAndDupFd(int32_t fd);
    static inline void closeFd(int32_t fd) {
        if (fd > -1) close(fd);
    }
#if WITH_LIBPLAYER_MODULE
    static bool checkSysfsStatus(const char* sysfstr, char* lastr, int32_t size);
#endif

    static const char* getHotplugUeventEnvelope();
    static const char* getHdcpUeventEnvelope();
    static const char* getSwitchState0();
    static const char* getSwitchState1();

    template <typename T, typename S>
    static inline bool compareRect(T a, S b) {
        if ((int32_t)a.left == (int32_t)b.left
                && (int32_t)a.top == (int32_t)b.top
                && (int32_t)a.right == (int32_t)b.right
                && (int32_t)a.bottom == (int32_t)b.bottom) {
            return true;
        }
        return false;
    }
    template <typename T, typename S>
    static inline bool compareSize(T a, S b) {
        if ((int32_t)(a.right-a.left) == (int32_t)(b.right-b.left)
                && (int32_t)(a.bottom-a.top) == (int32_t)(b.bottom-b.top)) {
            return true;
        }
        return false;
    }
    template<typename T>
    inline static T abs(const T& value) {
        return value < 0 ? - value : value;
    }
    template <typename T>
    static inline T min(T a, T b) {
        return a<b ? a : b;
    }
    template <typename T>
    static inline T max(T a, T b) {
        return a>b ? a : b;
    }
    template <typename T>
    static inline void swap(T& a, T& b) {
        T t = a;
        a = b;
        b = t;
    }

    /*
    * hwc_rect_t operation
    */
    enum OVERLAP_TYPE{
        OVERLAP_EMPTY = 0,
        OVERLAP_PART,
        OVERLAP_FULL
    };

    static bool rectEmpty(hwc_rect_t& rect);
    static bool rectIntersect(hwc_rect_t& source, hwc_rect_t& dest, hwc_rect_t& result);
    static OVERLAP_TYPE rectOverlap(hwc_rect_t& source, hwc_rect_t& dest);
};

} // namespace amlogic
} // namespace android
#endif /* UTILS_H_ */
