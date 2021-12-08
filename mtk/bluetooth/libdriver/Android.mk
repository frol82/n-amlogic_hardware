ifeq ($(BOARD_HAVE_BLUETOOTH_MTK),true)
LOCAL_PATH := $(call my-dir)
#$(call config-custom-folder,custom:hal/bluetooth)

###########################################################################
# MTK BT CHIP INIT LIBRARY FOR BLUEDROID
###########################################################################
include $(CLEAR_VARS)
$(info libbluetooth_mtk begain)
LOCAL_SRC_FILES := \
  mtk.c \
  radiomgr.c \
  radiomod.c
$(info libbluetooth_mtk c)
LOCAL_C_INCLUDES := system/bt/hci/include

$(info libbluetooth_mtk include)
LOCAL_CFLAGS += -DMTK_MT7662

#ifeq($(TARGET_BUILD_VARIANT),eng)
ifneq (,$(filter eng,$(TARGET_BUILD_VARIANT)))
  LOCAL_CFLAGS += -DBD_ADDR_AUTOGEN
endif

$(info libbluetooth_mtk out)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libbluetooth_mtk
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

###########################################################################
# MTK BT DRIVER FOR BLUEDROID
###########################################################################
include $(CLEAR_VARS)
$(info lib -vendor begain)
LOCAL_SRC_FILES := bt_drv.c
$(info lib -vendor c)
LOCAL_C_INCLUDES := system/bt/hci/include
$(info lib -vendor include)
LOCAL_CFLAGS :=

LOCAL_MODULE_TAGS := optional
ifeq ($(BLUETOOTH_MODULE), MULTI_BLUETOOTH_SUPPORT)
LOCAL_MODULE := libbt-vendor-mtk
else
LOCAL_MODULE := libbt-vendor
endif
LOCAL_SHARED_LIBRARIES := liblog libbluetooth_mtk
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
endif