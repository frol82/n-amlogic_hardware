/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "EmulatedCamera3_JpegCompressor"

#include <utils/Log.h>
#include <ui/GraphicBufferMapper.h>

#include "JpegCompressor.h"
#include "../EmulatedFakeCamera2.h"
#include "../EmulatedFakeCamera3.h"
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <cutils/properties.h>
#include "NV12_resize.h"


#define EXIF_MAKE_DEFAULT "default_make"
#define EXIF_MODEL_DEFAULT "default_model"
#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array)[0]))
#define FILE_BYTE_ORDER EXIF_BYTE_ORDER_INTEL

const size_t MARKER_LENGTH = 2; // length of a marker
const uint8_t MARK = 0xFF;
const uint8_t EOI = 0xD9;
bool checkJpegEnd(uint8_t *buf) {
    return buf[0] == MARK && buf[1] == EOI;
}
int extraSmallImg(unsigned char* SrcImg,int SrcW,int SrcH,
                unsigned char* DstImg,int DstW,int DstH)
{
    int skipW = SrcW/DstW;
    int skipH = SrcH/DstH;
    unsigned char* dst = DstImg;
    unsigned char* srcrow = SrcImg;
    unsigned char* srcrowidx = srcrow;
    int i = 0,j = 0;
    for (; i<DstH; i++)
    {
        for (j = 0; j<DstW; j++)
        {
            dst[0] = srcrowidx[0];
            dst[1] = srcrowidx[1];
            dst[2] = srcrowidx[2];
            dst += 3;
            srcrowidx += 3*skipW;
        }
        srcrow += skipH*SrcW*3;
        srcrowidx = srcrow;
    }
    return 1;
}

/* start of JPEG image data section */
static const unsigned int image_data_offset = 20;

/* raw EXIF header data */
static const unsigned char exif_header[] = {
  0xff, 0xd8, 0xff, 0xe1
};
/* length of data in exif_header */
static const unsigned int exif_header_len = sizeof(exif_header);


