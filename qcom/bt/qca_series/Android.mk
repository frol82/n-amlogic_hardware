ifneq ($(filter qca9377 qca6174,$(BLUETOOTH_MODULE)),)
include $(call all-named-subdir-makefiles,libbt-vendor)
endif
