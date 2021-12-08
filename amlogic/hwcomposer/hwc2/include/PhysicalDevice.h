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

#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include <utils/KeyedVector.h>
#include <SoftVsyncObserver.h>
#include <IDisplayDevice.h>
#include <HwcLayer.h>
#include <IComposer.h>
#include <DisplayHdmi.h>
#include <systemcontrol/ISystemControlService.h>
#include <systemcontrol/DisplayMode.h>
#include <binder/Binder.h>
#include <binder/IServiceManager.h>
#include <utils/RefBase.h>

namespace android {
namespace amlogic {

// class IHdcpControl;

typedef struct hdr_capabilities {
    bool init;
    bool dvSupport;
    bool hdrSupport;
    int maxLuminance;
    int avgLuminance;
    int minLuminance;
} hdr_capabilities_t;

class DeviceControlFactory {
public:
    virtual ~DeviceControlFactory(){}
public:
    // virtual IHdcpControl* createHdcpControl() = 0;
    virtual IComposer* createComposer(IDisplayDevice& disp) = 0;
};

class FBContext {
public:
    FBContext()
    : mStatus(false)
    {
        mFBInfo = new framebuffer_info_t();
    }
    virtual ~FBContext(){}

    virtual framebuffer_info_t* getInfo() { return mFBInfo; }
    virtual bool getStatus() { return mStatus; }
    virtual void setStatus(bool status) { mStatus = status; }
private:
    framebuffer_info_t *mFBInfo;
    bool mStatus;
};

class Hwcomposer;
class SoftVsyncObserver;

class PhysicalDevice : public IDisplayDevice {
public:
    PhysicalDevice(hwc2_display_t id, Hwcomposer& hwc, DeviceControlFactory* controlFactory);
    ~PhysicalDevice();

    friend class Hwcomposer;
    friend class HwcLayer;

    // Required by HWC2
    virtual int32_t acceptDisplayChanges();
    virtual bool createLayer(hwc2_layer_t* outLayer);
    virtual bool destroyLayer(hwc2_layer_t layer);
    virtual int32_t getActiveConfig(hwc2_config_t* outConfig);
    virtual int32_t getChangedCompositionTypes(uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* /*hwc2_composition_t*/ outTypes);
    virtual int32_t getClientTargetSupport(uint32_t width,
        uint32_t height, int32_t /*android_pixel_format_t*/ format,
        int32_t /*android_dataspace_t*/ dataspace);
    virtual int32_t getColorModes(uint32_t* outNumModes,
        int32_t* /*android_color_mode_t*/ outModes);
    virtual int32_t getDisplayAttribute(hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute, int32_t* outValue);
    virtual int32_t getDisplayConfigs(uint32_t* outNumConfigs, hwc2_config_t* outConfigs);
    virtual int32_t getDisplayName(uint32_t* outSize,char* outName);
    virtual int32_t getDisplayRequests(int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* /*hwc2_layer_request_t*/ outLayerRequests);
    virtual int32_t getDisplayType(int32_t* /*hwc2_display_type_t*/ outType);
    virtual int32_t getDozeSupport(int32_t* outSupport);
    virtual int32_t getHdrCapabilities(uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes, float* outMaxLuminance,
        float* outMaxAverageLuminance, float* outMinLuminance);
    virtual int32_t getReleaseFences(uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outFences);
    virtual int32_t presentDisplay(int32_t* outRetireFence);
    virtual int32_t setActiveConfig(hwc2_config_t config);
    virtual int32_t setClientTarget(buffer_handle_t target,
        int32_t acquireFence, int32_t /*android_dataspace_t*/ dataspace, hwc_region_t damage);
    virtual int32_t setColorMode(int32_t /*android_color_mode_t*/ mode);
    virtual int32_t setColorTransform(const float* matrix, int32_t /*android_color_transform_t*/ hint);

    //virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence); // virtual display only

    virtual int32_t setPowerMode(int32_t /*hwc2_power_mode_t*/ mode);
    virtual bool vsyncControl(bool enabled); // virtual hwc2_error_t setVsyncEnabled(hwc2_display_t display, int32_t /*hwc2_vsync_t*/ enabled);
    virtual int32_t validateDisplay(uint32_t* outNumTypes, uint32_t* outNumRequests);
    virtual int32_t setCursorPosition(hwc2_layer_t layerId, int32_t x, int32_t y);

    virtual int32_t createVirtualDisplay(uint32_t width, uint32_t height, int32_t* format, hwc2_display_t* outDisplay) = 0;
    virtual int32_t destroyVirtualDisplay(hwc2_display_t display) = 0;
    virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) = 0;

    // Other Display methods
    virtual Hwcomposer& getDevice() const { return mHwc; }
    virtual hwc2_display_t getId() const { return mId; }
    virtual bool isConnected() const { return mConnectorPresent; }
    virtual void updateHotplugState(bool connected);

    // device related operations
    virtual bool initCheck() const { return mInitialized; }
    virtual bool initialize();
    virtual void deinitialize();
    virtual const char* getName() const { return mName; };
    virtual int getDisplayId() const { return mId; };
    virtual HwcLayer* getLayerById(hwc2_layer_t layerId);

    // display config operations
    virtual bool updateDisplayConfigs();
    virtual void updateActiveDisplayAttribute();