namespace android {

struct string_pair {
    const char* string1;
    const char* string2;
};
static string_pair degress_to_exif_lut [] = {
    {"0",   "1"},
    {"90",  "6"},
    {"180", "3"},
    {"270", "8"},
};

struct params {
    uint8_t* src;
    int src_size;
    uint8_t* dst;
    int dst_size;
    int quality;
    int in_width;
    int in_height;
    int out_width;
    int out_height;
    int format;
    size_t jpeg_size;
};

enum format {
    YUV420SP,
    YUV422I,
    RGB24,
};

JpegCompressor::JpegCompressor():
        Thread(false),
        mIsBusy(false),
        mSynchronous(false),
        mExitJpegThread(false),
        mNeedexif(true),
        mMainJpegSize(0),
        mThumbJpegSize(0),
        mSrcThumbBuffer(NULL),
        mDstThumbBuffer(NULL),
        mBuffers(NULL),
        mPendingrequest(0),
        mListener(NULL) {
        memset(&mInfo,0,sizeof(struct ExifInfo));
}

JpegCompressor::~JpegCompressor() {
    Mutex::Autolock lock(mMutex);
}

void JpegCompressor::queueRequest(CaptureRequest &r) {
    Mutex::Autolock lock(mMutex);

    CaptureRequest* ri = new CaptureRequest();
    ri->buf = new camera3_stream_buffer();
    memcpy(ri->buf,r.buf,sizeof(camera3_stream_buffer_t));
    ri->frameNumber = r.frameNumber;
    ri->sensorBuffers = r.sensorBuffers;
    ri->mNeedThumbnail = r.mNeedThumbnail;
    mInJpegRequestQueue.push_back(ri);

    mPendingrequest++;
    mInJpegRequestSignal.signal();
}

status_t JpegCompressor::start() {
    status_t res;
    res = run("EmulatedFakeCamera2::JpegCompressor");
    if (res != OK) {
        ALOGE("%s: Unable to start up compression thread: %s (%d)",
                __FUNCTION__, strerror(-res), res);
    }
    return res;
}

status_t JpegCompressor::setlistener(JpegListener *listener) {
    status_t res = NO_ERROR;
    if (listener == NULL) {
        ALOGE("%s: NULL listener not allowed!", __FUNCTION__);
        return BAD_VALUE;
    }
    Mutex::Autolock lock(mMutex);
    {
        Mutex::Autolock busyLock(mBusyMutex);

        if (mIsBusy) {
            ALOGE("%s: Already processing a buffer!", __FUNCTION__);
            return INVALID_OPERATION;
        }

        mSynchronous = false;
        mListener = listener;
    }
    return res;
}

status_t JpegCompressor::compressSynchronous(Buffers *buffers) {
    status_t res;

    Mutex::Autolock lock(mMutex);
    {
        Mutex::Autolock busyLock(mBusyMutex);

        if (mIsBusy) {
            ALOGE("%s: Already processing a buffer!", __FUNCTION__);
            return INVALID_OPERATION;
        }

        mIsBusy = true;
        mSynchronous = true;
        mBuffers = buffers;
    }

    res = compress();

    cleanUp();

    return res;
}

status_t JpegCompressor::cancel() {
    mMutex.lock();
    mExitJpegThread = true;
    mPendingrequest++;
    mInJpegRequestSignal.signal();
    mMutex.unlock();
    requestExitAndWait();
    for (List<CaptureRequest*>::iterator i = mInJpegRequestQueue.begin();
         i != mInJpegRequestQueue.end(); i++) {
        delete (*i)->buf;
        delete (*i)->sensorBuffers;
    }

    return OK;
}

status_t JpegCompressor::readyToRun() {
    return OK;
}

status_t JpegCompressor::Create_Exif_Use_Libjpeg() {
    ExifElementsTable* exiftable = NULL;
    struct camera2_jpeg_blob blob;
    int offset;
    status_t res;
    if (mNeedexif) {
        memset(&blob,0,sizeof(struct camera2_jpeg_blob));
        exiftable = new ExifElementsTable();
        GenExif(exiftable);
    }

    if (mJpegRequest.mNeedThumbnail) {
        res = thumbcompress();
    }

    if (exiftable) {
        uint32_t realjpegsize = 0;
        Section_t* exif_section = NULL;
        ExifElementsTable* exif = exiftable;
        exif->insertExifToJpeg((unsigned char*)mJpegBuffer.img,mMainJpegSize);
        if ((mJpegRequest.mNeedThumbnail) && (mDstThumbBuffer != NULL)) {
            exif->insertExifThumbnailImage((const char*)mDstThumbBuffer,mThumbJpegSize);
        }
        exif_section = FindSection(M_EXIF);
        if (exif_section) {
            exif->saveJpeg((unsigned char*) mJpegBuffer.img, mMainJpegSize + exif_section->Size);
        }
        for (uint32_t size = (mMainJpegSize + exif_section->Size - 2); size > 0; size--) {
            if (checkJpegEnd(mJpegBuffer.img + size)) {
                realjpegsize = (size + MARKER_LENGTH);
                break;
            }
        }
        offset = mMaxbufsize-sizeof(struct camera2_jpeg_blob);
        blob.jpeg_blob_id = 0x00FF;
        blob.jpeg_size = realjpegsize;
        memcpy(mJpegBuffer.img+offset, &blob, sizeof(struct camera2_jpeg_blob));
    }

    if (mNeedexif) {
        if (exiftable != NULL) {
            delete exiftable;
            exiftable = NULL;
        }
    }
    return res;
}

status_t JpegCompressor::Create_Exif_Use_Libexif() {
    struct camera2_jpeg_blob blob;
    int offset;
    status_t res;
    memset(&blob,0,sizeof(struct camera2_jpeg_blob));
    if (mNeedexif) {
        uint32_t realjpegsize = 0;
        if (mJpegRequest.mNeedThumbnail) {
            res = thumbcompress();
        }

        exif_buffer *sEb = get_exif_buffer();
        if (sEb != NULL) {
            if (mJpegRequest.mNeedThumbnail) {
                uint8_t * mTempJpegBuffer = (uint8_t *)malloc(mMainJpegSize + sEb->size + mThumbJpegSize);
                memset(mTempJpegBuffer, 0, sizeof(char) * (mMainJpegSize + sEb->size + mThumbJpegSize));
                memcpy(mTempJpegBuffer, exif_header, exif_header_len);
                mTempJpegBuffer[exif_header_len] = (sEb->size + mThumbJpegSize + 2) >> 8;
                mTempJpegBuffer[exif_header_len + 1] = ((sEb->size + mThumbJpegSize + 2) & 0xff);
                memcpy(mTempJpegBuffer + exif_header_len + 2, sEb->data, sEb->size);
                memcpy(mTempJpegBuffer + exif_header_len + sEb->size + 2, mDstThumbBuffer, mThumbJpegSize);
                memcpy(mTempJpegBuffer + exif_header_len + sEb->size + mThumbJpegSize+ 2,
                    mJpegBuffer.img + image_data_offset, mMainJpegSize - image_data_offset);
                memcpy(mJpegBuffer.img, mTempJpegBuffer, mMainJpegSize + sEb->size + mThumbJpegSize);
                if (mTempJpegBuffer != NULL) {
                    free(mTempJpegBuffer);
                    mTempJpegBuffer = NULL;
                }
                for (uint32_t size = (mMainJpegSize + sEb->size + mThumbJpegSize); size > 0; size--) {
                    if (checkJpegEnd(mJpegBuffer.img + size)) {
                        realjpegsize = (size + MARKER_LENGTH);
                        break;
                    }
                }
                offset = mMaxbufsize-sizeof(struct camera2_jpeg_blob);
                blob.jpeg_blob_id = 0x00FF;
                blob.jpeg_size = realjpegsize;
                memcpy(mJpegBuffer.img+offset, &blob, sizeof(struct camera2_jpeg_blob));
                if (sEb != NULL) {
                    if (sEb->data) {
                        free(sEb->data);
                        sEb->data = NULL;
                    }
                    free(sEb);
                    sEb = NULL;
                    CAMHAL_LOGDA("free malloc sEb buffer");
                }
            } else {
                uint8_t * mTempJpegBuffer = (uint8_t *)malloc(mMainJpegSize + sEb->size);
                memset(mTempJpegBuffer, 0, sizeof(char) * (mMainJpegSize + sEb->size));
                memcpy(mTempJpegBuffer, exif_header, exif_header_len);
                mTempJpegBuffer[exif_header_len] = (sEb->size+2) >> 8;
                mTempJpegBuffer[exif_header_len + 1] = ((sEb->size+2) & 0xff);
                memcpy(mTempJpegBuffer + exif_header_len + 2, sEb->data, sEb->size);
                memcpy(mTempJpegBuffer + exif_header_len + sEb->size + 2, mJpegBuffer.img + image_data_offset,
                   mMainJpegSize - image_data_offset);
                memcpy(mJpegBuffer.img, mTempJpegBuffer, mMainJpegSize + sEb->size);
                if (mTempJpegBuffer != NULL) {
                    free(mTempJpegBuffer);
                    mTempJpegBuffer = NULL;
                }
                for (uint32_t size = (mMainJpegSize + sEb->size); size > 0; size--) {
                    if (checkJpegEnd(mJpegBuffer.img + size)) {
                        realjpegsize = (size + MARKER_LENGTH);
                        break;
                    }
                }
                offset = mMaxbufsize-sizeof(struct camera2_jpeg_blob);
                blob.jpeg_blob_id = 0x00FF;
                blob.jpeg_size = realjpegsize;
                memcpy(mJpegBuffer.img+offset, &blob, sizeof(struct camera2_jpeg_blob));
                if (sEb != NULL) {
                    if (sEb->data) {
                        free(sEb->data);
                        sEb->data = NULL;
                    }
                    free(sEb);
                    sEb = NULL;
                    CAMHAL_LOGDA("free malloc sEb buffer");
                }
            }
        } else {
            DBG_LOGA("get exif buffer failed, so only callback Main JPEG data");
            for (uint32_t size = (mMainJpegSize + sEb->size); size > 0; size--) {
                if (checkJpegEnd(mJpegBuffer.img + size)) {
                    realjpegsize = (size + MARKER_LENGTH);
                    break;
                }
            }
            offset = mMaxbufsize-sizeof(struct camera2_jpeg_blob);
            blob.jpeg_blob_id = 0x00FF;
            blob.jpeg_size = realjpegsize;
            memcpy(mJpegBuffer.img+offset, &blob, sizeof(struct camera2_jpeg_blob));
        }
    } else {
            uint32_t realjpegsize = 0;
            for (uint32_t size = (mMainJpegSize); size > 0; size--) {
                if (checkJpegEnd(mJpegBuffer.img + size)) {
                    realjpegsize = (size + MARKER_LENGTH);
                    break;
                }
            }
            int offset = mMaxbufsize-sizeof(struct camera2_jpeg_blob);
            blob.jpeg_blob_id = 0x00FF;
            blob.jpeg_size = realjpegsize;
            memcpy(mJpegBuffer.img+offset, &blob, sizeof(struct camera2_jpeg_blob));
    }
    return res;
}

bool JpegCompressor::threadLoop() {
    status_t res;
    CaptureRequest* ri = NULL;
    {
        mMutex.lock();
        if (mExitJpegThread) {
            mMutex.unlock();
            ALOGE("JpegCompressor Thread : exiting on request0");
            return false;
        }

        while (mPendingrequest == 0) {
            res = mInJpegRequestSignal.wait(mMutex);
        }
        mPendingrequest--;
        if (mInJpegRequestQueue.size() > 0) {
            List<CaptureRequest*>::iterator i = mInJpegRequestQueue.begin();
            mJpegRequest.frameNumber = (*i)->frameNumber;
            mJpegRequest.buf = (*i)->buf;
            mJpegRequest.sensorBuffers = (*i)->sensorBuffers;
            mJpegRequest.mNeedThumbnail = (*i)->mNeedThumbnail;
            ri = *mInJpegRequestQueue.begin();
            mInJpegRequestQueue.erase(mInJpegRequestQueue.begin());
            mBuffers = mJpegRequest.sensorBuffers;
        } else {
            mMutex.unlock();
            return true;
        }
        if (mExitJpegThread) {
            mMutex.unlock();
            ALOGE("JpegCompressor Thread : exiting on request1");
            if (mBuffers != NULL) {
                delete mBuffers;
                mBuffers = NULL;
            }
            if (ri != NULL) {
                if (ri->buf != NULL) {
                    delete ri->buf;
                }
                delete ri;
            }
            return false;
        }
        mMutex.unlock();
    }
    mFoundJpeg = false;
    mFoundAux = false;
    for (size_t i = 0; i < mBuffers->size(); i++) {
        const StreamBuffer &b = (*mBuffers)[i];
        if (b.format == HAL_PIXEL_FORMAT_BLOB) {
            mJpegBuffer = b;
            mFoundJpeg = true;
        } else if (b.streamId <= 0) {
            mAuxBuffer = b;
            mFoundAux = true;
        }
        if (mFoundJpeg && mFoundAux) break;
    }
    if (!mFoundJpeg || !mFoundAux) {
        ALOGE("%s: Unable to find buffers for JPEG source/destination",
                __FUNCTION__);
        return BAD_VALUE;
    }

    struct timeval mTimeStart,mTimeend;
    int intreval;
    ALOGV("%s: Starting compression thread", __FUNCTION__);
    gettimeofday(&mTimeStart, NULL);

    res = compress();

#if PLATFORM_SDK_VERSION <= 22
    Create_Exif_Use_Libjpeg();
#else
    Create_Exif_Use_Libexif();
#endif

    mListener->onJpegDone(mJpegBuffer, res == OK, mJpegRequest);

    if (ri != NULL) {
        if (ri->buf != NULL) {
            delete ri->buf;
        }
        delete ri;
    }
    gettimeofday(&mTimeend, NULL);
    intreval = (mTimeend.tv_sec - mTimeStart.tv_sec) * 1000 + ((mTimeend.tv_usec - mTimeStart.tv_usec))/1000;
    ALOGD("jpeg compress cost time =%d ms",intreval);
    cleanUp();

    return true;
}

struct libjpeg_destination_mgr : jpeg_destination_mgr {
    libjpeg_destination_mgr(uint8_t* input, int size);
    uint8_t* buf;
    int bufsize;
    size_t jpegsize;
};

static void libjpeg_init_destination (j_compress_ptr cinfo) {
    libjpeg_destination_mgr* dest = (libjpeg_destination_mgr*)cinfo->dest;

    dest->next_output_byte = dest->buf;
    dest->free_in_buffer = dest->bufsize;
    dest->jpegsize = 0;
}

static boolean libjpeg_empty_output_buffer(j_compress_ptr cinfo) {
    libjpeg_destination_mgr* dest = (libjpeg_destination_mgr*)cinfo->dest;

    dest->next_output_byte = dest->buf;
    dest->free_in_buffer = dest->bufsize;
    return TRUE; // ?
}

static void libjpeg_term_destination (j_compress_ptr cinfo) {
    libjpeg_destination_mgr* dest = (libjpeg_destination_mgr*)cinfo->dest;
    dest->jpegsize = dest->bufsize - dest->free_in_buffer;
}

libjpeg_destination_mgr::libjpeg_destination_mgr(uint8_t* input, int size) {
    this->init_destination = libjpeg_init_destination;
    this->empty_output_buffer = libjpeg_empty_output_buffer;
    this->term_destination = libjpeg_term_destination;
    this->buf = input;
    this->bufsize = size;
    jpegsize = 0;
}

static void resize_nv12(params* params, uint8_t* dst_buffer) {
    structConvImage o_img_ptr, i_img_ptr;

    if (!params || !dst_buffer) {
        return;
    }

    //input
    i_img_ptr.uWidth =  (mmInt32)params->in_width;
    i_img_ptr.uStride =  (mmInt32)i_img_ptr.uWidth;
    i_img_ptr.uHeight =  (mmInt32)params->in_height;
    i_img_ptr.eFormat = IC_FORMAT_YCbCr420_lp;
    i_img_ptr.imgPtr = (mmByte *) params->src;
    i_img_ptr.clrPtr = (mmByte *)i_img_ptr.imgPtr + (i_img_ptr.uWidth * i_img_ptr.uHeight);
    i_img_ptr.uOffset = 0;

    //ouput
    o_img_ptr.uWidth = (mmInt32)params->out_width;
    o_img_ptr.uStride = (mmInt32)o_img_ptr.uWidth;
    o_img_ptr.uHeight = (mmInt32)params->out_height;
    o_img_ptr.eFormat = IC_FORMAT_YCbCr420_lp;
    o_img_ptr.imgPtr = (mmByte *)dst_buffer;
    o_img_ptr.clrPtr = (mmByte *)o_img_ptr.imgPtr + (o_img_ptr.uWidth * o_img_ptr.uHeight);
    o_img_ptr.uOffset = 0;

    VT_resizeFrame_Video_opt2_lp(&i_img_ptr, &o_img_ptr, NULL, 0);
}

static void resize_yuyv(params* params, uint8_t* dst_buffer) {
    int step_x, step_y;
    int dst_pos, src_pos;
    int src_y_start_pos;
    step_x = params->in_width / params->out_width;
    step_y = params->in_height / params->out_height;
    dst_pos = 0;
    for (int y = 0; y < params->out_height; y++) {
        src_y_start_pos = (y * step_y * (params->in_width * 2));
        for (int x = 0; x < params->out_width; x += 2) {
            src_pos = src_y_start_pos + (x * (step_x * 2));
            dst_buffer[dst_pos++] = params->src[src_pos];
            dst_buffer[dst_pos++] = params->src[src_pos + 1];
            dst_buffer[dst_pos++] = params->src[src_pos + 2];
            dst_buffer[dst_pos++] = params->src[src_pos + 3];
        }
    }
}

/* private static functions */
static void nv21_to_yuv(uint8_t* dst, uint8_t* y, uint8_t* uv, int width) {
    if (!dst || !y || !uv) {
        return;
    }

    while ((width--) > 0) {
        uint8_t y0 = y[0];
        uint8_t v0 = uv[0];
        uint8_t u0 = *(uv+1);
        dst[0] = y0;
        dst[1] = u0;
        dst[2] = v0;
        dst += 3;
        y++;
        if (!(width % 2)) uv+=2;
    }
}

static void yuyv_to_yuv(uint8_t* dst, uint32_t* src, int width) {
    if (!dst || !src) {
        return;
    }

    if (width % 2) {
        return; // not supporting odd widths
    }

    // currently, neon routine only supports multiple of 16 width
    if (width % 16) {
        while ((width-=2) >= 0) {
            uint8_t y0 = (src[0] >> 0) & 0xFF;
            uint8_t u0 = (src[0] >> 8) & 0xFF;
            uint8_t y1 = (src[0] >> 16) & 0xFF;
            uint8_t v0 = (src[0] >> 24) & 0xFF;
            dst[0] = y0;
            dst[1] = u0;
            dst[2] = v0;
            dst[3] = y1;
            dst[4] = u0;
            dst[5] = v0;
            dst += 6;
            src++;
        }
    } else {
        int n = width;
#if defined(__arm__)
        asm volatile (
            "   pld [%[src], %[src_stride], lsl #2]                         \n\t"
            "   cmp %[n], #16                                               \n\t"
            "   blt 5f                                                      \n\t"
            "0: @ 16 pixel swap                                             \n\t"
            "   vld2.8  {q0, q1} , [%[src]]! @ q0 = y q1 = uv               \n\t"
            "   vuzp.8 q1, q2                @ d2 = u d4 = v                \n\t"
            "   vmov d3, d2                  @ q1 = u0u1u2..u0u1u2...       \n\t"
            "   vmov d5, d4                  @ q2 = v0v1v2..v0v1v2...       \n\t"
            "   vzip.8 d2, d3                @ q1 = u0u0u1u1u2u2...         \n\t"
            "   vzip.8 d4, d5                @ q2 = v0v0v1v1v2v2...         \n\t"
            "   vst3.8  {d0,d2,d4},[%[dst]]!                                \n\t"
            "   vst3.8  {d1,d3,d5},[%[dst]]!                                \n\t"
            "   sub %[n], %[n], #16                                         \n\t"
            "   cmp %[n], #16                                               \n\t"
            "   bge 0b                                                      \n\t"
            "5: @ end                                                       \n\t"
#ifdef NEEDS_ARM_ERRATA_754319_754320
            "   vmov s0,s0  @ add noop for errata item                      \n\t"
#endif
            : [dst] "+r" (dst), [src] "+r" (src), [n] "+r" (n)
            : [src_stride] "r" (width)
            : "cc", "memory", "q0", "q1", "q2"
            );
#elif defined(__aarch64__)
#endif
        }
}

static uint32_t calc_frame_length(int format, uint32_t width, uint32_t height)
{
    uint32_t length;
    switch (format) {
        case HAL_PIXEL_FORMAT_YCrCb_420_SP:
            length = width * height * 3/2;
            break;
        case HAL_PIXEL_FORMAT_RGB_888:
            length = width * height * 3;
            break;
        case HAL_PIXEL_FORMAT_YCbCr_422_I:
            length = width * height * 2;
            break;
        default:
            length = width * height * 3/2;
            break;
    }
    return length;
}

size_t encode(params* input) {
    jpeg_compress_struct    cinfo;
    jpeg_error_mgr jerr;
    jpeg_destination_mgr jdest;
    uint8_t* src = NULL;
    uint8_t* resize_src = NULL;
    uint8_t* row_tmp = NULL;
    uint8_t* row_src = NULL;
    uint8_t* row_uv = NULL; // used only for NV12
    int row_stride;
    int out_width = 0, in_width = 0;
    int out_height = 0, in_height = 0;
    int bpp = 2; // for uyvy

    format informat = YUV422I;

    if (!input) {
        return 0;
    }

    out_width = input->out_width;
    in_width = input->in_width;
    out_height = input->out_height;
    in_height = input->in_height;
    src = input->src;
    input->jpeg_size = 0;
    libjpeg_destination_mgr dest_mgr(input->dst, input->dst_size);

    // param check...
    if ((in_width < 2) || (out_width < 2) || (in_height < 2) || (out_height < 2) ||
         (src == NULL) || (input->dst == NULL) || (input->quality < 1) || (input->src_size < 1) ||
         (input->dst_size < 1) ) {
        goto exit;
    }

    if (input->format == HAL_PIXEL_FORMAT_YCrCb_420_SP) {
        informat = YUV420SP;
        bpp = 1;
        if ((in_width != out_width) || (in_height != out_height)) {
            resize_src = (uint8_t*) malloc(out_width * out_height *3);
            if (NULL != resize_src) {
                resize_nv12(input, resize_src);
                if (resize_src) src = resize_src;
            } else {
                CAMHAL_LOGDA("failed to malloc space to extra thumbnail\n");
                goto exit;
            }
        }
    } else if ((input->format == HAL_PIXEL_FORMAT_RGB_888)) {
        informat = RGB24;
        bpp = 1;
        if ((in_width != out_width) || (in_height != out_height)) {
            resize_src = (uint8_t*) malloc(out_width * out_height *3);
            if (NULL != resize_src) {
                extraSmallImg(input->src, in_width, in_height,
                             resize_src, out_width, out_height);
                src = resize_src;
            } else {
                CAMHAL_LOGDA("failed to malloc space to extra thumbnail\n");
                goto exit;
            }
        }
    } else if (input->format == HAL_PIXEL_FORMAT_YCbCr_422_I) {
        informat = YUV422I;
        bpp = 2;
        if ((in_width != out_width) || (in_height != out_height)) {
            resize_src = (uint8_t*) malloc(out_width * out_height *3);
            if (NULL != resize_src) {
                resize_yuyv(input,resize_src);
                if (resize_src) src = resize_src;
            } else {
                CAMHAL_LOGDA("failed to malloc space to extra thumbnail\n");
                goto exit;
            }
        }
    } else if ((in_width != out_width) || (in_height != out_height)) {
        CAMHAL_LOGEB("Encoder: resizing is not supported for this format: %d", input->format);
        goto exit;
    } else if ((input->format != HAL_PIXEL_FORMAT_YCbCr_422_I)) {
        // we currently only support yuv422i and yuv420sp
        CAMHAL_LOGEB("Encoder: format not supported: %d", input->format);
        goto exit;
    }

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);

