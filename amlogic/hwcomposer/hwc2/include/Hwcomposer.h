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

#ifndef HWCOMPOSER_H
#define HWCOMPOSER_H

#include <EGL/egl.h>
#include <hardware/hwcomposer2.h>
#include <utils/Vector.h>

#include <IDisplayDevice.h>
#include <VsyncManager.h>
#include <UeventObserver.h>
#include <IPlatFactory.h>
#include <gralloc_priv.h>

namespace android {
namespace amlogic {

class Hwcomposer : public hwc2_device_t {
public:
    virtual ~Hwcomposer();
public:
    virtual int32_t createVirtualDisplay(uint32_t width, uint32_t height,
        int32_t* /*android_pixel_format_t*/ format, hwc2_display_t* outDisplay);

    virtual int32_t destroyVirtualDisplay(hwc2_display_t display);
    virtual void dump(uint32_t* outSize, char* outBuffer);
    virtual uint32_t getMaxVirtualDisplayCount();
    virtual int32_t registerCallback(int32_t /*hwc2_callback_descriptor_t*/ descriptor,
        hwc2_callback_data_t callbackData, hwc2_function_pointer_t pointer);
    virtual int32_t acceptDisplayChanges(hwc2_display_t display);
    virtual int32_t createLayer(hwc2_display_t display, hwc2_layer_t* outLayer);
    virtual int32_t destroyLayer(hwc2_display_t display, hwc2_layer_t layer);
    virtual int32_t getActiveConfig(hwc2_display_t display,hwc2_config_t* outConfig);
    virtual int32_t getChangedCompositionTypes(hwc2_display_t display,
        uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* /*hwc2_composition_t*/ outTypes);
    virtual int32_t getClientTargetSupport(hwc2_display_t display, uint32_t width,
        uint32_t height, int32_t /*android_pixel_format_t*/ format,
        int32_t /*android_dataspace_t*/ dataspace);
    virtual int32_t getColorModes(hwc2_display_t display, uint32_t* outNumModes,
        int32_t* /*android_color_mode_t*/ outModes);
    virtual int32_t getDisplayAttribute(hwc2_display_t display, hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute, int32_t* outValue);
    virtual int32_t getDisplayConfigs(hwc2_display_t display, uint32_t* outNumConfigs, hwc2_config_t* outConfigs);
    virtual int32_t getDisplayName(hwc2_display_t display, uint32_t* outSize,char* outName);
    virtual int32_t getDisplayRequests(hwc2_display_t display, int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* /*hwc2_layer_request_t*/ outLayerRequests);
    virtual int32_t getDisplayType(hwc2_display_t display, int32_t* /*hwc2_display_type_t*/ outType);
    virtual int32_t getDozeSupport(hwc2_display_t display, int32_t* outSupport);
    virtual int32_t getHdrCapabilities(hwc2_display_t display, uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes, float* outMaxLuminance,
        float* outMaxAverageLuminance, float* outMinLuminance);
    virtual int32_t getReleaseFences(hwc2_display_t display, uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outFences);
    virtual int32_t presentDisplay(hwc2_display_t display, int32_t* outRetireFence);
    virtual int32_t setActiveConfig(hwc2_display_t display, hwc2_config_t config);
    virtual int32_t setClientTarget(hwc2_display_t display, buffer_handle_t target,
        int32_t acquireFence, int32_t /*android_dataspace_t*/ dataspace, hwc_region_t damage);
    virtual int32_t setColorMode(hwc2_display_t display, int32_t /*android_color_mode_t*/ mode);
    virtual int32_t setColorTransform(hwc2_display_t display, const float* matrix, int32_t /*android_color_transform_t*/ hint);
    virtual int32_t setOutputBuffer(hwc2_display_t display, buffer_handle_t buffer, int32_t releaseFence);
    virtual int32_t setPowerMode(hwc2_display_t display, int32_t /*hwc2_power_mode_t*/ mode);
    virtual int32_t setVsyncEnabled(hwc2_display_t display, int32_t /*hwc2_vsync_t*/ enabled);
    virtual int32_t validateDisplay(hwc2_display_t display, uint32_t* outNumTypes, uint32_t* outNumRequests);
    virtual int32_t setCursorPosition(hwc2_display_t display, hwc2_layer_t layer, int32_t x, int32_t y);
    virtual int32_t setLayerBuffer(hwc2_display_t display, hwc2_layer_t layer, buffer_handle_t buffer, int32_t acquireFence);
    virtual int32_t setLayerSurfaceDamage(hwc2_display_t display, hwc2_layer_t layer, hwc_region_t damage);
    virtual int32_t setLayerBlendMode(hwc2_display_t display, hwc2_layer_t layer, int32_t /*hwc2_blend_mode_t*/ mode);
    virtual int32_t setLayerColor(hwc2_display_t display, hwc2_layer_t layer, hwc_color_t color);
    virtual int32_t setLayerCompositionType(hwc2_display_t display, hwc2_layer_t layer, int32_t /*hwc2_composition_t*/ type);
    virtual int32_t setLayerDataspace(hwc2_display_t display, hwc2_layer_t layer, int32_t /*android_dataspace_t*/ dataspace);
    virtual int32_t setLayerDisplayFrame(hwc2_display_t display, hwc2_layer_t layer, hwc_rect_t frame);
    virtual int32_t setLayerPlaneAlpha(hwc2_display_t display, hwc2_layer_t layer, float alpha);
    virtual int32_t setLayerSidebandStream(hwc2_display_t display, hwc2_layer_t layer, const native_handle_t* stream);
    virtual int32_t setLayerSourceCrop(hwc2_display_t display, hwc2_layer_t layer, hwc_frect_t crop);
    virtual int32_t setLayerTransform(hwc2_display_t display, hwc2_layer_t layer, int32_t /*hwc_transform_t*/ transform);
    virtual int32_t setLayerVisibleRegion(hwc2_display_t display, hwc2_layer_t layer, hwc_region_t visible);
    virtual int32_t setLayerZOrder(hwc2_display_t display, hwc2_layer_t layer, uint32_t z);

