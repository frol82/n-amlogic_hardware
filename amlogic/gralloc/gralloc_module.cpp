/*
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may not use this file except in compliance with the License.
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
#define LOG_NDEBUG 0
#define LOG_TAG "Gralloc"

#include <errno.h>
#include <pthread.h>

#include <cutils/log.h>
#include <cutils/atomic.h>
#include <hardware/hardware.h>
#include <hardware/gralloc.h>

#include <hardware/hwcomposer_defs.h>

#include "gralloc_priv.h"
#include "alloc_device.h"
#include "framebuffer_device.h"

#include "gralloc_module_allocator_specific.h"

#if MALI_AFBC_GRALLOC == 1
#include "gralloc_buffer_priv.h"
#endif

#include "format_chooser.h"

static pthread_mutex_t s_map_lock = PTHREAD_MUTEX_INITIALIZER;

static int gralloc_device_open(const hw_module_t* module, const char* name, hw_device_t** device)
{
	int status = -EINVAL;

	if (!strncmp(name, GRALLOC_HARDWARE_GPU0, MALI_GRALLOC_HARDWARE_MAX_STR_LEN))
	{
		status = alloc_device_open(module, name, device);
	}
	else if (!strncmp(name, GRALLOC_HARDWARE_FB0, MALI_GRALLOC_HARDWARE_MAX_STR_LEN))
	{
		status = framebuffer_device_open(module, name, device);
	}

	return status;
}

static int gralloc_register_buffer(gralloc_module_t const* module, buffer_handle_t handle)
{
	if (private_handle_t::validate(handle) < 0)
	{
		AERR("Registering invalid buffer %p, returning error", handle);
		return -EINVAL;
	}

	// if this handle was created in this process, then we keep it as is.
	private_handle_t* hnd = (private_handle_t*)handle;

	if (hnd->pid == getpid())
	{
		// If the handle is created and registered in the same process this is valid,
		// but it could also be that application is registering twice which is illegal.
		AWAR("Registering handle %p coming from the same process: %d.", hnd, hnd->pid);
	}

	int retval = -EINVAL;

	pthread_mutex_lock(&s_map_lock);

	hnd->pid = getpid();

	if (hnd->flags & private_handle_t::PRIV_FLAGS_FRAMEBUFFER)
	{
		ALOGD("gralloc_register_buffer register framebuffer");
		hw_module_t * pmodule = NULL;
		private_module_t *m = NULL;
		if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, (const hw_module_t **)&pmodule) == 0)
		{
			m = reinterpret_cast<private_module_t *>(pmodule);
		}
		else
		{
			AERR("Could not get gralloc module for handle: 0x%p", hnd);
			retval = -errno;
			goto cleanup;
		}

		framebuffer_mapper_t* fbMaper = &(m->fb_primary);
		if (hnd->usage & GRALLOC_USAGE_EXTERNAL_DISP)
		{
			ALOGD("register external display");
			fbMaper = &(m->fb_external);
		}
		if (!fbMaper->framebuffer)
		{
			fbMaper->framebuffer = new private_handle_t(hnd->flags, hnd->usage, hnd->size, hnd->base, 0, dup(hnd->fd), 0, 0);
			fbMaper->bufferSize = hnd->offset;
			fbMaper->numBuffers = fbMaper->framebuffer->size / fbMaper->bufferSize;
			fbMaper->bufferMask = 0;
			//ALOGE("fbMaper->bufferSize: 0x%08x, fbMaper->numBuffers: %d, fbMaper->framebuffer->size: 0x%08x", fbMaper->bufferSize, fbMaper->numBuffers, fbMaper->framebuffer->size);

			/*
			* map the framebuffer
			*/
#if MALI_AFBC_GRALLOC == 1
			void* vaddr = mmap(0, fbMaper->bufferSize, PROT_READ|PROT_WRITE, MAP_SHARED, fbMaper->framebuffer->fd, 0);
#else
			void* vaddr = mmap(0, fbMaper->framebuffer->size, PROT_READ|PROT_WRITE, MAP_SHARED, fbMaper->framebuffer->fd, 0);
#endif
			if (vaddr == MAP_FAILED)
			{
				AERR( "Error mapping the framebuffer (%s)", strerror(errno) );
				return -errno;
			}
#if MALI_AFBC_GRALLOC == 1
			memset(vaddr, 0, fbMaper->bufferSize);
#else
			memset(vaddr, 0, fbMaper->framebuffer->size);