    CAMHAL_LOGDB("software encoding...  \n\t"
                 "width: %d    \n\t"
                 "height:%d    \n\t"
                 "dest %p      \n\t"
                 "dest size:%d \n\t"
                 "mSrc %p",
                 out_width, out_height, input->dst,
                 input->dst_size, src);

    cinfo.dest = &dest_mgr;
    cinfo.image_width = out_width;
    cinfo.image_height = out_height;
    cinfo.input_components = 3;
    if (informat == RGB24)
        cinfo.in_color_space = JCS_RGB;
    else
        cinfo.in_color_space = JCS_YCbCr;
    cinfo.input_gamma = 1;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, input->quality, TRUE);
    cinfo.dct_method = JDCT_IFAST;

    jpeg_start_compress(&cinfo, TRUE);

    row_tmp = (uint8_t*)malloc(out_width * 3);
    row_src = src;
    row_uv = src + out_width * out_height * bpp;
    row_stride = out_width * 3;

    while ((cinfo.next_scanline < cinfo.image_height)) {
        JSAMPROW row[1];    /* pointer to JSAMPLE row[s] */

        if (informat == RGB24) {
            row[0] = &src[cinfo.next_scanline * row_stride];
            (void) jpeg_write_scanlines(&cinfo, row, 1);
        } else {
            // convert input yuv format to yuv444
            if (informat == YUV420SP) {
                nv21_to_yuv(row_tmp, row_src, row_uv, out_width);
            } else if (informat == YUV422I) {
                //uyvy_to_yuv(row_tmp, (uint32_t*)row_src, out_width);
                yuyv_to_yuv(row_tmp, (uint32_t*)row_src, out_width);
            }

            row[0] = row_tmp;
            jpeg_write_scanlines(&cinfo, row, 1);
            row_src = row_src + out_width*bpp;

            // move uv row if input format needs it
            if (informat == YUV420SP) {
                if (!(cinfo.next_scanline % 2))
                    row_uv = row_uv +  out_width * bpp;
            }
        }
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    if (resize_src) free(resize_src);
    if (row_tmp) free(row_tmp);

 exit:
    input->jpeg_size = dest_mgr.jpegsize;
    return dest_mgr.jpegsize;
}

