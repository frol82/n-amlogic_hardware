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

//#define LOG_NDEBUG 0
#include <HwcTrace.h>
#include <binder/IServiceManager.h>
#include <utils/Tokenizer.h>
#include "DisplayHdmi.h"

namespace android {
namespace amlogic {


#define DEFAULT_DISPMODE "1080p60hz"
#define DEFAULT_DISPLAY_DPI 160

DisplayHdmi::DisplayHdmi()
    : mSC(NULL),
    mFirstBootup(true)
{
#if 0 //debug only.
    //mAllModes.push_back("480p60hz");
    //mAllModes.push_back("576p50hz");
    //mAllModes.push_back("720p50hz");
    //mAllModes.push_back("720p60hz");
    mAllModes.push_back("1080p60hz");
    mAllModes.push_back("1080p50hz");
    mAllModes.push_back("1080p30hz");
    mAllModes.push_back("1080p25hz");
    mAllModes.push_back("1080p24hz");
    mAllModes.push_back("2160p24hz");
    mAllModes.push_back("2160p25hz");
    mAllModes.push_back("2160p30hz");
    mAllModes.push_back("2160p50hz");
    mAllModes.push_back("2160p60hz");
#endif

    if (Utils::get_bool_prop("ro.sf.full_activemode")) {
        mWorkMode = REAL_ACTIVEMODE;
    } else {
        mWorkMode = NONE_ACTIVEMODE;
    }
}

DisplayHdmi::~DisplayHdmi() {
}

void DisplayHdmi::initialize(framebuffer_info_t& framebufferInfo) {
    reset();
    std::string dispMode;
    calcDefaultMode(framebufferInfo, dispMode);
    buildSingleConfigList(dispMode);
    updateActiveConfig(dispMode);

    mFbWidth = framebufferInfo.info.xres;
    mFbHeight = framebufferInfo.info.yres;
    if (mSC == NULL) mSC = getSystemControlService();
}

void DisplayHdmi::deinitialize() {
    reset();
}

void DisplayHdmi::reset() {
    clearSupportedConfigs();
    mActiveConfigStr.clear();
    mConnected = false;
    mActiveConfigId = mRealActiveConfigId = VMODE_NULL;
    mPhyWidth = mPhyHeight = 0;
    mSC = NULL;
}

bool DisplayHdmi::updateHotplug(bool connected,
        framebuffer_info_t& framebufferInfo) {
    bool ret = true;
    int32_t rate;
    mConnected = connected;

    if (!connected) {
        DTRACE("hdmi disconnected, keep old display configs.");
        return true;
    }

    updateDisplayAttributes(framebufferInfo);

    std::string activemode;
    if (readHdmiDispMode(activemode) != HWC2_ERROR_NONE) {
        ETRACE("get active display mode failed.");
        return false;
    }

    if (updateSupportedConfigs() != HWC2_ERROR_NONE) {
        ETRACE("updateHotplug: No supported display list, set default configs.");
        std::string dM (DEFAULT_DISPMODE);
        buildSingleConfigList(dM);
    }
    updateActiveConfig(activemode);
    // setBestDisplayMode();

    return true;
}

int DisplayHdmi::updateSupportedConfigs() {
    // clear display modes
    clearSupportedConfigs();

    std::vector<std::string> supportDispModes;
    std::string::size_type pos;
    std::string dM (DEFAULT_DISPMODE);

    bool isConfiged = readConfigFile("/system/etc/displayModeList.cfg", &supportDispModes);
    if (isConfiged) {
        DTRACE("Read supported modes from cfg file.");
    } else {
        if (mWorkMode == NONE_ACTIVEMODE) {
            DTRACE("Simple Active Mode!!!");
            return BAD_VALUE;
        }

        readEdidList(supportDispModes);
        if (supportDispModes.size() == 0) {
            ETRACE("SupportDispModeList null!!!");
            return BAD_VALUE;
        }
    }

    for (size_t i = 0; i < supportDispModes.size(); i++) {
        if (!supportDispModes[i].empty()) {
            pos = supportDispModes[i].find('*');
            if (pos != std::string::npos) {
                supportDispModes[i].erase(pos, 1);
                DTRACE("modify support display mode:%s", supportDispModes[i].c_str());
            }

            // skip default / fake active mode as we add it to the end
            if (supportDispModes[i] != dM)
                addSupportedConfig(supportDispModes[i]);
        }
    }

    addSupportedConfig(dM);
    return NO_ERROR;
}

int DisplayHdmi::buildSingleConfigList(std::string& defaultMode) {
    if (!isDispModeValid(defaultMode)) {
        ETRACE("buildSingleConfigList with invalidate mode (%s)", defaultMode.c_str());
        return false;
    }

    return addSupportedConfig(defaultMode);
}

int DisplayHdmi::calcDefaultMode(framebuffer_info_t& framebufferInfo,
        std::string& defaultMode) {
    const struct vinfo_s * mode =
        findMatchedMode(framebufferInfo.info.xres, framebufferInfo.info.yres, 60);
    if (mode == NULL) {
        defaultMode = DEFAULT_DISPMODE;
    } else {
        defaultMode = mode->name;
    }

    defaultMode = DEFAULT_DISPMODE;

    DTRACE("calcDefaultMode %s", defaultMode.c_str());
    return NO_ERROR;
}

int DisplayHdmi::addSupportedConfig(std::string& mode) {
    vmode_e vmode = vmode_name_to_mode(mode.c_str());
    const struct vinfo_s* vinfo = get_tv_info(vmode);
    if (vmode == VMODE_MAX || vinfo == NULL) {
        ETRACE("addSupportedConfig meet error mode (%s, %d)", mode.c_str(), vmode);
        return BAD_VALUE;
    }

    int dpiX  = DEFAULT_DISPLAY_DPI, dpiY = DEFAULT_DISPLAY_DPI;
    if (mPhyWidth > 0 && mPhyHeight > 0) {
        dpiX = (vinfo->width  * 25.4f) / mPhyWidth;
        dpiY = (vinfo->height  * 25.4f) / mPhyHeight;
    }

    DisplayConfig *config = new DisplayConfig(mode,
                                            vinfo->sync_duration_num,
                                            vinfo->width,
                                            vinfo->height,
                                            dpiX,
                                            dpiY,
                                            false);

    // add normal refresh rate config, like 24hz, 30hz...
    DTRACE("add display mode pair (%d, %s)", mSupportDispConfigs.size(), mode.c_str());
    mSupportDispConfigs.add(mSupportDispConfigs.size(), config);

    // add frac refresh rate config, like 23.976hz, 29.97hz...
    if (vinfo->sync_duration_num == REFRESH_24kHZ
        || vinfo->sync_duration_num == REFRESH_30kHZ
        || vinfo->sync_duration_num == REFRESH_60kHZ
        || vinfo->sync_duration_num == REFRESH_120kHZ
        || vinfo->sync_duration_num == REFRESH_240kHZ) {
        DisplayConfig *fracConfig = new DisplayConfig(mode,
                                        vinfo->sync_duration_num,
                                        vinfo->width,
                                        vinfo->height,
                                        dpiX,
                                        dpiY,
                                        true);
        mSupportDispConfigs.add(mSupportDispConfigs.size(), fracConfig);
    }

    return NO_ERROR;
}

int DisplayHdmi::updateActiveConfig(std::string& activeMode) {
    mRealActiveConfigStr = activeMode;
    for (size_t i = 0; i < mSupportDispConfigs.size(); i++) {
        DisplayConfig * cfg = mSupportDispConfigs.valueAt(i);
        if (activeMode == cfg->getDisplayMode()) {
            mRealActiveConfigId = mSupportDispConfigs.keyAt(i);
            DTRACE("updateRealActiveConfig to (%s, %d)", activeMode.c_str(), mRealActiveConfigId);
        }
    }
    mActiveConfigId = mSupportDispConfigs.size()-1;
    return NO_ERROR;
}

status_t DisplayHdmi::setBestDisplayMode() {
    std::string bM;

    readBestHdmiOutputMode(bM);
    if (mRealActiveConfigStr.compare(bM) || mFirstBootup) {
        DTRACE("setBestDisplayMode to %s", bM.c_str());
        setDisplayMode(bM);
    }
    // update real active config.
    updateActiveConfig(bM);

    if (mFirstBootup) mFirstBootup = false;
    return NO_ERROR;
}

void DisplayHdmi::switchRatePolicy(bool fracRatePolicy) {
    if (fracRatePolicy) {
        if (mSC.get() && mSC->writeSysfs(String16(HDMI_FRAC_RATE_POLICY), String16("1")))
            ETRACE("Switch to frac rate policy SUCCESS.");
        else
            ETRACE("Switch to frac rate policy FAIL.");
    } else {
        if (mSC.get() && mSC->writeSysfs(String16(HDMI_FRAC_RATE_POLICY), String16("0")))
            ETRACE("Switch to normal rate policy SUCCESS.");
        else
            ETRACE("Switch to normal rate policy FAIL.");
    }
}

int DisplayHdmi::setDisplayMode(std::string& dm, bool policy) {
    DTRACE("setDisplayMode to %s", dm.c_str());
    switchRatePolicy(policy);
    writeHdmiDispMode(dm);
    updateActiveConfig(dm);
    return NO_ERROR;
}

status_t DisplayHdmi::readHdmiPhySize(framebuffer_info_t& fbInfo) {
    struct fb_var_screeninfo vinfo;
    if ((fbInfo.fd >= 0) && (ioctl(fbInfo.fd, FBIOGET_VSCREENINFO, &vinfo) == 0)) {
        if (int32_t(vinfo.width) > 16 && int32_t(vinfo.height) > 9) {
            mPhyWidth = vinfo.width;
            mPhyHeight = vinfo.height;
        }
        return NO_ERROR;
    }
    return BAD_VALUE;
}

int DisplayHdmi::updateDisplayAttributes(framebuffer_info_t& framebufferInfo) {
    if (readHdmiPhySize(framebufferInfo) != NO_ERROR) {
        mPhyWidth = mPhyHeight = 0;
    }
    DTRACE("updateDisplayAttributes physical size (%d x %d)", mPhyWidth, mPhyHeight);
    return NO_ERROR;
}

int DisplayHdmi::getDisplayConfigs(uint32_t* outNumConfigs,
        hwc2_config_t* outConfigs) {
    size_t i;

    if (!isConnected()) {
        ETRACE("hdmi is not connected.");
    }

    size_t configsNum = mSupportDispConfigs.size();
    *outNumConfigs = configsNum;
    if (NULL != outConfigs) {
        for (i = 0; i < configsNum; i++) {
            outConfigs[i] = mSupportDispConfigs.keyAt(i);
        }
    }

    return NO_ERROR;
}

int DisplayHdmi::getDisplayAttribute(hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute,
        int32_t* outValue) {
    if (!isConnected()) {
        ETRACE("hdmi is not connected.");
    }

    DisplayConfig *configChosen = NULL;
    int modeIdx = mSupportDispConfigs.indexOfKey((vmode_e)config);
    if (modeIdx >= 0)
        configChosen = mSupportDispConfigs.valueAt(modeIdx);
    if (!configChosen) {
        ETRACE("failed to get display config: %d", config);
        return BAD_VALUE;
    }

    switch (attribute) {
        case HWC2_ATTRIBUTE_VSYNC_PERIOD:
            if (mWorkMode == REAL_ACTIVEMODE) {
                if (configChosen->getRefreshRate()) {
                    *outValue = 1e9 / configChosen->getRefreshRate();
                }
            } else if (mWorkMode == LOGIC_ACTIVEMODE ||
                            mWorkMode == NONE_ACTIVEMODE) {
                *outValue = 1e9 / 60;
            }
        break;
        case HWC2_ATTRIBUTE_WIDTH:
            if (mWorkMode == REAL_ACTIVEMODE) {
                *outValue = configChosen->getWidth();
            } else if (mWorkMode == LOGIC_ACTIVEMODE ||
                            mWorkMode == NONE_ACTIVEMODE) {
                *outValue = mFbWidth;
            }
        break;
        case HWC2_ATTRIBUTE_HEIGHT:
            if (mWorkMode == REAL_ACTIVEMODE) {
                *outValue = configChosen->getHeight();
            } else if (mWorkMode == LOGIC_ACTIVEMODE ||
                            mWorkMode == NONE_ACTIVEMODE) {
                *outValue = mFbHeight;
            }
        break;
        case HWC2_ATTRIBUTE_DPI_X:
            *outValue = configChosen->getDpiX() * 1000.0f;
        break;
        case HWC2_ATTRIBUTE_DPI_Y:
            *outValue =  configChosen->getDpiY() * 1000.0f;
        break;
        default:
            ETRACE("unknown display attribute %u", attribute);
            *outValue = -1;
        break;
    }

    return NO_ERROR;
}

int DisplayHdmi::getActiveConfig(hwc2_config_t* outConfig) {
    if (!isConnected()) {
        ETRACE("hdmi is not connected.");
    }
    // DTRACE("getActiveConfig to config(%d).", mActiveConfigId);
    *outConfig = mActiveConfigId;
    return NO_ERROR;
}

int DisplayHdmi::getRealActiveConfig(hwc2_config_t* outConfig) {
    if (!isConnected()) {
        ETRACE("hdmi is not connected.");
    }
    // DTRACE("getActiveConfig to config(%d).", mActiveConfigId);
    *outConfig = mRealActiveConfigId;
    return NO_ERROR;
}

int DisplayHdmi::setActiveConfig(int modeId) {
    if (!isConnected()) {
        ETRACE("hdmi display is not connected.");
    }

    DTRACE("setActiveConfig to mode(%d).", modeId);
    int modeIdx = mSupportDispConfigs.indexOfKey((const vmode_e)modeId);
    if (modeIdx >= 0) {
        DisplayConfig* cfg = mSupportDispConfigs.valueAt(modeIdx);
        std::string dM = cfg->getDisplayMode();

        DTRACE("setActiveConfig to (%d, %s).", modeId, dM.c_str());
        setDisplayMode(dM, cfg->getFracRatePolicy());

        // update real active config.
        updateActiveConfig(dM);
        return NO_ERROR;
    } else {
        ETRACE("set invalild active config (%d)", modeId);
        return BAD_VALUE;
    }
}

bool DisplayHdmi::readConfigFile(const char* configPath, std::vector<std::string>* supportDispModes) {
    const char* WHITESPACE = " \t\r";

    Tokenizer* tokenizer;
    status_t status = Tokenizer::open(String8(configPath), &tokenizer);

    if (status) {
        DTRACE("Error %d opening display config file %s.", status, configPath);
        return false;
    } else {
        while (!tokenizer->isEof()) {
            tokenizer->skipDelimiters(WHITESPACE);
            if (!tokenizer->isEol() && tokenizer->peekChar() != '#') {
                String8 token = tokenizer->nextToken(WHITESPACE);
                const char* dispMode = token.string();
                if (strstr(dispMode, "hz")) {
                    ETRACE("dispMode %s.", dispMode);
                    (*supportDispModes).push_back(std::string(dispMode));
                }
            }

            tokenizer->nextLine();
        }
        delete tokenizer;
    }

    size_t num = (*supportDispModes).size();

    if (num <= 0) {
        return false;
    } else {
        return true;
    }
}

int DisplayHdmi::clearSupportedConfigs() {
    // reset display configs
    for (size_t i = 0; i < mSupportDispConfigs.size(); i++) {
        DisplayConfig *config = mSupportDispConfigs.valueAt(i);
        if (config)
            delete config;
    }
    mSupportDispConfigs.clear();
    return NO_ERROR;
}

bool DisplayHdmi::chkPresent() {
    bool bConnect = false;
    std::string dispMode;
    if (!readHdmiDispMode(dispMode)) {
        bConnect = isDispModeValid(dispMode);
    }

    DTRACE("chkPresent %s", bConnect ? "connected" : "disconnected");
    return bConnect;
}

bool DisplayHdmi::isDispModeValid(std::string & dispmode){
    if (dispmode.empty())
        return false;

    vmode_e mode = vmode_name_to_mode(dispmode.c_str());
    // DTRACE("isDispModeValid get mode (%d)", mode);
    if (mode == VMODE_MAX)
        return false;

    if (want_hdmi_mode(mode) == 0)
        return false;

    return true;
}

sp<ISystemControlService> DisplayHdmi::getSystemControlService() {
    sp<ISystemControlService> systemControlService;
    sp<IServiceManager> sm = defaultServiceManager();
    if (sm == NULL) {
        ETRACE("Couldn't get default ServiceManager\n");
        return systemControlService;
    }

    systemControlService = interface_cast<ISystemControlService>(sm->getService(String16("system_control")));
    if (systemControlService == NULL) {
        ETRACE("Couldn't get connection to SystemControlService\n");
    }

    return systemControlService;
}

int DisplayHdmi::readHdmiDispMode(std::string &dispmode) {
    if (mSC.get() && mSC->getActiveDispMode(&dispmode)) {
        DTRACE("get current displaymode %s", dispmode.c_str());
        if (!isDispModeValid(dispmode)) {
            DTRACE("active mode %s not valid", dispmode.c_str());
            return BAD_VALUE;
        }
        return NO_ERROR;
    } else {
        ETRACE("syscontrol::getActiveDispMode FAIL.");
        return FAILED_TRANSACTION;
    }
}

int DisplayHdmi::writeHdmiDispMode(std::string &dispmode) {
    if (mSC.get() && mSC->setActiveDispMode(dispmode)) {
        return NO_ERROR;
    } else {
        ETRACE("syscontrol::setActiveDispMode FAIL.");
        return FAILED_TRANSACTION;
    }
}

int DisplayHdmi::readEdidList(std::vector<std::string>& edidlist) {
    if (mSC.get() && mSC->getSupportDispModeList(&edidlist)) {
        return NO_ERROR;
    } else {
        ETRACE("syscontrol::readEdidList FAIL.");
        return FAILED_TRANSACTION;
    }
}

int DisplayHdmi::readBestHdmiOutputMode(std::string &dispmode) {
    /* if (mSC.get() && mSC->getBestHdmiOutputMode(&dispmode)) {
        DTRACE("get best displaymode %s", dispmode.c_str());
        if (!isDispModeValid(dispmode)) {
            ETRACE("best mode %s not valid", dispmode.c_str());
            return BAD_VALUE;
        }
        return NO_ERROR;
    } else {
        ETRACE("syscontrol::getBestHdmiOutputMode FAIL.");
        return FAILED_TRANSACTION;
    } */

    return NO_ERROR;
}

void DisplayHdmi::dump(Dump& d) {
        d.append("Connector (HDMI, %s, %d, %d)\n",
                 mRealActiveConfigStr.c_str(),
                 mRealActiveConfigId,
                 mWorkMode);
        d.append("   CONFIG   |   VSYNC_PERIOD   |   WIDTH   |   HEIGHT   |"
            "   DPI_X   |   DPI_Y   \n");
        d.append("------------+------------------+-----------+------------+"
            "-----------+-----------\n");
        for (size_t i = 0; i < mSupportDispConfigs.size(); i++) {
            int mode = mSupportDispConfigs.keyAt(i);
            DisplayConfig *config = mSupportDispConfigs.valueAt(i);
            if (config) {
                d.append("%s %2d     |      %.3f      |   %5d   |   %5d    |"
                    "    %3d    |    %3d    \n",
                         (mode == (int)mActiveConfigId) ? "*   " : "    ",
                         mode,
                         config->getRefreshRate(),
                         config->getWidth(),
                         config->getHeight(),
                         config->getDpiX(),
                         config->getDpiY());
            }
        }
    }

} // namespace amlogic
} // namespace android



