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

#include <fcntl.h>
#include <inttypes.h>
#include <HwcTrace.h>
#include <PhysicalDevice.h>
#include <Hwcomposer.h>
#include <sys/ioctl.h>
#include <sync/sync.h>
#include <Utils.h>
#include <HwcFenceControl.h>
#include <cutils/properties.h>
#include <AmVideo.h>

namespace android {
namespace amlogic {

PhysicalDevice::PhysicalDevice(hwc2_display_t id, Hwcomposer& hwc, DeviceControlFactory* controlFactory)
    : mId(id),
      mHwc(hwc),
      mControlFactory(controlFactory),
      mVsyncObserver(NULL),
      mConnectorPresent(false),
      mSecure(false),
      mFramebufferHnd(NULL),
      mSystemControl(NULL),
      mFbSlot(0),
      mComposer(NULL),
      mPriorFrameRetireFence(-1),
      mClientTargetHnd(NULL),
      mTargetAcquireFence(-1),
      mRenderMode(GLES_COMPOSE_MODE),
      mPreviousRenderMode(GLES_COMPOSE_MODE),
      mIsValidated(false),
      mIsContinuousBuf(true),
      mDirectRenderLayerId(0),
      mVideoOverlayLayerId(0),
      mGE2DClearVideoRegionCount(0),
      mGE2DComposeFrameCount(0),
      mDirectComposeFrameCount(0),
      mBootanimStatus(0),
      mInitialized(false),
      mVideoLayerOpenByOMX(false) {
    CTRACE();

    switch (id) {
    case DEVICE_PRIMARY:
        mName = "Primary";
        break;
    case DEVICE_EXTERNAL:
        mName = "External";
        break;
    default:
        mName = "Unknown";
    }

    mHdrCapabilities.init = false;

    // clear layers vectors.
    mHwcSecureLayers.clear();
    mHwcLayersChangeType.clear();
    mHwcLayersChangeRequest.clear();
    mHwcGlesLayers.clear();
    mHwcLayers.clear();
    mGE2DRenderSortedLayerIds.clear();

    mHwcCurReleaseFences = mHwcPriorReleaseFences = NULL;
    mOmxKeepLastFrame = 0;
    AmVideo::getInstance()->getOmxKeepLastFrame(&mOmxKeepLastFrame);
}

PhysicalDevice::~PhysicalDevice() {
    WARN_IF_NOT_DEINIT();
    clearFenceList(mHwcCurReleaseFences);
    clearFenceList(mHwcPriorReleaseFences);
}

bool PhysicalDevice::initialize() {
    CTRACE();

    if (mId != DEVICE_PRIMARY && mId != DEVICE_EXTERNAL) {
        ETRACE("invalid device type");
        return false;
    }

    // init Display here.
    initDisplay();

    // create vsync event observer, we only have soft vsync now...
    mVsyncObserver = new SoftVsyncObserver(*this);
    if (!mVsyncObserver || !mVsyncObserver->initialize()) {
        DEINIT_AND_RETURN_FALSE("failed to create vsync observer");
    }

    UeventObserver *observer = Hwcomposer::getInstance().getUeventObserver();
    if (observer) {
        observer->registerListener(
            Utils::getHdcpUeventEnvelope(),
            hdcpEventListener,
            this);
    } else {
        ETRACE("PhysicalDevice::Uevent observer is NULL");
    }

    mDisplayHdmi = new DisplayHdmi();
    mDisplayHdmi->initialize(*(mFramebufferContext->getInfo()));
    if (mDisplayHdmi->chkPresent()) {
        updateHotplugState(true);
        updateDisplayConfigs();
    }

    mInitialized = true;
    return true;
}

void PhysicalDevice::hdcpEventListener(void *data, bool status) {
    PhysicalDevice *pThis = (PhysicalDevice*)data;
    if (pThis) {
        pThis->setSecureStatus(status);
    }
}

void PhysicalDevice::setSecureStatus(bool status) {
    DTRACE("hdcp event: %d", status);
    mSecure = status;
}

void PhysicalDevice::deinitialize() {
    Mutex::Autolock _l(mLock);

    DEINIT_AND_DELETE_OBJ(mVsyncObserver);
    DEINIT_AND_DELETE_OBJ(mDisplayHdmi);
    DEINIT_AND_DELETE_OBJ(mComposer);

    if (mFramebufferContext != NULL) {
        delete mFramebufferContext;
        mFramebufferContext = NULL;
    }

    if (mCursorContext != NULL) {
        delete mCursorContext;
        mCursorContext = NULL;
    }

    mInitialized = false;
}

HwcLayer* PhysicalDevice::getLayerById(hwc2_layer_t layerId) {
    HwcLayer* layer = NULL;
    ssize_t index = mHwcLayers.indexOfKey(layerId);

    if (index >= 0) {
        layer = mHwcLayers.valueFor(layerId);
    }

    if (!layer) {
        DTRACE("getLayerById %lld error!", layerId);
    }
    return layer;
}

int32_t PhysicalDevice::acceptDisplayChanges() {
    HwcLayer* layer = NULL;

    for (uint32_t i=0; i<mHwcLayersChangeType.size(); i++) {
        hwc2_layer_t layerId = mHwcLayersChangeType.keyAt(i);
        layer = mHwcLayersChangeType.valueAt(i);
        if (layer) {
            // deal non secure display.
            if (!mSecure && !mHwcSecureLayers.isEmpty()) {
                for (uint32_t j=0; j<mHwcSecureLayers.size(); j++) {
                    hwc2_layer_t secureLayerId = mHwcSecureLayers.keyAt(j);
                    HwcLayer* secureLayer = mHwcSecureLayers.valueAt(j);
                    // deal secure layers release fence and composition type on non secure display.
                    addReleaseFence(secureLayerId, secureLayer->getDuppedAcquireFence());
                    if (layerId == secureLayerId) {
                        if (layer->getCompositionType() != HWC2_COMPOSITION_DEVICE) {
                            layer->setCompositionType(HWC2_COMPOSITION_DEVICE);
                            continue;
                        }
                    }
                }
            }
            if (layer->getCompositionType() == HWC2_COMPOSITION_DEVICE
                    || layer->getCompositionType() == HWC2_COMPOSITION_SOLID_COLOR) {
                layer->setCompositionType(HWC2_COMPOSITION_CLIENT);
            } else if (layer->getCompositionType() == HWC2_COMPOSITION_SIDEBAND) {
                layer->setCompositionType(HWC2_COMPOSITION_DEVICE);
            }
        }
    }

    return HWC2_ERROR_NONE;
}

bool PhysicalDevice::createLayer(hwc2_layer_t* outLayer) {
    HwcLayer* layer = new HwcLayer(mId);

    if (layer == NULL || !layer->initialize()) {
        ETRACE("createLayer: failed !");
        return false;
    }

    hwc2_layer_t layerId = reinterpret_cast<hwc2_layer_t>(layer);
    mHwcLayers.add(layerId, layer);
    *outLayer = layerId;
    DTRACE("::createLayer layerId (%lld), size: [%d].\n", layerId, mHwcLayers.size());

    return true;
}

bool PhysicalDevice::destroyLayer(hwc2_layer_t layerId) {
    HwcLayer* layer = mHwcLayers.valueFor(layerId);
    DTRACE("::destroyLayer layerId %lld, size: [%d].\n", layerId, mHwcLayers.size());

    if (layer == NULL) {
        ETRACE("destroyLayer: no Hwclayer found (%d)", layerId);
        return false;
    }

    for (int i = 0; i < 2; i++) {
        ssize_t idx = mLayerReleaseFences[i].indexOfKey(layerId);
        if (idx >= 0) {
            HwcFenceControl::closeFd(mLayerReleaseFences[i].valueAt(idx));
            mLayerReleaseFences[i].removeItemsAt(idx);
            DTRACE("destroyLayer layer(%lld) from cur release list (%p).\n", layerId, &(mLayerReleaseFences[i]));
        }
    }

    mHwcLayers.removeItem(layerId);
    DEINIT_AND_DELETE_OBJ(layer);
    return true;
}

int32_t PhysicalDevice::getActiveConfig(
    hwc2_config_t* outConfig) {
    Mutex::Autolock _l(mLock);

    return mDisplayHdmi->getActiveConfig(outConfig);
}

int32_t PhysicalDevice::getChangedCompositionTypes(
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
                // deal non secure display.
                if (!mSecure && !mHwcSecureLayers.isEmpty()) {
                    for (uint32_t j=0; j<mHwcSecureLayers.size(); j++) {
                        hwc2_layer_t secureLayerId = mHwcSecureLayers.keyAt(j);
                        if (layerId == secureLayerId) {
                            if (layer->getCompositionType() != HWC2_COMPOSITION_DEVICE) {
                                outLayers[i] = layerId;
                                outTypes[i] = HWC2_COMPOSITION_DEVICE;
                                continue;
                            }
                        }
                    }
                }

                if (layer->getCompositionType() == HWC2_COMPOSITION_DEVICE
                    || layer->getCompositionType() == HWC2_COMPOSITION_SOLID_COLOR) {
                    // change all other device type to client.
                    outLayers[i] = layerId;
                    outTypes[i] = HWC2_COMPOSITION_CLIENT;
                    continue;
                }

                // sideband stream.
                if (layer->getCompositionType() == HWC2_COMPOSITION_SIDEBAND
                    && layer->getSidebandStream()) {
                    // TODO: we just transact SIDEBAND to OVERLAY for now;
                    DTRACE("get HWC_SIDEBAND layer, just change to overlay");
                    outLayers[i] = layerId;
                    outTypes[i] = HWC2_COMPOSITION_DEVICE;
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

int32_t PhysicalDevice::getClientTargetSupport(
    uint32_t width,
    uint32_t height,
    int32_t /*android_pixel_format_t*/ format,
    int32_t /*android_dataspace_t*/ dataspace) {
    framebuffer_info_t* fbInfo = mFramebufferContext->getInfo();

    if (width == fbInfo->info.xres
        && height == fbInfo->info.yres
        && format == HAL_PIXEL_FORMAT_RGBA_8888
        && dataspace == HAL_DATASPACE_UNKNOWN) {
        return HWC2_ERROR_NONE;
    }

    DTRACE("fbinfo: [%d x %d], client: [%d x %d]"
        "format: %d, dataspace: %d",
        fbInfo->info.xres,
        fbInfo->info.yres,
        width, height, format, dataspace);

    // TODO: ?
    return HWC2_ERROR_UNSUPPORTED;
}

int32_t PhysicalDevice::getColorModes(
    uint32_t* outNumModes,
    int32_t* /*android_color_mode_t*/ outModes) {

    if (NULL == outModes) {
        *outNumModes = 1;
    } else {
        *outModes = HAL_COLOR_MODE_NATIVE;
    }

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getDisplayAttribute(
        hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute,
        int32_t* outValue) {
    Mutex::Autolock _l(mLock);

    if (!mConnectorPresent) {
        ETRACE("display %d is not connected.", mId);
    }

    int ret = mDisplayHdmi->getDisplayAttribute(config, attribute, outValue);
    if (ret < 0)
        return HWC2_ERROR_BAD_CONFIG;

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getDisplayConfigs(
        uint32_t* outNumConfigs,
        hwc2_config_t* outConfigs) {
    Mutex::Autolock _l(mLock);

    return mDisplayHdmi->getDisplayConfigs(outNumConfigs, outConfigs);
}

int32_t PhysicalDevice::getDisplayName(
    uint32_t* outSize,
    char* outName) {
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getDisplayRequests(
    int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
    uint32_t* outNumElements,
    hwc2_layer_t* outLayers,
    int32_t* /*hwc2_layer_request_t*/ outLayerRequests) {

    // if outLayers or outTypes were NULL, the number of layers and types which would have been returned.
    if (NULL == outLayers || NULL == outLayerRequests) {
        *outNumElements = mHwcLayersChangeRequest.size();
    } else {
        for (uint32_t i=0; i<mHwcLayersChangeRequest.size(); i++) {
            hwc2_layer_t layerId = mHwcLayersChangeRequest.keyAt(i);
            HwcLayer *layer = mHwcLayersChangeRequest.valueAt(i);
            if (layer->getCompositionType() == HWC2_COMPOSITION_DEVICE) {
                // video overlay.
                if (layerId == mVideoOverlayLayerId) {
                    outLayers[i] = layerId;
                    outLayerRequests[i] = HWC2_LAYER_REQUEST_CLEAR_CLIENT_TARGET;
                }
                /* if (layer->getBufferHandle()) {
                    private_handle_t const* hnd =
                        private_handle_t::dynamicCast(layer->getBufferHandle());
                    if (hnd->flags & private_handle_t::PRIV_FLAGS_VIDEO_OVERLAY) {
                        outLayers[i] = layerId;
                        outLayerRequests[i] = HWC2_LAYER_REQUEST_CLEAR_CLIENT_TARGET;
                        continue;
                    }
                } */
            }

            // sideband stream.
            if ((layer->getCompositionType() == HWC2_COMPOSITION_SIDEBAND && layer->getSidebandStream())
                || layer->getCompositionType() == HWC2_COMPOSITION_CURSOR) {
                // TODO: we just transact SIDEBAND to OVERLAY for now;
                DTRACE("get HWC_SIDEBAND layer, just change to overlay");
                outLayers[i] = layerId;
                outLayerRequests[i] = HWC2_LAYER_REQUEST_CLEAR_CLIENT_TARGET;
                continue;
            }
        }

        if (mHwcLayersChangeRequest.size() > 0) {
            DTRACE("There are %d layer requests.", mHwcLayersChangeRequest.size());
            *outNumElements = mHwcLayersChangeRequest.size();
        } else {
            DTRACE("No layer requests.");
        }
    }

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getDisplayType(
    int32_t* /*hwc2_display_type_t*/ outType) {

    *outType = HWC2_DISPLAY_TYPE_PHYSICAL;
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getDozeSupport(
    int32_t* outSupport) {
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::getHdrCapabilities(
        uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes,
        float* outMaxLuminance,
        float* outMaxAverageLuminance,
        float* outMinLuminance) {

    Mutex::Autolock _l(mLock);
    if (!mConnectorPresent) {
        ETRACE("disp: %llu is not connected", mId);
        return HWC2_ERROR_BAD_DISPLAY;
    }

    if (!mHdrCapabilities.init) {
        ETRACE("HDRCapability not updated.");
    }

    if (NULL == outTypes) {
        int num = 0;
        if (mHdrCapabilities.dvSupport) num++;
        if (mHdrCapabilities.hdrSupport) num++;

        *outNumTypes = num;
    } else {
        if (mHdrCapabilities.dvSupport) *outTypes++ = HAL_HDR_DOLBY_VISION;
        if (mHdrCapabilities.hdrSupport) *outTypes++ = HAL_HDR_HDR10;

        *outMaxLuminance = mHdrCapabilities.maxLuminance;
        *outMaxAverageLuminance = mHdrCapabilities.avgLuminance;
        *outMinLuminance = mHdrCapabilities.minLuminance;
    }

    return HWC2_ERROR_NONE;
}

void PhysicalDevice::swapReleaseFence() {
    //dumpFenceList(mHwcCurReleaseFences);

    if (mHwcCurReleaseFences == NULL || mHwcPriorReleaseFences == NULL) {
        if (mHwcCurReleaseFences) {
            clearFenceList(mHwcPriorReleaseFences);
        }

        if (mHwcPriorReleaseFences) {
            clearFenceList(mHwcPriorReleaseFences);
        }

        mHwcCurReleaseFences = &(mLayerReleaseFences[0]);
        mHwcPriorReleaseFences = &(mLayerReleaseFences[1]);
    } else {
        KeyedVector<hwc2_layer_t, int32_t> * tmp =  mHwcCurReleaseFences;
        clearFenceList(mHwcPriorReleaseFences);
        mHwcCurReleaseFences = mHwcPriorReleaseFences;
        mHwcPriorReleaseFences = tmp;
    }
}

void PhysicalDevice::addReleaseFence(hwc2_layer_t layerId, int32_t fenceFd) {
    ssize_t idx = mHwcCurReleaseFences->indexOfKey(layerId);
    if (idx >= 0 && idx < mHwcCurReleaseFences->size()) {
        int32_t oldFence = mHwcCurReleaseFences->valueAt(idx);
        String8 mergeName("hwc-release");
        int32_t newFence = HwcFenceControl::merge(mergeName, oldFence, fenceFd);
        mHwcCurReleaseFences->replaceValueAt(idx, newFence);
        HwcFenceControl::closeFd(oldFence);
        HwcFenceControl::closeFd(fenceFd);
        DTRACE("addReleaseFence:(%d, %d) + %d -> (%d,%d)\n", idx, oldFence, fenceFd, idx, newFence);
        dumpFenceList(mHwcCurReleaseFences);
    } else {
        mHwcCurReleaseFences->add(layerId, fenceFd);
    }
}

void PhysicalDevice::clearFenceList(KeyedVector<hwc2_layer_t, int32_t> * fenceList) {
    if (!fenceList || !fenceList->size())
        return;

    for (int i = 0; i < fenceList->size(); i++) {
        int32_t fenceFd = fenceList->valueAt(i);
        HwcFenceControl::closeFd(fenceFd);
        DTRACE("clearFenceList close fd %d\n", fenceFd);
        fenceList->replaceValueAt(i, -1);
    }
    fenceList->clear();
}

void PhysicalDevice::dumpFenceList(KeyedVector<hwc2_layer_t, int32_t> * fenceList) {
    if (!fenceList || fenceList->isEmpty())
        return;

    String8 resultStr("dumpFenceList: ");
    for (int i = 0; i < fenceList->size(); i++) {
        hwc2_layer_t layerId = fenceList->keyAt(i);
        int32_t fenceFd = fenceList->valueAt(i);
        resultStr.appendFormat("(%lld, %d), ", layerId, fenceFd);
    }

    ETRACE("%s", resultStr.string());
}

int32_t PhysicalDevice::getReleaseFences(
        uint32_t* outNumElements,
        hwc2_layer_t* outLayers,
        int32_t* outFences) {
    *outNumElements = mHwcPriorReleaseFences->size();

    if (outLayers && outFences) {
        for (uint32_t i=0; i<mHwcPriorReleaseFences->size(); i++) {
            outLayers[i] = mHwcPriorReleaseFences->keyAt(i);
            outFences[i] = HwcFenceControl::dupFence(mHwcPriorReleaseFences->valueAt(i));
        }
    }

    return HWC2_ERROR_NONE;
}

void PhysicalDevice::directCompose(framebuffer_info_t * fbInfo) {
    HwcLayer* layer = NULL;
    ssize_t idx = mHwcLayers.indexOfKey(mDirectRenderLayerId);
    if (idx >= 0) {
        layer = mHwcLayers.valueAt(idx);
        if (mTargetAcquireFence > -1) {
            ETRACE("ERROR:directCompose with mTargetAcquireFence %d\n", mTargetAcquireFence);
            HwcFenceControl::closeFd(mTargetAcquireFence);
        }

        mTargetAcquireFence = layer->getDuppedAcquireFence();
        mClientTargetHnd = layer->getBufferHandle();
        DTRACE("Hit only one non video overlay layer, handle: %08" PRIxPTR ", fence: %d",
            intptr_t(mClientTargetHnd), mTargetAcquireFence);

        // fill up fb sync request struct.
        hwc_frect_t srcCrop = layer->getSourceCrop();
        hwc_rect_t displayFrame = layer->getDisplayFrame();
        mFbSyncRequest.xoffset = (unsigned int)srcCrop.left;
        mFbSyncRequest.yoffset = (unsigned int)srcCrop.top;
        mFbSyncRequest.width = (unsigned int)(srcCrop.right - srcCrop.left);
        mFbSyncRequest.height = (unsigned int)(srcCrop.bottom - srcCrop.top);
        mFbSyncRequest.dst_x = displayFrame.left;
        mFbSyncRequest.dst_y = displayFrame.top;
        mFbSyncRequest.dst_w = displayFrame.right - displayFrame.left;
        mFbSyncRequest.dst_h = displayFrame.bottom - displayFrame.top;
        return;
    }

    ETRACE("Didn't find direct compose layer!");
}

#ifdef ENABLE_AML_GE2D_COMPOSER
void PhysicalDevice::ge2dCompose(framebuffer_info_t * fbInfo, bool hasVideoOverlay) {
    if (mGE2DRenderSortedLayerIds.size() > 0) {
        DTRACE("GE2D compose mFbSlot: %d", mFbSlot);
        if (hasVideoOverlay) {
            if (mGE2DClearVideoRegionCount < 3) {
                mComposer->setVideoOverlayLayerId(mVideoOverlayLayerId);
            }
        }
        if (mTargetAcquireFence > -1) {
            ETRACE("ERROR:GE2D compose with mTargetAcquireFence %d\n", mTargetAcquireFence);
            HwcFenceControl::closeFd(mTargetAcquireFence);
        }
        mTargetAcquireFence = mComposer->startCompose(mGE2DRenderSortedLayerIds, &mFbSlot, mGE2DComposeFrameCount);
        for (uint32_t i=0; i<mGE2DRenderSortedLayerIds.size(); i++) {
            addReleaseFence(mGE2DRenderSortedLayerIds.itemAt(i), HwcFenceControl::dupFence(mTargetAcquireFence));
        }
        // HwcFenceControl::traceFenceInfo(mTargetAcquireFence);
        // dumpLayers(mGE2DRenderSortedLayerIds);
        if (mGE2DComposeFrameCount < 3) {
            mGE2DComposeFrameCount++;
        }
        mClientTargetHnd = mComposer->getBufHnd();
        fbInfo->yOffset = mFbSlot;
        return;
    }

    ETRACE("Didn't find ge2d compose layers!");
}
#endif

int32_t PhysicalDevice::postFramebuffer(int32_t* outRetireFence, bool hasVideoOverlay) {
    HwcLayer* layer = NULL;
    void *cbuffer;

    // deal physical display's client target layer
    framebuffer_info_t fbInfo = *(mFramebufferContext->getInfo());
    framebuffer_info_t* cbInfo = mCursorContext->getInfo();
    bool cursorShow = false;
    bool haveCursorLayer = false;
    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (layer && layer->getCompositionType()== HWC2_COMPOSITION_CURSOR) {
            private_handle_t *hnd = private_handle_t::dynamicCast(layer->getBufferHandle());
            if (!hnd) {
                ETRACE("invalid cursor layer handle.");
                break;
            }
            haveCursorLayer = true;
            DTRACE("This is a Sprite, hnd->stride is %d, hnd->height is %d", hnd->stride, hnd->height);
            if (cbInfo->info.xres != (uint32_t)hnd->stride || cbInfo->info.yres != (uint32_t)hnd->height) {
                DTRACE("disp: %d cursor need to redrew", mId);
                update_cursor_buffer_locked(cbInfo, hnd->stride, hnd->height);
                cbuffer = mmap(NULL, hnd->size, PROT_READ|PROT_WRITE, MAP_SHARED, cbInfo->fd, 0);
                if (cbuffer != MAP_FAILED) {
                    memcpy(cbuffer, hnd->base, hnd->size);
                    munmap(cbuffer, hnd->size);
                    DTRACE("setCursor ok");
                } else {
                   ETRACE("Cursor display buffer mmap fail!");
                }
            }
            cursorShow = true;
            break;
        }
    }

    if (mRenderMode == GLES_COMPOSE_MODE) {
        //if no layers to compose, post blank op to osd.
        if (mPreviousRenderMode != GLES_COMPOSE_MODE && mHwcGlesLayers.size() == 0) {
            mClientTargetHnd = NULL;
        }
    } else if (mRenderMode == DIRECT_COMPOSE_MODE) { // if only one layer exists, let hwc do her work.
        directCompose(&fbInfo);
    }
#ifdef ENABLE_AML_GE2D_COMPOSER
    else if (mRenderMode == GE2D_COMPOSE_MODE) {
        ge2dCompose(&fbInfo, hasVideoOverlay);
    }
#endif
    mFbSyncRequest.type = mRenderMode;

    if (mBootanimStatus == 0 && mSystemControl != NULL) {
        mSystemControl->getBootanimStatus(mBootanimStatus);
        if (mBootanimStatus == 0) {
            HwcFenceControl::wait(mTargetAcquireFence, 3000);
            *outRetireFence = -1;
            return HWC2_ERROR_NONE;
        }
    }

    if (!mClientTargetHnd || private_handle_t::validate(mClientTargetHnd) < 0 || mPowerMode == HWC2_POWER_MODE_OFF) {
        DTRACE("Post blank to screen, mClientTargetHnd(%p, %d), mTargetAcquireFence(%d)",
                    mClientTargetHnd, private_handle_t::validate(mClientTargetHnd), mTargetAcquireFence);
        *outRetireFence = HwcFenceControl::merge(String8("ScreenBlank"), mPriorFrameRetireFence, mPriorFrameRetireFence);
        HwcFenceControl::closeFd(mTargetAcquireFence);
        mTargetAcquireFence = -1;
        HwcFenceControl::closeFd(mPriorFrameRetireFence);
        mPriorFrameRetireFence = -1;
        //for nothing to display, post blank to osd which will signal the last retire fence.
        mFbSyncRequest.type = DIRECT_COMPOSE_MODE;
        mFbSyncRequest.op |= OSD_BLANK_OP_BIT;
        mFramebufferContext->setStatus(true);
        mPriorFrameRetireFence = hwc_fb_post_with_fence_locked(&fbInfo, &mFbSyncRequest, NULL);
     } else {
        *outRetireFence = HwcFenceControl::dupFence(mPriorFrameRetireFence);
        if (*outRetireFence >= 0) {
            DTRACE("Get prior frame's retire fence %d", *outRetireFence);
        } else {
            ETRACE("No valid prior frame's retire returned. %d ", *outRetireFence);
            // -1 means no fence, less than -1 is some error
            *outRetireFence = -1;
        }
        HwcFenceControl::closeFd(mPriorFrameRetireFence);
        mPriorFrameRetireFence = -1;

        bool needBlankFb0 = false;
        uint32_t layerNum = mHwcLayers.size();
        if (hasVideoOverlay
            && (layerNum == 1
            || (layerNum == 2
            && haveCursorLayer))) {
            needBlankFb0 = true;
        }
        // real post framebuffer here.
        DTRACE("render type: %d", mFbSyncRequest.type);
        if (!mIsContinuousBuf) {
            setOSD0Blank(needBlankFb0);
            mPriorFrameRetireFence = fb_post_with_fence_locked(&fbInfo, mClientTargetHnd, mTargetAcquireFence);
        } else {
            // bit 0 is osd blank flag.
            if (needBlankFb0) {
                mFbSyncRequest.op |= OSD_BLANK_OP_BIT;
            } else {
                mFbSyncRequest.op &= ~(OSD_BLANK_OP_BIT);
            }
            mFramebufferContext->setStatus(needBlankFb0);
            // acquire fence.
            mFbSyncRequest.in_fen_fd = mTargetAcquireFence;
            mPriorFrameRetireFence = hwc_fb_post_with_fence_locked(&fbInfo, &mFbSyncRequest, mClientTargetHnd);
        }
        mTargetAcquireFence = -1;

        if (mRenderMode == GE2D_COMPOSE_MODE) {
            mComposer->mergeRetireFence(mFbSlot, HwcFenceControl::dupFence(mPriorFrameRetireFence));
        } else {
            if (mComposer && mGE2DComposeFrameCount != 0) {
                mComposer->removeRetireFence(mFbSlot);
            }

            if (mRenderMode == DIRECT_COMPOSE_MODE) {
                addReleaseFence(mDirectRenderLayerId, HwcFenceControl::dupFence(mPriorFrameRetireFence));
            }
        }

        // finally we need to update cursor's blank status.
        if (cbInfo->fd > 0 && cursorShow != mCursorContext->getStatus()) {
            mCursorContext->setStatus(cursorShow);
            DTRACE("UPDATE FB1 status to %d", !cursorShow);
            ioctl(cbInfo->fd, FBIOBLANK, !cursorShow);
        }
    }

    if (mRenderMode != GE2D_COMPOSE_MODE) {
        mGE2DComposeFrameCount = 0;
    }

    return HWC2_ERROR_NONE;
}

// TODO: need add fence wait.
int32_t PhysicalDevice::setOSD0Blank(bool blank) {
    framebuffer_info_t* fbInfo = mFramebufferContext->getInfo();

    if (fbInfo->fd > 0 && blank != mFramebufferContext->getStatus()) {
        mFramebufferContext->setStatus(blank);
        DTRACE("UPDATE FB0 status to %d", blank);
        ioctl(fbInfo->fd, FBIOBLANK, blank);
    }

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::presentDisplay(
        int32_t* outRetireFence) {
    int32_t err = HWC2_ERROR_NONE;
    HwcLayer* layer = NULL;
    bool hasVideoOverlay = false;

    if (mIsValidated) {
        // TODO: need improve the way to set video axis.
#if WITH_LIBPLAYER_MODULE
        bool bPresent = true;
        if (mHwcSecureLayers.indexOfKey(mVideoOverlayLayerId) >= 0) {
            bPresent = false;
        }

        ssize_t index = mHwcLayers.indexOfKey(mVideoOverlayLayerId);
        if (index >= 0) {
            layer = mHwcLayers.valueFor(mVideoOverlayLayerId);
            if (layer != NULL) {
                layer->presentOverlay(bPresent);
                hasVideoOverlay = true;
                if (mGE2DClearVideoRegionCount < 3) {
                    mGE2DClearVideoRegionCount++;
                }
            }
        } else {
            mGE2DClearVideoRegionCount = 0;
        }
#endif
        err = postFramebuffer(outRetireFence, hasVideoOverlay);
    } else { // display not validate yet.
        err = HWC2_ERROR_NOT_VALIDATED;
    }

    finishCompose();
    return err;
}

int32_t PhysicalDevice::setActiveConfig(
    hwc2_config_t config) {
    Mutex::Autolock _l(mLock);

    int32_t err = mDisplayHdmi->setActiveConfig(config);
    if (err == HWC2_ERROR_NONE) {
        updateActiveDisplayAttribute();
    }

    return err;
}

int32_t PhysicalDevice::setClientTarget(
        buffer_handle_t target,
        int32_t acquireFence,
        int32_t /*android_dataspace_t*/ dataspace,
        hwc_region_t damage) {

    if (target && private_handle_t::validate(target) < 0) {
        return HWC2_ERROR_BAD_PARAMETER;
    }

    if (NULL != target) {
        mClientTargetHnd = target;
        mClientTargetDamageRegion = damage;
        mTargetAcquireFence = acquireFence;
        DTRACE("setClientTarget %p, %d", target, acquireFence);
        // TODO: HWC2_ERROR_BAD_PARAMETER && dataspace && damage.
    } else {
        DTRACE("client target is null!, no need to update this frame.");
    }

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::setColorMode(
    int32_t /*android_color_mode_t*/ mode) {
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::setColorTransform(
    const float* matrix,
    int32_t /*android_color_transform_t*/ hint) {
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::setPowerMode(
    int32_t /*hwc2_power_mode_t*/ mode){

    mPowerMode = mode;
    return HWC2_ERROR_NONE;
}

bool PhysicalDevice::vsyncControl(bool enabled) {
    RETURN_FALSE_IF_NOT_INIT();

    ATRACE("disp = %d, enabled = %d", mId, enabled);
    return mVsyncObserver->control(enabled);
}

void PhysicalDevice::dumpLayers(Vector < hwc2_layer_t > layerIds) {
    for (uint32_t x=0; x<layerIds.size(); x++) {
        HwcLayer* layer = getLayerById(layerIds.itemAt(x));
        static char const* compositionTypeName[] = {
                                    "UNKNOWN",
                                    "GLES",
                                    "HWC",
                                    "SOLID",
                                    "HWC_CURSOR",
                                    "SIDEBAND"};
        ETRACE("   %11s | %12" PRIxPTR " | %10d | %02x | %1.2f | %02x | %04x |%7.1f,%7.1f,%7.1f,%7.1f |%5d,%5d,%5d,%5d \n",
                        compositionTypeName[layer->getCompositionType()],
                        intptr_t(layer->getBufferHandle()), layer->getZ(), layer->getDataspace(),
                        layer->getPlaneAlpha(), layer->getTransform(), layer->getBlendMode(),
                        layer->getSourceCrop().left, layer->getSourceCrop().top, layer->getSourceCrop().right, layer->getSourceCrop().bottom,
                        layer->getDisplayFrame().left, layer->getDisplayFrame().top, layer->getDisplayFrame().right, layer->getDisplayFrame().bottom);
    }
}

void PhysicalDevice::dumpLayers(KeyedVector<hwc2_layer_t, HwcLayer*> layers) {
    for (uint32_t x=0; x<layers.size(); x++) {
        HwcLayer* layer = layers.valueAt(x);
        static char const* compositionTypeName[] = {
                                    "UNKNOWN",
                                    "GLES",
                                    "HWC",
                                    "SOLID",
                                    "HWC_CURSOR",
                                    "SIDEBAND"};
        ETRACE("   %11s | %12" PRIxPTR " | %10d | %02x | %1.2f | %02x | %04x |%7.1f,%7.1f,%7.1f,%7.1f |%5d,%5d,%5d,%5d \n",
                        compositionTypeName[layer->getCompositionType()],
                        intptr_t(layer->getBufferHandle()), layer->getZ(), layer->getDataspace(),
                        layer->getPlaneAlpha(), layer->getTransform(), layer->getBlendMode(),
                        layer->getSourceCrop().left, layer->getSourceCrop().top, layer->getSourceCrop().right, layer->getSourceCrop().bottom,
                        layer->getDisplayFrame().left, layer->getDisplayFrame().top, layer->getDisplayFrame().right, layer->getDisplayFrame().bottom);
    }
}

bool PhysicalDevice::layersStateCheck(int32_t renderMode,
        KeyedVector<hwc2_layer_t, HwcLayer*> & composeLayers) {
    bool ret = false;
    uint32_t layerNum = composeLayers.size();
    hwc_frect_t sourceCrop[HWC2_MAX_LAYERS];
    HwcLayer* layer[HWC2_MAX_LAYERS] = { NULL };
    private_handle_t const* hnd[HWC2_MAX_LAYERS] = { NULL };
    hwc_rect_t displayFrame[HWC2_MAX_LAYERS];

    for (int32_t i=0; i<layerNum; i++) {
        layer[i] = composeLayers.valueAt(i);
        sourceCrop[i] = layer[i]->getSourceCrop();
        displayFrame[i] = layer[i]->getDisplayFrame();
        hnd[i] = private_handle_t::dynamicCast(layer[i]->getBufferHandle());
        if (hnd[i] == NULL) return false; // no buffer to process.
        if (hnd[i]->share_fd == -1) return false; // no buffer to process.
        if ((sourceCrop[i].right - sourceCrop[i].left > HWC2_HW_COMPOSE_WIDTH_MAX) ||
            (sourceCrop[i].bottom - sourceCrop[i].top > HWC2_HW_COMPOSE_HEIGHT_MAX)) {
            return false;
        }
        DTRACE("layer[%d] zorder: %d, blend: %d, PlaneAlpha: %f, "
            "mColor: [%d, %d, %d, %d], mDataSpace: %d, format hnd[%d]: %x",
            i, layer[i]->getZ(), layer[i]->getBlendMode(), layer[i]->getPlaneAlpha(),
            layer[i]->getColor().r, layer[i]->getColor().g, layer[i]->getColor().b,
            layer[i]->getColor().a, layer[i]->getDataspace(), i, hnd[i]->format);
    }

    if (renderMode == DIRECT_COMPOSE_MODE) {
        switch (hnd[0]->format) {
            case HAL_PIXEL_FORMAT_RGBA_8888:
            case HAL_PIXEL_FORMAT_RGBX_8888:
            case HAL_PIXEL_FORMAT_RGB_888:
            case HAL_PIXEL_FORMAT_RGB_565:
            case HAL_PIXEL_FORMAT_BGRA_8888:
                DTRACE("Layer format match direct composer.");
                ret = true;
            break;
            default:
                DTRACE("Layer format not support by direct compose");
                return false;
            break;
        }
        if (layer[0]->getTransform() != 0) {
            //DTRACE("Direct composer can NOT support rotation now.");
            return false;
        }
    }
#ifdef ENABLE_AML_GE2D_COMPOSER
    else if (renderMode == GE2D_COMPOSE_MODE) {
        bool yuv420Sp = false;
        for (int32_t i=0; i<layerNum; i++) {
            switch (hnd[i]->format) {
                case HAL_PIXEL_FORMAT_YCrCb_420_SP:
                    yuv420Sp = true;
                case HAL_PIXEL_FORMAT_RGBA_8888:
                case HAL_PIXEL_FORMAT_RGBX_8888:
                case HAL_PIXEL_FORMAT_RGB_888:
                case HAL_PIXEL_FORMAT_RGB_565:
                case HAL_PIXEL_FORMAT_BGRA_8888:
                case HAL_PIXEL_FORMAT_YV12:
                case HAL_PIXEL_FORMAT_Y8:
                case HAL_PIXEL_FORMAT_YCbCr_422_SP:
                case HAL_PIXEL_FORMAT_YCbCr_422_I:
                    DTRACE("Layer format match ge2d composer.");
                    ret = true;
                break;
                default:
                    DTRACE("Layer format not support by ge2d");
                    return false;
                break;
            }
            if (layer[i]->havePlaneAlpha()
                || layer[i]->haveColor()
                || layer[i]->haveDataspace()
                || (layer[i]->isBlended()
                && layer[i]->isScaled())) {
                DTRACE("ge2d compose can not process!");
                return false;
            }
        }
#if 0
        if (yuv420Sp && HWC2_TWO_LAYERS == layerNum) {
            if (Utils::compareRect(sourceCrop[0], sourceCrop[1])
                && Utils::compareRect(sourceCrop[0], displayFrame[0])
                && Utils::compareRect(sourceCrop[1], displayFrame[1])) {
                DTRACE("2 layers is same size and have yuv420sp format ge2d compose can not process!");
                return false;
            }
        }
#endif
        if (HWC2_TWO_LAYERS == layerNum
            && (layer[0]->isScaled() || layer[1]->isScaled())) {
            DTRACE("when 2 layer's size is difference, ge2d compose can not process!");
            return false;
        }
    }
#endif

    return ret;
}

/*************************************************************
 * For direct framebuffer composer:
 * 1) only support one layer.
 * 2) layer format: rgba, rgbx,rgb565,bgra;
 * 3) layer no rotation.

 * For ge2d composer:
 * 1) support layer format that direct composer can't support.
 * 2) support 2 layers blending.
 * 3) support scale and rotation etc.
**************************************************************/
int32_t PhysicalDevice::composersFilter(
                KeyedVector<hwc2_layer_t, HwcLayer*> & composeLayers) {

    // direct Composer.
    if (composeLayers.size() == HWC2_ONE_LAYER) {
        // if only one layer exists, do direct framebuffer composer.
        bool directCompose = layersStateCheck(DIRECT_COMPOSE_MODE, composeLayers);
        if (directCompose) {
            if (mDirectComposeFrameCount >= 3) {
                hwc2_layer_t layerGlesLayerId = composeLayers.keyAt(0);
                composeLayers.clear();
                mDirectRenderLayerId = layerGlesLayerId;
                return DIRECT_COMPOSE_MODE;
            }
            mDirectComposeFrameCount++;
            return GLES_COMPOSE_MODE;
        }
    }

#ifdef ENABLE_AML_GE2D_COMPOSER
    // if direct composer can't work, try this.
    if (composeLayers.size() > HWC2_NO_LAYER
        && composeLayers.size() < HWC2_MAX_LAYERS) {
        bool ge2dCompose = layersStateCheck(GE2D_COMPOSE_MODE, composeLayers);
        if (!ge2dCompose) return GLES_COMPOSE_MODE;
        mGE2DRenderSortedLayerIds.clear();
        for (uint32_t i=0; i<composeLayers.size(); i++) {
            hwc2_layer_t layerGlesLayerId = composeLayers.keyAt(i);
            HwcLayer* layer = getLayerById(layerGlesLayerId);
            if (0 == i) {
                mGE2DRenderSortedLayerIds.push_front(layerGlesLayerId);
                continue;
            }
            for (uint32_t j=0; j<i; j++) {
                HwcLayer* layer1 = getLayerById(mGE2DRenderSortedLayerIds.itemAt(j));
                HwcLayer* layer2 = getLayerById(layerGlesLayerId);
                if (layer1 != NULL && layer2 != NULL) {
                    uint32_t z1 = layer1->getZ();
                    uint32_t z2 = layer2->getZ();
                    if (layer1->getZ() > layer2->getZ()) {
                        mGE2DRenderSortedLayerIds.insertAt(layerGlesLayerId, j, 1);
                        break;
                    }
                    if (j == i-1) mGE2DRenderSortedLayerIds.push_back(layerGlesLayerId);
                } else {
                    ETRACE("Layer1 or Layer2 is NULL!!!");
                }
            }
        }

        // Vector < hwc2_layer_t > layerIds;
        if (!mComposer) {
            // create ge2d composer...
            mComposer = mControlFactory->createComposer(*this);
            if (!mComposer || !mComposer->initialize(mFramebufferContext->getInfo())) {
                DEINIT_AND_DELETE_OBJ(mComposer);
                return GLES_COMPOSE_MODE;
            }
        }
        composeLayers.clear();
        return GE2D_COMPOSE_MODE;
    }
#endif

    return GLES_COMPOSE_MODE;
}

bool PhysicalDevice::calReverseScale() {
    static float fb_w = 1920; // Query activeConfig for FB size?
    static float fb_h = 1080; // Query activeConfig for FB size?

    mReverseScaleX = mReverseScaleY = 0.0f;
    if (fb_w <= 0.01f || fb_h <= 0.01f)
        return false;

    float display_w, display_h;
    hwc2_config_t config;
    if (HWC2_ERROR_NONE != mDisplayHdmi->getRealActiveConfig(&config))
        return false;

    int32_t tmpSize = 0.0f;
    if ( mDisplayHdmi->getDisplayAttribute(config,
                HWC2_ATTRIBUTE_WIDTH, &tmpSize) != NO_ERROR)
        return false;
    display_w = tmpSize;
    if ( mDisplayHdmi->getDisplayAttribute(config,
                HWC2_ATTRIBUTE_HEIGHT, &tmpSize) != NO_ERROR)
        return false;
    display_h = tmpSize;

    if (display_w <= 0.01f || display_h <= 0.01f)
        return false;

    mReverseScaleX = fb_w / display_w;
    mReverseScaleY = fb_h /display_h;
    return false;
}

int32_t PhysicalDevice::preValidate() {
    bool bScale = (mReverseScaleX >= 0.01f && mReverseScaleX >= 0.01f) ? true : false;
    HwcLayer* layer = NULL;
    int videoPresentFlags = 0; //0: no video, 1: video presetn, 2: omx video present;
    mOmxSideBandPresent = false;
    //find out video layer first.
    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (!layer) {
            ETRACE("Meet empty layer, id(%lld)", layerId);
            continue;
        }

        if (bScale && (layer->getDisplayFrame().right >= 3800))
            layer->reverseScaledFrame(mReverseScaleX, mReverseScaleY);

        private_handle_t const* hnd = private_handle_t::dynamicCast(layer->getBufferHandle());
        if (hnd && !((hnd->flags & private_handle_t::PRIV_FLAGS_CONTINUOUS_BUF)
            || (hnd->flags & private_handle_t::PRIV_FLAGS_VIDEO_OVERLAY))) {
            mIsContinuousBuf = false;
        }

        if ((hnd && (hnd->flags & private_handle_t::PRIV_FLAGS_VIDEO_OVERLAY) &&
                (layer->getCompositionType() == HWC2_COMPOSITION_DEVICE)) ||
                (layer->getCompositionType() == HWC2_COMPOSITION_SIDEBAND
                && layer->getSidebandStream())) {
            if (mVideoOverlayLayerId != 0) {
                ETRACE("ERROR: Find two video layer, should never get here !!");
            }
            mVideoOverlayLayerId = layerId;
        }
        if (layer->getCompositionType() == HWC2_COMPOSITION_SIDEBAND) {
            //ALOGD("SIDEBAND");
            mOmxSideBandPresent = true;
        }

        if (hnd && (hnd->flags & private_handle_t::PRIV_FLAGS_VIDEO_OMX)) {
             videoPresentFlags = 2;
        } else if (hnd && (hnd->flags & private_handle_t::PRIV_FLAGS_VIDEO_OVERLAY)) {
             videoPresentFlags = 1;
        }
    }

    if (videoPresentFlags == 2) {
         mOmxVideoPresent = true;
    } else {
         mOmxVideoPresent = false;
    }
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::beginCompose() {
    swapReleaseFence();
    // reset layer changed or requested size to zero.
    mHwcLayersChangeType.clear();
    mHwcLayersChangeRequest.clear();
    mHwcGlesLayers.clear();
    // deal non secure display device.
    mHwcSecureLayers.clear();

    memset(&mFbSyncRequest, 0, sizeof(mFbSyncRequest));
    mFbSyncRequest.in_fen_fd = -1;

    mVideoOverlayLayerId = 0;
    mIsContinuousBuf = true;
    mIsValidated = false;
    mRenderMode = GLES_COMPOSE_MODE;

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::finishCompose() {
    HwcLayer* layer = NULL;
    // reset layers' acquire fence.
    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (layer != NULL) {
            layer->resetAcquireFence();
        }
    }

    mClientTargetHnd = NULL;
    mPreviousRenderMode = mRenderMode;
    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::validateDisplay(uint32_t* outNumTypes,
    uint32_t* outNumRequests) {
    HwcLayer* layer = NULL, *videoLayer = NULL;
    hwc_rect_t videoRect;
    KeyedVector<hwc2_layer_t, HwcLayer*> composeLayers;
    composeLayers.clear();

    beginCompose();

    if (preValidate() != HWC2_ERROR_NONE) {
        return HWC2_ERROR_BAD_LAYER;
    }

    if (mVideoOverlayLayerId) {
        videoLayer = mHwcLayers.valueFor(mVideoOverlayLayerId);
        videoRect = videoLayer->getDisplayFrame();
    }

    for (uint32_t i=0; i<mHwcLayers.size(); i++) {
        int overlapType = Utils::OVERLAP_EMPTY;
        hwc2_layer_t layerId = mHwcLayers.keyAt(i);
        layer = mHwcLayers.valueAt(i);
        if (!layer)
            continue;

        private_handle_t const* hnd = private_handle_t::dynamicCast(layer->getBufferHandle());

        // secure or protected layer.
        if (!mSecure && hnd && (hnd->flags & private_handle_t::PRIV_FLAGS_SECURE_PROTECTED)) {
            DTRACE("layer's secure or protected buffer flag is set! usage (%x)", hnd->flags);
            if (layer->getCompositionType() != HWC2_COMPOSITION_DEVICE) {
                mHwcLayersChangeType.add(layerId, layer);
            }
            mHwcSecureLayers.add(layerId, layer);
            continue;
        }

        if (videoLayer && (layer->getZ() < videoLayer->getZ())) {
            DTRACE("Layer covered by video layer.");
            hwc_rect_t layerRect = layer->getDisplayFrame();
            overlapType = Utils::rectOverlap(layerRect, videoRect);
        }

        switch (layer->getCompositionType()) {
            case HWC2_COMPOSITION_CLIENT:
                mHwcGlesLayers.add(layerId, layer);
                DTRACE("Meet a client layer!");
                break;
            case HWC2_COMPOSITION_DEVICE:
                if (layerId == mVideoOverlayLayerId) {
                    mHwcLayersChangeRequest.add(layerId, layer);
                } else {
                    composeLayers.add(layerId, layer);
                }
                break;
            case HWC2_COMPOSITION_SOLID_COLOR:
                if (overlapType != Utils::OVERLAP_FULL) {
                    mHwcGlesLayers.add(layerId, layer);
                    mHwcLayersChangeType.add(layerId, layer);
                }
                break;
            case HWC2_COMPOSITION_CURSOR:
                DTRACE("This is a Cursor layer!");
                mHwcLayersChangeRequest.add(layerId, layer);
                break;
            case HWC2_COMPOSITION_SIDEBAND:
                if (layerId == mVideoOverlayLayerId) {
                    DTRACE("get HWC_SIDEBAND layer, just change to overlay");
                    mHwcLayersChangeRequest.add(layerId, layer);
                    mHwcLayersChangeType.add(layerId, layer);
                } else {
                    ETRACE("SIDEBAND not handled.");
                }
                break;
            default:
                ETRACE("get layer of unknown composition type (%d)", layer->getCompositionType());
                break;
        }
    }
   if (mOmxKeepLastFrame == 1) {
        int is_disable_video = -1;
        AmVideo::getInstance()->getvideodisable(&is_disable_video);
        //ALOGD("is_disable_video %d, mOmxVideoPresent %d, mOmxSideBandPresent %d, mVideoLayerOpenByOMX %d",is_disable_video,mOmxVideoPresent,mOmxSideBandPresent,mVideoLayerOpenByOMX);
        if (mOmxVideoPresent || mOmxSideBandPresent) {
            //enable video layer
            if (is_disable_video == 1) {
                ALOGI("video layer is close, enable video layer");
                AmVideo::getInstance()->setvideodisable(2);
            }
            mVideoLayerOpenByOMX = true;
        } else {
            if (mVideoLayerOpenByOMX) {
                //disable video layer.
                if (is_disable_video == 0 || is_disable_video == 2) {
                    if (mVideoOverlayLayerId == 0) {
                        AmVideo::getInstance()->setvideodisable(1);
                        ALOGI("no omx video layer, no OVERLAY, set display_mode %d->1",is_disable_video);
                    } else {
                        ALOGI("no omx video layer, but has OVERLAY, not set display_mode");
                    }
                }
            }
            mVideoLayerOpenByOMX = false;
        }
    }

    bool noDevComp = Utils::checkBoolProp("sys.sf.debug.nohwc");
#ifndef USE_CONTINOUS_BUFFER_COMPOSER
    DTRACE("No continous buffer composer!");
    noDevComp = true;
    mIsContinuousBuf = false;
#endif

    if (mHwcLayers.size() == 0) {
        mIsContinuousBuf = false;
    }

    // dumpLayers(mHwcLayers);
    if (mIsContinuousBuf && !noDevComp && (mHwcGlesLayers.size() == 0)) {
        mRenderMode = composersFilter(composeLayers);
    } else {
        mDirectComposeFrameCount = 0;
    }

    // DEVICE_COMPOSE layers set to CLIENT_COMPOSE layers.
    for (int i=0; i<composeLayers.size(); i++) {
        mHwcLayersChangeType.add(composeLayers.keyAt(i), composeLayers.valueAt(i));
        mHwcGlesLayers.add(composeLayers.keyAt(i), composeLayers.valueAt(i));
    }

    if (mHwcLayersChangeRequest.size() > 0) {
        DTRACE("There are %d layer requests.", mHwcLayersChangeRequest.size());
        *outNumRequests = mHwcLayersChangeRequest.size();
    }

    mIsValidated = true;

    if (mHwcLayersChangeType.size() > 0) {
        DTRACE("there are %d layer types has changed.", mHwcLayersChangeType.size());
        *outNumTypes = mHwcLayersChangeType.size();
        return HWC2_ERROR_HAS_CHANGES;
    }

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::setCursorPosition(hwc2_layer_t layerId, int32_t x, int32_t y) {
    HwcLayer* layer = getLayerById(layerId);
    if (layer && HWC2_COMPOSITION_CURSOR == layer->getCompositionType()) {
        framebuffer_info_t* cbInfo = mCursorContext->getInfo();
        fb_cursor cinfo;
        if (cbInfo->fd < 0) {
            ETRACE("setCursorPosition fd=%d", cbInfo->fd );
        }else {
            cinfo.hot.x = x;
            cinfo.hot.y = y;
            DTRACE("setCursorPosition x_pos=%d, y_pos=%d", cinfo.hot.x, cinfo.hot.y);
            ioctl(cbInfo->fd, FBIO_CURSOR, &cinfo);
        }
    } else {
        ETRACE("setCursorPosition bad layer.");
        return HWC2_ERROR_BAD_LAYER;
    }

    return HWC2_ERROR_NONE;
}


/*
Operater of framebuffer
*/
int32_t PhysicalDevice::initDisplay() {
    Mutex::Autolock _l(mLock);

    if (!mFramebufferHnd) {
        // init framebuffer context.
        mFramebufferContext = new FBContext();
        framebuffer_info_t* fbInfo = mFramebufferContext->getInfo();
        // init information from osd.
        fbInfo->displayType = mId;
        fbInfo->fbIdx = getOsdIdx(mId);
        int32_t err = init_frame_buffer_locked(fbInfo);
        int32_t bufferSize = fbInfo->finfo.line_length
            * fbInfo->info.yres;
        DTRACE("init_frame_buffer get fbinfo->fbIdx (%d) "
            "fbinfo->info.xres (%d) fbinfo->info.yres (%d)",
            fbInfo->fbIdx, fbInfo->info.xres,
            fbInfo->info.yres);
        int32_t usage = 0;
        private_module_t *grallocModule = Hwcomposer::getInstance().getGrallocModule();
        if (mId == HWC_DISPLAY_PRIMARY) {
            grallocModule->fb_primary.fb_info = *(fbInfo);
        } else if (mId == HWC_DISPLAY_EXTERNAL) {
            grallocModule->fb_external.fb_info = *(fbInfo);
            usage |= GRALLOC_USAGE_EXTERNAL_DISP;
        }
        fbInfo->grallocModule = grallocModule;

        //Register the framebuffer to gralloc module
        mFramebufferHnd = new private_handle_t(
                        private_handle_t::PRIV_FLAGS_FRAMEBUFFER,
                        usage, fbInfo->fbSize, 0,
                        0, fbInfo->fd, bufferSize, 0);
        grallocModule->base.registerBuffer(&(grallocModule->base), mFramebufferHnd);
        DTRACE("init_frame_buffer get frame size %d usage %d",
            bufferSize, usage);
    }

    // init cursor framebuffer
    mCursorContext = new FBContext();
    framebuffer_info_t* cbInfo = mCursorContext->getInfo();
    cbInfo->fd = -1;

    //init information from cursor framebuffer.
    cbInfo->fbIdx = mId*2+1;
    if (1 != cbInfo->fbIdx && 3 != cbInfo->fbIdx) {
        ETRACE("invalid fb index: %d, need to check!",
            cbInfo->fbIdx);
        return 0;
    }
    int32_t err = init_cursor_buffer_locked(cbInfo);
    if (err != 0) {
        ETRACE("init_cursor_buffer_locked failed, need to check!");
        return 0;
    }
    ITRACE("init_cursor_buffer get cbinfo->fbIdx (%d) "
        "cbinfo->info.xres (%d) cbinfo->info.yres (%d)",
                        cbInfo->fbIdx,
                        cbInfo->info.xres,
                        cbInfo->info.yres);

    if ( cbInfo->fd >= 0) {
        DTRACE("init_cursor_buffer success!");
    }else{
        DTRACE("init_cursor_buffer fail!");
    }

    return 0;
}

void PhysicalDevice::updateActiveDisplayAttribute() {
    hwc2_config_t config;
    if (HWC2_ERROR_NONE == mDisplayHdmi->getRealActiveConfig(&config)) {
        int32_t period = 0;
        mDisplayHdmi->getDisplayAttribute(config, HWC2_ATTRIBUTE_VSYNC_PERIOD, &period);
        mVsyncObserver->setRefreshPeriod(period);
    }

    calReverseScale();
}

bool PhysicalDevice::updateDisplayConfigs() {
    Mutex::Autolock _l(mLock);
    framebuffer_info_t* fbinfo = mFramebufferContext->getInfo();
    mDisplayHdmi->updateHotplug(mConnectorPresent, *fbinfo);

    if (mConnectorPresent) {
        updateActiveDisplayAttribute();
    } else {
        ETRACE("disp: %llu is not connected, should change mode to null", mId);
        // mDisplayHdmi->setBestDisplayMode();
        return false;
    }

    // update HDR info.
    if (!mHdrCapabilities.init) {
        ETRACE("update hdr infomation.");
        parseHdrCapabilities();
        mHdrCapabilities.init = true;
    }

    // check hdcp authentication status when hotplug is happen.
    if (mSystemControl == NULL) {
        mSystemControl = getSystemControlService();
    } else {
        DTRACE("already have system control instance.");
    }
    if (mSystemControl != NULL) {
        // mSecure = Utils::checkHdcp();
        int status = 0;
        mSystemControl->isHDCPTxAuthSuccess(status);
        DTRACE("hdcp status: %d", status);
        mSecure = (status == 1) ? true : false;
    } else {
        ETRACE("can't get system control.");
    }

    return true;
}

sp<ISystemControlService> PhysicalDevice::getSystemControlService() {
    sp<IServiceManager> sm = defaultServiceManager();
    if (sm == NULL) {
        ETRACE("Couldn't get default ServiceManager\n");
        return NULL;
    }
    sp<IBinder> binder = sm->getService(String16("system_control"));
    sp<ISystemControlService> sc = interface_cast<ISystemControlService>(binder);

    return sc;
}

void PhysicalDevice::onVsync(int64_t timestamp) {
    RETURN_VOID_IF_NOT_INIT();
    ATRACE("timestamp = %lld", timestamp);

    if (!mConnectorPresent)
        return;

    // notify hwc
    mHwc.vsync(mId, timestamp);
}

void PhysicalDevice::onHotplug(int disp, bool connected) {
    RETURN_VOID_IF_NOT_INIT();
    ETRACE("connect status = (%d)", connected);

    if (!updateDisplayConfigs())
        ETRACE("failed to update display config");

    // notify hwc
    if (connected)
        mHwc.hotplug(disp, connected);
}

int32_t PhysicalDevice::createVirtualDisplay(
        uint32_t width,
        uint32_t height,
        int32_t* /*android_pixel_format_t*/ format,
        hwc2_display_t* outDisplay) {

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::destroyVirtualDisplay(
        hwc2_display_t display) {

    return HWC2_ERROR_NONE;
}

int32_t PhysicalDevice::setOutputBuffer(
        buffer_handle_t buffer, int32_t releaseFence) {
    // Virtual Display Only.
    return HWC2_ERROR_NONE;
}

void PhysicalDevice::updateHotplugState(bool connected) {
    Mutex::Autolock _l(mLock);

    mConnectorPresent = connected;
    // if plug out, need reinit
    if (!connected)
        memset(&mHdrCapabilities, 0, sizeof(hdr_capabilities_t));
}

int32_t PhysicalDevice::getLineValue(const char *lineStr, const char *magicStr) {
    int len = 0;
    char value[100] = {0};
    char *pos = NULL;

    if ((NULL == lineStr) || (NULL == magicStr)) {
        ETRACE("line string: %s, magic string: %s\n", lineStr, magicStr);
        return 0;
    }

    if (NULL != (pos = strstr(lineStr, magicStr))) {
        pos = pos + strlen(magicStr);
        char* start = pos;
        while (*start != '\n' && (strlen(start) > 0))
            start++;

        len = start - pos;
        strncpy(value, pos, len);
        value[len] = '\0';
        return atoi(value);
    }

    return 0;
}

/*******************************************
* cat /sys/class/amhdmitx/amhdmitx0/hdr_cap
* Supported EOTF:
*     Traditional SDR: 1
*     Traditional HDR: 0
*     SMPTE ST 2084: 1
*     Future EOTF: 0
* Supported SMD type1: 1
* Luminance Data
*     Max: 0
*     Avg: 0
*     Min: 0
* cat /sys/class/amhdmitx/amhdmitx0/dv_cap
* DolbyVision1 RX support list:
*     2160p30hz: 1
*     global dimming
*     colorimetry
*     IEEEOUI: 0x00d046
*     DM Ver: 1
*******************************************/
int32_t PhysicalDevice::parseHdrCapabilities() {
    // DolbyVision1
    const char *DV_PATH = "/sys/class/amhdmitx/amhdmitx0/dv_cap";
    // HDR
    const char *HDR_PATH = "/sys/class/amhdmitx/amhdmitx0/hdr_cap";

    char buf[1024+1] = {0};
    char* pos = buf;
    int fd, len;

    memset(&mHdrCapabilities, 0, sizeof(hdr_capabilities_t));
    if ((fd = open(DV_PATH, O_RDONLY)) < 0) {
        ETRACE("open %s fail.", DV_PATH);
        goto exit;
    }

    len = read(fd, buf, 1024);
    if (len < 0) {
        ETRACE("read error: %s, %s\n", DV_PATH, strerror(errno));
        goto exit;
    }
    close(fd);

    if ((NULL != strstr(pos, "2160p30hz")) || (NULL != strstr(pos, "2160p60hz")))
        mHdrCapabilities.dvSupport = true;
    // dobly version parse end

    memset(buf, 0, 1024);
    if ((fd = open(HDR_PATH, O_RDONLY)) < 0) {
        ETRACE("open %s fail.", HDR_PATH);
        goto exit;
    }

    len = read(fd, buf, 1024);
    if (len < 0) {
        ETRACE("read error: %s, %s\n", HDR_PATH, strerror(errno));
        goto exit;
    }

    pos = strstr(pos, "SMPTE ST 2084: ");
    if ((NULL != pos) && ('1' == *(pos + strlen("SMPTE ST 2084: ")))) {
        mHdrCapabilities.hdrSupport = true;

        mHdrCapabilities.maxLuminance = getLineValue(pos, "Max: ");
        mHdrCapabilities.avgLuminance = getLineValue(pos, "Avg: ");
        mHdrCapabilities.minLuminance = getLineValue(pos, "Min: ");
    }

    ITRACE("dolby version support:%d, hdr support:%d max:%d, avg:%d, min:%d\n",
        mHdrCapabilities.dvSupport?1:0, mHdrCapabilities.hdrSupport?1:0, mHdrCapabilities.maxLuminance, mHdrCapabilities.avgLuminance, mHdrCapabilities.minLuminance);
exit:
    close(fd);
    return HWC2_ERROR_NONE;
}

void PhysicalDevice::dump(Dump& d) {
    Mutex::Autolock _l(mLock);
    d.append("-------------------------------------------------------------"
        "----------------------------------------------------------------\n");
    d.append("Device Name: %s (%s), (%f, %f)\n", mName,
            mConnectorPresent ? "connected" : "disconnected",
            mReverseScaleX, mReverseScaleY);

    d.append("isSecure : %s\n", mSecure ? "TRUE" : "FALSE");

    mDisplayHdmi->dump(d);

#if 0 //all the info already dumped by SurfaceFlinger, comment it.
    // dump layer list
    d.append("  Layers state:\n");
    d.append("    numLayers=%zu\n", mHwcLayers.size());
    // d.append("    numChangedTypeLayers=%zu\n", mHwcLayersChangeType.size());
    // d.append("    numChangedRequestLayers=%zu\n", mHwcLayersChangeRequest.size());

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
#endif

    // HDR info
    d.append("  HDR Capabilities:\n");
    d.append("    DolbyVision1=%zu\n", mHdrCapabilities.dvSupport?1:0);
    d.append("    HDR10=%zu, maxLuminance=%zu, avgLuminance=%zu, minLuminance=%zu\n",
        mHdrCapabilities.hdrSupport?1:0, mHdrCapabilities.maxLuminance, mHdrCapabilities.avgLuminance, mHdrCapabilities.minLuminance);
}

} // namespace amlogic
} // namespace android
