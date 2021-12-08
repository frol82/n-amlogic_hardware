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


#include <HwcTrace.h>
#include <HwcFenceControl.h>
#include <GE2DComposer.h>
#include <inttypes.h>
#include <linux/ion.h>
#include <ion/ion.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

namespace android {
namespace amlogic {

GE2DComposer::GE2DComposer(IDisplayDevice& disp)
    : Composers(disp),
      mDisplayDevice(disp),
      mLock(),
      mSyncTimelineFd(-1),
      mCondition(),
      mQueueItems(),
      mQueuedFrames(0),
      mBufferMask(0),
      mNumBuffers(1),
      mFbSlot(0),
      mCurGlesFbSlot(-1),
      mSingleFbSize(0),
      mGe2dBufHnd(NULL),
      mGe2dFd(-1),
      mSharedFd(-1),
      mVideoLayerId(0),
      mSrcBufferInfo(NULL),
      mDebug(false),
      mExitThread(false),
      mInitialized(false)
{
    mName = "GE2D";

    mQueueItems.setCapacity(8);
    mQueueItems.clear();
}

GE2DComposer::~GE2DComposer()
{
    WARN_IF_NOT_DEINIT();
}

int32_t GE2DComposer::allocBuffer(private_module_t* module, size_t size, int32_t usage, buffer_handle_t* pHandle)
{
    ion_user_handle_t ion_hnd;
    unsigned char *cpu_ptr = NULL;
    int32_t shared_fd;
    int32_t ret;
    int32_t ion_flags = 0;
    int32_t lock_state = 0;

    if (usage & GRALLOC_USAGE_HW_COMPOSER)
    {
        ret = ion_alloc(module->ion_client, size, 0, 1<<ION_HEAP_TYPE_CHUNK,
                    ion_flags, &ion_hnd);
    }

    if ( ret != 0)
    {
        ETRACE("Failed to ion_alloc from ion_client:%d,size=%d", module->ion_client, size);
        return -1;
    }

    ret = ion_share( module->ion_client, ion_hnd, &shared_fd );
    if ( ret != 0 )
    {
        ETRACE( "ion_share( %d ) failed", module->ion_client );
        if ( 0 != ion_free( module->ion_client, ion_hnd ) )
            ETRACE( "ion_free( %d ) failed", module->ion_client );
        return -1;
    }

    if (!(usage & GRALLOC_USAGE_PROTECTED))
    {
        cpu_ptr = (unsigned char*)mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_fd, 0 );

        if ( MAP_FAILED == cpu_ptr )
        {
            ETRACE( "ion_map( %d ) failed", module->ion_client );
            if ( 0 != ion_free( module->ion_client, ion_hnd ) )
                ETRACE( "ion_free( %d ) failed", module->ion_client );
            close( shared_fd );
            return -1;
        }
        lock_state = private_handle_t::LOCK_STATE_MAPPED;
    }

    private_handle_t *hnd = new private_handle_t( private_handle_t::PRIV_FLAGS_USES_ION /*TODO ion extend*| priv_heap_flag*/,
                                                    usage, size, cpu_ptr, lock_state );

    if ( NULL != hnd )
    {
        hnd->share_fd = shared_fd;
        hnd->ion_hnd = ion_hnd;
        /*TODO ion extend hnd->min_pgsz = min_pgsz; */
        *pHandle = hnd;
        return 0;
    }
    else
    {
        ETRACE( "Gralloc out of mem for ion_client:%d", module->ion_client );
    }

    close( shared_fd );

    if (!(usage & GRALLOC_USAGE_PROTECTED))
    {
        ret = munmap( cpu_ptr, size );
        if ( 0 != ret )
            ETRACE( "munmap failed for base:%p size: %zd", cpu_ptr, size );
    }