status_t JpegCompressor::compress() {
    // Find source and target buffers. Assumes only one buffer matches
    // each condition!
    if (mJpegRequest.mNeedThumbnail == true) {
        mSrcThumbBuffer = mAuxBuffer.img;
        if (mDstThumbBuffer == NULL) {
            mDstThumbBuffer = (uint8_t*)malloc(mInfo.thumbwidth * mInfo.thumbheight * 3);
        }
    }

    params  enc_params;
    enc_params.src = mAuxBuffer.img;
    enc_params.src_size = calc_frame_length(mAuxBuffer.format, mAuxBuffer.width, mAuxBuffer.height);
    enc_params.dst = mJpegBuffer.img;
    enc_params.dst_size = mMaxbufsize;
    enc_params.quality = 80;
    enc_params.in_width = mAuxBuffer.width;
    enc_params.in_height = mAuxBuffer.height;
    enc_params.out_width= mAuxBuffer.width;
    enc_params.out_height = mAuxBuffer.height;
    enc_params.format = mAuxBuffer.format;
    enc_params.jpeg_size = 0;

    mMainJpegSize = encode(&enc_params);
    ALOGD("mMainJpegSize = %d",mMainJpegSize);

    return OK;
}

status_t JpegCompressor::thumbcompress() {
    if ((mSrcThumbBuffer == NULL) || (mDstThumbBuffer == NULL))
            return 0;

    params  enc_params;
    enc_params.src = mSrcThumbBuffer;
    enc_params.dst = mDstThumbBuffer;
    enc_params.dst_size = mInfo.thumbwidth * mInfo.thumbheight * 3;
    enc_params.quality = 70;
    enc_params.src_size = calc_frame_length(mAuxBuffer.format, mAuxBuffer.width, mAuxBuffer.height);
    enc_params.in_width = mAuxBuffer.width;
    enc_params.in_height = mAuxBuffer.height;
    enc_params.out_width= mInfo.thumbwidth;
    enc_params.out_height = mInfo.thumbheight;
    enc_params.format = mAuxBuffer.format;
    enc_params.jpeg_size = 0;

    mThumbJpegSize = encode(&enc_params);
    ALOGD("mThumbJpegSize = %d",mThumbJpegSize);

    return OK;
}
bool JpegCompressor::isBusy() {
    Mutex::Autolock busyLock(mBusyMutex);
    return mIsBusy;
}

bool JpegCompressor::isStreamInUse(uint32_t id) {
    Mutex::Autolock lock(mBusyMutex);

    if (mBuffers && mIsBusy) {
        for (size_t i = 0; i < mBuffers->size(); i++) {
            if ( (*mBuffers)[i].streamId == (int)id ) return true;
        }
    }
    return false;
}

