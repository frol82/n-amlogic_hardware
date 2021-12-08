/*
// Copyright (c) 2017 Amlogic
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

#ifndef AML_DISPLAY_HDMI_H
#define AML_DISPLAY_HDMI_H

#include <gralloc_priv.h>
#include <utils/String8.h>
#include <utils/Errors.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <linux/fb.h>
#include <string>
#include <vector>

#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>
#include <Hwcomposer.h>
#include <Utils.h>
#include <ISystemControlService.h>
#include <gui/SurfaceComposerClient.h>
#include <AmVinfo.h>

#define HDMI_FRAC_RATE_POLICY "/sys/class/amhdmitx/amhdmitx0/frac_rate_policy"

namespace android {
namespace amlogic {

// refresh rates.
enum {
    REFRESH_24kHZ = 24,
    REFRESH_30kHZ = 30,
    REFRESH_60kHZ = 60,
    REFRESH_120kHZ = 120,
    REFRESH_240kHZ = 240
};

// display config
class DisplayConfig {
public:
    DisplayConfig(const std::string dm,
        int rr,
        int w = 0,
        int h = 0,
        int dpix = 0,
        int dpiy = 0,
        bool frac = false)
        : mDisplayMode(dm),
          mRefreshRate(rr),
          mWidth(w),
          mHeight(h),
          mDpiX(dpix),
          mDpiY(dpiy),
          mFracRate(frac)
    {}
public:
    std::string getDisplayMode() const { return mDisplayMode; };
    float getRefreshRate() const {
        float actualRate = 0.0f;

        if (mRefreshRate) {
            if (mFracRate) {
                actualRate = (mRefreshRate * 1000) / (float)1001;
            } else {
                actualRate = mRefreshRate;
            }
        }
        return actualRate;
    };
    int getWidth() const { return mWidth; };
    int getHeight() const { return mHeight; };
    int getDpiX() const { return mDpiX; };
    int getDpiY() const { return mDpiY; };
    void setDpi(int dpix, int dpiy) {
        mDpiX = dpix;
        mDpiY = dpiy;
    };
    bool getFracRatePolicy() { return mFracRate; };

private:
    std::string mDisplayMode;
    int mRefreshRate;
    int mWidth;
    int mHeight;
    int mDpiX;
    int mDpiY;
    bool mFracRate;
};

class DisplayHdmi {
public:
    DisplayHdmi();
    ~DisplayHdmi();

    void initialize(framebuffer_info_t& framebufferInfo);
    void deinitialize();
    bool updateHotplug(bool connected, framebuffer_info_t& framebufferInfo);
    status_t setBestDisplayMode();

    status_t getDisplayConfigs(uint32_t* outNumConfigs, hwc2_config_t* outConfigs);
    status_t getDisplayAttribute(hwc2_config_t config, int32_t  attribute, int32_t* outValue);
    status_t getActiveConfig(hwc2_config_t* outConfig);
    status_t getRealActiveConfig(hwc2_config_t* outConfig);
    status_t setActiveConfig(int modeId);
    // int setPowerMode(int power) {return 0;};
    int getDisplayWorkMode() const { return mWorkMode; };

    inline bool isConnected() {return mConnected;};
    bool chkPresent();

    void dump(Dump& d);

protected:
    /* hdmi operations:
      * TODO: need move all these operations to HAL.
     */
    sp<ISystemControlService> getSystemControlService();
    status_t readEdidList(std::vector<std::string> &edidlist);
    status_t writeHdmiDispMode(std::string &dispmode);
    status_t readHdmiDispMode(std::string &dispmode);
    status_t readHdmiPhySize(framebuffer_info_t& fbInfo);
    status_t readBestHdmiOutputMode(std::string &dispmode);

    void switchRatePolicy(bool fracRatePolicy);
    void reset();

    // operations on mSupportDispModes
    status_t clearSupportedConfigs();
    status_t updateSupportedConfigs();
    status_t updateDisplayAttributes(framebuffer_info_t& framebufferInfo);
    status_t addSupportedConfig(std::string& mode);

    // ensure the active mode equals the current displaymode.
    status_t updateActiveConfig(std::string& activeMode);

    status_t setDisplayMode(std::string& dispmode, bool policy = false);
    bool isDispModeValid(std::string& dispmode);

    bool readConfigFile(const char* configPath, std::vector<std::string>* supportDispModes);

    status_t calcDefaultMode(framebuffer_info_t& framebufferInfo, std::string& defaultMode);
    status_t buildSingleConfigList(std::string& defaultMode);

    bool checkVinfo(framebuffer_info_t *fbInfo);

private:
    bool mConnected;
    sp<ISystemControlService> mSC;

    // configures variables.
    hwc2_config_t mActiveConfigId; // for amlogic, it is vmode_e.
    std::string mActiveConfigStr;
    hwc2_config_t mRealActiveConfigId;
    std::string mRealActiveConfigStr;
    KeyedVector<int, DisplayConfig*> mSupportDispConfigs;

    // physical size in mm.
    int mPhyWidth;
    int mPhyHeight;
    // framebuffer size.
    int mFbWidth;
    int mFbHeight;

    // work modes
    enum {
        REAL_ACTIVEMODE = 0,
        LOGIC_ACTIVEMODE, // return the logic size which is framebuffer size.
        NONE_ACTIVEMODE // no active mode list, always return a default config.
    };
    int mWorkMode;
    // first boot up flag.
    bool mFirstBootup;
};
} // namespace amlogic
} // namespace android

#endif
