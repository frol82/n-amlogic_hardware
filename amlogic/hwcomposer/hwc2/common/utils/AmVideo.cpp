/*
// Copyright (c) 2017 Amlogic
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

#define LOG_TAG "AmVideo"
//#define LOG_NDEBUG 0
#include <cutils/log.h>

#include <AmVideo.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

//#define AMVIDEO_DEBUG

using namespace android;

#define AM_VIDEO_DEV "/dev/amvideo"

#define AMSTREAM_IOC_MAGIC  'S'
#define AMSTREAM_IOC_GLOBAL_GET_VIDEO_OUTPUT  _IOR(AMSTREAM_IOC_MAGIC, 0x21, int)
#define AMSTREAM_IOC_GLOBAL_SET_VIDEO_OUTPUT  _IOW(AMSTREAM_IOC_MAGIC, 0x22, int)
#define AMSTREAM_IOC_GET_VIDEO_DISABLE _IOR((AMSTREAM_IOC_MAGIC), 0x48, int)
#define AMSTREAM_IOC_SET_VIDEO_DISABLE _IOW((AMSTREAM_IOC_MAGIC), 0x49, int)
#define AMSTREAM_IOC_GET_OMX_INFO  _IOR((AMSTREAM_IOC_MAGIC), 0xb2, unsigned int)

AmVideo* AmVideo::mInstance = NULL;
Mutex AmVideo::mLock;

AmVideo::AmVideo() {
    mDevFd = open(AM_VIDEO_DEV, O_RDWR | O_NONBLOCK);
    if (mDevFd < 0) {
        ALOGE("Open %s Failed. ", AM_VIDEO_DEV);
    }

    if (getVideoPresent(mVideoPresent) != 0) {
        ALOGE("Get video mute failed.");
        mVideoPresent = true;
    }
}

AmVideo::~AmVideo() {
    if (mDevFd >= 0) {
        close(mDevFd);
        mDevFd = -1;
    }
}

AmVideo* AmVideo::getInstance() {
    if (mInstance == NULL) {
        Mutex::Autolock _l(mLock);
        if (mInstance == NULL) {
            mInstance = new AmVideo();
        }
    }

    return mInstance;
}

int AmVideo::presentVideo(bool bPresent) {
    if (mDevFd < 0)
        return -EBADF;

    if (mVideoPresent != bPresent) {
        ALOGD("muteVideo to %d", bPresent);
        uint32_t val = bPresent ? 1 : 0;
        if (ioctl(mDevFd, AMSTREAM_IOC_GLOBAL_SET_VIDEO_OUTPUT, val) != 0) {
            ALOGE("AMSTREAM_SET_VIDEO_OUTPUT ioctl (%d) return(%d)", bPresent, errno);
            return -EINVAL;
        }
        mVideoPresent = bPresent;
    } else {
        #ifdef AMVIDEO_DEBUG
        bool val = true;
        getVideoPresent(val);
        if (mVideoPresent != val) {
            ALOGE("presentVideo (%d) vs (%d)", mVideoPresent, val);
        }
        #endif
        ALOGD("Already set video to (%d)", bPresent);
    }

    return 0;
}

int AmVideo::getVideoPresent(bool& output) {
    if (mDevFd < 0)
        return -EBADF;

    uint32_t val = 1;
    if (ioctl(mDevFd, AMSTREAM_IOC_GLOBAL_GET_VIDEO_OUTPUT, &val) != 0) {
        ALOGE("AMSTREAM_GET_VIDEO_OUTPUT ioctl fail(%d)", errno);
        return -EINVAL;
    }

    output = (val ==0) ? false : true;
    return 0;
}

int AmVideo::getvideodisable(int* mode) {
    if (mDevFd < 0)
        return -EBADF;
    int ret = ioctl(mDevFd, AMSTREAM_IOC_GET_VIDEO_DISABLE, mode);
    if (ret < 0) {
        ALOGE("getvideodisable error, ret=%d", ret);
        return ret;
    }
    return 0;
}

int AmVideo::setvideodisable(int mode) {
    if (mDevFd < 0)
        return -EBADF;
    int ret = ioctl(mDevFd, AMSTREAM_IOC_SET_VIDEO_DISABLE, &mode);
    if (ret < 0) {
        ALOGE("setvideodisable error, ret=%d", ret);
        return ret;
    }
    return 0;
}

int AmVideo::getOmxKeepLastFrame(unsigned int *keepLastFrame) {
    if (mDevFd < 0)
        return -EBADF;
    int omx_info = 0;
    int ret = ioctl(mDevFd, AMSTREAM_IOC_GET_OMX_INFO, (unsigned long)&omx_info);
    if (ret < 0) {
        ALOGE("get omx info error, ret =%d", ret);
        *keepLastFrame = 0;
        return ret;
    } else {
        *keepLastFrame = omx_info & 0x1; //omx_info bit0: keep last frmame
    }
    //ALOGV("video layer keepLastFrame %d", *keepLastFrame);
    return 0;

}