bool JpegCompressor::waitForDone(nsecs_t timeout) {
    Mutex::Autolock lock(mBusyMutex);
    status_t res = OK;
    if (mIsBusy) {
        res = mDone.waitRelative(mBusyMutex, timeout);
    }
    return (res == OK);
}

bool JpegCompressor::checkError(const char *msg) {
    if (mJpegErrorInfo) {
        char errBuffer[JMSG_LENGTH_MAX];
        mJpegErrorInfo->err->format_message(mJpegErrorInfo, errBuffer);
        ALOGE("%s: %s: %s",
                __FUNCTION__, msg, errBuffer);
        mJpegErrorInfo = NULL;
        return true;
    }
    return false;
}

void JpegCompressor::cleanUp() {
    status_t res;
    Mutex::Autolock lock(mBusyMutex);
    if (mJpegRequest.mNeedThumbnail == true) {
        if (mSrcThumbBuffer != NULL) {
            mSrcThumbBuffer = NULL;
        }
        if (mDstThumbBuffer != NULL) {
            free(mDstThumbBuffer);
            mDstThumbBuffer = NULL;
        }
    }
    if (mFoundAux) {
        if (mAuxBuffer.streamId == 0) {
            delete[] mAuxBuffer.img;
        } else if (!mSynchronous) {
            mListener->onJpegInputDone(mAuxBuffer);
        }
    }
    if (!mSynchronous) {
        delete mBuffers;
    }

    mBuffers = NULL;

    mIsBusy = false;
    mDone.signal();
}

JpegCompressor::JpegListener::~JpegListener() {
}

void JpegCompressor::SetMaxJpegBufferSize(ssize_t size)
{
    mMaxbufsize = size;
}
ssize_t JpegCompressor::GetMaxJpegBufferSize()
{
    return mMaxbufsize;
}
void JpegCompressor::SetExifInfo(struct ExifInfo info)
{
    memcpy(&mInfo, &info, sizeof(struct ExifInfo));
}
int JpegCompressor::GenExif(ExifElementsTable* exiftable)
{
    char exifcontent[256];
    int width,height;
    bool newexif = true; //add new exif tag for cts
    float exposuretime = 1.0;
    float ApertureValue = 1.0;
    int flash = 0;
    int whitebalance = 1;
    int iso = 100;
    char  SubSecTime[10] = "63";
    char  SubSecTimeOrig[10]= "63";
    char  SubSecTimeDig[10]= "63";
    char property[PROPERTY_VALUE_MAX];

    property_get("ro.product.manufacturer", property, EXIF_MAKE_DEFAULT);
    exiftable->insertElement("Make",property);
    property_get("ro.product.model", property, EXIF_MODEL_DEFAULT);
    exiftable->insertElement("Model",property);
//  int orientation = mInfo.orientation;
    width = mInfo.mainwidth;
    height = mInfo.mainheight;
#if 0
    if (orientation == 0)
        orientation = 1;
    else if (orientation == 90)
        orientation = 6;
    else if (orientation == 180)
        orientation = 3;
    else if (orientation == 270)
        orientation = 8;
    sprintf(exifcontent,"%d",orientation);
    exiftable->insertElement("Orientation",(const char*)exifcontent);
#endif
    sprintf(exifcontent,"%d",width);
    exiftable->insertElement("ImageWidth",(const char*)exifcontent);
    sprintf(exifcontent,"%d",height);
    exiftable->insertElement("ImageLength",(const char*)exifcontent);

    sprintf(exifcontent,"%f",exposuretime);
    exiftable->insertElement("ExposureTime",(const char*)exifcontent);
    sprintf(exifcontent,"%f",ApertureValue);
    exiftable->insertElement("ApertureValue",(const char*)exifcontent);
    sprintf(exifcontent,"%d",flash);
    exiftable->insertElement("Flash",(const char*)exifcontent);
    sprintf(exifcontent,"%d",whitebalance);
    exiftable->insertElement("WhiteBalance",(const char*)exifcontent);
    sprintf(exifcontent,"%d",iso);
    exiftable->insertElement("ISOSpeedRatings",(const char*)exifcontent);
    if (newexif) {
        time_t times;
        {
            time(&times);
            struct tm tmstruct;
            tmstruct = *(localtime(&times)); //convert to local time
            strftime(exifcontent, 30, "%Y:%m:%d %H:%M:%S", &tmstruct);
            exiftable->insertElement("DateTimeDigitized",(const char*)exifcontent);
        }
        {
            sprintf(exifcontent, "%s", SubSecTime);
            exiftable->insertElement("SubSecTime",(const char*)exifcontent);
        }
        {

            sprintf(exifcontent, "%s", SubSecTimeOrig);
            exiftable->insertElement("SubSecTimeOriginal",(const char*)exifcontent);
        }
        {

            sprintf(exifcontent, "%s", SubSecTimeDig);
            exiftable->insertElement("SubSecTimeDigitized",(const char*)exifcontent);
        }
    }

    if (mInfo.has_focallen) {
        float focallen = mInfo.focallen;
        if (focallen >= 0) {
            int focalNum = focallen*1000;
            int focalDen = 1000;
            sprintf(exifcontent,"%d/%d",focalNum,focalDen);
            exiftable->insertElement("FocalLength",(const char*)exifcontent);
        }
    }
    time_t times;
    {
        time(&times);
        struct tm tmstruct;
        tmstruct = *(localtime(&times)); //convert to local time
        strftime(exifcontent, 30, "%Y:%m:%d %H:%M:%S", &tmstruct);
        exiftable->insertElement("DateTime",(const char*)exifcontent);
    }
    if (mInfo.has_gpsTimestamp) {
        times = mInfo.gpsTimestamp;
        if (times != -1) {
            struct tm tmstruct;
            tmstruct = *(gmtime(&times));//convert to standard time
            strftime(exifcontent, 20, "%Y:%m:%d", &tmstruct);
            exiftable->insertElement("GPSDateStamp",(const char*)exifcontent);
            sprintf(exifcontent,"%d/%d,%d/%d,%d/%d",tmstruct.tm_hour,1,tmstruct.tm_min,1,tmstruct.tm_sec,1);
            exiftable->insertElement("GPSTimeStamp",(const char*)exifcontent);
        }
    }
    if (mInfo.has_latitude) {
        int offset = 0;
        float latitude = mInfo.latitude;
        if (latitude < 0.0) {
            offset = 1;
            latitude*= (float)(-1);
        }
        int latitudedegree = latitude;
        float latitudeminuts = (latitude-(float)latitudedegree)*60;
        int latitudeminuts_int = latitudeminuts;
        float latituseconds = (latitudeminuts-(float)latitudeminuts_int)*60+0.5;
        int latituseconds_int = latituseconds;
        sprintf(exifcontent,"%d/%d,%d/%d,%d/%d",latitudedegree,1,latitudeminuts_int,1,latituseconds_int,1);
        exiftable->insertElement("GPSLatitude",(const char*)exifcontent);
        exiftable->insertElement("GPSLatitudeRef",(offset==1)?"S":"N");
    }
    if (mInfo.has_longitude) {
        int offset = 0;
        float longitude = mInfo.longitude;
        if (longitude < 0.0) {
            offset = 1;
            longitude*= (float)(-1);
        }
        int longitudedegree = longitude;
        float longitudeminuts = (longitude-(float)longitudedegree)*60;
        int longitudeminuts_int = longitudeminuts;
        float longitudeseconds = (longitudeminuts-(float)longitudeminuts_int)*60+0.5;
        int longitudeseconds_int = longitudeseconds;
        sprintf(exifcontent,"%d/%d,%d/%d,%d/%d",longitudedegree,1,longitudeminuts_int,1,longitudeseconds_int,1);
        exiftable->insertElement("GPSLongitude",(const char*)exifcontent);
        exiftable->insertElement("GPSLongitudeRef",(offset==1)?"S":"N");
    }
    if (mInfo.has_altitude) {
        int offset = 0;
        float altitude = mInfo.altitude;
        if (altitude < 0.0) {
            offset = 1;
            altitude*= (float)(-1);
        }
        int altitudenum = altitude*1000;
        int altitudedec= 1000;
        sprintf(exifcontent,"%d/%d",altitudenum,altitudedec);
        exiftable->insertElement("GPSAltitude",(const char*)exifcontent);
        sprintf(exifcontent,"%d",offset);
        exiftable->insertElement("GPSAltitudeRef",(const char*)exifcontent);
    }
    if (mInfo.has_gpsProcessingMethod) {
        char* processmethod = (char*)mInfo.gpsProcessingMethod;
        if (processmethod != NULL) {
            memset(exifcontent,0,sizeof(exifcontent));
            char ExifAsciiPrefix[] = { 0x41, 0x53, 0x43, 0x49, 0x49, 0x0, 0x0, 0x0 };//asicii
            memcpy(exifcontent,ExifAsciiPrefix,8);
            memcpy(exifcontent+8,processmethod,strlen(processmethod));
            exiftable->insertElement("GPSProcessingMethod",(const char*)exifcontent);
        }
    }
    return 1;
}

