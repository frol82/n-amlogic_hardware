LOCAL_PATH := $(call my-dir)

ifneq ($(BOARD_HAVE_BLUETOOTH_BCM),)

include $(CLEAR_VARS)

BDROID_DIR := $(TOP_DIR)system/bt

LOCAL_SRC_FILES := \
        src/bt_vendor_brcm.c \
        src/hardware.c \
        src/userial_vendor.c \
        src/upio.c \
        src/conf.c \
        src/sysbridge.cpp

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/include \
        $(BDROID_DIR)/hci/include \
        $(TOP)/vendor/amlogic/frameworks/services

LOCAL_SHARED_LIBRARIES := \
        libcutils \
        liblog \
        libbinder \
        libsystemcontrolservice \
        libutils \
        libdl
LOCAL_CFLAGS += -DANDROID_PLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)  -DUSE_SYS_WRITE_SERVICE=1

LOCAL_MODULE := libbt-vendor
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_OWNER := broadcom
LOCAL_PROPRIETARY_MODULE := true

include $(LOCAL_PATH)/vnd_buildcfg.mk

include $(BUILD_SHARED_LIBRARY)

ifeq ($(BCM_USB_BT), true)
    include $(LOCAL_PATH)/conf/bcm_usb_bt/Android.mk
else
    include $(LOCAL_PATH)/conf/meson/Android.mk
endif

ifeq ($(TARGET_PRODUCT), full_maguro)
    include $(LOCAL_PATH)/conf/samsung/maguro/Android.mk
endif
ifeq ($(TARGET_PRODUCT), full_crespo)
    include $(LOCAL_PATH)/conf/samsung/crespo/Android.mk
endif
ifeq ($(TARGET_PRODUCT), full_crespo4g)
    include $(LOCAL_PATH)/conf/samsung/crespo4g/Android.mk
endif
ifeq ($(TARGET_PRODUCT), full_wingray)
    include $(LOCAL_PATH)/conf/moto/wingray/Android.mk
endif

endif # BOARD_HAVE_BLUETOOTH_BCM
