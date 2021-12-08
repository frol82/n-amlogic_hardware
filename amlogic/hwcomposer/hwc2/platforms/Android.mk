# Copyright (C) 2016 Amlogic
#
#

LOCAL_PATH := $(call my-dir)
include $(TOP)/hardware/amlogic/media/media_base_config.mk
# HAL module implemenation, not prelinked and stored in
# hw/<OVERLAY_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)

LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_SRC_FILES := \
    ../common/base/HwcLayer.cpp \
    ../common/base/HwcFenceControl.cpp \
    ../common/base/Hwcomposer.cpp \
    ../common/base/HwcModule.cpp \
    ../common/base/VsyncManager.cpp \
    ../common/devices/PhysicalDevice.cpp \
    ../common/devices/PrimaryDevice.cpp \
    ../common/devices/VirtualDevice.cpp \
    ../common/hdmi/DisplayHdmi.cpp \
    ../common/observers/SoftVsyncObserver.cpp \
    ../common/observers/UeventObserver.cpp \
    ../common/composers/Composers.cpp \
    ../common/composers/GE2DComposer.cpp \
    ../common/utils/Utils.cpp \
    ../common/utils/Dump.cpp \
    ../common/utils/AmVinfo.cpp \
    ../common/utils/AmVideo.cpp

LOCAL_SRC_FILES += \
    PlatFactory.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libEGL \
    libdl \
    libhardware \
    libutils \
    libsync \
    libion \
    libfbcnf \
    libge2d \
    libbinder \
    libsystemcontrolservice \
    libgui

LOCAL_C_INCLUDES := \
    system/core \
    system/core/libsync \
    system/core/libsync/include \
    system/core/include \
    vendor/amlogic/system/libge2d/inlcude \
    vendor/amlogic/frameworks/services

LOCAL_C_INCLUDES += $(LOCAL_PATH) \
    $(LOCAL_PATH)/../include \
    $(LOCAL_PATH)/../common/base \
    $(LOCAL_PATH)/../common/devices \
    $(LOCAL_PATH)/../common/hdmi \
    $(LOCAL_PATH)/../common/observers \
    $(LOCAL_PATH)/../common/utils \
    $(LOCAL_PATH)/../common/composers \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/ \
    $(TOP)/vendor/amlogic/frameworks/services/systemcontrol \

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

LOCAL_CPPFLAGS += -std=c++14

MESON_GRALLOC_DIR ?= hardware/amlogic/gralloc

LOCAL_C_INCLUDES += $(MESON_GRALLOC_DIR)

LOCAL_C_INCLUDES += system/core/libion/include/ \
                system/core/libion/kernel-headers

ifeq ($(TARGET_APP_LAYER_USE_CONTINUOUS_BUFFER),true)
LOCAL_CFLAGS += -DUSE_CONTINOUS_BUFFER_COMPOSER
# LOCAL_CFLAGS += -DENABLE_AML_GE2D_COMPOSER
endif

# WITH_LIBPLAYER_MODULE := true
ifneq ($(WITH_LIBPLAYER_MODULE),false)
LOCAL_SHARED_LIBRARIES += libamavutils_alsa
LOCAL_C_INCLUDES += $(AMAVUTILS_PATH)/include
LOCAL_CFLAGS += -DWITH_LIBPLAYER_MODULE=1
endif

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := hwcomposer.amlogic
# LOCAL_CFLAGS += -DLINUX

ifneq ($(TARGET_BUILD_VARIANT),user)
   LOCAL_CFLAGS += -DHWC_TRACE_FPS
endif

include $(BUILD_SHARED_LIBRARY)

