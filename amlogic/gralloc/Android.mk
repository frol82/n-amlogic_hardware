# 
# Copyright (C) 2010 ARM Limited. All rights reserved.
# 
# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

# Include platform specific makefiles
include $(if $(wildcard $(LOCAL_PATH)/Android.$(TARGET_BOARD_PLATFORM).mk), $(LOCAL_PATH)/Android.$(TARGET_BOARD_PLATFORM).mk,)

MALI_ION?=1
GRALLOC_VSYNC_BACKEND?=default
DISABLE_FRAMEBUFFER_HAL?=0
MALI_SUPPORT_AFBC_WIDEBLK?=0
GRALLOC_USE_ION_DMA_HEAP?=0
GRALLOC_USE_ION_COMPOUND_PAGE_HEAP?=0

#framebuffer apis
include $(CLEAR_VARS)
ifneq ($(NUM_FRAMEBUFFER_SURFACE_BUFFERS),)
  LOCAL_CFLAGS += -DNUM_BUFFERS=$(NUM_FRAMEBUFFER_SURFACE_BUFFERS)
endif

ifeq ($(TARGET_EXTERNAL_DISPLAY),true)
ifeq ($(TARGET_SINGLE_EXTERNAL_DISPLAY_USE_FB1),true)
	LOCAL_CFLAGS += -DSINGLE_EXTERNAL_DISPLAY_USE_FB1
endif
endif

LOCAL_KK=0
ifeq ($(GPU_TYPE),t83x)
LOCAL_KK:=1
endif
ifeq ($(GPU_ARCH),midgard)
LOCAL_KK:=1
endif
ifeq ($(LOCAL_KK),1)
	LOCAL_CFLAGS += -DMALI_AFBC_GRALLOC=1
else
	LOCAL_CFLAGS += -DMALI_AFBC_GRALLOC=0
endif

LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := framebuffer.cpp
LOCAL_MODULE := libfbcnf
LOCAL_SHARED_LIBRARIES := liblog libcutils libutils
LOCAL_C_INCLUDES += system/core/libion/include/ \
		system/core/libion/kernel-headers
include $(BUILD_SHARED_LIBRARY)

# HAL module implemenation, not prelinked and stored in
# hw/<OVERLAY_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)
include $(BUILD_SYSTEM)/version_defaults.mk

ifeq ($(LOCAL_KK),1)
	LOCAL_CFLAGS += -DGRALLOC_T83X
	MALI_AFBC_GRALLOC := 1
	MALI_ARCHITECTURE_UTGARD?=0
else
	MALI_AFBC_GRALLOC := 0
	MALI_ARCHITECTURE_UTGARD?=1
endif

ifeq ($(MALI_ARCHITECTURE_UTGARD),1)
	# Utgard build settings
	MALI_LOCAL_PATH?=hardware/arm/mali
	GRALLOC_DEPTH?=GRALLOC_32_BITS
	GRALLOC_FB_SWAP_RED_BLUE?=0
	MALI_DDK_INCLUDES=$(MALI_LOCAL_PATH)/include $(MALI_LOCAL_PATH)/src/ump/include
	ifeq ($(MALI_ION),1)
		ALLOCATION_LIB := libion
		ALLOCATOR_SPECIFIC_FILES := alloc_ion.cpp gralloc_module_ion.cpp
	else
		ALLOCATION_LIB := libUMP
		ALLOCATOR_SPECIFIC_FILES := alloc_ump.cpp gralloc_module_ump.cpp
	endif
$(info GRALLOC_FB_SWAP_RED_BLUE0 is $(GRALLOC_FB_SWAP_RED_BLUE))
else
	# Midgard build settings
	MALI_LOCAL_PATH?=vendor/arm/t83x
	GRALLOC_DEPTH?=GRALLOC_32_BITS
	GRALLOC_FB_SWAP_RED_BLUE?=0
	MALI_DDK_INCLUDES=$(MALI_LOCAL_PATH)/include $(MALI_LOCAL_PATH)/kernel/include
  ifeq ($(MALI_ION),1)
		ALLOCATION_LIB := libion
		ALLOCATOR_SPECIFIC_FILES := alloc_ion.cpp gralloc_module_ion.cpp
  else
		ALLOCATION_LIB := libGLES_mali
		ALLOCATOR_SPECIFIC_FILES := alloc_ump.cpp gralloc_module_ump.cpp
  endif
