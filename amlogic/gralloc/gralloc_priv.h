/*
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 *
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef GRALLOC_PRIV_H_
#define GRALLOC_PRIV_H_

#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#include <utils/Log.h>

#include <hardware/gralloc.h>
#include <cutils/native_handle.h>
#include "alloc_device.h"
#include "framebuffer.h"
#include <utils/Log.h>

#include "format_chooser.h"

#define HAL_PIXEL_FORMAT_YCbCr_420_SP 0x100
//#define MALI_ION  1

#define GRALLOC_ARM_UMP_MODULE 0
#define GRALLOC_ARM_DMA_BUF_MODULE 1
#if MALI_AFBC_GRALLOC
#define MALI_AFBC_GRALLOC 1
#endif
#if !defined(GRALLOC_OLD_ION_API)
/* new libion */
typedef int ion_user_handle_t;
#define ION_INVALID_HANDLE 0
#else
typedef struct ion_handle *ion_user_handle_t;
#define ION_INVALID_HANDLE NULL
#endif /* GRALLOC_OLD_ION_API */

/* NOTE:
 * If your framebuffer device driver is integrated with UMP, you will have to
 * change this IOCTL definition to reflect your integration with the framebuffer
 * device.
 * Expected return value is a UMP secure id backing your framebuffer device memory.
 */
#if GRALLOC_ARM_UMP_MODULE
#define IOCTL_GET_FB_UMP_SECURE_ID	_IOWR('m', 0xF8, __u32)
#endif

/* NOTE:
 * If your framebuffer device driver is integrated with dma_buf, you will have to
 * change this IOCTL definition to reflect your integration with the framebuffer
 * device.
 * Expected return value is a structure filled with a file descriptor
 * backing your framebuffer device memory.
 */
#if GRALLOC_ARM_DMA_BUF_MODULE
struct fb_dmabuf_export
{
	__u32 buffer_idx;
	__u32 fd;
	__u32 flags;
};
#define FBIOGET_DMABUF	_IOR('F', 0x21, struct fb_dmabuf_export)
#define FBIOGET_OSD_DMABUF               0x46fc
#endif

/* the max string size of GRALLOC_HARDWARE_GPU0 & GRALLOC_HARDWARE_FB0
 * 8 is big enough for "gpu0" & "fb0" currently
 */
#define MALI_GRALLOC_HARDWARE_MAX_STR_LEN 8

/* Define number of shared file descriptors */
#if MALI_AFBC_GRALLOC == 1 && GRALLOC_ARM_DMA_BUF_MODULE
#define GRALLOC_ARM_NUM_FDS 2
#elif MALI_AFBC_GRALLOC == 1 || GRALLOC_ARM_DMA_BUF_MODULE
#define GRALLOC_ARM_NUM_FDS 1
#else
#define GRALLOC_ARM_NUM_FDS 0
#endif


#define NUM_INTS_IN_PRIVATE_HANDLE ((sizeof(struct private_handle_t) - sizeof(native_handle)) / sizeof(int) - sNumFds)

// This value is platform specific and should be set according to hardware YUV planes restrictions.
// Please note that EGL winsys platform config file needs to use the same value when importing buffers.
#define YUV_MALI_PLANE_ALIGN 32

// Default YUV stride aligment in Android
#define YUV_ANDROID_PLANE_ALIGN 16


#if GRALLOC_ARM_UMP_MODULE
#include <ump/ump.h>
#endif

#define SZ_4K      0x00001000
#define SZ_2M      0x00200000

typedef enum
{
	MALI_YUV_NO_INFO,
	MALI_YUV_BT601_NARROW,
	MALI_YUV_BT601_WIDE,
	MALI_YUV_BT709_NARROW,
	MALI_YUV_BT709_WIDE
} mali_gralloc_yuv_info;

typedef enum
{
	MALI_DPY_TYPE_UNKNOWN = 0,
	MALI_DPY_TYPE_CLCD,
	MALI_DPY_TYPE_HDLCD
} mali_dpy_type;

struct private_handle_t;

//used by gralloc mode to only.
struct framebuffer_mapper_t{
    private_handle_t* framebuffer;
    framebuffer_info_t fb_info;
    uint32_t numBuffers;
    uint32_t bufferMask;
    uint32_t bufferSize;
};