void JpegCompressor::exif_entry_set_string (ExifData * pEdata, ExifIfd eEifd, ExifTag eEtag, const char *s)
{
    ExifEntry *pE;

    pE = exif_entry_new ();
    exif_content_add_entry (pEdata->ifd[eEifd], pE);
    exif_entry_initialize (pE, eEtag);
    if (pE->data)
       free (pE->data);
    pE->components = strlen (s) + 1;
    pE->size = sizeof (char) * pE->components;
    pE->data = (unsigned char *) malloc (pE->size);
    if (!pE->data) {
       DBG_LOGB("Cannot allocate %d bytes.\nTerminating.\n", (int) pE->size);
       exit (1);
    }
    strcpy ((char *) pE->data, (char *) s);
    exif_entry_fix (pE);
    exif_entry_unref (pE);
}

void JpegCompressor::exif_entry_set_short (ExifData * pEdata, ExifIfd eEifd, ExifTag eEtag, ExifShort n)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = exif_entry_new ();
    exif_content_add_entry (pEdata->ifd[eEifd], pE);
    exif_entry_initialize (pE, eEtag);
    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
       exif_set_short (pE->data, eO, n);
    } else {
       DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
    exif_entry_fix (pE);
    exif_entry_unref (pE);
}

void JpegCompressor::exif_entry_set_long (ExifData * pEdata, ExifIfd eEifd, ExifTag eEtag, ExifLong n)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = exif_entry_new ();
    exif_content_add_entry (pEdata->ifd[eEifd], pE);
    exif_entry_initialize (pE, eEtag);
    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
       exif_set_long (pE->data, eO, n);
    } else {
       DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
    exif_entry_fix (pE);
    exif_entry_unref (pE);
}

void JpegCompressor::exif_entry_set_rational (ExifData * pEdata, ExifIfd eEifd, ExifTag eEtag, ExifRational r)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = exif_entry_new ();
    exif_content_add_entry (pEdata->ifd[eEifd], pE);
    exif_entry_initialize (pE, eEtag);
    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
       exif_set_rational (pE->data, eO, r);
    } else {
       DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
    exif_entry_fix (pE);
    exif_entry_unref (pE);
}

void JpegCompressor::exif_entry_set_undefined (ExifData * pEdata, ExifIfd eEifd, ExifTag eEtag, exif_buffer * buf)
{
    ExifEntry *pE;
    pE = exif_entry_new ();
    exif_content_add_entry (pEdata->ifd[eEifd], pE);
    exif_entry_initialize (pE, eEtag);
    if (buf != NULL) {
        if (pE->data)
            free (pE->data);
        pE->components = buf->size;
        pE->size = buf->size;
        pE->data = (unsigned char *) malloc (pE->size);
        if (!pE->data) {
            DBG_LOGB("Cannot allocate %d bytes.\nTerminating.\n", (int) pE->size);
            exit (1);
        }
        memcpy ((void *) pE->data, (void *) buf->data, buf->size);
    }
    exif_entry_fix (pE);
    exif_entry_unref (pE);
}

/****************************************************************************
 * Public API
 ***************************************************************************/

/* Get an existing tag, or create one if it doesn't exist */
ExifEntry* JpegCompressor::init_tag(ExifData *exif, ExifIfd ifd, ExifTag tag)
{
    ExifEntry *entry;
    /* Return an existing tag if one exists */
    if (!((entry = exif_content_get_entry (exif->ifd[ifd], tag)))) {
        /* Allocate a new entry */
        entry = exif_entry_new ();
        assert(entry != NULL); /* catch an out of memory condition */
        entry->tag = tag; /* tag must be set before calling
                                             exif_content_add_entry */

        /* Attach the ExifEntry to an IFD */
        exif_content_add_entry (exif->ifd[ifd], entry);

        /* Allocate memory for the entry and fill with default data */
        exif_entry_initialize (entry, tag);

        /* Ownership of the ExifEntry has now been passed to the IFD.
               * One must be very careful in accessing a structure after
               * unref'ing it; in this case, we know "entry" won't be freed
              * because the reference count was bumped when it was added to
              * the IFD.
              */
        exif_entry_unref(entry);
    }
    return entry;
}

/* Create a brand-new tag with a data field of the given length, in the
 * given IFD. This is needed when exif_entry_initialize() isn't able to create
 * this type of tag itself, or the default data length it creates isn't the
 * correct length.
 */
ExifEntry *JpegCompressor::create_tag(ExifData *exif, ExifIfd ifd, ExifTag tag, size_t len)
{
    void *buf;
    ExifEntry *entry;

    /* Create a memory allocator to manage this ExifEntry */
    ExifMem *mem = exif_mem_new_default();
    assert(mem != NULL); /* catch an out of memory condition */

    /* Create a new ExifEntry using our allocator */
    entry = exif_entry_new_mem (mem);
    assert(entry != NULL);

    /* Allocate memory to use for holding the tag data */
    buf = exif_mem_alloc(mem, len);
    assert(buf != NULL);

    /* Fill in the entry */
    entry->data = (unsigned char*)buf;
    entry->size = len;
    entry->tag = tag;
    entry->components = len;
    entry->format = EXIF_FORMAT_UNDEFINED;

    /* Attach the ExifEntry to an IFD */
    exif_content_add_entry (exif->ifd[ifd], entry);

    /* The ExifMem and ExifEntry are now owned elsewhere */
    exif_mem_unref(mem);
    exif_entry_unref(entry);

    return entry;
}

void JpegCompressor::exif_entry_set_gps_coord(ExifData * pEdata, ExifTag eEtag,
    ExifRational r1, ExifRational r2, ExifRational r3)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = create_tag(pEdata, EXIF_IFD_GPS, eEtag,
          3 * exif_format_get_size(EXIF_FORMAT_RATIONAL));

    pE->components = 3;
    pE->format = EXIF_FORMAT_RATIONAL;

    eO = exif_data_get_byte_order (pE->parent->parent);

    if (pE->data) {
        exif_set_rational (pE->data, eO, r1);
        exif_set_rational (pE->data + exif_format_get_size (pE->format), eO, r2);
        exif_set_rational (pE->data + 2 * exif_format_get_size (pE->format), eO, r3);
    } else {
        DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
}

void JpegCompressor::exif_entry_set_gps_altitude(ExifData * pEdata, ExifTag eEtag, ExifRational r1)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = create_tag(pEdata, EXIF_IFD_GPS, eEtag,
          1 * exif_format_get_size(EXIF_FORMAT_RATIONAL));

    pE->components = 1;
    pE->format = EXIF_FORMAT_RATIONAL;

    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
        exif_set_rational (pE->data, eO, r1);
    } else {
        DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
}

