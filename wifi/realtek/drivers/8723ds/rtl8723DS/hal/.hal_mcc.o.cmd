cmd_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/.hal_mcc.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Wno-date-time   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/include   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/phydm   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/btc -DCONFIG_RTL8723D -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_BT_COEXIST -DCONFIG_EFUSE_CONFIG_FILE -DEFUSE_MAP_PATH=\"/system/etc/wifi/wifi_efuse_8723ds.map\" -DWIFIMAC_PATH=\"/data/wifimac.txt\" -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_TXPWR_BY_RATE_EN=1 -DCONFIG_TXPWR_LIMIT_EN=0 -DCONFIG_RTW_ADAPTIVITY_EN=0 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DCONFIG_RTW_NAPI -DCONFIG_RTW_GRO -DCONFIG_RTW_DEBUG -DRTW_LOG_LEVEL=4 -DDM_ODM_SUPPORT_TYPE=0x04 -Wno-error=date-time -DCONFIG_PLATFORM_AML_S905 -DCONFIG_LITTLE_ENDIAN -fno-pic -DCONFIG_IOCTL_CFG80211 -DCONFIG_CONCURRENT_MODE -DCONFIG_P2P_IPS -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_RADIO_WORK -DCONFIG_PLATFORM_OPS  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(hal_mcc)"  -D"KBUILD_MODNAME=KBUILD_STR(8723ds)" -c -o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.c

source_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o := /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.c

deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o := \
    $(wildcard include/config/mcc/mode.h) \
    $(wildcard include/config/mcc/mode/debug.h) \

/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/hal_mcc.o):