    // callbacks
    virtual void vsync(int disp, int64_t timestamp);
    virtual void hotplug(int disp, bool connected);
    virtual void refresh(int disp);
    virtual bool release();

    virtual bool initCheck() const;
    virtual bool initialize(private_module_t *grallocModule);
    virtual void deinitialize();

public:
    VsyncManager* getVsyncManager();
    private_module_t* getGrallocModule();

    IDisplayDevice* getDisplayDevice(int disp);
    UeventObserver* getUeventObserver();
    IPlatFactory* getPlatFactory() {return mPlatFactory;}

    void (*pfnHotplug)(hwc2_callback_data_t, hwc2_display_t, int32_t);
    void (*pfnRefresh)(hwc2_callback_data_t, hwc2_display_t);
    void (*pfnVsync)(hwc2_callback_data_t, hwc2_display_t, int64_t);

protected:
    Hwcomposer(IPlatFactory *factory);

public:
    static Hwcomposer& getInstance() {
        Hwcomposer *instance = sInstance;
        if (instance == 0) {
            instance = createHwcomposer();
            sInstance = instance;
        }
        return *sInstance;
    }
    static void releaseInstance() {
        delete sInstance;
        sInstance = NULL;
    }
    // Need to be implemented
    static Hwcomposer* createHwcomposer();

private:
    hwc2_callback_data_t hotplug_cb_data;
    hwc2_callback_data_t refresh_cb_data;
    hwc2_callback_data_t vsync_cb_data;

    // plugin through set
    IPlatFactory *mPlatFactory;
    VsyncManager *mVsyncManager;
    private_module_t *mGrallocModule;
    UeventObserver *mUeventObserver;

    Vector<IDisplayDevice*> mDisplayDevices;

    bool mInitialized;

    static Hwcomposer *sInstance;
};

} // namespace amlogic
}

#endif /*HW_COMPOSER_H*/
