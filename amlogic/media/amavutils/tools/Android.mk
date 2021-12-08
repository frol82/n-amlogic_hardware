LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := mediactl.cpp
LOCAL_SHARED_LIBRARIES := liblog libcutils libmedia.amlogic.hal
LOCAL_MODULE := mediactl
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

