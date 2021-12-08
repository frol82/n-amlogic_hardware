# Copyright (C) 2014 The Android Open Source Project
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

##################################
# Audio HAL
##################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    audio_hal_hooks.c \
    audio_hal_thunks.cpp \
    AudioHardwareInput.cpp \
    AudioStreamIn.cpp \
    AudioHotplugThread.cpp

LOCAL_C_INCLUDES := \
    external/tinyalsa/include \
    $(call include-path-for, audio-utils)

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libutils \
    libmedia \
    libtinyalsa \
    libaudioutils

LOCAL_STATIC_LIBRARIES += libmedia_helper

LOCAL_MODULE := audio.dia_remote.default
#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_TAGS := optional

#ifeq ($(PLATFORM_VERSION),4.4.4)
#LOCAL_CFLAGS += -D__KITKAT__
#endif

include $(BUILD_SHARED_LIBRARY)