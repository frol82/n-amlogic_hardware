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

#include <inttypes.h>
#include <HwcTrace.h>
#include <HwcLayer.h>
#include <Hwcomposer.h>
#include <IDisplayDevice.h>
#include <cutils/properties.h>
#include <sync/sync.h>
#include <AmVideo.h>


namespace android {
namespace amlogic {

HwcLayer::HwcLayer(hwc2_display_t& dpy)
    : mDisplayId(dpy),
      mBlendMode(0),
      mCompositionType(0),
      mAcquireFence(-1),
      mDataSpace(HAL_DATASPACE_UNKNOWN),
      mPlaneAlpha(0.0f),
      mTransform(HAL_TRANSFORM_RESERVED),
      mZ(0),
      mBufferHnd(NULL),
      mInitialized(false)
{
    // initial layer's state.
    mColor.r = 0;
    mColor.g = 0;
    mColor.b = 0;
    mColor.a = 0;

    mSourceCrop.left = 0.0f;
    mSourceCrop.top = 0.0f;
    mSourceCrop.right = 0.0f;
    mSourceCrop.bottom = 0.0f;

    mDisplayFrame.left = 0;
    mDisplayFrame.top = 0;
    mDisplayFrame.right = 0;
    mDisplayFrame.bottom = 0;

    mDamageRegion.numRects = 0;
    mVisibleRegion.numRects = 0;
}

HwcLayer::~HwcLayer()
{

}

bool HwcLayer::initialize() {
    Mutex::Autolock _l(mLock);

    mInitialized = true;
    return true;
}

void HwcLayer::deinitialize() {
    Mutex::Autolock _l(mLock);

    mInitialized = false;
}

void HwcLayer::resetAcquireFence() {
    Mutex::Autolock _l(mLock);

    HwcFenceControl::closeFd(mAcquireFence);
    mAcquireFence = -1;
}

bool HwcLayer::isCropped() {
    bool rtn = true;
    private_handle_t const* buffer = private_handle_t::dynamicCast(mBufferHnd);

    if (buffer && buffer->width && buffer->height) {
        float widthCmp = (mSourceCrop.right - mSourceCrop.left) / buffer->width;
        float heightCmp = (mSourceCrop.bottom - mSourceCrop.top) / buffer->height;

        if (Utils::abs(widthCmp - 1.0f) <= 0.01f
            && Utils::abs(heightCmp - 1.0f) <= 0.01f) {
            rtn = false;
        }
    }

    DTRACE("chkIsCropped %d", rtn);
    return rtn;
}

bool HwcLayer::isScaled() {
    bool rtn = true;
    float sourceWidth = mSourceCrop.right - mSourceCrop.left;
    float sourceHeight = mSourceCrop.bottom - mSourceCrop.top;
    int displayWidth = mDisplayFrame.right - mDisplayFrame.left;
    int displayHeight = mDisplayFrame.bottom - mDisplayFrame.top;

    if (displayWidth > 0 && displayHeight > 0) {
        float widthCmp = sourceWidth / displayWidth;
        float heightCmp = sourceHeight / displayHeight;

        if (Utils::abs(widthCmp - 1.0f) <= 0.01f
            && Utils::abs(heightCmp - 1.0f) <= 0.01f) {
            rtn = false;
        }
    }

    DTRACE("chkIsScaled %d", rtn);
    return rtn;
}

bool HwcLayer::isOffset() {
    bool rtn = false;
    if (mDisplayFrame.left != 0 || mDisplayFrame.top != 0)
        rtn = true;

    DTRACE("chkIsOffset %d", rtn);
    return rtn;
}

bool HwcLayer::isBlended() {
    DTRACE("chkIsBlended %d", mBlendMode);
    return mBlendMode != HWC2_BLEND_MODE_INVALID;
}

bool HwcLayer::haveColor() {
    DTRACE("[%d, %d, %d, %d]", mColor.r, mColor.g, mColor.b, mColor.a);
    return !(0 == mColor.r && 0 == mColor.g && 0 == mColor.b && 0 == mColor.a);
}

bool HwcLayer::havePlaneAlpha() {
    DTRACE("mPlaneAlpha: %d", mPlaneAlpha);
    return mPlaneAlpha > 0.0f && mPlaneAlpha < 1.0f;
}

bool HwcLayer::haveDataspace() {
    DTRACE("mDataSpace: %d", mDataSpace);
    return mDataSpace != HAL_DATASPACE_UNKNOWN;
}

void HwcLayer::reverseScaledFrame(const float& scaleX, const float& scaleY) {
    if (mScaleReversed)
        return;

    mDisplayFrame.left = mDisplayFrame.left * scaleX;
    mDisplayFrame.top = mDisplayFrame.top * scaleY;
    mDisplayFrame.right = mDisplayFrame.right * scaleX;
    mDisplayFrame.bottom = mDisplayFrame.bottom * scaleY;
    mScaleReversed = true;
}

int32_t HwcLayer::setBuffer(buffer_handle_t buffer, int32_t acquireFence) {
    Mutex::Autolock _l(mLock);
    resetLayerBuffer();

    // Bad parameter
    if (!private_handle_t::dynamicCast(buffer)) {
        DTRACE("Layer buffer is null! no need to update this layer.");
        return HWC2_ERROR_BAD_PARAMETER;
    }

    mBufferHnd = buffer;
    mAcquireFence = acquireFence;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setSurfaceDamage(hwc_region_t damage) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do here.
    mDamageRegion = damage;
    return HWC2_ERROR_NONE;
}

// HWC2 Layer state functions
int32_t HwcLayer::setBlendMode(int32_t mode) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mBlendMode = mode;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setColor(hwc_color_t color) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mColor = color;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setCompositionType(int32_t type) {
    // Mutex::Autolock _l(mLock);

    mCompositionType = type;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setDataspace(int32_t dataspace) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mDataSpace = dataspace;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setDisplayFrame(hwc_rect_t frame) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mDisplayFrame = frame;
    mScaleReversed = false;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setPlaneAlpha(float alpha) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mPlaneAlpha = alpha;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setSidebandStream(const native_handle_t* stream) {
    Mutex::Autolock _l(mLock);
    resetLayerBuffer();

    // Bad parameter.
    if (NULL == stream) {
        return HWC2_ERROR_BAD_PARAMETER;
    }
    mSidebandStream = stream;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setSourceCrop(hwc_frect_t crop) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mSourceCrop = crop;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setTransform(int32_t transform) {
    Mutex::Autolock _l(mLock);

    mTransform = transform;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setVisibleRegion(hwc_region_t visible) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mVisibleRegion = visible;
    return HWC2_ERROR_NONE;
}

int32_t HwcLayer::setZ(uint32_t z) {
    Mutex::Autolock _l(mLock);

    // TODO: still have some work to do.
    mZ = z;
    return HWC2_ERROR_NONE;
}

void HwcLayer::resetLayerBuffer() {
   mSidebandStream = NULL;
   mBufferHnd = NULL;
   HwcFenceControl::closeFd(mAcquireFence);
   mAcquireFence = -1;
}

#if WITH_LIBPLAYER_MODULE
void HwcLayer::presentOverlay(bool bPresent) {
    int32_t angle = 0;
    bool vpp_changed = false;
    bool axis_changed = false;
    bool mode_changed = false;
    bool free_scale_changed = false;
    bool window_axis_changed =false;
    hwc_rect_t* displayframe = &mDisplayFrame;

    AmVideo::getInstance()->presentVideo(bPresent);

    if (Utils::checkBoolProp("ro.vout.dualdisplay4")) {
        vpp_changed = Utils::checkSysfsStatus(
            SYSFS_AMVIDEO_CURIDX, mLastVal, 32);
    }

    mode_changed            = Utils::checkSysfsStatus(SYSFS_DISPLAY_MODE, mLastMode, 32);
    free_scale_changed      = Utils::checkSysfsStatus(SYSFS_FB0_FREE_SCALE, mLastFreescale, 32);
    axis_changed            = Utils::checkSysfsStatus(SYSFS_VIDEO_AXIS, mLastAxis, 32);
    window_axis_changed     = Utils::checkSysfsStatus(SYSFS_WINDOW_AXIS, mLastWindowaxis, 50);

    if (mLastTransform == mTransform
        && mLastDisplayFrame.left == displayframe->left
        && mLastDisplayFrame.top == displayframe->top
        && mLastDisplayFrame.right == displayframe->right
        && mLastDisplayFrame.bottom== displayframe->bottom
        && !vpp_changed && !mode_changed && !axis_changed
        && !free_scale_changed && !window_axis_changed) {
        return;
    }

    switch (mTransform) {
        case 0:
            angle = 0;
        break;
        case HAL_TRANSFORM_ROT_90:
            angle = 90;
        break;
        case HAL_TRANSFORM_ROT_180:
            angle = 180;
        break;
        case HAL_TRANSFORM_ROT_270:
            angle = 270;
        break;
        default:
        return;
    }

    amvideo_utils_set_virtual_position(displayframe->left, displayframe->top,
        displayframe->right -displayframe->left,
        displayframe->bottom - displayframe->top,
        angle);

    /* the screen mode from Android framework should always be set to normal mode
    * to match the relationship between the UI and video overlay window position.
    */
    /*set screen_mode in amvideo_utils_set_virtual_position(),pls check in libplayer*/
    //amvideo_utils_set_screen_mode(0);
    mLastTransform = mTransform;
    mLastDisplayFrame.left = displayframe->left;
    mLastDisplayFrame.top = displayframe->top;
    mLastDisplayFrame.right = displayframe->right;
    mLastDisplayFrame.bottom = displayframe->bottom;

    memset(mLastAxis, 0, sizeof(mLastAxis));
    if (Utils::getSysfsStr(SYSFS_VIDEO_AXIS, mLastAxis, sizeof(mLastAxis)) == 0) {
        DTRACE("****last video axis is: %s", mLastAxis);
    }

}
#endif

void HwcLayer::dump(Dump& d) {
    Mutex::Autolock _l(mLock);

    static char const* compositionTypeName[] = {
                    "UNKNOWN",
                    "GLES",
                    "HWC",
                    "SOLID",
                    "HWC_CURSOR",
                    "SIDEBAND"};

    d.append(
            "   %11s | %12" PRIxPTR " | %10d | %02x | %1.2f | %02x | %04x |%7.1f,%7.1f,%7.1f,%7.1f |%5d,%5d,%5d,%5d \n",
                    compositionTypeName[mCompositionType], intptr_t(mBufferHnd),
                    mZ, mDataSpace, mPlaneAlpha, mTransform, mBlendMode,
                    mSourceCrop.left, mSourceCrop.top, mSourceCrop.right, mSourceCrop.bottom,
                    mDisplayFrame.left, mDisplayFrame.top, mDisplayFrame.right, mDisplayFrame.bottom);
}


} // namespace amlogic
} // namespace android
