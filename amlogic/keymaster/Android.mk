# Copyright (C) 2012 The Android Open Source Project
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

BUILD_CA_FROM_SOURCE := true
KEYMASTER_TA_BINARY := 27768e80-717d-11e5-b4b00002a5d5c51b

include $(CLEAR_VARS)
LOCAL_MODULE := keystore.amlogic
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_SRC_FILES := module.cpp \
		   optee/aml_keymaster1.cpp \
		   optee/keymaster1_secure_api.cpp \
		   optee/aml_keymaster_context.cpp \
		   optee/aml_integrity_assured_key_blob.cpp \
		   optee/keymaster_ca.c \

LOCAL_C_INCLUDES := \
    system/security/keystore \
    $(LOCAL_PATH)/include \
    system/keymaster/ \
    system/keymaster/include \
    external/boringssl/include \
    vendor/amlogic/tdk/ca_export_arm/include \
    vendor/amlogic/tdk/ta_export/host_include \
    hardware/amlogic/keymaster/optee

LOCAL_CFLAGS = -fvisibility=hidden -Wall -Werror
LOCAL_CFLAGS += -DANDROID_BUILD
ifeq ($(USE_SOFT_KEYSTORE), false)
LOCAL_CFLAGS += -DUSE_HW_KEYMASTER
endif
LOCAL_SHARED_LIBRARIES := libcrypto \
			  liblog \
			  libkeystore_binder \
			  libteec \
			  libkeymaster_messages \
			  libkeymaster1 \
			  libteec

LOCAL_MODULE_TAGS := optional
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk
LOCAL_REQUIRED_MODULES := $(KEYMASTER_TA_BINARY)
include $(BUILD_SHARED_LIBRARY)

######################################################
#	TA Library
######################################################
include $(CLEAR_VARS)
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := $(KEYMASTER_TA_BINARY)
LOCAL_MODULE_SUFFIX := .ta
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/teetz
LOCAL_SRC_FILES := optee/$(LOCAL_MODULE)$(LOCAL_MODULE_SUFFIX)
include $(BUILD_PREBUILT)


# Unit tests for libkeymaster
include $(CLEAR_VARS)
LOCAL_MODULE := amlkeymaster_tests
LOCAL_SRC_FILES := \
	unit_test/android_keymaster_test.cpp \
	unit_test/android_keymaster_test_utils.cpp \
	unit_test/attestation_record_test.cpp \
	unit_test/authorization_set_test.cpp \
#	unit_test/android_keymaster_messages_test.cpp \
	unit_test/hkdf_test.cpp \
	unit_test/hmac_test.cpp \
	unit_test/kdf1_test.cpp \
	unit_test/kdf2_test.cpp \
	unit_test/kdf_test.cpp \
	unit_test/key_blob_test.cpp \
	unit_test/keymaster_enforcement_test.cpp

LOCAL_C_INCLUDES := \
	external/boringssl/include \
	system/keymaster/include \
	system/keymaster \
	system/security/softkeymaster/include

LOCAL_CFLAGS = -Wall -Werror -Wunused -DKEYMASTER_NAME_TAGS
LOCAL_CLANG_CFLAGS += -Wno-error=unused-const-variable -Wno-error=unused-private-field
# TODO(krasin): reenable coverage flags, when the new Clang toolchain is released.
# Currently, if enabled, these flags will cause an internal error in Clang.
LOCAL_CLANG_CFLAGS += -fno-sanitize-coverage=edge,indirect-calls,8bit-counters,trace-cmp
LOCAL_MODULE_TAGS := tests
LOCAL_SHARED_LIBRARIES := \
	libsoftkeymasterdevice \
	libkeymaster_messages \
	libkeymaster1 \
	libcrypto \
	libsoftkeymaster \
	libhardware

LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk
include $(BUILD_NATIVE_TEST)

