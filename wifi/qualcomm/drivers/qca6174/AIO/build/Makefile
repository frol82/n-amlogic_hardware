#
# Main Makefile
#
export ATH_TOPDIR=$(shell pwd)/..
export BACKPORT_PWD=$(shell pwd)/backports
# different customer want to use different wpa_supplicant
# in board_type config file, we can override it
export WPA_SUPPLICANT_TOPDIR=${ATH_TOPDIR}/apps/wpa_supplicant_8

include ./env.makefile
include scripts/${BOARD_TYPE}/config.${BOARD_TYPE}
include scripts/${BOARD_TYPE}/Makefile.${BOARD_TYPE}
ifneq ($(wildcard scripts/${BOARD_TYPE}/Makefile.${BLUETOOTHSTACK}), )
    include scripts/${BOARD_TYPE}/Makefile.${BLUETOOTHSTACK}
endif

#################################################################################################################################
ifndef KERNELPATH
$(error "Must specify KERNELPATH value")
endif

ifndef KERNELARCH
$(error "Must specify KERNELARCH value")
endif

#################################################################################################################################
export MAKEARCH=make ARCH=$(KERNELARCH) CROSS_COMPILE=$(TOOLPREFIX)

export INSTALL_ROOT=${ATH_TOPDIR}/rootfs-x86-android.build
export ROOTFS_TOPDIR=${ATH_TOPDIR}/rootfs
export WLAN_DRIVER_TOPDIR=${ATH_TOPDIR}/drivers
export IW30_TOPDIR=${ATH_TOPDIR}/apps/iw-3.0
export LIBNL32_TOPDIR=${ATH_TOPDIR}/apps/libnl-3.2.25
export QCMBR_TOPDIR=${ATH_TOPDIR}/apps/qcmbr
export BLUETOPIA_TOPDIR=${ATH_TOPDIR}/apps/Bluetopia
export BTDIAG_TOPDIR=${ATH_TOPDIR}/apps/Btdiag
export ATH_QCACLD_TOPDIR=${WLAN_DRIVER_TOPDIR}/qcacld-new
export ATH_ATH6KL_TOPDIR=${WLAN_DRIVER_TOPDIR}/ath6kl
export ATHDIAG_TOPDIR=${ATH_QCACLD_TOPDIR}/tools/athdiag
#################################################################################################################################
# qcacld PATH
#################################################################################################################################
export FW_WLAN_NAME=qcacld-new
#################################################################################################################################
# CFG80211 PATH
#################################################################################################################################
export CFG80211_NAME=backports

#################################################################################################################################
clean:  drivers_clean rootfs_clean

#
# rootfs build
#
rootfs_prep:
	@mkdir -p $(INSTALL_ROOT)
	@mkdir -p $(INSTALL_ROOT)/sbin
	@mkdir -p $(INSTALL_ROOT)/usr/sbin
	@mkdir -p $(INSTALL_ROOT)/lib/modules
	@mkdir -p $(INSTALL_ROOT)/etc

rootfs_build:
	@echo Build rootfs

rootfs_clean:
	@echo Clean rootfs
	@rm -rf $(INSTALL_ROOT)

#
# drivers build
# include WLAN & BT 
#
drivers: rootfs_prep
	@echo Build drivers
	cd ${WLAN_DRIVER_TOPDIR} && ${MAKEARCH}
	find ${WLAN_DRIVER_TOPDIR} -name 'cfg80211.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'compat.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'wlan.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'bluetooth.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'hci_uart.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'btusb.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'ath3k.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'hidp.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'rfcomm.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'cmtp.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'bnep.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'Tuffelo_wlan.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	@echo Strip modules
	@cd ${INSTALL_ROOT}/lib/modules && ${TOOLPREFIX}strip --strip-unneeded *.ko


drivers_firmware: rootfs_prep
	@echo Install firmware
	cd ${WLAN_DRIVER_TOPDIR} && ${MAKEARCH} firmware_install

drivers_firmware_transfer:
	@echo Transfer driver firmwares
	cd ${WLAN_DRIVER_TOPDIR} && ${MAKEARCH} firmware_toarray

drivers_clean:
	@echo Clean drivers
	cd ${WLAN_DRIVER_TOPDIR} && ${MAKEARCH} clean

common_patch:
	@echo Start Common Patches
	@cd ${WLAN_DRIVER_TOPDIR} && patch -s -p0 < patches/001-cfg80211-backports-3.12.8-1.patch
	@cd ${WLAN_DRIVER_TOPDIR}/../apps/ && patch -s -p0 < ${WLAN_DRIVER_TOPDIR}/patches/002-wpa_supplicant-for-aio.patch
	@cd ${WPA_SUPPLICANT_TOPDIR} && cp wpa_supplicant/android.config wpa_supplicant/.config
	@cd ${WPA_SUPPLICANT_TOPDIR} && cp hostapd/android.config hostapd/.config
	@echo End of Common Patches