    // events
    virtual void onVsync(int64_t timestamp);
    virtual void onHotplug(int disp, bool connected);
    virtual void dump(Dump& d);
    DisplayHdmi* getDisplayHdmi()  const { return mDisplayHdmi; };

private:
    // For use by Device
    int32_t initDisplay();
    int32_t postFramebuffer(int32_t* outRetireFence,  bool hasVideoOverlay);
    int32_t getLineValue(const char *lineStr, const char *magicStr);

    int32_t clearLayersStats();
    int32_t preValidate();
    int32_t parseHdrCapabilities();
    void directCompose(framebuffer_info_t * fbInfo);
    void ge2dCompose(framebuffer_info_t * fbInfo, bool hasVideoOverlay);
    int32_t setOSD0Blank(bool blank);
    bool layersStateCheck(int32_t renderMode, KeyedVector<hwc2_layer_t, HwcLayer*> & composeLayers);
    int32_t composersFilter(KeyedVector<hwc2_layer_t, HwcLayer*>& composeLayers);

    int32_t beginCompose();
    int32_t finishCompose();

    //swap the mHwcCurReleaseFence and mHwcPriorReleaseFence;
    void swapReleaseFence();
    //this function will take contorl of fencefd, if you need use it also, please dup it before call.
    void addReleaseFence(hwc2_layer_t layerId, int32_t fenceFd);
    void clearFenceList(KeyedVector<hwc2_layer_t, int32_t> * fenceList);
    void dumpFenceList(KeyedVector<hwc2_layer_t, int32_t> * fenceList);
    void dumpLayers(Vector < hwc2_layer_t > layerIds);
    void dumpLayers(KeyedVector<hwc2_layer_t, HwcLayer*> layers);
    void clearFramebuffer();

    sp<ISystemControlService> getSystemControlService();
    static void hdcpEventListener(void *data, bool status);
    void setSecureStatus(bool status);

    // for vpp post scale.
    bool calReverseScale();

    template <typename T, typename S>
    static inline bool compareSize(T a, S b) {
        if ((int32_t)(a.right - a.left) == (int32_t)(b.right - b.left)
                && (int32_t)(a.bottom - a.top) == (int32_t)(b.bottom - b.top)) {
            return true;
        }
        return false;
    }

    // Member variables
    hwc2_display_t mId;
    const char *mName;
    bool mSecure;
    Hwcomposer& mHwc;
    DisplayHdmi* mDisplayHdmi;
    DeviceControlFactory *mControlFactory;
    SoftVsyncObserver *mVsyncObserver;

    IComposer *mComposer;

    // DeviceControlFactory *mControlFactory;

    // framebuffer_info_t *mFramebufferInfo;
    private_handle_t  *mFramebufferHnd;
    FBContext *mCursorContext;
    FBContext *mFramebufferContext;
    int32_t mFbSlot;

    sp<ISystemControlService> mSystemControl;

    int32_t /*android_color_mode_t*/ mColorMode;

    int32_t /*hwc2_power_mode_t*/ mPowerMode;

    // client target layer.
    buffer_handle_t mClientTargetHnd;
    hwc_region_t mClientTargetDamageRegion;
    int32_t mTargetAcquireFence;
    int32_t mGE2DComposeFrameCount;
    int32_t mDirectComposeFrameCount;
    int32_t mPriorFrameRetireFence;
    int32_t mRenderMode;
    int32_t mPreviousRenderMode;
    bool mIsValidated;
    bool mIsContinuousBuf;

    // num of composition type changed layer.
    uint32_t mNumLayersChangetype;
    uint32_t mNumLayerChangerequest;

    // layer
    hwc2_layer_t mDirectRenderLayerId;
    hwc2_layer_t mVideoOverlayLayerId;
    int32_t mGE2DClearVideoRegionCount;
    Vector< hwc2_layer_t > mGE2DRenderSortedLayerIds;
    KeyedVector<hwc2_layer_t, HwcLayer*> mHwcLayersChangeType;
    KeyedVector<hwc2_layer_t, HwcLayer*> mHwcLayersChangeRequest;
    KeyedVector<hwc2_layer_t, HwcLayer*> mHwcGlesLayers;
    KeyedVector<hwc2_layer_t, HwcLayer*> mHwcLayers;
    KeyedVector<hwc2_layer_t, HwcLayer*> mHwcSecureLayers;

    // HDR Capabilities
    hdr_capabilities_t mHdrCapabilities;

    // fb sync requests.
    hwc_fb_sync_request_t mFbSyncRequest;

    // record the release fence of layer.
    KeyedVector<hwc2_layer_t, int32_t> mLayerReleaseFences[2];
    KeyedVector<hwc2_layer_t, int32_t> * mHwcCurReleaseFences;
    KeyedVector<hwc2_layer_t, int32_t> * mHwcPriorReleaseFences;

    // lock
    Mutex mLock;
    bool mInitialized;

    // status of display connector.(hdmi, cvbs, panel)
    bool mConnectorPresent;

    //rever the scaled displayframe, for we use the vpp scale.
    float mReverseScaleX;
    float mReverseScaleY;
    int mBootanimStatus;

    //for omx video layer status.
    bool mOmxVideoPresent;
    uint32_t mOmxKeepLastFrame;
    bool mVideoLayerOpenByOMX;
    bool mOmxSideBandPresent;
};


}
}

#endif /* PHYSICAL_DEVICE_H */
