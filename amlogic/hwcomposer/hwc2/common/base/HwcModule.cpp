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

#include <hardware/hardware.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <HwcTrace.h>
#include <Hwcomposer.h>

#define GET_HWC_RETURN_X_IF_NULL(X) \
    CTRACE(); \
    Hwcomposer *hwc = static_cast<Hwcomposer*>(device); \
    do {\
        if (!hwc) { \
            ETRACE("invalid HWC device."); \
            return X; \
        } \
    } while (0)

#define GET_HWC() \
    CTRACE(); \
    Hwcomposer *hwc = static_cast<Hwcomposer*>(device); \
    do {\
        if (!hwc) { \
            ETRACE("invalid HWC device."); \
        } \
    } while (0)

#define GET_HWC_RETURN_ERROR_IF_NULL()        GET_HWC_RETURN_X_IF_NULL(-EINVAL)
#define GET_HWC_RETURN_VOID_IF_NULL()         GET_HWC_RETURN_X_IF_NULL()
#define GET_HWC_RETURN_NULL_IF_NULL()         GET_HWC_RETURN_X_IF_NULL(NULL)

namespace android {
namespace amlogic {

static int hwc2_device_close(struct hw_device_t *dev)
{
    CTRACE();
    Hwcomposer::releaseInstance();
    return 0;
}

int32_t createVirtualDisplay(
        hwc2_device_t* device, uint32_t width,
        uint32_t height, int32_t* format,
        hwc2_display_t* outDisplay) {
    GET_HWC();

    if (width > 1920 && height > 1080) {
        return HWC2_ERROR_UNSUPPORTED;
    }

    int32_t ret = hwc->createVirtualDisplay(width, height, format, outDisplay);

    return ret;
}

int32_t destroyVirtualDisplay(
        hwc2_device_t* device, hwc2_display_t display) {
    GET_HWC();

    int32_t ret = hwc->destroyVirtualDisplay(display);

    return ret;
}

void dump(hwc2_device_t* device,
        uint32_t* outSize,
        char* outBuffer) {
    GET_HWC_RETURN_VOID_IF_NULL();

    hwc->dump(outSize, outBuffer);
}

uint32_t getMaxVirtualDisplayCount(
        hwc2_device_t* device) {
    GET_HWC();

    uint32_t ret = hwc->getMaxVirtualDisplayCount();

    return ret;
}

int32_t registerCallback(
        hwc2_device_t* device,
        hwc2_callback_descriptor_t descriptor,
        hwc2_callback_data_t callbackData,
        hwc2_function_pointer_t pointer) {
    GET_HWC();

    int32_t ret = hwc->registerCallback(descriptor, callbackData, pointer);

    return ret;
}

int32_t acceptDisplayChanges(
        hwc2_device_t* device, hwc2_display_t display) {
    GET_HWC();

    int32_t ret = hwc->acceptDisplayChanges(display);

    return ret;
}

int32_t createLayer(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t* outLayer) {
    GET_HWC();

    int32_t ret = hwc->createLayer(display, outLayer);

    return ret;
}

int32_t destroyLayer(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer) {
    GET_HWC();

    int32_t ret = hwc->destroyLayer(display, layer);

    return ret;
}

int32_t getActiveConfig(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_config_t* outConfig) {
    GET_HWC();

    int32_t ret = hwc->getActiveConfig(display, outConfig);

    return ret;
}

int32_t getChangedCompositionTypes(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* outTypes) {
    GET_HWC();

    int32_t ret = hwc->getChangedCompositionTypes(display, outNumElements,
        outLayers, outTypes);

    return ret;
}

int32_t getClientTargetSupport(
        hwc2_device_t* device, hwc2_display_t display, uint32_t width,
        uint32_t height, android_pixel_format_t format,
        android_dataspace_t dataspace) {
    GET_HWC();

    int32_t ret = hwc->getClientTargetSupport(display, width, height, format, dataspace);

    return ret;
}

int32_t getColorModes(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumModes, int32_t* /*android_color_mode_t*/ outModes) {
    GET_HWC();

    int32_t ret = hwc->getColorModes(display, outNumModes, outModes);

    return ret;
}

int32_t getDisplayAttribute(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_config_t config, hwc2_attribute_t attribute, int32_t* outValue) {
    GET_HWC();

    int32_t ret = hwc->getDisplayAttribute(display, config, attribute, outValue);

    return ret;
}

int32_t getDisplayConfigs(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumConfigs, hwc2_config_t* outConfigs) {
    GET_HWC();

    int32_t ret = hwc->getDisplayConfigs(display, outNumConfigs, outConfigs);

    return ret;
}

int32_t getDisplayName(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outSize, char* outName) {
    GET_HWC();

    int32_t ret = hwc->getDisplayName(display, outSize, outName);

    return ret;
}

int32_t getDisplayRequests(
        hwc2_device_t* device,
        hwc2_display_t display,
        int32_t* outDisplayRequests,
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* outLayerRequests) {
    GET_HWC();

    int32_t ret = hwc->getDisplayRequests(display, outDisplayRequests,
        outNumElements, outLayers, outLayerRequests);

    return ret;
}

int32_t getDisplayType(
        hwc2_device_t* device, hwc2_display_t display,
        int32_t* outType) {
    GET_HWC();

    int32_t ret = hwc->getDisplayType(display, outType);

    return ret;
}

int32_t getDozeSupport(
        hwc2_device_t* device, hwc2_display_t display,
        int32_t* outSupport) {
    GET_HWC();

    int32_t ret = hwc->getDozeSupport(display, outSupport);

    return ret;
}

int32_t getHdrCapabilities(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumTypes, int32_t* /*android_hdr_t*/ outTypes,
        float* outMaxLuminance, float* outMaxAverageLuminance,
        float* outMinLuminance) {
    GET_HWC();

    int32_t ret = hwc->getHdrCapabilities(display, outNumTypes, outTypes,
        outMaxLuminance, outMaxAverageLuminance, outMinLuminance);

    return ret;
}

int32_t getReleaseFences(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* outFences) {
    GET_HWC();

    int32_t ret = hwc->getReleaseFences(display, outNumElements, outLayers, outFences);

    return ret;
}

int32_t presentDisplay(
        hwc2_device_t* device, hwc2_display_t display,
        int32_t* outRetireFence) {
    GET_HWC();

    int32_t ret = hwc->presentDisplay(display, outRetireFence);

    return ret;
}

int32_t setActiveConfig(
        hwc2_device_t* device,
        hwc2_display_t display,
        hwc2_config_t config) {
    GET_HWC();

    int32_t ret = hwc->setActiveConfig(display, config);

    return ret;
}

int32_t setClientTarget(
        hwc2_device_t* device, hwc2_display_t display,
        buffer_handle_t target, int32_t acquireFence,
        android_dataspace_t dataspace, hwc_region_t damage) {
    GET_HWC();

    int32_t ret = hwc->setClientTarget(display, target, acquireFence, dataspace, damage);

    return ret;
}

int32_t setColorMode(
        hwc2_device_t* device, hwc2_display_t display,
        int32_t /*android_color_mode_t*/ mode) {
    GET_HWC();

    int32_t ret = hwc->setColorMode(display, mode);

    return ret;
}

int32_t setColorTransform(
        hwc2_device_t* device, hwc2_display_t display,
        const float* matrix, int32_t /*android_color_transform_t*/ hint) {
    GET_HWC();

    int32_t ret = hwc->setColorTransform(display, matrix, hint);

    return ret;
}

int32_t setOutputBuffer(
        hwc2_device_t* device, hwc2_display_t display,
        buffer_handle_t buffer, int32_t releaseFence) {
    GET_HWC();

    int32_t ret = hwc->setOutputBuffer(display, buffer, releaseFence);

    return ret;
}

int32_t setPowerMode(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_power_mode_t mode) {
    GET_HWC();

    int32_t ret = hwc->setPowerMode(display, mode);

    return ret;
}

int32_t setVsyncEnabled(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_vsync_t enabled) {
    GET_HWC();

    int32_t ret = hwc->setVsyncEnabled(display, enabled);

    return ret;
}

int32_t validateDisplay(
        hwc2_device_t* device, hwc2_display_t display,
        uint32_t* outNumTypes, uint32_t* outNumRequests) {
    GET_HWC();

    int32_t ret = hwc->validateDisplay(display, outNumTypes, outNumRequests);

    return ret;
}

int32_t setCursorPosition(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, int32_t x, int32_t y) {
    GET_HWC();

    int32_t ret = hwc->setCursorPosition(display, layer, x, y);

    return ret;
}

int32_t setLayerBuffer(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, buffer_handle_t buffer,
        int32_t acquireFence) {
    GET_HWC();

    int32_t ret = hwc->setLayerBuffer(display, layer, buffer, acquireFence);

    return ret;
}

int32_t setLayerSurfaceDamage(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_region_t damage) {
    GET_HWC();

    int32_t ret = hwc->setLayerSurfaceDamage(display, layer, damage);

    return ret;
}

/*
 * Layer State Functions
 *
 * These functions modify the state of a given layer. They do not take effect
 * until the display configuration is successfully validated with
 * validateDisplay and the display contents are presented with presentDisplay.
 *
 * All of these functions take as their first three parameters a device pointer,
 * a display handle for the display which contains the layer, and a layer
 * handle, so these parameters are omitted from the described parameter lists.
 */

int32_t setLayerBlendMode(
        hwc2_device_t* device, hwc2_display_t display, hwc2_layer_t layer,
        hwc2_blend_mode_t mode) {
    GET_HWC();

    int32_t ret = hwc->setLayerBlendMode(display, layer, mode);

    return ret;
}

int32_t setLayerColor(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_color_t color) {
    GET_HWC();

    int32_t ret = hwc->setLayerColor(display, layer, color);

    return ret;
}

int32_t setLayerCompositionType(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc2_composition_t type) {
    GET_HWC();

    int32_t ret = hwc->setLayerCompositionType(display, layer, type);

    return ret;
}

int32_t setLayerDataspace(
        hwc2_device_t* device, hwc2_display_t display, hwc2_layer_t layer,
        int32_t /*android_dataspace_t*/ dataspace) {
    GET_HWC();

    int32_t ret = hwc->setLayerDataspace(display, layer, dataspace);

    return ret;
}

int32_t setLayerDisplayFrame(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_rect_t frame) {
    GET_HWC();

    int32_t ret = hwc->setLayerDisplayFrame(display, layer, frame);

    return ret;
}

int32_t setLayerPlaneAlpha(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, float alpha) {
    GET_HWC();

    int32_t ret = hwc->setLayerPlaneAlpha(display, layer, alpha);

    return ret;
}

int32_t setLayerSidebandStream(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, const native_handle_t* stream) {
    GET_HWC();

    int32_t ret = hwc->setLayerSidebandStream(display, layer, stream);

    return ret;
}

int32_t setLayerSourceCrop(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_frect_t crop) {
    GET_HWC();

    int32_t ret = hwc->setLayerSourceCrop(display, layer, crop);

    return ret;
}

int32_t setLayerTransform(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_transform_t transform) {
    GET_HWC();

    int32_t ret = hwc->setLayerTransform(display, layer, transform);

    return ret;
}

int32_t setLayerVisibleRegion(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, hwc_region_t visible) {
    GET_HWC();

    int32_t ret = hwc->setLayerVisibleRegion(display, layer, visible);

    return ret;
}

int32_t setLayerZOrder(
        hwc2_device_t* device, hwc2_display_t display,
        hwc2_layer_t layer, uint32_t z) {
    GET_HWC();

    int32_t ret = hwc->setLayerZOrder(display, layer, z);

    return ret;
}

hwc2_function_pointer_t hwc2_getFunction(struct hwc2_device* device,
        int32_t /*hwc2_function_descriptor_t*/ descriptor) {
    GET_HWC_RETURN_NULL_IF_NULL();

    switch (descriptor) {
        // Device functions
        case HWC2_FUNCTION_CREATE_VIRTUAL_DISPLAY:
            return reinterpret_cast<hwc2_function_pointer_t>(createVirtualDisplay);
        case HWC2_FUNCTION_DESTROY_VIRTUAL_DISPLAY:
            return reinterpret_cast<hwc2_function_pointer_t>(destroyVirtualDisplay);
        case HWC2_FUNCTION_DUMP:
            return reinterpret_cast<hwc2_function_pointer_t>(dump);
        case HWC2_FUNCTION_GET_MAX_VIRTUAL_DISPLAY_COUNT:
            return reinterpret_cast<hwc2_function_pointer_t>(getMaxVirtualDisplayCount);
        case HWC2_FUNCTION_REGISTER_CALLBACK:
            return reinterpret_cast<hwc2_function_pointer_t>(registerCallback);

        // Display functions
        case HWC2_FUNCTION_ACCEPT_DISPLAY_CHANGES:
            return reinterpret_cast<hwc2_function_pointer_t>(acceptDisplayChanges);
        case HWC2_FUNCTION_CREATE_LAYER:
            return reinterpret_cast<hwc2_function_pointer_t>(createLayer);
        case HWC2_FUNCTION_DESTROY_LAYER:
            return reinterpret_cast<hwc2_function_pointer_t>(destroyLayer);
        case HWC2_FUNCTION_GET_ACTIVE_CONFIG:
            return reinterpret_cast<hwc2_function_pointer_t>(getActiveConfig);
        case HWC2_FUNCTION_GET_CHANGED_COMPOSITION_TYPES:
            return reinterpret_cast<hwc2_function_pointer_t>(getChangedCompositionTypes);
        case HWC2_FUNCTION_GET_COLOR_MODES:
            return reinterpret_cast<hwc2_function_pointer_t>(getColorModes);
        case HWC2_FUNCTION_GET_DISPLAY_ATTRIBUTE:
            return reinterpret_cast<hwc2_function_pointer_t>(getDisplayAttribute);
        case HWC2_FUNCTION_GET_DISPLAY_CONFIGS:
            return reinterpret_cast<hwc2_function_pointer_t>(getDisplayConfigs);
        case HWC2_FUNCTION_GET_DISPLAY_NAME:
            return reinterpret_cast<hwc2_function_pointer_t>(getDisplayName);
        case HWC2_FUNCTION_GET_DISPLAY_REQUESTS:
            return reinterpret_cast<hwc2_function_pointer_t>(getDisplayRequests);
        case HWC2_FUNCTION_GET_DISPLAY_TYPE:
            return reinterpret_cast<hwc2_function_pointer_t>(getDisplayType);
        case HWC2_FUNCTION_GET_DOZE_SUPPORT:
            return reinterpret_cast<hwc2_function_pointer_t>(getDozeSupport);
        case HWC2_FUNCTION_GET_HDR_CAPABILITIES:
            return reinterpret_cast<hwc2_function_pointer_t>(getHdrCapabilities);
        case HWC2_FUNCTION_GET_RELEASE_FENCES:
            return reinterpret_cast<hwc2_function_pointer_t>(getReleaseFences);
        case HWC2_FUNCTION_PRESENT_DISPLAY:
            return reinterpret_cast<hwc2_function_pointer_t>(presentDisplay);
        case HWC2_FUNCTION_SET_ACTIVE_CONFIG:
            return reinterpret_cast<hwc2_function_pointer_t>(setActiveConfig);
        case HWC2_FUNCTION_SET_CLIENT_TARGET:
            return reinterpret_cast<hwc2_function_pointer_t>(setClientTarget);
        case HWC2_FUNCTION_SET_COLOR_MODE:
            return reinterpret_cast<hwc2_function_pointer_t>(setColorMode);
        case HWC2_FUNCTION_SET_COLOR_TRANSFORM:
            return reinterpret_cast<hwc2_function_pointer_t>(setColorTransform);
        case HWC2_FUNCTION_SET_OUTPUT_BUFFER:
            return reinterpret_cast<hwc2_function_pointer_t>(setOutputBuffer);
        case HWC2_FUNCTION_SET_POWER_MODE:
            return reinterpret_cast<hwc2_function_pointer_t>(setPowerMode);
        case HWC2_FUNCTION_SET_VSYNC_ENABLED:
            return reinterpret_cast<hwc2_function_pointer_t>(setVsyncEnabled);
        case HWC2_FUNCTION_VALIDATE_DISPLAY:
            return reinterpret_cast<hwc2_function_pointer_t>(validateDisplay);

        // Layer functions
        case HWC2_FUNCTION_SET_CURSOR_POSITION:
            return reinterpret_cast<hwc2_function_pointer_t>(setCursorPosition);
        case HWC2_FUNCTION_SET_LAYER_BUFFER:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerBuffer);
        case HWC2_FUNCTION_SET_LAYER_SURFACE_DAMAGE:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerSurfaceDamage);