void JpegCompressor::exif_entry_set_gps_coord_ref(ExifData * pEdata, ExifTag eEtag, const char *s)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = create_tag(pEdata, EXIF_IFD_GPS, eEtag,
          (strlen (s) + 1) * exif_format_get_size(EXIF_FORMAT_ASCII));

    pE->components = strlen (s) + 1;
    pE->format = EXIF_FORMAT_ASCII;

    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
        strcpy ((char *) pE->data, s);
    } else {
        DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
}

void JpegCompressor::exif_entry_set_gps_altitude_ref(ExifData * pEdata, ExifTag eEtag, ExifByte n)
{
    ExifEntry *pE;
    ExifByteOrder eO;

    pE = create_tag(pEdata, EXIF_IFD_GPS, eEtag,
           1 * exif_format_get_size(EXIF_FORMAT_BYTE));

    pE->components = 1;
    pE->format = EXIF_FORMAT_BYTE;

    eO = exif_data_get_byte_order (pE->parent->parent);
    if (pE->data) {
        *(pE->data) = n;
    } else {
        DBG_LOGB("ERROR: unallocated e->data Tag %d\n", eEtag);
    }
}

exif_buffer * JpegCompressor::get_exif_buffer() {

    char exifcontent[256];
    ExifData *pEd;
    ExifEntry *entry;
    exif_buffer *sEb;
    ExifRational sR;
    int res;
    int orientation;
    struct timeval sTv;
    time_t times;
    struct tm tmstruct;
    char property[PROPERTY_VALUE_MAX];

    sEb = (exif_buffer *) malloc (sizeof (exif_buffer));

    pEd = exif_data_new ();

    if (pEd == NULL)
        goto EXIT;

    /* Set the image options */
    exif_data_set_option(pEd, EXIF_DATA_OPTION_FOLLOW_SPECIFICATION);
    exif_data_set_data_type(pEd, EXIF_DATA_TYPE_COMPRESSED);
    exif_data_set_byte_order(pEd, FILE_BYTE_ORDER);

    property_get("ro.product.manufacturer", property, EXIF_MAKE_DEFAULT);
    exif_entry_set_string (pEd, EXIF_IFD_0, EXIF_TAG_MAKE, property);
    property_get("ro.product.model", property, EXIF_MODEL_DEFAULT);
    exif_entry_set_string (pEd, EXIF_IFD_0, EXIF_TAG_MODEL, property);

    switch (mInfo.orientation) {
        case 180:
            orientation = 3;
            //orientation = 1;
            break;
        case 90:
            orientation = 6;
            //orientation = 8;
            break;
        case 270:
            orientation = 8;
            break;
        default:
            orientation = 1;
            break;
    }

    exif_entry_set_short(pEd, EXIF_IFD_0, EXIF_TAG_ORIENTATION, (ExifShort)orientation);

    sR.numerator = 1;
    sR.denominator = 629;
    exif_entry_set_rational (pEd, EXIF_IFD_EXIF, EXIF_TAG_EXPOSURE_TIME, sR);

    /* time */
    /* this sould be last resort */
    time(&times);
    tmstruct = *(localtime(&times)); //convert to local time
    res = gettimeofday (&sTv, NULL);
    strftime(exifcontent, 20, "%Y:%m:%d %H:%M:%S", &tmstruct);
    exif_entry_set_string (pEd, EXIF_IFD_0, EXIF_TAG_DATE_TIME, exifcontent);
    exif_entry_set_string (pEd, EXIF_IFD_EXIF, EXIF_TAG_DATE_TIME_ORIGINAL, exifcontent);
    exif_entry_set_string (pEd, EXIF_IFD_EXIF, EXIF_TAG_DATE_TIME_DIGITIZED, exifcontent);

    sR.numerator = 28;
    sR.denominator = 10;
    exif_entry_set_rational (pEd, EXIF_IFD_EXIF, EXIF_TAG_FNUMBER, sR);//android 6 is EXIF_TAG_APERTURE_VALUE

    exif_entry_set_short(pEd, EXIF_IFD_EXIF, EXIF_TAG_FLASH, 0);

    sR.numerator = 3299;
    sR.denominator = 1000;
    exif_entry_set_rational(pEd, EXIF_IFD_EXIF, EXIF_TAG_FOCAL_LENGTH, sR);

    memset(exifcontent, 0, sizeof(exifcontent));
    snprintf(exifcontent, 20, "%06d", (int) sTv.tv_usec);
    exif_entry_set_string (pEd, EXIF_IFD_EXIF, EXIF_TAG_SUB_SEC_TIME, exifcontent);
    exif_entry_set_string (pEd, EXIF_IFD_EXIF, EXIF_TAG_SUB_SEC_TIME_ORIGINAL, exifcontent);
    exif_entry_set_string (pEd, EXIF_IFD_EXIF, EXIF_TAG_SUB_SEC_TIME_DIGITIZED, exifcontent);

    exif_entry_set_short (pEd, EXIF_IFD_EXIF, EXIF_TAG_WHITE_BALANCE, 0);

    if (mInfo.has_latitude) {
        ExifRational r1, r2, r3;
        int offset = 0;
        /* gps data */
        r1.denominator = 1;
        r2.denominator = 1;
        r3.denominator = 1;

        float latitude = mInfo.latitude;
        if (latitude < 0.0) {
            latitude*= (float)(-1);
            offset = 1;
        }
        r1.numerator = (uint32_t)latitude;
        float latitudeminuts = (latitude-(float)(r1.numerator))*60;
        r2.numerator = (uint32_t)latitudeminuts;
        float latituseconds = (latitudeminuts-(float)(r2.numerator))*60+0.5;
        r3.numerator = (uint32_t)latituseconds;
        exif_entry_set_gps_coord(pEd, (ExifTag) EXIF_TAG_GPS_LATITUDE, r1, r2, r3);
        exif_entry_set_gps_coord_ref(pEd, (ExifTag) EXIF_TAG_GPS_LATITUDE_REF, offset == 1 ? "S":"N");
    }

    if (mInfo.has_longitude) {
        ExifRational r1, r2, r3;
        int offset = 0;
        /* gps data */
        r1.denominator = 1;
        r2.denominator = 1;
        r3.denominator = 1;

        float longitude = mInfo.longitude;
        if (longitude < 0.0) {
            longitude*= (float)(-1);
            offset = 1;
        }
        r1.numerator = (uint32_t)longitude;
        float longitudeminuts = (longitude-(float)(r1.numerator))*60;
        r2.numerator = (uint32_t)longitudeminuts;
        float longitudeseconds = (longitudeminuts-(float)(r2.numerator))*60+0.5;
        r3.numerator = (uint32_t)longitudeseconds;
        exif_entry_set_gps_coord(pEd, (ExifTag) EXIF_TAG_GPS_LONGITUDE, r1, r2, r3);
        exif_entry_set_gps_coord_ref(pEd, (ExifTag) EXIF_TAG_GPS_LONGITUDE_REF, offset == 1 ? "W":"E");
    }

    if (mInfo.has_altitude) {
        ExifRational r1;
        int offset = 0;
        float altitude = mInfo.altitude;
        if (altitude < 0.0) {
            altitude*= (float)(-1);
            offset = 1;
        }
        r1.denominator = 1;
        r1.numerator = (uint32_t)altitude;
        exif_entry_set_gps_altitude(pEd, (ExifTag) EXIF_TAG_GPS_ALTITUDE, r1);
        exif_entry_set_gps_altitude_ref(pEd, (ExifTag) EXIF_TAG_GPS_ALTITUDE_REF, (ExifByte)offset);
    }

    if (mInfo.has_gpsTimestamp) {
        ExifRational r1, r2, r3;
        time_t times;
        struct tm tmstruct;
        times = mInfo.gpsTimestamp;

        r1.denominator = 1;
        r2.denominator = 1;
        r3.denominator = 1;
        memset(exifcontent, 0, sizeof(exifcontent));
        if (times != -1) {
            tmstruct = *(gmtime(&times));//convert to standard time
            strftime(exifcontent, 20, "%Y:%m:%d", &tmstruct);
            exif_entry_set_gps_coord_ref(pEd, (ExifTag) EXIF_TAG_GPS_DATE_STAMP, exifcontent);

            r1.numerator = tmstruct.tm_hour;
            r2.numerator = tmstruct.tm_min;
            r3.numerator = tmstruct.tm_sec;
            exif_entry_set_gps_coord(pEd, (ExifTag) EXIF_TAG_GPS_TIME_STAMP, r1, r2, r3);
        }
    }

    if (mInfo.has_gpsProcessingMethod) {
        char* processmethod = (char*)mInfo.gpsProcessingMethod;
        if (processmethod != NULL) {
            const char ExifAsciiPrefix[] = { 0x41, 0x53, 0x43, 0x49, 0x49, 0x0, 0x0, 0x0 };//asicii
            unsigned char* data = (unsigned char*)malloc(strlen(processmethod) + sizeof(ExifAsciiPrefix));
            exif_buffer buffer;
            if (data != NULL)
            {
                memcpy(data, ExifAsciiPrefix, sizeof(ExifAsciiPrefix));
                memcpy(data+sizeof(ExifAsciiPrefix), processmethod, strlen(processmethod));
                buffer.data = data;
                buffer.size = strlen(processmethod)+sizeof(ExifAsciiPrefix);
                exif_entry_set_undefined (pEd, EXIF_IFD_GPS, (ExifTag) EXIF_TAG_GPS_PROCESSING_METHOD, &buffer);
                free(data);
            }
        }
    }

    //write IDF1 for thumbnail
    if (mJpegRequest.mNeedThumbnail) {
        exif_entry_set_short(pEd, EXIF_IFD_1, EXIF_TAG_IMAGE_WIDTH, mInfo.thumbwidth);
        exif_entry_set_short(pEd, EXIF_IFD_1, EXIF_TAG_IMAGE_LENGTH, mInfo.thumbheight);
        exif_entry_set_short(pEd, EXIF_IFD_1, EXIF_TAG_ORIENTATION, (ExifShort)orientation);
        //fan say need check
        entry = init_tag(pEd, EXIF_IFD_1, EXIF_TAG_EXIF_IFD_POINTER);
        entry = init_tag(pEd, EXIF_IFD_1, EXIF_TAG_JPEG_INTERCHANGE_FORMAT);
        entry = init_tag(pEd, EXIF_IFD_1, EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH);
        exif_set_long(entry->data, FILE_BYTE_ORDER, (long)mThumbJpegSize);
        entry = init_tag(pEd, EXIF_IFD_1, EXIF_TAG_COMPRESSION);
        exif_set_short (entry->data, FILE_BYTE_ORDER, 6);
    }

    /* copy data to our buffer */
    exif_data_save_data (pEd, &sEb->data, &sEb->size);
    assert(sEb->data != NULL);

    if (mJpegRequest.mNeedThumbnail) {
        entry = init_tag(pEd, EXIF_IFD_1, EXIF_TAG_JPEG_INTERCHANGE_FORMAT);
        exif_set_long(entry->data, FILE_BYTE_ORDER, (long)(sEb->size + 6 - 0x0c));

        exif_data_save_data(pEd, &sEb->data, &sEb->size);
        assert(sEb->data != NULL);
    }
    DBG_LOGB("total exif data length = %d\n", sEb->size);
    /* destroy exif structure */
    exif_data_unref(pEd);

    return sEb;

EXIT:
    if (sEb != NULL)
        free(sEb);

    return NULL;
}

