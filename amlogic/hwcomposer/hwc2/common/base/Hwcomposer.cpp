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
#include <Dump.h>
#include <UeventObserver.h>
#include <inttypes.h>

namespace android {
namespace amlogic {

Hwcomposer* Hwcomposer::sInstance(0);

Hwcomposer::Hwcomposer(IPlatFactory *factory)
    : mPlatFactory(factory),
      mVsyncManager(0),
      mInitialized(false)
{
    CTRACE();

    mDisplayDevices.setCapacity(IDisplayDevice::DEVICE_COUNT);
    mDisplayDevices.clear();
}

Hwcomposer::~Hwcomposer()
{
    CTRACE();
    deinitialize();
}

bool Hwcomposer::initCheck() const {
    return mInitialized;
}

int32_t Hwcomposer::createVirtualDisplay(
        uint32_t width,
        uint32_t height,
        int32_t* /*android_pixel_format_t*/ format,
        hwc2_display_t* outDisplay) {
    DTRACE("createVirtualDisplay");
    if (width > 1920 && height > 1080) {
        return HWC2_ERROR_UNSUPPORTED;
    }

    IDisplayDevice *device = getDisplayDevice(HWC_DISPLAY_VIRTUAL);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->createVirtualDisplay(width, height, format, outDisplay);
}

int32_t Hwcomposer::destroyVirtualDisplay(
        hwc2_display_t display) {
    DTRACE("destroyVirtualDisplay: %d", (int32_t)display);
    IDisplayDevice *device = getDisplayDevice(HWC_DISPLAY_VIRTUAL);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->destroyVirtualDisplay(display);

    return HWC2_ERROR_NONE;
}

void Hwcomposer::dump(
        uint32_t* outSize,
        char* outBuffer) {
    RETURN_VOID_IF_NOT_INIT();

    if (NULL == outBuffer) {
        *outSize = 4096;
    } else {
        Dump d(outBuffer, *outSize);

        // dump composer status
        d.append("Hardware Composer state(version: %08x):\n",
            this->common.version & HARDWARE_API_VERSION_2_MAJ_MIN_MASK);
        // dump device status
        for (size_t i= 0; i < mDisplayDevices.size(); i++) {
            IDisplayDevice *device = mDisplayDevices.itemAt(i);
            if (device)
                device->dump(d);
        }
    }
}

uint32_t Hwcomposer::getMaxVirtualDisplayCount() {

    // TODO: we only support 1 virtual display now.
    return 1;
}

int32_t Hwcomposer::registerCallback(
        int32_t /*hwc2_callback_descriptor_t*/ descriptor,
        hwc2_callback_data_t callbackData,
        hwc2_function_pointer_t pointer) {
    switch (descriptor) {
        // callback functions
        case HWC2_CALLBACK_HOTPLUG:
            hotplug_cb_data = callbackData;
            pfnHotplug = reinterpret_cast<HWC2_PFN_HOTPLUG>(pointer);
            if (pfnHotplug) {
                DTRACE("First primary hotplug, just for now!!");
                IDisplayDevice *device = getDisplayDevice(HWC_DISPLAY_PRIMARY);
                if (!device) {
                    ETRACE("no device found");
                }
                device->onHotplug(HWC_DISPLAY_PRIMARY, true);
            }
            break;
        case HWC2_CALLBACK_REFRESH:
            refresh_cb_data = callbackData;
            pfnRefresh = reinterpret_cast<HWC2_PFN_REFRESH>(pointer);;
            break;
        case HWC2_CALLBACK_VSYNC:
            vsync_cb_data = callbackData;
            pfnVsync = reinterpret_cast<HWC2_PFN_VSYNC>(pointer);;
            break;
        case HWC2_CALLBACK_INVALID:
        default:
            ETRACE("registerCallback bad parameter: %d", descriptor);
            return HWC2_ERROR_BAD_PARAMETER;
    }

    return HWC2_ERROR_NONE;
}

int32_t Hwcomposer::acceptDisplayChanges(
        hwc2_display_t display) {
    DTRACE("acceptDisplayChanges disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->acceptDisplayChanges();
}

int32_t Hwcomposer::createLayer(
        hwc2_display_t display,
        hwc2_layer_t* outLayer) {
    DTRACE("createLayer disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    bool ret = device->createLayer(outLayer);
    if (ret == false) {
        ETRACE("createLayer failed on display = %d", (int32_t)display);
        return HWC2_ERROR_NO_RESOURCES;
    }

    return HWC2_ERROR_NONE;
}

int32_t Hwcomposer::destroyLayer(
        hwc2_display_t display,
        hwc2_layer_t layer) {
    DTRACE("destroyLayer disp = %d, layer = %llu", (int32_t)display, layer);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    bool ret = device->destroyLayer(layer);
    if (ret == false) {
        ETRACE("destroyLayer failed on display = %d", (int32_t)display);
        return HWC2_ERROR_BAD_LAYER;
    }

    return HWC2_ERROR_NONE;
}

int32_t Hwcomposer::getActiveConfig(
        hwc2_display_t display,
        hwc2_config_t* outConfig) {
    DTRACE("getActiveConfig disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getActiveConfig(outConfig);
}

int32_t Hwcomposer::getChangedCompositionTypes(
        hwc2_display_t display,
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* /*hwc2_composition_t*/ outTypes) {
    DTRACE("getChangedCompositionTypes disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getChangedCompositionTypes(outNumElements, outLayers, outTypes);
}

int32_t Hwcomposer::getClientTargetSupport(
        hwc2_display_t display,
        uint32_t width,
        uint32_t height,
        int32_t /*android_pixel_format_t*/ format,
        int32_t /*android_dataspace_t*/ dataspace) {
    DTRACE("getClientTargetSupport disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getClientTargetSupport(width, height, format, dataspace);
}

int32_t Hwcomposer::getColorModes(
        hwc2_display_t display,
        uint32_t* outNumModes,
        int32_t* /*android_color_mode_t*/ outModes) {
    DTRACE("getColorModes disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getColorModes(outNumModes, outModes);
}

int32_t Hwcomposer::getDisplayAttribute(
        hwc2_display_t display,
        hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute,
        int32_t* outValue) {
    DTRACE("getDisplayAttribute disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDisplayAttribute(config, attribute, outValue);
}

int32_t Hwcomposer::getDisplayConfigs(
        hwc2_display_t display,
        uint32_t* outNumConfigs,
        hwc2_config_t* outConfigs) {
    DTRACE("getDisplayConfigs disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDisplayConfigs(outNumConfigs, outConfigs);
}

int32_t Hwcomposer::getDisplayName(
        hwc2_display_t display,
        uint32_t* outSize,
        char* outName) {
    DTRACE("getDisplayName disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDisplayName(outSize, outName);
}

int32_t Hwcomposer::getDisplayRequests(
        hwc2_display_t display,
        int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* /*hwc2_layer_request_t*/ outLayerRequests) {
    DTRACE("getDisplayRequests disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDisplayRequests(outDisplayRequests, outNumElements,
        outLayers, outLayerRequests);
}

int32_t Hwcomposer::getDisplayType(
        hwc2_display_t display,
        int32_t* /*hwc2_display_type_t*/ outType) {
    DTRACE("getDisplayType disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDisplayType(outType);
}

int32_t Hwcomposer::getDozeSupport(
        hwc2_display_t display,
        int32_t* outSupport) {
    DTRACE("getDozeSupport disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getDozeSupport(outSupport);
}

int32_t Hwcomposer::getHdrCapabilities(
        hwc2_display_t display,
        uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes,
        float* outMaxLuminance,
        float* outMaxAverageLuminance,
        float* outMinLuminance) {
    DTRACE("getHdrCapabilities disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getHdrCapabilities(outNumTypes, outTypes, outMaxLuminance,
        outMaxAverageLuminance, outMinLuminance);
}

int32_t Hwcomposer::getReleaseFences(
        hwc2_display_t display,
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* outFences) {
    DTRACE("getReleaseFences disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->getReleaseFences(outNumElements, outLayers, outFences);
}

int32_t Hwcomposer::presentDisplay(
        hwc2_display_t display,
        int32_t* outRetireFence) {
    DTRACE("presentDisplay disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->presentDisplay(outRetireFence);
}

int32_t Hwcomposer::setActiveConfig(
        hwc2_display_t display,
        hwc2_config_t config) {
    DTRACE("setActiveConfig disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setActiveConfig(config);
}

int32_t Hwcomposer::setClientTarget(
        hwc2_display_t display,
        buffer_handle_t target,
        int32_t acquireFence,
        int32_t /*android_dataspace_t*/ dataspace,
        hwc_region_t damage) {
    DTRACE("setClientTarget disp = %d, targetHnd = %" PRIxPTR ","
        "acquireFence = %d, dataspace = %d", (int32_t)display, target, acquireFence, dataspace);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setClientTarget(target, acquireFence,
        dataspace, damage);
}

int32_t Hwcomposer::setColorMode(
        hwc2_display_t display,
        int32_t /*android_color_mode_t*/ mode) {
    DTRACE("setColorMode disp = %d, mode = %d", (int32_t)display, mode);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setColorMode(mode);
}

int32_t Hwcomposer::setColorTransform(
        hwc2_display_t display,
        const float* matrix,
        int32_t /*android_color_transform_t*/ hint) {
    DTRACE("setColorTransform disp = %d, hint = %d", (int32_t)display, hint);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setColorTransform(matrix, hint);
}

int32_t Hwcomposer::setOutputBuffer(
        hwc2_display_t display,
        buffer_handle_t buffer,
        int32_t releaseFence) {
    DTRACE("setOutputBuffer disp = %d, releaseFence = %d", (int32_t)display, releaseFence);
    if (display != HWC_DISPLAY_VIRTUAL) {
        ETRACE("Should be a virtual display: %d", (int32_t)display);
        return HWC2_ERROR_UNSUPPORTED;
    }

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setOutputBuffer(buffer, releaseFence);
}

int32_t Hwcomposer::setPowerMode(
        hwc2_display_t display,
        int32_t /*hwc2_power_mode_t*/ mode) {
    DTRACE("setPowerMode disp = %d, mode = %d", (int32_t)display, mode);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setPowerMode(mode);
}

int32_t Hwcomposer::setVsyncEnabled(
        hwc2_display_t display,
        int32_t /*hwc2_vsync_t*/ enabled) {
    DTRACE("disp = %d, enabled = %d", (int32_t)display, enabled);

    bool vsync_enable = false;
    switch (enabled) {
        case HWC2_VSYNC_ENABLE:
            vsync_enable = true;
            break;
        case HWC2_VSYNC_DISABLE:
            vsync_enable = false;
            break;
        case HWC2_VSYNC_INVALID:
        default:
            ETRACE("setVsyncEnabled bad parameter: %d", enabled);
            return HWC2_ERROR_BAD_PARAMETER;
    }

    return mVsyncManager->handleVsyncControl((int32_t)display, vsync_enable);
}

int32_t Hwcomposer::validateDisplay(
        hwc2_display_t display,
        uint32_t* outNumTypes,
        uint32_t* outNumRequests) {
    DTRACE("validateDisplay disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->validateDisplay(outNumTypes, outNumRequests);
}

int32_t Hwcomposer::setCursorPosition(
        hwc2_display_t display,
        hwc2_layer_t layer,
        int32_t x,
        int32_t y) {
    DTRACE("setCursorPosition disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    return device->setCursorPosition(layer, x, y);
}

int32_t Hwcomposer::setLayerBuffer(
        hwc2_display_t display,
        hwc2_layer_t layer,
        buffer_handle_t buffer,
        int32_t acquireFence) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerBuffer disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setBuffer(buffer,acquireFence);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerSurfaceDamage(
        hwc2_display_t display,
        hwc2_layer_t layer,
        hwc_region_t damage) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerSurfaceDamage disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setSurfaceDamage(damage);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerBlendMode(
        hwc2_display_t display,
        hwc2_layer_t layer,
        int32_t /*hwc2_blend_mode_t*/ mode) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerBlendMode disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setBlendMode(mode);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerColor(
        hwc2_display_t display,
        hwc2_layer_t layer,
        hwc_color_t color) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerColor disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setColor(color);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerCompositionType(
        hwc2_display_t display,
        hwc2_layer_t layer,
        int32_t /*hwc2_composition_t*/ type) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerCompositionType disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setCompositionType(type);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerDataspace(
        hwc2_display_t display,
        hwc2_layer_t layer,
        int32_t /*android_dataspace_t*/ dataspace) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerDataspace disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setDataspace(dataspace);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerDisplayFrame(
    hwc2_display_t display,
    hwc2_layer_t layer,
    hwc_rect_t frame) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerDisplayFrame disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setDisplayFrame(frame);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerPlaneAlpha(
        hwc2_display_t display,
        hwc2_layer_t layer,
        float alpha) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerPlaneAlpha disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setPlaneAlpha(alpha);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerSidebandStream(
        hwc2_display_t display,
        hwc2_layer_t layer,
        const native_handle_t* stream) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerSidebandStream disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setSidebandStream(stream);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerSourceCrop(
        hwc2_display_t display,
        hwc2_layer_t layer,
        hwc_frect_t crop) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerSourceCrop disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setSourceCrop(crop);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerTransform(
        hwc2_display_t display,
        hwc2_layer_t layer,
        int32_t /*hwc_transform_t*/ transform) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerTransform disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setTransform(transform);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerVisibleRegion(
        hwc2_display_t display,
        hwc2_layer_t layer,
        hwc_region_t visible) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerVisibleRegion disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setVisibleRegion(visible);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

int32_t Hwcomposer::setLayerZOrder(
        hwc2_display_t display,
        hwc2_layer_t layer,
        uint32_t z) {
    HwcLayer* hwcLayer = NULL;
    int32_t err = HWC2_ERROR_NONE;
    DTRACE("setLayerZOrder disp = %d", (int32_t)display);

    IDisplayDevice *device = getDisplayDevice((int32_t)display);
    if (!device) {
        ETRACE("no device found");
        return HWC2_ERROR_BAD_DISPLAY;
    }

    hwcLayer = device->getLayerById(layer);
    if (hwcLayer) {
        err = hwcLayer->setZ(z);
    } else {
        ETRACE("bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return err;
}

template <typename T>
static hwc2_function_pointer_t asFP(T function)
{
    return reinterpret_cast<hwc2_function_pointer_t>(function);
}

void Hwcomposer::vsync(int disp, int64_t timestamp) {
    RETURN_VOID_IF_NOT_INIT();

    if (pfnVsync) {
        VTRACE("report vsync on disp %d, timestamp %llu", disp, timestamp);
        // workaround to pretend vsync is from primary display
        // Display will freeze if vsync is from external display.
        pfnVsync(vsync_cb_data, IDisplayDevice::DEVICE_PRIMARY, timestamp);
    }
}

void Hwcomposer::hotplug(int disp, bool connected) {
    RETURN_VOID_IF_NOT_INIT();

    int32_t cnet = HWC2_CONNECTION_INVALID;
    if (connected)
        cnet = HWC2_CONNECTION_CONNECTED;
    else
        cnet = HWC2_CONNECTION_DISCONNECTED;

    if (pfnHotplug) {
        DTRACE("report hotplug on disp %d, connected %d", disp, cnet);
        pfnHotplug(hotplug_cb_data, disp, cnet);
        DTRACE("hotplug callback processed and returned!");
    }

    // mDisplayAnalyzer->postHotplugEvent(connected);
}

void Hwcomposer::refresh(int disp) {
    RETURN_VOID_IF_NOT_INIT();

    if (pfnRefresh) {
        DTRACE("refresh screen...");
        pfnRefresh(refresh_cb_data, disp);
    }
}

bool Hwcomposer::release() {
    RETURN_FALSE_IF_NOT_INIT();

    return true;
}

bool Hwcomposer::initialize(private_module_t *grallocModule) {
    CTRACE();

    if (!mPlatFactory || !grallocModule) {
        DEINIT_AND_RETURN_FALSE("failed to provide a PlatFactory");
    }

    // initial gralloc module.
    mGrallocModule = grallocModule;

    mUeventObserver = new UeventObserver();
    if (!mUeventObserver || !mUeventObserver->initialize()) {
        DEINIT_AND_RETURN_FALSE("failed to initialize uevent observer");
    }

    // create display device
    mDisplayDevices.clear();
    for (int i = 0; i < IDisplayDevice::DEVICE_COUNT; i++) {
        IDisplayDevice *device = mPlatFactory->createDisplayDevice(i);
        if (!device || !device->initialize()) {
            DEINIT_AND_DELETE_OBJ(device);
            ETRACE("failed to create device %d", i);
        }
        // add this device
        DTRACE("HWC devices initialize device is %p at %d", device, i);
        mDisplayDevices.insertAt(device, i, 1);
    }

    mVsyncManager = new VsyncManager(*this);
    if (!mVsyncManager || !mVsyncManager->initialize()) {
        DEINIT_AND_RETURN_FALSE("failed to create Vsync Manager");
    }

    // all initialized, starting uevent observer
    mUeventObserver->start();

    mInitialized = true;
    return true;
}

void Hwcomposer::deinitialize() {
    // delete mVsyncManager first as it holds reference to display devices.
    DEINIT_AND_DELETE_OBJ(mVsyncManager);

    // destroy display devices
    for (size_t i = 0; i < mDisplayDevices.size(); i++) {
        IDisplayDevice *device = mDisplayDevices.itemAt(i);
        DEINIT_AND_DELETE_OBJ(device);
    }
    mDisplayDevices.clear();

    if (mPlatFactory) {
        delete mPlatFactory;
        mPlatFactory = 0;
    }

    mInitialized = false;
}

IDisplayDevice* Hwcomposer::getDisplayDevice(int disp) {
    if (disp < 0 || disp >= IDisplayDevice::DEVICE_COUNT) {
        ETRACE("invalid disp %d", disp);
        return NULL;
    }
    return mDisplayDevices.itemAt(disp);
}

VsyncManager* Hwcomposer::getVsyncManager() {
    return mVsyncManager;
}

UeventObserver* Hwcomposer::getUeventObserver()
{
    return mUeventObserver;
}

private_module_t* Hwcomposer::getGrallocModule() {
    return mGrallocModule;
}

} // namespace amlogic
} // namespace android