        // Layer state functions
        case HWC2_FUNCTION_SET_LAYER_BLEND_MODE:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerBlendMode);
        case HWC2_FUNCTION_SET_LAYER_COLOR:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerColor);
        case HWC2_FUNCTION_SET_LAYER_COMPOSITION_TYPE:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerCompositionType);
        case HWC2_FUNCTION_SET_LAYER_DATASPACE:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerDataspace);
        case HWC2_FUNCTION_SET_LAYER_DISPLAY_FRAME:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerDisplayFrame);
        case HWC2_FUNCTION_SET_LAYER_PLANE_ALPHA:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerPlaneAlpha);
        case HWC2_FUNCTION_SET_LAYER_SIDEBAND_STREAM:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerSidebandStream);
        case HWC2_FUNCTION_SET_LAYER_SOURCE_CROP:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerSourceCrop);
        case HWC2_FUNCTION_SET_LAYER_TRANSFORM:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerTransform);
        case HWC2_FUNCTION_SET_LAYER_VISIBLE_REGION:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerVisibleRegion);
        case HWC2_FUNCTION_SET_LAYER_Z_ORDER:
            return reinterpret_cast<hwc2_function_pointer_t>(setLayerZOrder);
        default:
            ETRACE("getFunction: Unknown function descriptor: %d", descriptor);
            return NULL;
    }
}