//TODO: NEED CHANGE NAME TO BE MORE READABLE!!
struct framebuffer_t{
    struct framebuffer_device_t base;
    struct framebuffer_info_t fb_info;
    struct private_handle_t*  fb_hnd;
};

struct private_module_t
{
	gralloc_module_t base;

	framebuffer_mapper_t fb_primary;
	framebuffer_mapper_t fb_external;
	pthread_mutex_t lock;
	int ion_client;
	mali_dpy_type dpy_type;

	int swapInterval;

	enum
	{
		// flag to indicate we'll post this buffer
		PRIV_USAGE_LOCKED_FOR_POST = 0x80000000
	};

#ifdef __cplusplus
	/* default constructor */
	private_module_t();
#endif
};


/*
ATTENTATION: don't add member in this struct, it is used by other modules.
*/
#ifdef __cplusplus
struct private_handle_t : public native_handle
{
#else
struct private_handle_t
{
	struct native_handle nativeHandle;
#endif

	enum
	{
		PRIV_FLAGS_FRAMEBUFFER = 0x00000001,
		PRIV_FLAGS_USES_UMP    = 0x00000002,
		PRIV_FLAGS_USES_ION    = 0x00000004,
		PRIV_FLAGS_USES_ION_DMA_HEAP = 0x00000008,
		PRIV_FLAGS_VIDEO_OVERLAY = 0x00000010,
		PRIV_FLAGS_VIDEO_OMX     = 0x00000020,
		PRIV_FLAGS_CURSOR = 0x00000040,
		PRIV_FLAGS_OSD_VIDEO_OMX = 0x00000080,
		PRIV_FLAGS_CONTINUOUS_BUF = 0x00000100,
		PRIV_FLAGS_SECURE_PROTECTED = 0x00000200,
	};

	enum
	{
		LOCK_STATE_WRITE     =   1<<31,
		LOCK_STATE_MAPPED    =   1<<30,
		LOCK_STATE_READ_MASK =   0x3FFFFFFF
	};

#if GRALLOC_ARM_DMA_BUF_MODULE
	/*
	 * Shared file descriptor for dma_buf sharing. This must be the first element in the
	 * structure so that binder knows where it is and can properly share it between
	 * processes.
	 * DO NOT MOVE THIS ELEMENT!
	 */
	int     share_fd;
#endif

	int     share_attr_fd;

#if GRALLOC_ARM_DMA_BUF_MODULE
	ion_user_handle_t ion_hnd;
#endif

	// ints
	int        magic;
	int        req_format;
	uint64_t   internal_format;
	int        byte_stride;
	int        flags;
	int        usage;
	int        size;
	int        width;
	int        height;
    int        format;
	int        internalWidth;
	int        internalHeight;
	int        stride;
	union {
		void*    base;
		uint64_t padding;
	};
	int        lockState;
	int        writeOwner;
	int        pid;

	// locally mapped shared attribute area
	union {
		void*    attr_base;
		uint64_t padding3;
	};

	mali_gralloc_yuv_info yuv_info;

    // Following members is for framebuffer only
	int     fd; //to mmap osd memory
    //current buffer offset from framebuffer base
	union {
		off_t    offset;
		uint64_t padding4;
	};

	// Following members are for UMP memory only
#if GRALLOC_ARM_UMP_MODULE
	ump_secure_id ump_id;
	union {
		void*    ump_mem_handle;
		uint64_t padding5;
	};
#endif
    uint64_t padding_1;
    uint64_t padding_2;
    uint64_t padding_3;
    int padding_4;
	/*
	 * min_pgsz denotes minimum phys_page size used by this buffer.
	 * if buffer memory is physical contiguous set min_pgsz to buff->size
	 * if not sure buff's real phys_page size, you can use SZ_4K for safe.
	 */
	int min_pgsz;

#ifdef __cplusplus
	/*
	 * We track the number of integers in the structure. There are 16 unconditional
	 * integers (magic - pid, yuv_info, fd and offset). Note that the fd element is
	 * considered an int not an fd because it is not intended to be used outside the
	 * surface flinger process. The GRALLOC_ARM_NUM_INTS variable is used to track the
	 * number of integers that are conditionally included. Similar considerations apply
	 * to the number of fds.
	 */
	static const int sNumFds = GRALLOC_ARM_NUM_FDS;
	static const int sMagic = 0x3141592;

#if GRALLOC_ARM_UMP_MODULE
	private_handle_t(int flags, int usage, int size, void *base, int lock_state, ump_secure_id secure_id, ump_handle handle):
		share_attr_fd(-1),
		magic(sMagic),
		flags(flags),
		usage(usage),
		size(size),
		width(0),
		height(0),
		format(0),
		stride(0),
		base(base),
		lockState(lock_state),
		writeOwner(0),
		pid(getpid()),
		attr_base(MAP_FAILED),
		yuv_info(MALI_YUV_NO_INFO),
		fd(0),
		offset(0),
		ump_id(secure_id),
		ump_mem_handle(handle)

