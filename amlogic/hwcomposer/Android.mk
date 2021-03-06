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
LOCAL_ROOT_PATH := $(call my-dir)

# USE_HWC2_CPP := true

# ifeq ($(USE_HWC2_CPP),true)
#     include $(LOCAL_PATH)/hwc2/platforms/Android.mk
# else
#     include $(LOCAL_PATH)/hwc2_old/Android.mk
# endif

USE_HWC2 := true
ifeq ($(USE_HWC2),true)
    include $(LOCAL_PATH)/hwc2/platforms/Android.mk
else
    include $(LOCAL_PATH)/hwc1.4/Android.mk
endif

# include $(LOCAL_PATH)/hwc2/platforms/Android.mk

include $(LOCAL_ROOT_PATH)/tvp/Android.mk
