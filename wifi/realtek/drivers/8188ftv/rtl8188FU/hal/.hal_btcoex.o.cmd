cmd_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/.hal_btcoex.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/include   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/phydm   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/platform -DCONFIG_RTL8188F -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_CALIBRATE_TX_POWER_TO_MAX -DCONFIG_RTW_ADAPTIVITY_EN=0 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DDM_ODM_SUPPORT_TYPE=0x04 -DCONFIG_LITTLE_ENDIAN -DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_LITTLE_ENDIAN -fno-pic -DCONFIG_IOCTL_CFG80211 -DCONFIG_CONCURRENT_MODE -DCONFIG_P2P_IPS -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_LPS_SLOW_TRANSITION -DCONFIG_RADIO_WORK  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(hal_btcoex)"  -D"KBUILD_MODNAME=KBUILD_STR(8188fu)" -c -o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.c

source_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o := /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.c

deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o := \
    $(wildcard include/config/bt/coexist.h) \
    $(wildcard include/config/lps/lclk.h) \
    $(wildcard include/config/concurrent/mode.h) \
    $(wildcard include/config/p2p.h) \
    $(wildcard include/config/bt/coexist/socket/trx.h) \
    $(wildcard include/config/rtl8723b.h) \
    $(wildcard include/config/pci/hci.h) \
    $(wildcard include/config/usb/hci.h) \
    $(wildcard include/config/sdio/hci.h) \
    $(wildcard include/config/gspi/hci.h) \
    $(wildcard include/config/load/phy/para/from/file.h) \

/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8188ftv/rtl8188FU/hal/hal_btcoex.o):