#endif
			fbMaper->framebuffer->base = vaddr;

			#if GRALLOC_ARM_UMP_MODULE
			#ifdef IOCTL_GET_FB_UMP_SECURE_ID
			ioctl(fbMaper->framebuffer->fd, IOCTL_GET_FB_UMP_SECURE_ID, &fbMaper->framebuffer->ump_id);
			#endif
			if ( (int)UMP_INVALID_SECURE_ID != fbMaper->framebuffer->ump_id )
			{
				AINF("framebuffer accessed with UMP secure ID %i\n", fbMaper->framebuffer->ump_id);
			}
			#endif
			ALOGD("register frame buffer count %d ",fbMaper->numBuffers );
		} else {
			ALOGE("ERROR::register frambuffer again!!!");
		}
	}
	else if (hnd->flags & (private_handle_t::PRIV_FLAGS_USES_UMP |
	                       private_handle_t::PRIV_FLAGS_USES_ION))
	{
		retval = gralloc_backend_register(hnd);
	}
	else
	{
		AERR("registering non-UMP buffer not supported. flags = %d", hnd->flags );
	}

cleanup:
	pthread_mutex_unlock(&s_map_lock);
	return retval;
}

static int gralloc_unregister_buffer(gralloc_module_t const* module, buffer_handle_t handle)
{
	if (private_handle_t::validate(handle) < 0)
	{
		AERR("unregistering invalid buffer %p, returning error", handle);
		return -EINVAL;
	}

	private_handle_t* hnd = (private_handle_t*)handle;

	AERR_IF(hnd->lockState & private_handle_t::LOCK_STATE_READ_MASK, "[unregister] handle %p still locked (state=%08x)", hnd, hnd->lockState);

	if (hnd->flags & private_handle_t::PRIV_FLAGS_FRAMEBUFFER)
	{
		pthread_mutex_lock(&s_map_lock);

		ALOGD("unregister framebuffer ");
		//AERR( "Can't unregister buffer 0x%x as it is a framebuffer", (unsigned int)handle );
		hw_module_t * pmodule = NULL;
		private_module_t *m = NULL;
		if (hw_get_module(GRALLOC_HARDWARE_MODULE_ID, (const hw_module_t **)&pmodule) == 0)
		{
			m = reinterpret_cast<private_module_t *>(pmodule);
			framebuffer_mapper_t* fbMaper = &(m->fb_primary);
			if (hnd->usage & GRALLOC_USAGE_EXTERNAL_DISP)
			{
				ALOGD("unregister external display");
				fbMaper = &(m->fb_external);
			}

			if (fbMaper->framebuffer)
			{
#if MALI_AFBC_GRALLOC == 1
				munmap((void*)fbMaper->framebuffer->base,fbMaper->bufferSize);
#else
				munmap((void*)fbMaper->framebuffer->base,fbMaper->framebuffer->size);
#endif
				close(fbMaper->framebuffer->fd);
				//reset framebuffer info
				delete fbMaper->framebuffer;
				fbMaper->framebuffer = 0;
				fbMaper->bufferMask = 0;
				fbMaper->numBuffers = 0;
			} else {
				AERR("Can't unregister a not exist buffers: 0x%p", hnd);
			}
		} else {
			AERR("Could not get gralloc module for handle: 0x%p", hnd);
		}
	// never unmap buffers that were not created in this process
	} else if (hnd->pid == getpid()) {
		pthread_mutex_lock(&s_map_lock);

		if (hnd->flags & (private_handle_t::PRIV_FLAGS_USES_UMP |
							private_handle_t::PRIV_FLAGS_USES_ION))
		{
			gralloc_backend_unregister(hnd);
		}
		else
		{
			AERR("Unregistering unknown buffer is not supported. Flags = %d", hnd->flags);
		}

#if MALI_AFBC_GRALLOC
		/*
		 * Close shared attribute region file descriptor. It might seem strange to "free"
		 * this here since this can happen in a client process, but free here is nothing
		 * but unmapping and closing the duplicated file descriptor. The original ashmem
		 * fd instance is still open until alloc_device_free() is called. Even sharing
		 * of gralloc buffers within the same process should have fds dup:ed.
		 */
		gralloc_buffer_attr_free( hnd );

#endif
		hnd->base = 0;
		hnd->lockState  = 0;
		hnd->writeOwner = 0;

		pthread_mutex_unlock(&s_map_lock);
	}
	else
	{
		AERR( "Trying to unregister buffer %p from process %d that was not created in current process: %d", hnd, hnd->pid, getpid());
	}

	return 0;
}

