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

#ifndef HWC_LAYER_H
#define HWC_LAYER_H

#include <hardware/hwcomposer2.h>
#include <utils/threads.h>
#include <Dump.h>
#include <utils/Vector.h>
#include <Utils.h>
#include <HwcFenceControl.h>

namespace android {
namespace amlogic {

class HwcLayer {
    public:
        HwcLayer(hwc2_display_t& dpy);
        virtual ~HwcLayer();

        // HWC2 Layer functions
        int32_t setBuffer(buffer_handle_t buffer, int32_t acquireFence);
        int32_t setSurfaceDamage(hwc_region_t damage);

        // HWC2 Layer state functions
        int32_t setBlendMode(int32_t mode);
        int32_t setColor(hwc_color_t color);
        int32_t setDataspace(int32_t dataspace);
        int32_t setDisplayFrame(hwc_rect_t frame);
        int32_t setPlaneAlpha(float alpha);
        int32_t setSidebandStream(const native_handle_t* stream);
        int32_t setSourceCrop(hwc_frect_t crop);
        int32_t setTransform(int32_t transform);
        int32_t setVisibleRegion(hwc_region_t visible);
        int32_t setZ(uint32_t z);
        uint32_t getZ() const { return mZ; }

        int32_t setCompositionType(int32_t type);
        int32_t getCompositionType() const { return mCompositionType; }

        // get HWC2 Layer state functions
        buffer_handle_t getBufferHandle() const { return mBufferHnd; }
        const native_handle_t* getSidebandStream() const { return mSidebandStream; }
        int32_t getAcquireFence() const { return mAcquireFence; }
        int32_t getDuppedAcquireFence() { return HwcFenceControl::dupFence(mAcquireFence); }
        hwc_region_t getSurfaceDamage() { return mDamageRegion; };
        int32_t getBlendMode() { return mBlendMode; };
        hwc_color_t getColor() { return mColor; };
        int32_t getDataspace() { return mDataSpace; };
        hwc_rect_t getDisplayFrame() { return mDisplayFrame;};
        float getPlaneAlpha() { return mPlaneAlpha; };
        hwc_frect_t getSourceCrop() { return mSourceCrop; };
        int32_t getTransform() { return mTransform; };
        hwc_region_t getVisibleRegion() { return mVisibleRegion; };

        bool initialize();
        void deinitialize();
        void dump(Dump& d);

        void resetAcquireFence();

        bool isCropped();
        bool isScaled();
        bool isOffset();
        bool isBlended();
        bool haveColor();
        bool havePlaneAlpha();
        bool haveDataspace();
        void reverseScaledFrame(const float& scaleX, const float& scaleY);

#if WITH_LIBPLAYER_MODULE
        void presentOverlay(bool bPresent);
#endif

    private:
        void resetLayerBuffer();

    private:
        hwc2_display_t mDisplayId;
        int32_t mBlendMode;
        hwc_color_t mColor;
        int32_t mCompositionType;
        int32_t mAcquireFence;
        int32_t mDataSpace;
        float mPlaneAlpha;
        int32_t mTransform;
        int32_t mLastTransform;
        uint32_t mZ;
        hwc_frect_t mSourceCrop;
        hwc_rect_t mDisplayFrame;
        hwc_rect_t mLastDisplayFrame;
        hwc_region_t mDamageRegion;
        hwc_region_t mVisibleRegion;


        union {
            buffer_handle_t mBufferHnd;

            /* When compositionType is HWC_SIDEBAND, this is the handle
             * of the sideband video stream to compose. */
            const native_handle_t* mSidebandStream;
        };

#if WITH_LIBPLAYER_MODULE
        // for store overlay layer's state.
        char mLastVal[32];
        char mLastAxis[32];
        char mLastMode[32];
        char mLastFreescale[32];
        char mLastWindowaxis[50];
#endif
        // lock
        Mutex mLock;
        bool mInitialized;
        bool mScaleReversed;
};

} // namespace amlogic
} // namespace android


#endif /* HWC_LAYER_H */