    ret = ion_free( module->ion_client, ion_hnd );
    if ( 0 != ret )
        ETRACE( "ion_free( %d ) failed", module->ion_client );
    return -1;
}

void GE2DComposer::freeBuffer(private_handle_t const* hnd, private_module_t* m)
{
    if ( hnd->flags & private_handle_t::PRIV_FLAGS_USES_ION )
    {
        /* Buffer might be unregistered already so we need to assure we have a valid handle*/
        if ( 0 != hnd->base )
        {
            if ( 0 != munmap( (void*)hnd->base, hnd->size ) ) ETRACE( "Failed to munmap handle %p", hnd );
        }
        close( hnd->share_fd );
        if ( 0 != ion_free( m->ion_client, hnd->ion_hnd ) ) ETRACE( "Failed to ion_free( ion_client: %d ion_hnd: %p )", m->ion_client, hnd->ion_hnd );
        memset( (void*)hnd, 0, sizeof( *hnd ) );
    }
}

bool GE2DComposer::initialize(framebuffer_info_t* fbInfo)
{
    if (mInitialized) {
        WTRACE("object has been initialized");
        return true;
    }

    // framebuffer stuff.
    mFbInfo = fbInfo;
    mSingleFbSize = fbInfo->finfo.line_length * fbInfo->info.yres;
    mNumBuffers = fbInfo->fbSize / mSingleFbSize;

    if (!mGe2dBufHnd) {
        int32_t usage = GRALLOC_USAGE_HW_COMPOSER;
        int32_t ret = allocBuffer(mFbInfo->grallocModule, mFbInfo->fbSize, usage, &mGe2dBufHnd);
        if (ret < 0) {
            DEINIT_AND_RETURN_FALSE("allocBuffer failed!");
        }
        private_handle_t const *pHandle = private_handle_t::dynamicCast(mGe2dBufHnd);
        if (pHandle) {
            mSharedFd = pHandle->share_fd;
        }
    } else {
        DTRACE("Buffer alloced already.");
    }

    // create a release fence timeline.
    mSyncTimelineFd = HwcFenceControl::createFenceTimeline();
    if (mSyncTimelineFd == -1) {
        DEINIT_AND_RETURN_FALSE("sync timeline create failed!");
    }
    mCurrentSyncTime = 1;

    // create ge2d composer thread.
    mExitThread = false;
    mThread = new GE2DRenderThread(this);
    if (!mThread.get()) {
        DEINIT_AND_RETURN_FALSE("failed to create ge2d composer thread.");
    }
    mThread->run("GE2DComposer", PRIORITY_URGENT_DISPLAY);

    // ge2d info.
    mSrcBufferInfo = new aml_ge2d_info_t();

    // ge2d init.
    mGe2dFd = ge2d_open();
    mInitialized = true;
    return true;
}

void GE2DComposer::deinitialize()
{
    mExitThread = true;
    mCondition.signal();

    if (mThread.get()) {
        mThread->requestExitAndWait();
        mThread = NULL;
    }

    if (mSrcBufferInfo) {
        delete mSrcBufferInfo;
        mSrcBufferInfo = NULL;
    }

    private_handle_t const* hnd = private_handle_t::dynamicCast(mGe2dBufHnd);
    if (NULL != hnd) {
        freeBuffer(hnd, mFbInfo->grallocModule);
        mGe2dBufHnd = NULL;
    }

    // ge2d exit.
    ge2d_close(mGe2dFd);

    if (mSyncTimelineFd != -1) {
        close(mSyncTimelineFd);
        mSyncTimelineFd = -1;
    }
    mInitialized = false;
}

const char* GE2DComposer::getName() const
{
    return mName;
}

const buffer_handle_t GE2DComposer::getBufHnd()
{
    Mutex::Autolock _l(mLock);

    return mGe2dBufHnd;
}

/* void GE2DComposer::setCurGlesFbSlot(uint32_t slot)
{
    Mutex::Autolock _l(mLock);

    mCurGlesFbSlot = slot;
}*/

void GE2DComposer::mergeRetireFence(int32_t slot, int32_t retireFence)
{
    Mutex::Autolock _l(mLock);
    DTRACE("slot:%d, retireFence: %d", slot, retireFence);

    int32_t index = slot / mFbInfo->info.yres;
    mSlots[index].mSlot = slot;
    int32_t tempFence = HwcFenceControl::merge(String8("retire_fences"), mSlots[index].mFence, retireFence);
    HwcFenceControl::closeFd(retireFence);
    HwcFenceControl::closeFd(mSlots[index].mFence);
    mSlots[index].mFence = tempFence;
}

void GE2DComposer::removeRetireFence(int32_t slot)
{
    Mutex::Autolock _l(mLock);
    DTRACE("slot:%d", slot);

    int32_t index = slot / mFbInfo->info.yres;
    // mSlots[index].mSlot = 0;
    HwcFenceControl::closeFd(mSlots[index].mFence);
    mSlots[index].mFence = -1;
}

void GE2DComposer::setVideoOverlayLayerId(hwc2_layer_t layerId)
{
    Mutex::Autolock _l(mLock);
    DTRACE("layerId:%d", layerId);

    mVideoLayerId = layerId;
}

uint32_t GE2DComposer::findFreeFbSlot()
{
    int32_t fbSlot = 0;

    if (mNumBuffers == 1) {
        // If we have only one buffer, we never use page-flipping.
        return 0;
    }

    if (mBufferMask >= ((1LU<<mNumBuffers)-1)) {
        // We ran out of buffers. reinit to 0;
        mBufferMask = 0x1;
        return 0;
    }

    // find a free slot
    for (uint32_t i=0 ; i<mNumBuffers ; i++) {
        if ((mBufferMask & (1LU<<i)) == 0) {
            mBufferMask |= (1LU<<i);
            break;
        }

        fbSlot += mFbInfo->info.yres;
    }

    return fbSlot;
}

int32_t GE2DComposer::startCompose(
    Vector< hwc2_layer_t > hwcLayers,
    int32_t *offset, int32_t frameCount)
{
    Mutex::Autolock _l(mLock);

    // find a free slot of fb.
    *offset = mFbSlot = findFreeFbSlot();

    // add hwcLayers to work queue.
    int32_t index = mFbSlot / mFbInfo->info.yres;
    mSlots[index].mSlot = mFbSlot;
    mSlots[index].mVideoLayerId = mVideoLayerId;
    if (frameCount < 3) {
        mSlots[index].mClearBuffer = true;
    } else {
        mSlots[index].mClearBuffer = false;
    }
    mSlots[index].mLayersState.clear();
    for (uint32_t i=0; i<hwcLayers.size(); i++) {
        hwc2_layer_t layerId = hwcLayers.itemAt(i);
        HwcLayer* hwcLayer = mDisplayDevice.getLayerById(layerId);
        if (NULL != hwcLayer) {
            // Merge layers's fences and prior retire fence.
            int32_t fence = hwcLayer->getDuppedAcquireFence();
            int32_t tempFence = HwcFenceControl::merge(String8("layers"), fence, mSlots[index].mFence);
            HwcFenceControl::closeFd(mSlots[index].mFence);
            HwcFenceControl::closeFd(fence);
            mSlots[index].mFence = tempFence;

            // push layers state to mQueueItems.
            LayerState* layerState = new LayerState();
            layerState->setLayerState(hwcLayer);
            mSlots[index].mLayersState.push_back(layerState);
        }
    }
    // mSlots[index].mLayersState = layersState;
    android_atomic_inc(&mQueuedFrames);
    mQueueItems.push_back(mSlots[index]);

    mSlots[index].mFence = -1;
    mSlots[index].mVideoLayerId = 0;
    mVideoLayerId = 0;

    int32_t ge2dFence = HwcFenceControl::createFence(mSyncTimelineFd, "ge2d_flag_fence", mCurrentSyncTime++);

    mCondition.signal();
    return ge2dFence;
}

void GE2DComposer::fillRectangle(hwc_rect_t clipRect, uint32_t color, uint32_t offset, int shared_fd)
{
    mSrcBufferInfo->src_info[0].offset = offset;
    mSrcBufferInfo->src_info[0].shared_fd = shared_fd;
    mSrcBufferInfo->src_info[0].format = HAL_PIXEL_FORMAT_RGBA_8888;
    mSrcBufferInfo->src_info[0].rect.x = clipRect.left;
    mSrcBufferInfo->src_info[0].rect.y = clipRect.top;
    mSrcBufferInfo->src_info[0].rect.w = clipRect.right -  clipRect.left;
    mSrcBufferInfo->src_info[0].rect.h = clipRect.bottom - clipRect.top;
    mSrcBufferInfo->src_info[0].canvas_w = clipRect.right -  clipRect.left;
    mSrcBufferInfo->src_info[0].canvas_h = clipRect.bottom - clipRect.top;
    mSrcBufferInfo->src_info[0].memtype = CANVAS_ALLOC;

    mSrcBufferInfo->dst_info.offset = offset;
    mSrcBufferInfo->dst_info.shared_fd = shared_fd;
    mSrcBufferInfo->dst_info.format = HAL_PIXEL_FORMAT_RGBA_8888;
    mSrcBufferInfo->color = color;
    mSrcBufferInfo->offset = 0;
    mSrcBufferInfo->dst_info.rect.x = clipRect.left;
    mSrcBufferInfo->dst_info.rect.y = clipRect.top;
    mSrcBufferInfo->dst_info.rect.w = clipRect.right -  clipRect.left;
    mSrcBufferInfo->dst_info.rect.h = clipRect.bottom - clipRect.top;
    mSrcBufferInfo->dst_info.canvas_w = clipRect.right -  clipRect.left;
    mSrcBufferInfo->dst_info.canvas_h = clipRect.bottom - clipRect.top;
    mSrcBufferInfo->dst_info.memtype = CANVAS_ALLOC;
    mSrcBufferInfo->ge2d_op = AML_GE2D_FILLRECTANGLE;
    ge2d_process(mGe2dFd, mSrcBufferInfo);
}

bool GE2DComposer::isFullScreen(
    hwc_rect_t displayFrame)
{
    if (displayFrame.left == 0
        && displayFrame.top == 0
        && displayFrame.right == mFbInfo->info.xres
        && displayFrame.bottom == mFbInfo->info.yres) {
        return true;
    }

    return false;
}

void GE2DComposer::tracer()
{
    static char const* ge2dOp[] = {
                    "AML_GE2D_FILLRECTANGLE",
                    "AML_GE2D_BLEND",
                    "AML_GE2D_STRETCHBLIT",
                    "AML_GE2D_BLIT",
                    "AML_GE2D_NONE"};

    static char const* memType[] = {
                    "CANVAS_OSD0",
                    "CANVAS_OSD1",
                    "CANVAS_ALLOC",
                    "CANVAS_INVALID"};
    ETRACE("  OP: %22s", ge2dOp[mSrcBufferInfo->ge2d_op]);
    ETRACE(
        "       addr     |     memtype     | canvas size | fmt | tr | blnd |"
        "     source crop (x,y,w,h)      |\n"
        "  --------------+-----------------+-------------+-----+----+------|"
        "--------------------------------+\n");
    ETRACE(
        "  SRC0:\n"
        "   %12x | %15s | %5dx%5d | %03x | %02s | %04s |%5d,%5d,%5d,%5d \n",
                mSrcBufferInfo->src_info[0].offset, memType[mSrcBufferInfo->src_info[0].memtype],
                mSrcBufferInfo->src_info[0].canvas_w, mSrcBufferInfo->src_info[0].canvas_h, mSrcBufferInfo->src_info[0].format,
                "no", "  no", mSrcBufferInfo->src_info[0].rect.x, mSrcBufferInfo->src_info[0].rect.y,
                mSrcBufferInfo->src_info[0].rect.w, mSrcBufferInfo->src_info[0].rect.h);
    ETRACE(
        "  SRC1:\n"
        "   %12x | %15s | %5dx%5d | %03x | %02s | %04s |%5d,%5d,%5d,%5d \n",
                mSrcBufferInfo->src_info[1].offset, memType[mSrcBufferInfo->src_info[1].memtype],
                mSrcBufferInfo->src_info[1].canvas_w, mSrcBufferInfo->src_info[1].canvas_h, mSrcBufferInfo->src_info[1].format,
                "no", "  no", mSrcBufferInfo->src_info[1].rect.x, mSrcBufferInfo->src_info[1].rect.y,
                mSrcBufferInfo->src_info[1].rect.w, mSrcBufferInfo->src_info[1].rect.h);
    ETRACE(
        "  DST:\n"
        "   %12x | %15s | %5dx%5d | %03x | %02x | %04x |%5d,%5d,%5d,%5d \n",
                mSrcBufferInfo->dst_info.offset, memType[mSrcBufferInfo->dst_info.memtype],
                mSrcBufferInfo->dst_info.canvas_w, mSrcBufferInfo->dst_info.canvas_h, mSrcBufferInfo->dst_info.format,
                mSrcBufferInfo->dst_info.rotation, mSrcBufferInfo->blend_mode,
                mSrcBufferInfo->dst_info.rect.x, mSrcBufferInfo->dst_info.rect.y,
                mSrcBufferInfo->dst_info.rect.w, mSrcBufferInfo->dst_info.rect.h);
    ETRACE(
        "  --------------+-----------------+-------------+-----+----+------|"
        "--------------------------------+\n\n");
}

void GE2DComposer::dumpLayers(
    private_handle_t const* hnd)
{
    void *layerBuffer = NULL;

    layerBuffer = mmap(NULL, hnd->size, PROT_READ|PROT_WRITE, MAP_SHARED, hnd->share_fd, 0);
    if (layerBuffer != MAP_FAILED) {
#if 1
        int32_t base = 4 * (hnd->stride * (hnd->height / 2) + 10);
        char* tmp = (char*)layerBuffer + base;
        ETRACE("GE2DComposer dump layer:\n"
            "[0x%x, 0x%x, 0x%x, 0x%x]\n"
            "[0x%x, 0x%x, 0x%x, 0x%x]\n"
            "[0x%x, 0x%x, 0x%x, 0x%x]\n"
            "[0x%x, 0x%x, 0x%x, 0x%x]\n",
            tmp[0], tmp[1], tmp[2], tmp[3],
            tmp[4], tmp[5], tmp[6], tmp[7],
            tmp[8], tmp[9], tmp[10], tmp[11],
            tmp[12], tmp[13], tmp[14], tmp[15]);
#else
        int fd;
        char path[128];

        sprintf(path, "/data/local/tmp/layer_%" PRId64 ".bin", systemTime(SYSTEM_TIME_MONOTONIC));
        fd = open(path, O_RDWR | O_CREAT);
        if (-1 == fd) {
            ETRACE("open file failed!");
            return;
        }
        write(fd, layerBuffer, hnd->size);
        sync();
        close(fd);
#endif
        munmap(layerBuffer, hnd->size);
    } else {
        ETRACE("layerBuffer mmap fail");
    }
}

void GE2DComposer::runGE2DProcess(int32_t slot, Vector< LayerState* > &hwcLayersState)
{
    bool sameSize = false;
    hwc_frect_t sourceCrop[HWC2_MAX_LAYERS];
    const LayerState* layer[HWC2_MAX_LAYERS] = { NULL };
    private_handle_t const* hnd[HWC2_MAX_LAYERS] = { NULL };
    uint32_t layerNum = hwcLayersState.size();
    hwc_rect_t displayFrame[HWC2_MAX_LAYERS];

    for (int32_t i=0; i<layerNum; i++) {
        layer[i] = hwcLayersState.itemAt(i);
        sourceCrop[i] = layer[i]->mSourceCrop;
        displayFrame[i] = layer[i]->mDisplayFrame;
        hnd[i] = private_handle_t::dynamicCast(layer[i]->mBufferHnd);
        DTRACE("layer[%d] zorder: %d, blend: %d, PlaneAlpha: %f, "
            "mColor: [%d, %d, %d, %d], mDataSpace: %d, format hnd[%d]: %x",
            i, layer[i]->mZ, layer[i]->mBlendMode, layer[i]->mPlaneAlpha,
            layer[i]->mColor.r, layer[i]->mColor.g, layer[i]->mColor.b,
            layer[i]->mColor.a, layer[i]->mDataSpace, i, hnd[i] ? hnd[i]->format : 0xff);
    }

    bool debugSameSize = Utils::checkBoolProp("sys.sf.debug.ss");
    // TODO:2 same size layers case.
    if (!debugSameSize && layerNum > HWC2_ONE_LAYER) {
        if (Utils::compareRect(sourceCrop[0], sourceCrop[1])
            && Utils::compareRect(sourceCrop[0], displayFrame[0])
            && Utils::compareRect(sourceCrop[1], displayFrame[1])) {
            sameSize = true;
            // swap layers and hnds.
            Utils::swap(layer[0], layer[1]);
            Utils::swap(hnd[0], hnd[1]);
        }
    }

    if ((layerNum == HWC2_TWO_LAYERS && !hnd[1])
            || (layerNum == HWC2_MAX_LAYERS && (!hnd[1] || !hnd[2]))) {
        ETRACE("%d layers compose, hnd should not be null", layerNum);
        return;
    }

    mSrcBufferInfo->offset = 0;
    if (sameSize) {
        for (int32_t i=0; i<HWC2_TWO_LAYERS; i++) {
            mSrcBufferInfo->src_info[i].offset = 0;
            mSrcBufferInfo->src_info[i].shared_fd = hnd[i]->share_fd;
            mSrcBufferInfo->src_info[i].format = hnd[i]->format;
            mSrcBufferInfo->src_info[i].rect.x = (int32_t)sourceCrop[i].left;
            mSrcBufferInfo->src_info[i].rect.y = (int32_t)sourceCrop[i].top;
            mSrcBufferInfo->src_info[i].rect.w = (int32_t)(sourceCrop[i].right - sourceCrop[i].left);
            mSrcBufferInfo->src_info[i].rect.h = (int32_t)(sourceCrop[i].bottom- sourceCrop[i].top);
            mSrcBufferInfo->src_info[i].canvas_w = hnd[i]->stride;
            mSrcBufferInfo->src_info[i].canvas_h = hnd[i]->height;
            mSrcBufferInfo->src_info[i].memtype = CANVAS_ALLOC;
        }

        mSrcBufferInfo->blend_mode = layer[0]->mBlendMode;

        mSrcBufferInfo->dst_info.offset = slot * mFbInfo->finfo.line_length;
        mSrcBufferInfo->dst_info.shared_fd = mSharedFd;
        mSrcBufferInfo->dst_info.format = HAL_PIXEL_FORMAT_RGBA_8888;
        mSrcBufferInfo->dst_info.rect.x = displayFrame[0].left;
        mSrcBufferInfo->dst_info.rect.y = displayFrame[0].top;
        mSrcBufferInfo->dst_info.rect.w = displayFrame[0].right - displayFrame[0].left;
        mSrcBufferInfo->dst_info.rect.h = displayFrame[0].bottom - displayFrame[0].top;
        mSrcBufferInfo->dst_info.canvas_w = mFbInfo->info.xres;
        mSrcBufferInfo->dst_info.canvas_h = mFbInfo->info.yres;
        mSrcBufferInfo->dst_info.memtype = CANVAS_ALLOC;
        mSrcBufferInfo->dst_info.rotation = layer[0]->mTransform;

        // ge2d processing.
        mSrcBufferInfo->ge2d_op = AML_GE2D_BLEND;
        ge2d_process(mGe2dFd, mSrcBufferInfo);

        if (mDebug) {
            // ETRACE("hnd[0]->format: 0x%x, hnd[1]->format: 0x%x", hnd[0]->format, hnd[1]->format);
            // dumpLayers(hnd[0]);

            ETRACE("  same crop");
            tracer();
        }

        if (layerNum == HWC2_TWO_LAYERS) return;
    }

    int32_t beginWith = 0;
    if (sameSize) {
        if (layerNum == HWC2_THREE_LAYERS) {
            beginWith = HWC2_THREE_LAYERS -1;
        }
    }

    bool canBlend = false;
    for (int32_t i=beginWith; i<layerNum; i++) {
        mSrcBufferInfo->blend_mode = layer[i]->mBlendMode;
        canBlend = Utils::compareSize(sourceCrop[i], displayFrame[i]);

        if (0 == i && !isFullScreen(displayFrame[i])) {
            hwc_rect_t clipRect;
            clipRect.left = 0;
            clipRect.top = 0;
            clipRect.right = mFbInfo->info.xres;
            clipRect.bottom = mFbInfo->info.yres;
            fillRectangle(clipRect, 0, slot * mFbInfo->finfo.line_length, mSharedFd);
        }

        mSrcBufferInfo->src_info[0].offset = 0;
        mSrcBufferInfo->src_info[0].shared_fd = hnd[i]->share_fd;
        mSrcBufferInfo->src_info[0].format = hnd[i]->format;
        mSrcBufferInfo->src_info[0].rect.x = (int32_t)sourceCrop[i].left;
        mSrcBufferInfo->src_info[0].rect.y = (int32_t)sourceCrop[i].top;
        mSrcBufferInfo->src_info[0].rect.w = (int32_t)(sourceCrop[i].right - sourceCrop[i].left);
        mSrcBufferInfo->src_info[0].rect.h = (int32_t)(sourceCrop[i].bottom- sourceCrop[i].top);
        mSrcBufferInfo->src_info[0].canvas_w = hnd[i]->stride;
        mSrcBufferInfo->src_info[0].canvas_h = hnd[i]->height;
        mSrcBufferInfo->src_info[0].memtype = CANVAS_ALLOC;

        // SRC1 equals DST.
        mSrcBufferInfo->src_info[1].offset = slot * mFbInfo->finfo.line_length;
        mSrcBufferInfo->src_info[1].shared_fd = mSharedFd;
        mSrcBufferInfo->src_info[1].format = HAL_PIXEL_FORMAT_RGBA_8888;
        mSrcBufferInfo->src_info[1].rect.x = displayFrame[i].left;
        mSrcBufferInfo->src_info[1].rect.y = displayFrame[i].top;
        mSrcBufferInfo->src_info[1].rect.w = displayFrame[i].right - displayFrame[i].left;
        mSrcBufferInfo->src_info[1].rect.h = displayFrame[i].bottom - displayFrame[i].top;
        mSrcBufferInfo->src_info[1].canvas_w = mFbInfo->info.xres;
        mSrcBufferInfo->src_info[1].canvas_h = mFbInfo->info.yres;
        mSrcBufferInfo->src_info[1].memtype = CANVAS_ALLOC;

        mSrcBufferInfo->dst_info.offset = slot * mFbInfo->finfo.line_length;
        mSrcBufferInfo->dst_info.shared_fd = mSharedFd;
        mSrcBufferInfo->dst_info.format = HAL_PIXEL_FORMAT_RGBA_8888;
        mSrcBufferInfo->dst_info.rect.x = displayFrame[i].left;
        mSrcBufferInfo->dst_info.rect.y = displayFrame[i].top;
        /*mSrcBufferInfo->dst_info.rect.w = displayFrame.right - displayFrame.left;
        mSrcBufferInfo->dst_info.rect.h = displayFrame.bottom - displayFrame.top;*/
        mSrcBufferInfo->dst_info.canvas_w = mFbInfo->info.xres;
        mSrcBufferInfo->dst_info.canvas_h = mFbInfo->info.yres;
        mSrcBufferInfo->dst_info.memtype = CANVAS_ALLOC;

        mSrcBufferInfo->dst_info.rotation = layer[i]->mTransform;

        // ge2d processing.
        if (0 == i || !canBlend || BLEND_MODE_INVALID == mSrcBufferInfo->blend_mode) {
            mSrcBufferInfo->dst_info.rect.w = displayFrame[i].right - displayFrame[i].left;
            mSrcBufferInfo->dst_info.rect.h = displayFrame[i].bottom - displayFrame[i].top;
            mSrcBufferInfo->ge2d_op = AML_GE2D_STRETCHBLIT;
        } else {
            mSrcBufferInfo->dst_info.rect.w = Utils::min(mSrcBufferInfo->src_info[0].rect.w, mSrcBufferInfo->src_info[1].rect.w);
            mSrcBufferInfo->dst_info.rect.h = Utils::min(mSrcBufferInfo->src_info[0].rect.h, mSrcBufferInfo->src_info[1].rect.h);
            mSrcBufferInfo->ge2d_op = AML_GE2D_BLEND;
            // if (mDebug) dumpLayers(hnd[i]);
        }

        ge2d_process(mGe2dFd, mSrcBufferInfo);
        if (mDebug) {
            ETRACE("  layers sameSize is %d", sameSize);
            tracer();
        }
    }
}

// #define GE2D_PORCESS_TIMESTAMP
bool GE2DComposer::threadLoop()
{
    Mutex::Autolock _l(mLock);
    mCondition.wait(mLock);
    if (mExitThread) {
        ITRACE("exiting thread loop");
        return false;
    }

    Fifo::iterator front(mQueueItems.begin());
    // do ge2d compose.
    while (mQueuedFrames > 0 && mQueueItems.size() > 0) {
#ifdef GE2D_PORCESS_TIMESTAMP
        nsecs_t beforeTimeStamp = systemTime(SYSTEM_TIME_MONOTONIC);
#endif
        // wait all layers fence here.
        int32_t slot = front->mSlot;
        int32_t mergedFence = front->mFence;
        Vector< LayerState* > layersState = front->mLayersState;

        { // clear display region.
            bool clearBuffer = front->mClearBuffer;
            hwc_rect_t clipRect;
            uint32_t offset = slot * mFbInfo->finfo.line_length;
            if (clearBuffer) {
                clipRect.left = 0;
                clipRect.top = 0;
                clipRect.right = mFbInfo->info.xres;
                clipRect.bottom = mFbInfo->info.yres;
                fillRectangle(clipRect, 0, offset, mSharedFd);
            }

            hwc2_layer_t videoLayerId = front->mVideoLayerId;
            HwcLayer* videoLayer = mDisplayDevice.getLayerById(videoLayerId);
            if (!clearBuffer && videoLayer) {
                clipRect = videoLayer->getDisplayFrame();
                fillRectangle(clipRect, 0, offset, mSharedFd);
            }
        }

        // wait all fence to be signaled here.
        HwcFenceControl::waitAndCloseFd(mergedFence, 2800);

        // run ge2d process here.
        runGE2DProcess(slot, layersState);

        // ge2d finished process, make sure fd close here.
        for (int32_t i=0; i<layersState.size(); i++) {
            LayerState* layer = layersState.itemAt(i);
            // DTRACE("close->layer:[%12" PRIxPTR ", %d]", layer->mBufferHnd, layer->mBufferFd);
            if (layer != NULL) {
                Utils::closeFd(layer->mBufferFd);
                layer->mBufferFd = -1;
                delete layer;
            }
        }

#ifdef GE2D_PORCESS_TIMESTAMP
        nsecs_t afterTimeStamp = systemTime(SYSTEM_TIME_MONOTONIC);
        ETRACE("Ge2d process Period: %" PRId64 "", afterTimeStamp - beforeTimeStamp);
#endif
        // usleep(1000*100);
        // signal ge2d's release fence.
        HwcFenceControl::syncTimelineInc(mSyncTimelineFd);

        mQueueItems.erase(front);
        front = mQueueItems.begin();
        android_atomic_dec(&mQueuedFrames);
    }

    return true;
}

} // namespace amlogic
} // namesapce android

