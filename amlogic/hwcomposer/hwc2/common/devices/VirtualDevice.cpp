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
#include <VirtualDevice.h>
#include <Utils.h>
#include <sync/sync.h>

namespace android {
namespace amlogic {

VirtualDevice::VirtualDevice(Hwcomposer& hwc)
    : mHwc(hwc),
      mId(HWC_DISPLAY_VIRTUAL),
      mIsConnected(false),
      mInitialized(false),
      mWidth(0),
      mHeight(0),
      mFormat(0),
      mRetireFence(-1)
{
    CTRACE();
    mName = "Virtual";

    // set capacity of layers, layer's changed type, layer's changed request.
    mHwcLayersChangeType.setCapacity(LAYER_MAX_NUM_CHANGE_TYPE);
    mHwcLayers.setCapacity(LAYER_MAX_NUM_SUPPORT);
}

VirtualDevice::~VirtualDevice()
{
    CTRACE();
}

bool VirtualDevice::initialize() {
    CTRACE();

    mInitialized = true;
    return true;
}

void VirtualDevice::deinitialize() {
    CTRACE();
    mInitialized = false;
}

HwcLayer* VirtualDevice::getLayerById(hwc2_layer_t layerId) {
    HwcLayer* layer = NULL;

    layer = mHwcLayers.valueFor(layerId);
    if (!layer) ETRACE("getLayerById %lld error!", layerId);

    return layer;
}

int32_t VirtualDevice::acceptDisplayChanges() {
    HwcLayer* layer = NULL;

    for (uint32_t i=0; i<mHwcLayersChangeType.size(); i++) {
        hwc2_layer_t layerId = mHwcLayersChangeType.keyAt(i);
        layer = mHwcLayersChangeType.valueAt(i);
        if (layer) {
            if (layer->getCompositionType() != HWC2_COMPOSITION_CLIENT) {
                layer->setCompositionType(HWC2_COMPOSITION_CLIENT);
            }
        }
    }
    // reset layer changed or requested to zero.
    mHwcLayersChangeType.clear();

    return HWC2_ERROR_NONE;
}

bool VirtualDevice::createLayer(hwc2_layer_t* outLayer) {
    HwcLayer* layer = new HwcLayer(mId);

    if (layer == NULL || !layer->initialize()) {
        ETRACE("createLayer: failed !");
        return false;
    }

    hwc2_layer_t layerId = reinterpret_cast<hwc2_layer_t>(layer);
    mHwcLayers.add(layerId, layer);
    *outLayer = layerId;
    return true;
}

bool VirtualDevice::destroyLayer(hwc2_layer_t layerId) {
    //HwcLayer* layer = reinterpret_cast<HwcLayer*>(layerId);
    HwcLayer* layer = mHwcLayers.valueFor(layerId);

    if (layer == NULL) {
        ETRACE("destroyLayer: no Hwclayer found (%d)", layerId);
        return false;
    }

    mHwcLayers.removeItem(layerId);
    DEINIT_AND_DELETE_OBJ(layer);
    return true;
}

int32_t VirtualDevice::getActiveConfig(
    hwc2_config_t* outConfig) {

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getChangedCompositionTypes(
    uint32_t* outNumElements,
    hwc2_layer_t* outLayers,
    int32_t* /*hwc2_composition_t*/ outTypes) {
    HwcLayer* layer = NULL;

    // if outLayers or outTypes were NULL, the number of layers and types which would have been returned.
    if (NULL == outLayers || NULL == outTypes) {
        *outNumElements = mHwcLayersChangeType.size();
    } else {
        for (uint32_t i=0; i<mHwcLayersChangeType.size(); i++) {
            hwc2_layer_t layerId = mHwcLayersChangeType.keyAt(i);
            layer = mHwcLayersChangeType.valueAt(i);
            if (layer) {
                if (layer->getCompositionType() != HWC2_COMPOSITION_CLIENT) {
                    // change all other device type to client.
                    outLayers[i] = layerId;
                    outTypes[i] = HWC2_COMPOSITION_CLIENT;
                    continue;
                }
            }
        }

        if (mHwcLayersChangeType.size() > 0) {
            DTRACE("There are %d layers type has changed.", mHwcLayersChangeType.size());
            *outNumElements = mHwcLayersChangeType.size();
        } else {
            DTRACE("No layers compositon type changed.");
        }
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getClientTargetSupport(
    uint32_t width,
    uint32_t height,
    int32_t /*android_pixel_format_t*/ format,
    int32_t /*android_dataspace_t*/ dataspace) {

    // TODO: ?
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getColorModes(
    uint32_t* outNumModes,
    int32_t* /*android_color_mode_t*/ outModes) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDisplayAttribute(
        hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute,
        int32_t* outValue) {
    Mutex::Autolock _l(mLock);

    if (!mIsConnected) {
        ETRACE("display %d is not connected.", mId);
    }

    // TODO: HWC2_ERROR_BAD_CONFIG?
    switch (attribute) {
        case HWC2_ATTRIBUTE_VSYNC_PERIOD:
            *outValue = 1e9 / 60;
            ETRACE("refresh period: %d", *outValue);
        break;
        case HWC2_ATTRIBUTE_WIDTH:
            *outValue = mWidth;
        break;
        case HWC2_ATTRIBUTE_HEIGHT:
            *outValue = mHeight;
        break;
        case HWC2_ATTRIBUTE_DPI_X:
            *outValue = 160;
        break;
        case HWC2_ATTRIBUTE_DPI_Y:
            *outValue = 160;
        break;
        default:
            ETRACE("unknown display attribute %u", attribute);
            *outValue = -1;
        break;
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDisplayConfigs(
        uint32_t* outNumConfigs,
        hwc2_config_t* outConfigs) {
    Mutex::Autolock _l(mLock);

    if (!mIsConnected) {
        ETRACE("display %d is not connected.", mId);
    }

    if (NULL != outConfigs) outConfigs[0] = 0;
    *outNumConfigs = 1;

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDisplayName(
    uint32_t* outSize,
    char* outName) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDisplayRequests(
        int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* /*hwc2_layer_request_t*/ outLayerRequests) {
    *outNumElements = 0;

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDisplayType(
    int32_t* /*hwc2_display_type_t*/ outType) {
    if (!mIsConnected) {
        ETRACE("display %d is not connected.", mId);
    }

    *outType = HWC2_DISPLAY_TYPE_VIRTUAL;
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getDozeSupport(
    int32_t* outSupport) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getHdrCapabilities(
        uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes,
        float* outMaxLuminance,
        float* outMaxAverageLuminance,
        float* outMinLuminance) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::getReleaseFences(
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* outFences) {

    //No hw compose for virtual display.
    *outNumElements= 0;
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::presentDisplay(
        int32_t* outRetireFence) {
    if (!mIsConnected)
        return HWC2_ERROR_BAD_DISPLAY;

    if (!mVirtualHnd) {
        ETRACE("virtual display handle is null.");
        return HWC2_ERROR_NO_RESOURCES;
    }

    if (private_handle_t::validate(mVirtualHnd) < 0)
        return HWC2_ERROR_NO_RESOURCES;

    if (mTargetAcquireFence > -1 && mVirtualReleaseFence > -1) {
        mRetireFence = sync_merge("VirtualDevice-2", mTargetAcquireFence, mVirtualReleaseFence);
    } else if (mTargetAcquireFence > -1) {
        mRetireFence = sync_merge("VirtualDevice-0", mTargetAcquireFence, mTargetAcquireFence);
    } else if (mVirtualReleaseFence > -1) {
        mRetireFence = sync_merge("VirtualDevice-1", mVirtualReleaseFence, mVirtualReleaseFence);
    } else {
        mRetireFence = -1;
    }

    *outRetireFence = mRetireFence;

    DTRACE("VirtualDevice::presentDisplay retire fence %d", mRetireFence);

    if (mTargetAcquireFence > -1) {
        close(mTargetAcquireFence);
        mTargetAcquireFence = -1;
    }
    if (mVirtualReleaseFence > -1) {
        close(mVirtualReleaseFence);
        mVirtualReleaseFence = -1;
    }

    //reset layers' acquire fence.
    HwcLayer * layer = NULL;
    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (layer != NULL) {
            close(layer->getAcquireFence());
            layer->resetAcquireFence();
        }
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setActiveConfig(
    hwc2_config_t config) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setClientTarget(
        buffer_handle_t target,
        int32_t acquireFence,
        int32_t /*android_dataspace_t*/ dataspace,
        hwc_region_t damage) {

    DTRACE("VirtualDevice::setClientTarget %p, %d", target, acquireFence);

    if (mTargetAcquireFence > -1) {
        close(mTargetAcquireFence);
        mTargetAcquireFence = -1;
    }

    if (!mIsConnected)
        return HWC2_ERROR_BAD_DISPLAY;

    if (target && private_handle_t::validate(target) < 0) {
        return HWC2_ERROR_BAD_PARAMETER;
    }

    if (NULL != target) {
        mClientTargetHnd = target;
        mClientTargetDamageRegion = damage;
        mTargetAcquireFence = acquireFence;
    } else {
        DTRACE("client target is null!, no need to update this frame.");
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setColorMode(
    int32_t /*android_color_mode_t*/ mode) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setColorTransform(
    const float* matrix,
    int32_t /*android_color_transform_t*/ hint) {
    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setPowerMode(
    int32_t /*hwc2_power_mode_t*/ mode){
    return HWC2_ERROR_NONE;
}

bool VirtualDevice::vsyncControl(bool enabled) {
    RETURN_FALSE_IF_NOT_INIT();

    return true;
}

int32_t VirtualDevice::validateDisplay(uint32_t* outNumTypes,
    uint32_t* outNumRequests) {
    HwcLayer* layer = NULL;

    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (layer) {
            // Virtual Display.
            if (mVirtualHnd && private_handle_t::validate(mVirtualHnd) >=0) {
                if (layer->getCompositionType() != HWC2_COMPOSITION_CLIENT) {
                    // change all other device type to client.
                    mHwcLayersChangeType.add(layerId, layer);
                    continue;
                }
            }
        }
    }

    // No requests.
    *outNumRequests = 0;

    if (mHwcLayersChangeType.size() > 0) {
        DTRACE("there are %d layer types has changed.", mHwcLayersChangeType.size());
        *outNumTypes = mHwcLayersChangeType.size();
        return HWC2_ERROR_HAS_CHANGES;
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setCursorPosition(
        hwc2_layer_t layerId,
        int32_t x,
        int32_t y) {
    Mutex::Autolock _l(mLock);
    return HWC2_ERROR_NONE;
}

bool VirtualDevice::updateDisplayConfigs()
{
    Mutex::Autolock _l(mLock);
    return true;
}

void VirtualDevice::onVsync(int64_t timestamp) {
    // dont need implement now.
}

void VirtualDevice::onHotplug(int disp, bool connected) {
    // dont need implement now.
}

int32_t VirtualDevice::createVirtualDisplay(
        uint32_t width,
        uint32_t height,
        int32_t* /*android_pixel_format_t*/ format,
        hwc2_display_t* outDisplay) {
    mIsConnected = true;
    mWidth = width;
    mHeight = height;
    mFormat = *format;
    mVirtualReleaseFence= -1;
    mRetireFence = -1;
    mTargetAcquireFence = -1;
    *outDisplay = HWC_DISPLAY_VIRTUAL;

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::destroyVirtualDisplay(
        hwc2_display_t display) {
    if (display != HWC_DISPLAY_VIRTUAL) {
        return HWC2_ERROR_BAD_PARAMETER;
    }
    mIsConnected = false;
    mWidth = 0;
    mHeight = 0;
    mFormat = 0;

    //release fence.
    if (mRetireFence > -1) {
        close(mRetireFence);
        mRetireFence = -1;
    }
    if (mVirtualReleaseFence > -1) {
        close(mVirtualReleaseFence);
        mVirtualReleaseFence = -1;
    }
    if (mTargetAcquireFence > -1) {
        close(mTargetAcquireFence);
        mTargetAcquireFence = -1;
    }

    //release layers.
    if (!mHwcLayers.isEmpty()) {
        int i = 0;
        HwcLayer* layer = NULL;
        for (i = 0; i < mHwcLayers.size(); i++) {
            layer = mHwcLayers[i];
            DEINIT_AND_DELETE_OBJ(layer);
        }
        mHwcLayers.clear();
    }

    return HWC2_ERROR_NONE;
}

int32_t VirtualDevice::setOutputBuffer(
        buffer_handle_t buffer, int32_t releaseFence) {
    DTRACE("VirtualDevice::setOutputBuffer");

    if (mVirtualReleaseFence > -1) {
        close(mVirtualReleaseFence);
        mVirtualReleaseFence = -1;
    }

    if (!mIsConnected)
        return HWC2_ERROR_BAD_DISPLAY;

    if (NULL == buffer) {
        ETRACE("Virtual Display output buffer target is null!, no need to update this frame.");
        return HWC2_ERROR_BAD_PARAMETER;
    }

    if (buffer && private_handle_t::validate(buffer) < 0) {
        ETRACE("buffer handle is invalid");
        return HWC2_ERROR_BAD_PARAMETER;
    }

    mVirtualHnd = buffer;
    mVirtualReleaseFence = releaseFence;
    DTRACE("VirtualDevice setOutputBuffer %d, %p ", releaseFence, buffer);
    return HWC2_ERROR_NONE;
}

void VirtualDevice::dump(Dump& d) {
    Mutex::Autolock _l(mLock);
    d.append("----------------------------------------------------------"
        "-------------------------------------------------------------------\n");
    d.append("Device Name: %s (%s)\n", mName,
            mIsConnected ? "connected" : "disconnected");

    if (mIsConnected) {
        d.append("  Layers state:\n");
        d.append("    numLayers=%zu\n", mHwcLayers.size());
        d.append("    numChangedTypeLayers=%zu\n", mHwcLayersChangeType.size());
        if (mHwcLayers.size() > 0) {
            d.append(
                "       type    |    handle    |   zorder   | ds | alpa | tr | blnd |"
                "     source crop (l,t,r,b)      |          frame         \n"
                "  -------------+--------------+------------+----+------+----+------+"
                "--------------------------------+------------------------\n");
            for (uint32_t i=0; i<mHwcLayers.size(); i++) {
                hwc2_layer_t layerId = mHwcLayers.keyAt(i);
                HwcLayer *layer = mHwcLayers.valueAt(i);
                if (layer) layer->dump(d);
            }
        }
    }
}

} // namespace amlogic
} // namespace android
