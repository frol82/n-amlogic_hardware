LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:=                     \
        OmxUtil.cpp            \

LOCAL_C_INCLUDES := \

LOCAL_MODULE:= libomxutil

include $(BUILD_STATIC_LIBRARY)
