cmd_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/.platform_AML_S905_sdio.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Wno-date-time   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/include   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/phydm   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/hal/btc -DCONFIG_RTL8723D -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_BT_COEXIST -DCONFIG_EFUSE_CONFIG_FILE -DEFUSE_MAP_PATH=\"/system/etc/wifi/wifi_efuse_8723ds.map\" -DWIFIMAC_PATH=\"/data/wifimac.txt\" -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_TXPWR_BY_RATE_EN=1 -DCONFIG_TXPWR_LIMIT_EN=0 -DCONFIG_RTW_ADAPTIVITY_EN=0 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DCONFIG_RTW_NAPI -DCONFIG_RTW_GRO -DCONFIG_RTW_DEBUG -DRTW_LOG_LEVEL=4 -DDM_ODM_SUPPORT_TYPE=0x04 -Wno-error=date-time -DCONFIG_PLATFORM_AML_S905 -DCONFIG_LITTLE_ENDIAN -fno-pic -DCONFIG_IOCTL_CFG80211 -DCONFIG_CONCURRENT_MODE -DCONFIG_P2P_IPS -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_RADIO_WORK -DCONFIG_PLATFORM_OPS  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(platform_AML_S905_sdio)"  -D"KBUILD_MODNAME=KBUILD_STR(8723ds)" -c -o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.c

source_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o := /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.c

deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o := \
    $(wildcard include/config/platform/aml/s905.h) \
  include/generated/uapi/linux/version.h \
  /home/xaldey/n-amlogic/common/include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/lib/gcc/aarch64-linux-gnu/4.9.2/include/stdarg.h \
  /home/xaldey/n-amlogic/common/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \
  /home/xaldey/n-amlogic/common/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/xaldey/n-amlogic/common/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/xaldey/n-amlogic/common/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/types.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/int-ll64.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/int-ll64.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/bitsperlong.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/posix_types.h \
  /home/xaldey/n-amlogic/common/include/linux/stddef.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/stddef.h \
  arch/arm64/include/generated/asm/posix_types.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/posix_types.h \
  /home/xaldey/n-amlogic/common/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
  /home/xaldey/n-amlogic/common/include/linux/kern_levels.h \
  /home/xaldey/n-amlogic/common/include/linux/linkage.h \
  /home/xaldey/n-amlogic/common/include/linux/stringify.h \
  /home/xaldey/n-amlogic/common/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/linkage.h \
  /home/xaldey/n-amlogic/common/include/linux/cache.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/kernel.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sysinfo.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/cache.h \
  /home/xaldey/n-amlogic/common/include/linux/dynamic_debug.h \
  /home/xaldey/n-amlogic/common/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/string.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/string.h \
  /home/xaldey/n-amlogic/common/include/linux/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/errno-base.h \
  /home/xaldey/n-amlogic/common/include/linux/delay.h \
  /home/xaldey/n-amlogic/common/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/xaldey/n-amlogic/common/include/linux/bitops.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/bitops.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/barrier.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/builtin-__ffs.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/builtin-ffs.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/builtin-__fls.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/builtin-fls.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/ffz.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/fls64.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/sched.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/hweight.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/arch_hweight.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/const_hweight.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/lock.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/non-atomic.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitops/le.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/byteorder.h \
  /home/xaldey/n-amlogic/common/include/linux/byteorder/little_endian.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/byteorder/little_endian.h \
  /home/xaldey/n-amlogic/common/include/linux/swab.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/swab.h \
  /home/xaldey/n-amlogic/common/include/linux/byteorder/generic.h \
  /home/xaldey/n-amlogic/common/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/xaldey/n-amlogic/common/include/linux/typecheck.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/delay.h \

/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8723ds/rtl8723DS/platform/platform_AML_S905_sdio.o):