static int gralloc_lock(gralloc_module_t const* module, buffer_handle_t handle, int usage, int l, int t, int w, int h, void** vaddr)
{
	private_handle_t* hnd = (private_handle_t*)handle;
	if (private_handle_t::validate(handle) < 0)
	{
		AERR("Locking invalid buffer %p, returning error", handle );
		return -EINVAL;
	}
	if (hnd->internal_format != hnd->format)
	{
		AERR("failed, this buffer may be compressed!!\n");
	}

	if (hnd->flags & private_handle_t::PRIV_FLAGS_USES_UMP || hnd->flags & private_handle_t::PRIV_FLAGS_USES_ION)
	{
		hnd->writeOwner = usage & GRALLOC_USAGE_SW_WRITE_MASK;
	}
	if ((usage & (GRALLOC_USAGE_SW_READ_MASK | GRALLOC_USAGE_SW_WRITE_MASK))
	   || (usage & GRALLOC_USAGE_HW_CAMERA_MASK)
	   || (usage & GRALLOC_USAGE_HW_VIDEO_ENCODER))
	{
		*vaddr = (void*)hnd->base;
	}
	return 0;
}

static int gralloc_lock_ycbcr(gralloc_module_t const* module,
                        buffer_handle_t handle, int usage,
                        int l, int t, int w, int h,
                        android_ycbcr *ycbcr)
{
	private_module_t *gr = (private_module_t *)module;
	private_handle_t *hnd = (private_handle_t *)handle;

	if (!ycbcr) {
		AERR("gralloc_lock_ycbcr got NULL ycbcr struct");
		return -EINVAL;
	}
	if (hnd->internal_format != hnd->format)
	{
		AERR("failed, this buffer may be compressed!!\n");
	}

	if (!gr || (private_handle_t::validate(hnd) < 0)) {
		AERR("gralloc_lock_ycbcr bad handle\n");
		return -EINVAL;
	}

	// Validate usage
	// For now, only allow camera write, software read.
	bool sw_read = (0 != (usage & GRALLOC_USAGE_SW_READ_MASK));
	bool hw_cam_write = (usage & GRALLOC_USAGE_HW_CAMERA_WRITE);
	bool sw_read_allowed = (0 != (hnd->usage & GRALLOC_USAGE_SW_READ_MASK));

#if 0
	if ( (!hw_cam_write && !sw_read) ||
		(sw_read && !sw_read_allowed) ) {
		AERR("gralloc_lock_ycbcr usage mismatch usage:0x%x cb->usage:0x%x\n",
		usage, hnd->usage);
		return -EINVAL;
	}
#endif

	uint8_t *cpu_addr = NULL;
	cpu_addr = (uint8_t *)hnd->base;

	// Calculate offsets to underlying YUV data
	size_t yStride;
	size_t cStride;
	size_t yOffset;
	size_t uOffset;
	size_t vOffset;
	size_t cStep;
	switch (hnd->format) {
		case HAL_PIXEL_FORMAT_YCrCb_420_SP: //this is NV21
		case HAL_PIXEL_FORMAT_YCbCr_420_SP:
		case HAL_PIXEL_FORMAT_YCbCr_420_888:
			yStride = GRALLOC_ALIGN(hnd->width, YUV_MALI_PLANE_ALIGN);
			cStride = GRALLOC_ALIGN(hnd->width, YUV_MALI_PLANE_ALIGN);
			yOffset = 0;
			vOffset = yStride * hnd->height;
			uOffset = vOffset + 1;
			cStep = 2;
			break;
		case HAL_PIXEL_FORMAT_YV12:
			yStride = GRALLOC_ALIGN(hnd->width, YUV_ANDROID_PLANE_ALIGN);
			cStride = GRALLOC_ALIGN(yStride / 2, YUV_ANDROID_PLANE_ALIGN);
			yOffset = 0;
			vOffset = yStride * hnd->height;
			uOffset = vOffset + cStride * hnd->height / 2;
			cStep = 1;
			break;
		default:
			AERR("gralloc_lock_ycbcr unexpected internal format %x",
			hnd->format);
			return -EINVAL;
	}

	ycbcr->y = cpu_addr + yOffset;
	ycbcr->cb = cpu_addr + uOffset;
	ycbcr->cr = cpu_addr + vOffset;
	ycbcr->ystride = yStride;
	ycbcr->cstride = cStride;
	ycbcr->chroma_step = cStep;

	// Zero out reserved fields
	memset(ycbcr->reserved, 0, sizeof(ycbcr->reserved));

#if 0
	ALOGV("gralloc_lock_ycbcr success. usage: %x, ycbcr.y: %p, .cb: %p, .cr: %p, "
		".ystride: %d , .cstride: %d, .chroma_step: %d", usage,
		ycbcr->y, ycbcr->cb, ycbcr->cr, ycbcr->ystride, ycbcr->cstride,
		ycbcr->chroma_step);
#endif

    return 0;
}

