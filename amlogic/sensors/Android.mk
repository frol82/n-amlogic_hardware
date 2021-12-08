ifneq ($(BOARD_USES_AML_SENSOR_HAL),false)
LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := sensors.amlogic
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MULTILIB := 32
LOCAL_SRC_FILES := sensors.amlogic.so
include $(BUILD_PREBUILT)


#libraries to copy

endif