strip_modules:
	@echo Strip modules
	@cd ${INSTALL_ROOT}/lib/modules && ${TOOLPREFIX}strip --strip-unneeded *.ko

#
# wpa_supplicant build
#
wpa_supplicant: rootfs_prep wpa_supplicant_clean libnl
ifneq ($(BUILD_APP_WLAN_WPA_SUPPLICANT_8), n)
	@echo Build wpa_supplicant
	cd $(WPA_SUPPLICANT_TOPDIR)/wpa_supplicant && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	${MAKEARCH} DESTDIR=$(INSTALL_ROOT) BINDIR=/sbin LIBDIR=/lib install
endif

wpa_supplicant_clean:
ifneq ($(BUILD_APP_WLAN_WPA_SUPPLICANT_8), n)
	@echo Clean wpa_supplicant
	cd $(WPA_SUPPLICANT_TOPDIR)/wpa_supplicant && ${MAKEARCH} clean
endif

#
# hostapd build
#
hostapd: rootfs_prep hostapd_clean libnl
ifneq ($(BUILD_APP_WLAN_HOSTAP_2_4), n)
	@echo Build hostapd
	cd $(WPA_SUPPLICANT_TOPDIR)/hostapd && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	cp -f hostapd $(INSTALL_ROOT)/sbin && \
	cp -f hostapd_cli $(INSTALL_ROOT)/sbin
endif


hostapd_clean:
ifneq ($(BUILD_APP_WLAN_HOSTAP_2_4), n)
	@echo Clean hostapd
	cd $(WPA_SUPPLICANT_TOPDIR)/hostapd && ${MAKEARCH} clean
endif


#
# iw build
#
iw: rootfs_prep iw_clean
	@echo Build iw-3.0
	cd $(IW30_TOPDIR) && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	${MAKEARCH} DESTDIR=$(INSTALL_ROOT) SBINDIR=/sbin install

iw_clean:
	@echo Clean iw-3.0
	cd $(IW30_TOPDIR) && ${MAKEARCH} clean

#
# libnl build
#
libnl_config:
ifneq ($(BUILD_APP_WLAN_LIBNL_3_2_25), n)
	@echo Config libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && \
	./configure --host=$(KERNELARCH) CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld
endif

libnl: libnl_config libnl_clean
ifneq ($(BUILD_APP_WLAN_LIBNL_3_2_25), n)
	@echo Build libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && \
	${MAKEARCH}
endif

libnl_clean:
ifneq ($(BUILD_APP_WLAN_LIBNL_3_2_25), n)
	@echo Clean libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && ${MAKEARCH} clean
endif


#
# qcmbr build
#
qcmbr: qcmbr_clean
	@echo Build qcmbr
	cd $(QCMBR_TOPDIR) && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	cp -f Qcmbr $(INSTALL_ROOT)/sbin
	
qcmbr_clean:
	@echo Clean qcmbr
	cd $(QCMBR_TOPDIR) && ${MAKEARCH} clean
	
#
# set athdiag build
#
athdiag: athdiag_tool_clean
	@echo Build athdiag
	cd $(ATHDIAG_TOPDIR) && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	cp -f athdiag $(INSTALL_ROOT)/sbin
	
athdiag_tool_clean:
	@echo Clean athdiag
	cd $(ATHDIAG_TOPDIR) && ${MAKEARCH} clean
	

#
# Btdiag build
#
btdiag: btdiag_clean
	@echo Build Btdiag
	cd $(BTDIAG_TOPDIR) && \
	${MAKEARCH} CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld && \
	cp -f Btdiag $(INSTALL_ROOT)/sbin
	
btdiag_clean:
	@echo Clean Btdiag
	cd $(BTDIAG_TOPDIR) && ${MAKEARCH} clean


drivers_ath6kl: rootfs_prep
	@echo Build drivers
	cd ${WLAN_DRIVER_TOPDIR} && ${MAKEARCH} -f Makefile.ath6kl
	find ${WLAN_DRIVER_TOPDIR} -name 'ath6kl_usb.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'cfg80211.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'compat.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'wlan.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'bluetooth.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'hci_uart.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'btusb.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'ath3k.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'hidp.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'rfcomm.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'cmtp.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'bnep.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	find ${WLAN_DRIVER_TOPDIR} -name 'Tuffelo_wlan.ko' -exec cp '{}' $(INSTALL_ROOT)/lib/modules ';'
	@echo Strip modules
	@cd ${INSTALL_ROOT}/lib/modules && ${TOOLPREFIX}strip --strip-unneeded *.ko
