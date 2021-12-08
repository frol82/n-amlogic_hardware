/*
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 *     AMLOGIC OMX IOCTL WRAPPER
 */


#define LOG_NDEBUG 0
#define LOG_TAG "omxutil"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <media/stagefright/foundation/ADebug.h>

#define AMSTREAM_IOC_MAGIC  'S'

#define AMSTREAM_IOC_SET_OMX_VPTS  _IOW(AMSTREAM_IOC_MAGIC, 0xaf, int)
#define AMSTREAM_IOC_SET_VIDEO_DISABLE  _IOW(AMSTREAM_IOC_MAGIC, 0x49, int)

static int amvideo_handle = 0;

#define TVP_SECRET "amlogic_omx_decoder,pts="
#define TVP_SECRET_RENDER "is rendered = true"
#define TVP_SECRET_VERSION "version="
#define TVP_SECRET_FRAME_NUM "frame_num="

int openamvideo() {
    amvideo_handle = open("/dev/amvideo",O_RDWR | O_NONBLOCK);
    return amvideo_handle;
}

void closeamvideo() {
    if (amvideo_handle != 0) {
        int ret = close(amvideo_handle);
        amvideo_handle = 0;
        if (ret < 0)
            ALOGE("close Amvideo error");
    }
}

int setomxdisplaymode() {
    return ioctl(amvideo_handle, AMSTREAM_IOC_SET_VIDEO_DISABLE, 2);

}
int setomxpts(int time_video) {
    return ioctl(amvideo_handle, AMSTREAM_IOC_SET_OMX_VPTS, (unsigned long)&time_video);
}

int setomxpts(uint32_t* omx_info) {
    return ioctl(amvideo_handle, AMSTREAM_IOC_SET_OMX_VPTS, (unsigned long)omx_info);
}

void set_omx_pts(char* data, int* handle) {
    if (data == NULL) {
        ALOGE("hnd->base is NULL!!!!");
        return;
    }
    if (strncmp(data, TVP_SECRET, strlen(TVP_SECRET)) == 0) {
        if (*handle == 0 || amvideo_handle == 0) {
             *handle = openamvideo();
            if (*handle == 0)
                ALOGW("can not open amvideo");
        }
        uint32_t omx_version = 0;
        if (strncmp(data+sizeof(TVP_SECRET)+sizeof(signed long long), TVP_SECRET_RENDER, strlen(TVP_SECRET_RENDER)) != 0) {
            signed long long time;
            int offset = 0;
            offset += sizeof(TVP_SECRET);
            memcpy(&time, (char*)data+offset, sizeof(signed long long));
            offset += sizeof(signed long long);
            int time_video = time * 9 / 100 + 1;
            //ALOGW("render____time=%lld,time_video=%d",time,time_video);
            uint32_t frame_num = 0;
            if (strncmp(data+offset, TVP_SECRET_VERSION, strlen(TVP_SECRET_VERSION)) == 0) {
                offset += sizeof(TVP_SECRET_VERSION);
                memcpy(&omx_version, (char*)data+offset, sizeof(uint32_t));
                offset += sizeof(uint32_t);
            }
            int ret = 0;
            if (omx_version >= 2) {
                if (strncmp(data+offset, TVP_SECRET_FRAME_NUM, strlen(TVP_SECRET_FRAME_NUM)) == 0) {
                    offset += sizeof(TVP_SECRET_FRAME_NUM);
                    memcpy(&frame_num, (char*)data+offset, sizeof(uint32_t));
                    offset += sizeof(uint32_t);
                }
                uint32_t omx_info[6];
                omx_info[0] = time_video;
                omx_info[1] = omx_version;
                omx_info[2] = 1; // set by hw
                omx_info[3] = frame_num;
                omx_info[4] = 0; // 0:need reset omx_pts;1:do not need reset omx_pts
                omx_info[5] = 0; // Reserved
                ret = setomxpts(omx_info);
            } else
                ret = setomxpts(time_video);
            if (ret < 0) {
                ALOGW("setomxpts error, ret =%d",ret);
            }
        }
        memcpy((char*)data + sizeof(TVP_SECRET) + sizeof(signed long long), TVP_SECRET_RENDER, sizeof(TVP_SECRET_RENDER));
    }
}

