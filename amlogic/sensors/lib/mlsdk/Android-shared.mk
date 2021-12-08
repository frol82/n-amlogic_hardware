SHELL=/bin/bash

# Modify the following variables according to your product and source location.
PRODUCT      = g02_d8ref
ANDROID_ROOT = /home/amlogic/work/ics-mx0625
KERNEL_ROOT  = /home/amlogic/work/ics-mx0625/common

#For android versions of Jellybean and later, use androideabi
#CROSS		 = $(ANDROID_ROOT)/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-
#For android versions earlier than Jellybean, use arm-eabi
CROSS		 = $(ANDROID_ROOT)/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
 

# Verbose compile info for android target
VERBOSE		 = 1
TARGET 	     = android

MLSDK_ROOT   = $(CURDIR)

ifeq ($(VERBOSE),1)
	DUMP=1>/dev/stdout
else
	DUMP=1>/dev/null
endif

include Android-common.mk

#############################################################################
## targets

LIB_FOLDERS  = platform/linux
LIB_FOLDERS += mllite/mpl/$(TARGET)
LIB_FOLDERS += mldmp/mpl/$(TARGET)
LIB_FOLDERS += external/aichi/mpl/$(TARGET)
LIB_FOLDERS += external/akmd/mpl/$(TARGET)

APP_FOLDERS  = mlapps/DemoAppPoll/PollUnix
ifeq ($(MPU_NAME),MPU3050)
APP_FOLDERS += mltools/driver_selftest
endif

INSTALL_DIR = $(CURDIR)

####################################################################################################
## macros

define echo_in_colors
	echo -ne "\e[1;34m"$(1)"\e[0m"
endef	

define maker_libs
	echo "MLPLATFORM_LIB_NAME = $(MLPLATFORM_LIB_NAME)" >> /tmp/makeecho
	echo "MLLITE_LIB_NAME     = $(MLLITE_LIB_NAME)" >> /tmp/makeecho
	echo "AICHI_LIB_NAME      = $(AICHI_LIB_NAME)" >> /tmp/makeecho
	echo "AKM_LIB_NAME        = $(AKM_LIB_NAME)" >> /tmp/makeecho
	echo "MPL_LIB_NAME        = $(MPL_LIB_NAME)" >> /tmp/makeecho 
	echo "MLSDK_ROOT          = $(MLSDK_ROOT)" >> /tmp/makeecho 

	$(call echo_in_colors, "\n<making '$(1)' in folder 'platform/linux'>\n"); \
	make MLSDK_ROOT=$(MLSDK_ROOT) MLPLATFORM_LIB_NAME=$(MLPLATFORM_LIB_NAME) ANDROID_ROOT=$(ANDROID_ROOT) KERNEL_ROOT=$(KERNEL_ROOT) PRODUCT=$(PRODUCT) -C platform/linux -f Android-shared.mk $@ $(DUMP)

	$(call echo_in_colors, "\n<making '$(1)' in folder 'mllite/mpl/$(TARGET)'>\n"); \
	make MLSDK_ROOT=$(MLSDK_ROOT) MLLITE_LIB_NAME=$(MLLITE_LIB_NAME) ANDROID_ROOT=$(ANDROID_ROOT) KERNEL_ROOT=$(KERNEL_ROOT) PRODUCT=$(PRODUCT) -C mllite/mpl/$(TARGET) -f Android-shared.mk $@ $(DUMP)

	if test -f external/aichi/mpl/$(TARGET)/Android-shared.mk; then \
		$(call echo_in_colors, "\n<making '$(1)' in folder 'external/aichi/mpl/$(TARGET)'>\n"); \
		make MLSDK_ROOT=$(MLSDK_ROOT) AICHI_LIB_NAME=$(AICHI_LIB_NAME) ANDROID_ROOT=$(ANDROID_ROOT) KERNEL_ROOT=$(KERNEL_ROOT) PRODUCT=$(PRODUCT) -C external/aichi/mpl/$(TARGET) -f Android-shared.mk $@ $(DUMP); \
	fi

	if test -f external/akmd/mpl/$(TARGET)/Android-shared.mk; then \
		$(call echo_in_colors, "\n<making '$(1)' in folder 'external/akmd/mpl/$(TARGET)'>\n"); \
		make MLSDK_ROOT=$(MLSDK_ROOT) AKM_LIB_NAME=$(AKM_LIB_NAME) ANDROID_ROOT=$(ANDROID_ROOT) KERNEL_ROOT=$(KERNEL_ROOT) PRODUCT=$(PRODUCT) -C external/akmd/mpl/$(TARGET) -f Android-shared.mk $@ $(DUMP); \
	fi

	if test -f mldmp/mpl/$(TARGET)/Android-shared.mk; then \
		$(call echo_in_colors, "\n<making '$(1)' in folder 'mldmp/mpl/$(TARGET)'>\n"); \
	        make MLSDK_ROOT=$(MLSDK_ROOT) MPL_LIB_NAME=$(MPL_LIB_NAME) ANDROID_ROOT=$(ANDROID_ROOT) KERNEL_ROOT=$(KERNEL_ROOT) PRODUCT=$(PRODUCT) -C mldmp/mpl/$(TARGET) -f Android-shared.mk $@ $(DUMP); \
	fi
endef

define maker_apps
	for dir in $(APP_FOLDERS); do \
		$(call echo_in_colors, "\n<making '$(1)' in folder $$dir>\n"); \
		make MLSDK_ROOT=$(MLSDK_ROOT) -C $$dir TARGET=$(TARGET) -f Android-shared.mk $@ $(DUMP); \
	done
endef 

#############################################################################
## rules

.PHONY : all $(LIB_FOLDERS) $(APP_FOLDERS) clean cleanall install

all :
	@$(call maker_libs,$@)
	#@$(call maker_apps,$@)

clean :
	@$(call maker_libs,$@)
	@$(call maker_apps,$@)

cleanall :
	@$(call maker_libs,$@)
	@$(call maker_apps,$@)

