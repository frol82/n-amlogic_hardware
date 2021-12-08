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

#ifndef IDISPLAY_DEVICE_H
#define IDISPLAY_DEVICE_H

#include <utils/KeyedVector.h>
#include <Dump.h>
#include <hardware/hwcomposer2.h>
#include <Hwcomposer.h>
#include <HwcLayer.h>

namespace android {
namespace amlogic {

enum {
    HWC2_NO_LAYER = 0,
    HWC2_ONE_LAYER = 1,
    HWC2_TWO_LAYERS = 2,
    HWC2_THREE_LAYERS = 3,
    HWC2_MAX_LAYERS = HWC2_THREE_LAYERS,
};


#define HWC2_HW_COMPOSE_WIDTH_MAX       (1920)
#define HWC2_HW_COMPOSE_HEIGHT_MAX      (1080)

//  display device interface
class IDisplayDevice {
public:
    // display device type
    enum {
        DEVICE_PRIMARY = HWC_DISPLAY_PRIMARY,
        DEVICE_EXTERNAL = HWC_DISPLAY_EXTERNAL,
        DEVICE_VIRTUAL = HWC_DISPLAY_VIRTUAL,
        DEVICE_COUNT,
    };
    enum {
        DEVICE_DISCONNECTED = 0,
        DEVICE_CONNECTED,
    };
    enum {
        DEVICE_DISPLAY_OFF = 0,
        DEVICE_DISPLAY_ON,
        DEVICE_DISPLAY_STANDBY,
    };
public:
    IDisplayDevice() {}
    virtual ~IDisplayDevice() {}
public:
    virtual int32_t acceptDisplayChanges() = 0;
    virtual bool createLayer(hwc2_layer_t* outLayer) = 0;
    virtual bool destroyLayer(hwc2_layer_t layer) = 0;
    virtual int32_t getActiveConfig(hwc2_config_t* outConfig) = 0;
    virtual int32_t getChangedCompositionTypes(uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* /*hwc2_composition_t*/ outTypes) = 0;
    virtual int32_t getClientTargetSupport(uint32_t width,
        uint32_t height, int32_t /*android_pixel_format_t*/ format,
        int32_t /*android_dataspace_t*/ dataspace) = 0;
    virtual int32_t getColorModes(uint32_t* outNumModes,
        int32_t* /*android_color_mode_t*/ outModes) = 0;
    virtual int32_t getDisplayAttribute(hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute, int32_t* outValue) = 0;
    virtual int32_t getDisplayConfigs(uint32_t* outNumConfigs, hwc2_config_t* outConfigs) = 0;
    virtual int32_t getDisplayName(uint32_t* outSize,char* outName) = 0;
    virtual int32_t getDisplayRequests(int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* /*hwc2_layer_request_t*/ outLayerRequests) = 0;
    virtual int32_t getDisplayType(int32_t* /*hwc2_display_type_t*/ outType) = 0;
    virtual int32_t getDozeSupport(int32_t* outSupport) = 0;
    virtual int32_t getHdrCapabilities(uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes, float* outMaxLuminance,
        float* outMaxAverageLuminance, float* outMinLuminance) = 0;
    virtual int32_t getReleaseFences(uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outFences) = 0;
    virtual int32_t presentDisplay(int32_t* outRetireFence) = 0;
    virtual int32_t setActiveConfig(hwc2_config_t config) = 0;
    virtual int32_t setClientTarget(buffer_handle_t target,
        int32_t acquireFence, int32_t /*android_dataspace_t*/ dataspace, hwc_region_t damage) = 0;
    virtual int32_t setColorMode(int32_t /*android_color_mode_t*/ mode) = 0;
    virtual int32_t setColorTransform(const float* matrix, int32_t /*android_color_transform_t*/ hint) = 0;
    // virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) = 0;
    virtual int32_t setPowerMode(int32_t /*hwc2_power_mode_t*/ mode) = 0;
    virtual bool vsyncControl(bool enabled) = 0;
    virtual int32_t validateDisplay(uint32_t* outNumTypes, uint32_t* outNumRequests) = 0;
    virtual int32_t setCursorPosition(hwc2_layer_t layerId, int32_t x, int32_t y) = 0;

    // Virtual display.
    virtual int32_t createVirtualDisplay(uint32_t width, uint32_t height, int32_t* format, hwc2_display_t* outDisplay) = 0;
    virtual int32_t destroyVirtualDisplay(hwc2_display_t display) = 0;
    virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) = 0;

    // Other Display methods
    virtual hwc2_display_t getId() const = 0;
    virtual bool isConnected() const = 0;

    // device related operations
    virtual bool initCheck() const = 0;
    virtual bool initialize() = 0;
    virtual void deinitialize() = 0;
    virtual const char* getName() const = 0;
    virtual int getDisplayId() const = 0;

    virtual HwcLayer* getLayerById(hwc2_layer_t layerId) = 0;

    // events
    virtual void onVsync(int64_t timestamp) = 0;
    virtual void onHotplug(int disp, bool connected) = 0;
    virtual void dump(Dump& d) = 0;

};

}
}

#endif /* IDISPLAY_DEVICE_H */