#if 0
static int gralloc_lock_ycbcr(gralloc_module_t const* module, buffer_handle_t handle, int usage,
                              int l, int t, int w, int h,
                              android_ycbcr *ycbcr)
{
	if (private_handle_t::validate(handle) < 0)
	{
		AERR("Locking invalid buffer %p, returning error", handle );
		return -EINVAL;
	}

	private_handle_t* hnd = (private_handle_t*)handle;

	if (hnd->flags & private_handle_t::PRIV_FLAGS_USES_UMP || hnd->flags & private_handle_t::PRIV_FLAGS_USES_ION)
	{
		hnd->writeOwner = usage & GRALLOC_USAGE_SW_WRITE_MASK;
	}
	if (usage & (GRALLOC_USAGE_SW_READ_MASK | GRALLOC_USAGE_SW_WRITE_MASK))
	{
		char* base = (char*)hnd->base;
		int y_stride = hnd->byte_stride;
		int y_size =  y_stride * hnd->height;

		int u_offset = 0;
		int v_offset = 0;
		int c_stride = 0;
		int step = 0;

		switch (hnd->internal_format & GRALLOC_ARM_INTFMT_FMT_MASK)
		{
			case HAL_PIXEL_FORMAT_YCbCr_420_888: /* Internally interpreted as NV12 */
				c_stride = y_stride;
				/* Y plane, UV plane */
				u_offset = y_size;
				v_offset = y_size + 1;
				step = 2;
				break;

			case HAL_PIXEL_FORMAT_YV12:
			case GRALLOC_ARM_HAL_FORMAT_INDEXED_YV12:
			{
				int c_size;

				/* Stride alignment set to 16 as the SW access flags were set */
				c_stride = GRALLOC_ALIGN(hnd->byte_stride / 2, 16);
				c_size = c_stride * (hnd->height / 2);
				/* Y plane, V plane, U plane */
				v_offset = y_size;
				u_offset = y_size + c_size;
				step = 1;
				break;
			}

			default:
				AERR("Can't lock buffer %p: wrong format %llx", hnd, hnd->internal_format);
				return -EINVAL;
		}

		ycbcr->y = base;
		ycbcr->cb = base + u_offset;
		ycbcr->cr = base + v_offset;
		ycbcr->ystride = y_stride;
		ycbcr->cstride = c_stride;
		ycbcr->chroma_step = step;
	}
	return 0;
}
#endif

static int gralloc_unlock(gralloc_module_t const* module, buffer_handle_t handle)
{
	if (private_handle_t::validate(handle) < 0)
	{
		AERR( "Unlocking invalid buffer %p, returning error", handle );
		return -EINVAL;
	}

	private_handle_t* hnd = (private_handle_t*)handle;

	if (hnd->flags & (private_handle_t::PRIV_FLAGS_USES_UMP |
	                  private_handle_t::PRIV_FLAGS_USES_ION)
	    && hnd->writeOwner)
	{
		gralloc_backend_sync(hnd);
	}

	return 0;
}

// There is one global instance of the module

static struct hw_module_methods_t gralloc_module_methods =
{
	open: gralloc_device_open
};

private_module_t::private_module_t()
{
#define INIT_ZERO(obj) (memset(&(obj),0,sizeof((obj))))

	base.common.tag = HARDWARE_MODULE_TAG;
	base.common.version_major = 1;
	base.common.version_minor = 0;
	base.common.id = GRALLOC_HARDWARE_MODULE_ID;
	base.common.name = "Graphics Memory Allocator Module";
	base.common.author = "ARM Ltd.";
	base.common.methods = &gralloc_module_methods;
	base.common.dso = NULL;
	INIT_ZERO(base.common.reserved);

	base.registerBuffer = gralloc_register_buffer;
	base.unregisterBuffer = gralloc_unregister_buffer;
	base.lock = gralloc_lock;
	base.lock_ycbcr = gralloc_lock_ycbcr;
	base.unlock = gralloc_unlock;
	base.perform = NULL;
	INIT_ZERO(base.reserved_proc);

	INIT_ZERO(fb_primary);
	INIT_ZERO(fb_external);

	pthread_mutex_init(&(lock), NULL);
	swapInterval = 1;

	initialize_blk_conf();

#undef INIT_ZERO
};

/*
 * HAL_MODULE_INFO_SYM will be initialized using the default constructor
 * implemented above
 */
struct private_module_t HAL_MODULE_INFO_SYM;