void hwc2_getCapabilities(struct hwc2_device* device,
                                uint32_t* outCount,
                                int32_t* /*hwc2_capability_t*/ outCapabilities) {
    GET_HWC_RETURN_VOID_IF_NULL();
    if (NULL == outCapabilities) {
        *outCount = 1;
    } else {
        *outCount = 1;
        outCapabilities[0] = HWC2_CAPABILITY_SIDEBAND_STREAM;
    }
}

//------------------------------------------------------------------------------

static int hwc2_device_open(const struct hw_module_t* module,
                              const char* name,
                              struct hw_device_t** device)
{
    if (!name) {
        ETRACE("invalid name.");
        return -EINVAL;
    }

    ATRACE("open device %s", name);

    if (strcmp(name, HWC_HARDWARE_COMPOSER) != 0) {
        ETRACE("try to open unknown HWComposer %s", name);
        return -EINVAL;
    }

    private_module_t *gralloc_module = NULL;
    if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID,
        (const struct hw_module_t **)&gralloc_module)) {
        ETRACE("failed to get gralloc hw module");
        return -EINVAL;
    }

    Hwcomposer& hwc = Hwcomposer::getInstance();
    // initialize our state here
    if (hwc.initialize(gralloc_module) == false) {
        ETRACE("failed to intialize HWComposer");
        Hwcomposer::releaseInstance();
        return -EINVAL;
    }

    // initialize the procs
    hwc.hwc2_device_t::common.tag = HARDWARE_DEVICE_TAG;
    hwc.hwc2_device_t::common.module =
        const_cast<hw_module_t*>(module);
    hwc.hwc2_device_t::common.close = hwc2_device_close;

    hwc.hwc2_device_t::getFunction = hwc2_getFunction;
    hwc.hwc2_device_t::getCapabilities = hwc2_getCapabilities;
    hwc.hwc2_device_t::common.version = HWC_DEVICE_API_VERSION_2_0;
    *device = &hwc.hwc2_device_t::common;

    return 0;
}

} // namespace amlogic
} // namespace android

typedef struct hwc_module {
    /**
     * Common methods of the hardware composer module.  This *must* be the first member of
     * hwc_module as users of this structure will cast a hw_module_t to
     * hwc_module pointer in contexts where it's known the hw_module_t references a
     * hwc_module.
     */
    struct hw_module_t common;
} hwc_module_t;

static struct hw_module_methods_t hwc2_module_methods = {
    .open = android::amlogic::hwc2_device_open
};

hwc_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 2,
        .version_minor = 0,
        .id = HWC_HARDWARE_MODULE_ID,
        .name = "AML Hardware Composer",
        .author = "aml",
        .methods = &hwc2_module_methods,
        .dso = NULL,
        .reserved = {0},
    }
};