$(info GRALLOC_FB_SWAP_RED_BLUE1 is $(GRALLOC_FB_SWAP_RED_BLUE))
endif
#MALI_AFBC_GRALLOC?=1
ifeq ($(MALI_AFBC_GRALLOC), 1)
AFBC_FILES = gralloc_buffer_priv.cpp
else
MALI_AFBC_GRALLOC := 0
AFBC_FILES =
endif
$(info MALI_AFBC_GRALLOC is $(MALI_AFBC_GRALLOC))

#If cropping should be enabled for AFBC YUV420 buffers
AFBC_YUV420_EXTRA_MB_ROW_NEEDED ?= 0

ifdef GRALLOC_DISP_W
LOCAL_CFLAGS += -DGRALLOC_DISP_W=$(GRALLOC_DISP_W)
endif
ifdef GRALLOC_DISP_H
LOCAL_CFLAGS += -DGRALLOC_DISP_H=$(GRALLOC_DISP_H)
endif

ifdef MALI_DISPLAY_VERSION
#if Mali display is available, should disable framebuffer HAL
DISABLE_FRAMEBUFFER_HAL := 1
endif

LOCAL_PRELINK_MODULE := false


LOCAL_SHARED_LIBRARIES := libhardware liblog libcutils libGLESv1_CM $(ALLOCATION_LIB) libfbcnf
LOCAL_C_INCLUDES := $(MALI_LOCAL_PATH) $(MALI_DDK_INCLUDES)
LOCAL_CFLAGS += -DLOG_TAG=\"gralloc\" -DSTANDARD_LINUX_SCREEN -DMALI_ION=$(MALI_ION) -DMALI_AFBC_GRALLOC=$(MALI_AFBC_GRALLOC) -D$(GRALLOC_DEPTH) -DMALI_ARCHITECTURE_UTGARD=$(MALI_ARCHITECTURE_UTGARD) -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION) -DDISABLE_FRAMEBUFFER_HAL=$(DISABLE_FRAMEBUFFER_HAL) -DMALI_SUPPORT_AFBC_WIDEBLK=$(MALI_SUPPORT_AFBC_WIDEBLK) -DAFBC_YUV420_EXTRA_MB_ROW_NEEDED=$(AFBC_YUV420_EXTRA_MB_ROW_NEEDED) -DGRALLOC_USE_ION_DMA_HEAP=$(GRALLOC_USE_ION_DMA_HEAP) -DGRALLOC_USE_ION_COMPOUND_PAGE_HEAP=$(GRALLOC_USE_ION_COMPOUND_PAGE_HEAP)

ifdef MALI_DISPLAY_VERSION
LOCAL_CFLAGS += -DMALI_DISPLAY_VERSION=$(MALI_DISPLAY_VERSION)
endif

ifeq ($(wildcard system/core/libion/include/ion/ion.h),)
LOCAL_C_INCLUDES += system/core/include
LOCAL_CFLAGS += -DGRALLOC_OLD_ION_API
else
LOCAL_C_INCLUDES += system/core/libion/include
endif

ifeq ($(GRALLOC_FB_SWAP_RED_BLUE),1)
LOCAL_CFLAGS += -DGRALLOC_FB_SWAP_RED_BLUE
endif

ifeq ($(GRALLOC_ARM_NO_EXTERNAL_AFBC),1)
LOCAL_CFLAGS += -DGRALLOC_ARM_NO_EXTERNAL_AFBC=1
endif

ifdef PLATFORM_CFLAGS
LOCAL_CFLAGS += $(PLATFORM_CFLAGS)
endif

ifeq ($(TARGET_APP_LAYER_USE_CONTINUOUS_BUFFER),true)
LOCAL_CFLAGS += -DGRALLOC_APP_ALLOC_CONTINUOUS_BUF
endif

ifeq ($(TARGET_SUPPORT_SECURE_LAYER),true)
LOCAL_CFLAGS += -DGRALLOC_ENABLE_SECURE_LAYER
endif

ifneq ($(TARGET_2ND_ARCH),)
LOCAL_MODULE_RELATIVE_PATH := hw
else
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
endif
ifeq ($(TARGET_BOARD_PLATFORM),)
LOCAL_MODULE := gralloc.default
else
LOCAL_MODULE := gralloc.amlogic
endif

LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := both

LOCAL_SRC_FILES := \
	gralloc_module.cpp \
	alloc_device.cpp \
	$(ALLOCATOR_SPECIFIC_FILES) \
	framebuffer_device.cpp \
	format_chooser.cpp \
	format_chooser_blockinit.cpp \
	$(AFBC_FILES) \
	gralloc_vsync_${GRALLOC_VSYNC_BACKEND}.cpp

LOCAL_MODULE_OWNER := arm

include $(BUILD_SHARED_LIBRARY)
