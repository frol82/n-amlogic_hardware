/*
// Copyright (c) 2016 Amlogic
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

#ifndef GE2D_COMPOSER_H
#define GE2D_COMPOSER_H

#include <utils/KeyedVector.h>
#include <SimpleThread.h>
#include <Composers.h>
#include <IDisplayDevice.h>
#include <inttypes.h>

#include <ge2d_port.h>
#include <../kernel-headers/linux/ge2d.h>

namespace android {
namespace amlogic {

class LayerState {
public:
    LayerState()
    : mBufferHnd(NULL),
      mBlendMode(0),
      mTransform(HAL_TRANSFORM_RESERVED),
      mBufferFd(-1) {
    }

    ~LayerState() {
    }

    //void setLayerState(HwcLayer* hwcLayer);
    void setLayerState(HwcLayer* hwcLayer) {
        mBlendMode = hwcLayer->getBlendMode();
        mColor = hwcLayer->getColor();
        mCompositionType = hwcLayer->getCompositionType();
        mAcquireFence = hwcLayer->getAcquireFence();
        mDataSpace = hwcLayer->getDataspace();
        mPlaneAlpha = hwcLayer->getPlaneAlpha();
        mTransform = hwcLayer->getTransform();
        mZ = hwcLayer->getZ();
        mSourceCrop = hwcLayer->getSourceCrop();
        mDisplayFrame = hwcLayer->getDisplayFrame();
        mBufferHnd = hwcLayer->getBufferHandle();

        private_handle_t const* hnd = private_handle_t::dynamicCast(mBufferHnd);
        if (hnd)
            mBufferFd = Utils::checkAndDupFd(hnd->ion_hnd);
        else
            mBufferFd = -1;
    }

    int32_t mBlendMode;
    hwc_color_t mColor;
    int32_t mCompositionType;
    int32_t mAcquireFence;
    int32_t mDataSpace;
    float mPlaneAlpha;
    int32_t mTransform;
    uint32_t mZ;
    hwc_frect_t mSourceCrop;
    hwc_rect_t mDisplayFrame;
    // hwc_region_t mDamageRegion;
    hwc_region_t mVisibleRegion;

    buffer_handle_t mBufferHnd;

    // hold this until ge2d finish process.
    int32_t mBufferFd;
};

class SlotInfo {
public:
    SlotInfo()
    : mSlot(-1),
      mFence(-1),
      mVideoLayerId(0),
      mClearBuffer(false),
      mLayersState() {
        mLayersState.setCapacity(HWC2_MAX_LAYERS);
        mLayersState.clear();
    }

    ~SlotInfo() {
    }

    const int32_t getSlot() const { return mSlot; };
    const int32_t getMergedFence() const { return mFence; };
    const Vector< LayerState* > getLayersState() const { return mLayersState; };

    int32_t mSlot;
    int32_t mFence;
    hwc2_layer_t mVideoLayerId;
    bool mClearBuffer;
    Vector< LayerState* > mLayersState;
};

enum { NUM_GE2D_BUFFER_SLOTS = 3 };

class IDisplayDevice;

class GE2DComposer : public Composers {

public:
    GE2DComposer(IDisplayDevice& disp);
    virtual ~GE2DComposer();

public:
    typedef Vector< SlotInfo > Fifo;

    virtual bool initialize(framebuffer_info_t* fbInfo);
    virtual void deinitialize();
    virtual const char* getName() const;
    virtual int32_t startCompose(Vector< hwc2_layer_t > hwcLayers, int32_t *offset = 0, int32_t frameCount = 0);
    // virtual void setCurGlesFbSlot(uint32_t slot);
    virtual const buffer_handle_t getBufHnd();
    virtual void mergeRetireFence(int32_t slot, int32_t retireFence);
    virtual void removeRetireFence(int32_t slot);
    virtual void setVideoOverlayLayerId(hwc2_layer_t layerId);
    virtual void fillRectangle(hwc_rect_t clipRect, uint32_t color, uint32_t offset, int shared_fd);
private:
    uint32_t findFreeFbSlot();
    void runGE2DProcess(int32_t slot, Vector< LayerState* > &hwcLayersState);
    void directMemcpy(Fifo::iterator front); // test.
    int32_t allocBuffer(private_module_t* module, size_t size, int32_t usage, buffer_handle_t* pHandle);
    void freeBuffer(private_handle_t const* hnd, private_module_t* m);
    bool isFullScreen(hwc_rect_t displayFrame);
    void tracer();
    void dumpLayers(private_handle_t const* hnd);


    IDisplayDevice& mDisplayDevice;
    const char* mName;

    // Thread safe, mQueueItems is a FIFO of queued work used in synchronous mode.
    volatile int32_t mQueuedFrames;
    Fifo mQueueItems;

    // Fence.
    int32_t mSyncTimelineFd;
    uint32_t mCurrentSyncTime;

    int32_t mBufferMask;
    int32_t mNumBuffers;
    SlotInfo mSlots[NUM_GE2D_BUFFER_SLOTS];
    hwc2_layer_t mVideoLayerId;
    // LayerState mVideoLayerState;
    int32_t mFbSlot;
    int32_t mCurGlesFbSlot;
    framebuffer_info_t* mFbInfo;
    int32_t mSingleFbSize;

    buffer_handle_t mGe2dBufHnd;
    int mSharedFd;
    int32_t mGe2dFd;

    aml_ge2d_info_t *mSrcBufferInfo;
    bool mDebug;

    int32_t mDevice;
    mutable Mutex mLock;
    Condition mCondition;
    bool mExitThread;
    bool mInitialized;

private:
    DECLARE_THREAD(GE2DRenderThread, GE2DComposer);
};

} // namespace amlogic
} // namespace android



#endif /* GE2D_COMPOSITOR_H */