const char* ExifElementsTable::degreesToExifOrientation(const char* degrees) {
    for (unsigned int i = 0; i < ARRAY_SIZE(degress_to_exif_lut); i++) {
        if (!strcmp(degrees, degress_to_exif_lut[i].string1)) {
            return degress_to_exif_lut[i].string2;
        }
    }
    return NULL;
}
void ExifElementsTable::stringToRational(const char* str, unsigned int* num, unsigned int* den) {
    int len;
    char * tempVal = NULL;
    if (str != NULL) {
        len = strlen(str);
        tempVal = (char*) malloc( sizeof(char) * (len + 1));
    }
    if (tempVal != NULL) {
        size_t den_len;
        char *ctx;
        unsigned int numerator = 0;
        unsigned int denominator = 0;
        char* temp = NULL;
        memset(tempVal, '\0', len + 1);
        strncpy(tempVal, str, len);
        temp = strtok_r(tempVal, ".", &ctx);
        if (temp != NULL)
            numerator = atoi(temp);
        if (!numerator)
            numerator = 1;
        temp = strtok_r(NULL, ".", &ctx);
        if (temp != NULL) {
            den_len = strlen(temp);
            if(HUGE_VAL == den_len ) {
                den_len = 0;
            }
            denominator = static_cast<unsigned int>(pow(10, den_len));
            numerator = numerator * denominator + atoi(temp);
        } else {
            denominator = 1;
        }
        free(tempVal);
        *num = numerator;
        *den = denominator;
    }
}
bool ExifElementsTable::isAsciiTag(const char* tag) {
    return (strcmp(tag, TAG_GPS_PROCESSING_METHOD) == 0);
}
status_t ExifElementsTable::insertElement(const char* tag, const char* value) {
    int value_length = 0;
    status_t ret = NO_ERROR;
    if (!value || !tag) {
        return -EINVAL;
    }
    if (position >= MAX_EXIF_TAGS_SUPPORTED) {
        CAMHAL_LOGEA("Max number of EXIF elements already inserted");
        return NO_MEMORY;
    }
    if (isAsciiTag(tag)) {
        value_length = sizeof(ExifAsciiPrefix) + strlen(value + sizeof(ExifAsciiPrefix));
    } else {
        value_length = strlen(value);
    }
    if (IsGpsTag(tag)) {
        table[position].GpsTag = TRUE;
        table[position].Tag = GpsTagNameToValue(tag);
        gps_tag_count++;
    } else {
        table[position].GpsTag = FALSE;
        table[position].Tag = TagNameToValue(tag);
        exif_tag_count++;
    }
    table[position].DataLength = 0;
    table[position].Value = (char*) malloc(sizeof(char) * (value_length + 1));
    if (table[position].Value) {
        memcpy(table[position].Value, value, value_length + 1);
        table[position].DataLength = value_length + 1;
    }
    position++;
    return ret;
}
void  ExifElementsTable::saveJpeg(unsigned char* jpeg, size_t jpeg_size) {
    int ret;
    if (jpeg_opened) {
        ret = WriteJpegToBuffer(jpeg, jpeg_size);
        ALOGD("saveJpeg :: ret =%d",ret);
        DiscardData();
        jpeg_opened = false;
    }
}
void ExifElementsTable::insertExifToJpeg(unsigned char* jpeg, size_t jpeg_size) {
    ReadMode_t read_mode = (ReadMode_t)(READ_METADATA | READ_IMAGE);
    ResetJpgfile();
    if (ReadJpegSectionsFromBuffer(jpeg, jpeg_size, read_mode)) {
        jpeg_opened = true;
        create_EXIF(table, exif_tag_count, gps_tag_count,true);
    }
}
status_t ExifElementsTable::insertExifThumbnailImage(const char* thumb, int len) {
    status_t ret = NO_ERROR;
    if ((len > 0) && jpeg_opened) {
        ret = ReplaceThumbnailFromBuffer(thumb, len);
        CAMHAL_LOGDB("insertExifThumbnailImage. ReplaceThumbnail(). ret=%d", ret);
    }
    return ret;
}
ExifElementsTable::~ExifElementsTable() {
    int num_elements = gps_tag_count + exif_tag_count;
    for (int i = 0; i < num_elements; i++) {
        if (table[i].Value) {
            free(table[i].Value);
        }
    }
    if (jpeg_opened) {
        DiscardData();
    }
}
} // namespace android