	{
		version = sizeof(native_handle);
		numFds = sNumFds;
		numInts = NUM_INTS_IN_PRIVATE_HANDLE;
	}
#endif

	private_handle_t(int flags, int usage, int size, void *base, int lock_state):
#if GRALLOC_ARM_DMA_BUF_MODULE
		share_fd(-1),
#endif
		share_attr_fd(-1),
#if GRALLOC_ARM_DMA_BUF_MODULE
		ion_hnd(ION_INVALID_HANDLE),
#endif
		magic(sMagic),
		flags(flags),
		usage(usage),
		size(size),
		width(0),
		height(0),
		format(0),
		stride(0),
		base(base),
		lockState(lock_state),
		writeOwner(0),
		pid(getpid()),
		attr_base(MAP_FAILED),
		yuv_info(MALI_YUV_NO_INFO),
		fd(0),
		offset(0)
#if GRALLOC_ARM_UMP_MODULE
		,ump_id(UMP_INVALID_SECURE_ID),
		ump_mem_handle(UMP_INVALID_MEMORY_HANDLE)
#endif


	{
		version = sizeof(native_handle);
		numFds = sNumFds;
		numInts = NUM_INTS_IN_PRIVATE_HANDLE;
	}

	private_handle_t(int flags, int usage, int size, void *base, int lock_state, int fb_file, off_t fb_offset, int unused):
#if GRALLOC_ARM_DMA_BUF_MODULE
		share_fd(-1),
#endif
		share_attr_fd(-1),
#if GRALLOC_ARM_DMA_BUF_MODULE
		ion_hnd(ION_INVALID_HANDLE),
#endif
		magic(sMagic),
		flags(flags),
		usage(usage),
		size(size),
		width(0),
		height(0),
		format(0),
		stride(0),
		base(base),
		lockState(lock_state),
		writeOwner(0),
		pid(getpid()),
		attr_base(MAP_FAILED),
		yuv_info(MALI_YUV_NO_INFO),
		fd(fb_file),
		offset(fb_offset)

#if GRALLOC_ARM_UMP_MODULE
		,ump_id(UMP_INVALID_SECURE_ID),
		ump_mem_handle(UMP_INVALID_MEMORY_HANDLE)
#endif

	{
		version = sizeof(native_handle);
		numFds = sNumFds;
		numInts = NUM_INTS_IN_PRIVATE_HANDLE;
        /*
         * because -Werror option, need to remove this warning;
         */
        (void)unused;
	}

	~private_handle_t()
	{
		magic = 0;
	}

	bool usesPhysicallyContiguousMemory()
	{
		return (flags & PRIV_FLAGS_FRAMEBUFFER) ? true : false;
	}

	static int validate(const native_handle* h)
	{
		const private_handle_t* hnd = (const private_handle_t*)h;
		if (!h ||
		    h->version != sizeof(native_handle) ||
		    h->numInts != NUM_INTS_IN_PRIVATE_HANDLE ||
		    h->numFds != sNumFds ||
		    hnd->magic != sMagic)
		{
			return -EINVAL;
		}
		return 0;
	}

	static private_handle_t* dynamicCast(const native_handle* in)
	{
		if (validate(in) == 0)
		{
			return (private_handle_t*) in;
		}
		return NULL;
	}
#endif
};

#endif /* GRALLOC_PRIV_H_ */
