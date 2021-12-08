cmd_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/.hal_sdio.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Wno-date-time   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/phydm   -I/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/platform -DCONFIG_RTL8188F -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_EFUSE_CONFIG_FILE -DEFUSE_MAP_PATH=\"/system/etc/wifi/wifi_efuse_8189fs.map\" -DWIFIMAC_PATH=\"/data/wifimac.txt\" -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_TXPWR_BY_RATE_EN=1 -DCONFIG_TXPWR_LIMIT_EN=0 -DCONFIG_RTW_ADAPTIVITY_EN=0 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DDM_ODM_SUPPORT_TYPE=0x04 -DCONFIG_LITTLE_ENDIAN -DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_LITTLE_ENDIAN -fno-pic -DCONFIG_IOCTL_CFG80211 -DCONFIG_CONCURRENT_MODE -DCONFIG_P2P_IPS -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_RADIO_WORK  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(hal_sdio)"  -D"KBUILD_MODNAME=KBUILD_STR(8189fs)" -c -o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.c

source_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o := /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.c

deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o := \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/drv_types.h \
    $(wildcard include/config/arp/keep/alive.h) \
    $(wildcard include/config/80211n/ht.h) \
    $(wildcard include/config/80211ac/vht.h) \
    $(wildcard include/config/intel/widi.h) \
    $(wildcard include/config/beamforming.h) \
    $(wildcard include/config/prealloc/rx/skb/buffer.h) \
    $(wildcard include/config/tdls.h) \
    $(wildcard include/config/wapi/support.h) \
    $(wildcard include/config/drvext.h) \
    $(wildcard include/config/mp/included.h) \
    $(wildcard include/config/br/ext.h) \
    $(wildcard include/config/iol.h) \
    $(wildcard include/config/bt/coexist.h) \
    $(wildcard include/config/1t1r.h) \
    $(wildcard include/config/2t2r.h) \
    $(wildcard include/config/tx/early/mode.h) \
    $(wildcard include/config/adaptor/info/caching/file.h) \
    $(wildcard include/config/layer2/roaming.h) \
    $(wildcard include/config/80211d.h) \
    $(wildcard include/config/special/setting/for/funai/tv.h) \
    $(wildcard include/config/ieee80211/band/5ghz.h) \
    $(wildcard include/config/load/phy/para/from/file.h) \
    $(wildcard include/config/multi/vir/ifaces.h) \
    $(wildcard include/config/auto/chnl/sel/nhm.h) \
    $(wildcard include/config/sdio/hci.h) \
    $(wildcard include/config/gspi/hci.h) \
    $(wildcard include/config/pci/hci.h) \
    $(wildcard include/config/concurrent/mode.h) \
    $(wildcard include/config/dbg/counter.h) \
    $(wildcard include/config/dfs/master.h) \
    $(wildcard include/config/sdio/indirect/access.h) \
    $(wildcard include/config/ioctl/cfg80211.h) \
    $(wildcard include/config/usb/hci.h) \
    $(wildcard include/config/usb/vendor/req/mutex.h) \
    $(wildcard include/config/usb/vendor/req/buffer/prealloc.h) \
    $(wildcard include/config/intel/proxim.h) \
    $(wildcard include/config/mac/loopback/driver.h) \
    $(wildcard include/config/ieee80211w.h) \
    $(wildcard include/config/ap/mode.h) \
    $(wildcard include/config/p2p.h) \
    $(wildcard include/config/wfd.h) \
    $(wildcard include/config/bt/coexist/socket/trx.h) \
    $(wildcard include/config/gpio/api.h) \
    $(wildcard include/config/autosuspend.h) \
    $(wildcard include/config/pno/support.h) \
    $(wildcard include/config/pno/set/debug.h) \
    $(wildcard include/config/wowlan.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/drv_conf.h \
    $(wildcard include/config/android.h) \
    $(wildcard include/config/platform/android.h) \
    $(wildcard include/config/validate/ssid.h) \
    $(wildcard include/config/signal/display/dbm.h) \
    $(wildcard include/config/has/earlysuspend.h) \
    $(wildcard include/config/resume/in/workqueue.h) \
    $(wildcard include/config/android/power.h) \
    $(wildcard include/config/wakelock.h) \
    $(wildcard include/config/vendor/req/retry.h) \
    $(wildcard include/config/rtw/hiq/filter.h) \
    $(wildcard include/config/rtw/adaptivity/en.h) \
    $(wildcard include/config/rtw/adaptivity/mode.h) \
    $(wildcard include/config/rtw/adaptivity/dml.h) \
    $(wildcard include/config/rtw/adaptivity/dc/backoff.h) \
    $(wildcard include/config/rtw/adaptivity/th/l2h/ini.h) \
    $(wildcard include/config/rtw/adaptivity/th/edcca/hl/diff.h) \
    $(wildcard include/config/txpwr/by/rate/en.h) \
    $(wildcard include/config/txpwr/limit/en.h) \
    $(wildcard include/config/calibrate/tx/power/by/regulatory.h) \
    $(wildcard include/config/calibrate/tx/power/to/max.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/a.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/b.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/c.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/d.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/a.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/b.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/c.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/d.h) \
    $(wildcard include/config/rtw/amplifier/type/2g.h) \
    $(wildcard include/config/rtw/amplifier/type/5g.h) \
    $(wildcard include/config/rtw/rfe/type.h) \
    $(wildcard include/config/rtw/glna/type.h) \
    $(wildcard include/config/rtw/pll/ref/clk/sel.h) \
    $(wildcard include/config/rtl8812a.h) \
    $(wildcard include/config/rtl8821a.h) \
    $(wildcard include/config/rtl8814a.h) \
    $(wildcard include/config/deauth/before/connect.h) \
    $(wildcard include/config/wext/dont/join/byssid.h) \
    $(wildcard include/config/doscan/in/busytraffic.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/autoconf.h \
    $(wildcard include/config/rtl8188f.h) \
    $(wildcard include/config/recv/reordering/ctrl.h) \
    $(wildcard include/config/platform/intel/byt.h) \
    $(wildcard include/config/cfg80211/force/compatible/2/6/37/under.h) \
    $(wildcard include/config/debug/cfg80211.h) \
    $(wildcard include/config/set/scan/deny/timer.h) \
    $(wildcard include/config/nativeap/mlme.h) \
    $(wildcard include/config/hostapd/mlme.h) \
    $(wildcard include/config/find/best/channel.h) \
    $(wildcard include/config/tx/mcast2uni.h) \
    $(wildcard include/config/p2p/remove/group/info.h) \
    $(wildcard include/config/dbg/p2p.h) \
    $(wildcard include/config/p2p/ps.h) \
    $(wildcard include/config/p2p/op/chk/social/ch.h) \
    $(wildcard include/config/cfg80211/onechannel/under/concurrent.h) \
    $(wildcard include/config/p2p/chk/invite/ch/list.h) \
    $(wildcard include/config/p2p/invite/iot.h) \
    $(wildcard include/config/tdls/driver/setup.h) \
    $(wildcard include/config/tdls/autosetup.h) \
    $(wildcard include/config/tdls/autocheckalive.h) \
    $(wildcard include/config/tdls/ch/sw.h) \
    $(wildcard include/config/hwport/swap.h) \
    $(wildcard include/config/runtime/port/switch.h) \
    $(wildcard include/config/tsf/reset/offload.h) \
    $(wildcard include/config/scan/backop.h) \
    $(wildcard include/config/layer2/roaming/resume.h) \
    $(wildcard include/config/antenna/diversity.h) \
    $(wildcard include/config/sw/led.h) \
    $(wildcard include/config/xmit/ack.h) \
    $(wildcard include/config/active/keep/alive/check.h) \
    $(wildcard include/config/c2h/packet/en.h) \
    $(wildcard include/config/rf/gain/offset.h) \
    $(wildcard include/config/sdio/chk/hci/resume.h) \
    $(wildcard include/config/tx/aggregation.h) \
    $(wildcard include/config/sdio/rx/copy.h) \
    $(wildcard include/config/xmit/thread/mode.h) \
    $(wildcard include/config/sdio/tx/enable/aval/int.h) \
    $(wildcard include/config/skb/copy.h) \
    $(wildcard include/config/new/signal/stat/process.h) \
    $(wildcard include/config/embedded/fwimg.h) \
    $(wildcard include/config/file/fwimg.h) \
    $(wildcard include/config/long/delay/issue.h) \
    $(wildcard include/config/patch/join/wrong/channel.h) \
    $(wildcard include/config/attempt/to/fix/ap/beacon/error.h) \
    $(wildcard include/config/power/saving.h) \
    $(wildcard include/config/mp/iwpriv/support.h) \
    $(wildcard include/config/ips.h) \
    $(wildcard include/config/lps.h) \
    $(wildcard include/config/lps/lclk.h) \
    $(wildcard include/config/check/leave/lps.h) \
    $(wildcard include/config/lps/slow/transition.h) \
    $(wildcard include/config/detect/cpwm/by/polling.h) \
    $(wildcard include/config/lps/rpwm/timer.h) \
    $(wildcard include/config/lps/lclk/wd/timer.h) \
    $(wildcard include/config/ips/check/in/wd.h) \
    $(wildcard include/config/swlps/in/ips.h) \
    $(wildcard include/config/fwlps/in/ips.h) \
    $(wildcard include/config/gtk/ol.h) \
    $(wildcard include/config/gpio/wakeup.h) \
    $(wildcard include/config/debug.h) \
    $(wildcard include/config/debug/rtl871x.h) \
    $(wildcard include/config/proc/debug.h) \
    $(wildcard include/config/error/detect.h) \
    $(wildcard include/config/fw/c2h/debug.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_ic_cfg.h \
    $(wildcard include/config/multidrv.h) \
    $(wildcard include/config/rtl8188e.h) \
    $(wildcard include/config/rtl8192e.h) \
    $(wildcard include/config/rtl8723b.h) \
    $(wildcard include/config/rtl8703b.h) \
    $(wildcard include/config/rtl8822b.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/basic_types.h \
  include/generated/uapi/linux/version.h \
  /home/xaldey/n-amlogic/common/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/types.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/int-ll64.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/int-ll64.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bitsperlong.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/bitsperlong.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/posix_types.h \
  /home/xaldey/n-amlogic/common/include/linux/stddef.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/stddef.h \
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
  arch/arm64/include/generated/asm/posix_types.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/posix_types.h \
  /home/xaldey/n-amlogic/common/include/linux/module.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/xaldey/n-amlogic/common/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/xaldey/n-amlogic/common/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/const.h \
  /home/xaldey/n-amlogic/common/include/linux/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/stat.h \
    $(wildcard include/config/compat.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/stat.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/compat.h \
  /home/xaldey/n-amlogic/common/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/no/hz/common.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/sched/hmp.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/preempt/notifiers.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/mm/owner.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sched.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/param.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/param.h \
  /home/xaldey/n-amlogic/common/include/linux/capability.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/capability.h \
  /home/xaldey/n-amlogic/common/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/xaldey/n-amlogic/common/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
  /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/lib/gcc/aarch64-linux-gnu/4.9.2/include/stdarg.h \
  /home/xaldey/n-amlogic/common/include/linux/linkage.h \
  /home/xaldey/n-amlogic/common/include/linux/stringify.h \
  /home/xaldey/n-amlogic/common/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/linkage.h \
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
  /home/xaldey/n-amlogic/common/include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/xaldey/n-amlogic/common/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
  /home/xaldey/n-amlogic/common/include/linux/kern_levels.h \
  /home/xaldey/n-amlogic/common/include/linux/cache.h \
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
  /home/xaldey/n-amlogic/common/include/linux/timex.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/timex.h \
  /home/xaldey/n-amlogic/common/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/xaldey/n-amlogic/common/include/linux/seqlock.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/xaldey/n-amlogic/common/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/xaldey/n-amlogic/common/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
  arch/arm64/include/generated/asm/preempt.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/preempt.h \
  /home/xaldey/n-amlogic/common/include/linux/thread_info.h \
  /home/xaldey/n-amlogic/common/include/linux/bug.h \
  arch/arm64/include/generated/asm/bug.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
  /home/xaldey/n-amlogic/common/include/linux/irqflags.h \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/irqflags.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/ptrace.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/ptrace.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/hwcap.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/hwcap.h \
  /home/xaldey/n-amlogic/common/include/linux/bottom_half.h \
  /home/xaldey/n-amlogic/common/include/linux/preempt_mask.h \
  /home/xaldey/n-amlogic/common/include/linux/spinlock_types.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/spinlock_types.h \
  /home/xaldey/n-amlogic/common/include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwlock_types.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/spinlock.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/processor.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/fpsimd.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwlock.h \
  /home/xaldey/n-amlogic/common/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/xaldey/n-amlogic/common/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/atomic.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/cmpxchg.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/atomic-long.h \
  /home/xaldey/n-amlogic/common/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/div64.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/time.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/param.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/timex.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/arch_timer.h \
  /home/xaldey/n-amlogic/common/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/xaldey/n-amlogic/common/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/xaldey/n-amlogic/common/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/xaldey/n-amlogic/common/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/xaldey/n-amlogic/common/include/linux/jiffies.h \
  /home/xaldey/n-amlogic/common/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/io.h \
  /home/xaldey/n-amlogic/common/include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/transparent/hugepage.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/proc-fns.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/page.h \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable-3level-types.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/pgtable-nopud.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/memory.h \
  arch/arm64/include/generated/asm/sizes.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/sizes.h \
  /home/xaldey/n-amlogic/common/include/linux/sizes.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/getorder.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable-hwdef.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable-3level-hwdef.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
    $(wildcard include/config/arch/uses/numa/prot/none.h) \
  /home/xaldey/n-amlogic/common/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/compaction.h) \
  /home/xaldey/n-amlogic/common/include/linux/auxvec.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/auxvec.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/auxvec.h \
  /home/xaldey/n-amlogic/common/include/linux/rbtree.h \
  /home/xaldey/n-amlogic/common/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwsem-spinlock.h \
  /home/xaldey/n-amlogic/common/include/linux/completion.h \
  /home/xaldey/n-amlogic/common/include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/current.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/wait.h \
  /home/xaldey/n-amlogic/common/include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/xaldey/n-amlogic/common/include/linux/bitmap.h \
  /home/xaldey/n-amlogic/common/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/xaldey/n-amlogic/common/include/linux/uprobes.h \
  /home/xaldey/n-amlogic/common/include/linux/page-flags-layout.h \
  /home/xaldey/n-amlogic/common/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/generated/bounds.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/sparsemem.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/mmu.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  /home/xaldey/n-amlogic/common/include/xen/xen.h \
    $(wildcard include/config/xen.h) \
    $(wildcard include/config/xen/dom0.h) \
    $(wildcard include/config/xen/pvh.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/iomap.h \
    $(wildcard include/config/has/ioport.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/generic/iomap.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/timex.h \
  /home/xaldey/n-amlogic/common/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/xaldey/n-amlogic/common/include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/movable/node.h) \
  arch/arm64/include/generated/asm/cputime.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/cputime_jiffies.h \
  /home/xaldey/n-amlogic/common/include/linux/smp.h \
  /home/xaldey/n-amlogic/common/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/smp.h \
  /home/xaldey/n-amlogic/common/include/linux/sem.h \
  /home/xaldey/n-amlogic/common/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  /home/xaldey/n-amlogic/common/include/linux/rcutree.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sem.h \
  /home/xaldey/n-amlogic/common/include/linux/ipc.h \
  /home/xaldey/n-amlogic/common/include/linux/uidgid.h \
    $(wildcard include/config/user/ns.h) \
  /home/xaldey/n-amlogic/common/include/linux/highuid.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/asm/ipcbuf.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/asm/sembuf.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/sembuf.h \
  /home/xaldey/n-amlogic/common/include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/signal.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/signal.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/signal.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/signal.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/signal-defs.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/sigcontext.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/siginfo.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/siginfo.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/siginfo.h \
  /home/xaldey/n-amlogic/common/include/linux/pid.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/xaldey/n-amlogic/common/include/linux/pfn.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/percpu.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/percpu.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/xaldey/n-amlogic/common/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/xaldey/n-amlogic/common/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/xaldey/n-amlogic/common/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sysctl.h \
  /home/xaldey/n-amlogic/common/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/xaldey/n-amlogic/common/include/linux/notifier.h \
  /home/xaldey/n-amlogic/common/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /home/xaldey/n-amlogic/common/include/linux/srcu.h \
  /home/xaldey/n-amlogic/common/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/topology.h \
    $(wildcard include/config/disable/cpu/sched/domain/balance.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/topology.h \
  /home/xaldey/n-amlogic/common/include/linux/proportions.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu_counter.h \
  /home/xaldey/n-amlogic/common/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/seccomp/filter.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/seccomp.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/seccomp.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/unistd.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/unistd.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/unistd.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/unistd.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/seccomp.h \
  /home/xaldey/n-amlogic/common/include/linux/rculist.h \
  /home/xaldey/n-amlogic/common/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/xaldey/n-amlogic/common/include/linux/resource.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/resource.h \
  arch/arm64/include/generated/asm/resource.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/resource.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/resource.h \
  /home/xaldey/n-amlogic/common/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/xaldey/n-amlogic/common/include/linux/timerqueue.h \
  /home/xaldey/n-amlogic/common/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/xaldey/n-amlogic/common/include/linux/latencytop.h \
  /home/xaldey/n-amlogic/common/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  /home/xaldey/n-amlogic/common/include/linux/key.h \
  /home/xaldey/n-amlogic/common/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /home/xaldey/n-amlogic/common/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/xaldey/n-amlogic/common/include/linux/gfp.h \
    $(wildcard include/config/pm/sleep.h) \
  /home/xaldey/n-amlogic/common/include/linux/ptrace.h \
  /home/xaldey/n-amlogic/common/include/linux/err.h \
  /home/xaldey/n-amlogic/common/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /home/xaldey/n-amlogic/common/include/linux/mm.h \
    $(wildcard include/config/have/arch/mmap/rnd/bits.h) \
    $(wildcard include/config/have/arch/mmap/rnd/compat/bits.h) \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/metag.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /home/xaldey/n-amlogic/common/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/xaldey/n-amlogic/common/include/linux/migrate_mode.h \
  /home/xaldey/n-amlogic/common/include/linux/range.h \
  /home/xaldey/n-amlogic/common/include/linux/bit_spinlock.h \
  /home/xaldey/n-amlogic/common/include/linux/shrinker.h \
  /home/xaldey/n-amlogic/common/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
  /home/xaldey/n-amlogic/common/include/linux/huge_mm.h \
  /home/xaldey/n-amlogic/common/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
  /home/xaldey/n-amlogic/common/include/linux/vm_event_item.h \
    $(wildcard include/config/migration.h) \
  /home/xaldey/n-amlogic/common/include/linux/nsproxy.h \
  /home/xaldey/n-amlogic/common/include/linux/kref.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/ptrace.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/stat.h \
  /home/xaldey/n-amlogic/common/include/linux/kmod.h \
  /home/xaldey/n-amlogic/common/include/linux/elf.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/elf.h \
  arch/arm64/include/generated/asm/user.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/user.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/elf.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/elf-em.h \
  /home/xaldey/n-amlogic/common/include/linux/kobject.h \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/xaldey/n-amlogic/common/include/linux/sysfs.h \
  /home/xaldey/n-amlogic/common/include/linux/kernfs.h \
  /home/xaldey/n-amlogic/common/include/linux/idr.h \
  /home/xaldey/n-amlogic/common/include/linux/kobject_ns.h \
  /home/xaldey/n-amlogic/common/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /home/xaldey/n-amlogic/common/include/linux/tracepoint.h \
  /home/xaldey/n-amlogic/common/include/linux/static_key.h \
  /home/xaldey/n-amlogic/common/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/jump_label.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/insn.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/module.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /home/xaldey/n-amlogic/common/include/linux/utsname.h \
    $(wildcard include/config/uts/ns.h) \
    $(wildcard include/config/proc/sysctl.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/utsname.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/osdep_service.h \
    $(wildcard include/config/use/vmalloc.h) \
    $(wildcard include/config/ap/wowlan.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/osdep_service_linux.h \
    $(wildcard include/config/net/radio.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/tcp/csum/offload/tx.h) \
    $(wildcard include/config/efuse/config/file.h) \
    $(wildcard include/config/file.h) \
    $(wildcard include/config/usb/suspend.h) \
  /home/xaldey/n-amlogic/common/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/debug/slab.h) \
  /home/xaldey/n-amlogic/common/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/xaldey/n-amlogic/common/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/memcg/kmem.h) \
  /home/xaldey/n-amlogic/common/include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/bql.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/net/rx/busy/poll.h) \
    $(wildcard include/config/libfcoe.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/net/dsa/tag/dsa.h) \
    $(wildcard include/config/net/dsa/tag/trailer.h) \
    $(wildcard include/config/netpoll/trap.h) \
    $(wildcard include/config/net/flow/limit.h) \
  /home/xaldey/n-amlogic/common/include/linux/pm_qos.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
  /home/xaldey/n-amlogic/common/include/linux/miscdevice.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/major.h \
  /home/xaldey/n-amlogic/common/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/xaldey/n-amlogic/common/include/linux/ioport.h \
  /home/xaldey/n-amlogic/common/include/linux/klist.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/devinfo.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/consumer.h \
  /home/xaldey/n-amlogic/common/include/linux/seq_file.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/pinctrl-state.h \
  /home/xaldey/n-amlogic/common/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/xaldey/n-amlogic/common/include/linux/ratelimit.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  /home/xaldey/n-amlogic/common/include/linux/pm_wakeup.h \
  /home/xaldey/n-amlogic/common/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/delay.h \
  /home/xaldey/n-amlogic/common/include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /home/xaldey/n-amlogic/common/include/linux/uio.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/uio.h \
  /home/xaldey/n-amlogic/common/include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/scatterlist.h \
    $(wildcard include/config/arm64/has/sg/chain.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/xaldey/n-amlogic/common/include/linux/dynamic_queue_limits.h \
  /home/xaldey/n-amlogic/common/include/linux/ethtool.h \
  /home/xaldey/n-amlogic/common/include/linux/compat.h \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /home/xaldey/n-amlogic/common/include/linux/socket.h \
  arch/arm64/include/generated/asm/socket.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/asm/sockios.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/sockios.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sockios.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/socket.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/hdlc/ioctl.h \
  /home/xaldey/n-amlogic/common/include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
  /home/xaldey/n-amlogic/common/include/linux/kdev_t.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/kdev_t.h \
  /home/xaldey/n-amlogic/common/include/linux/dcache.h \
  /home/xaldey/n-amlogic/common/include/linux/rculist_bl.h \
  /home/xaldey/n-amlogic/common/include/linux/list_bl.h \
  /home/xaldey/n-amlogic/common/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /home/xaldey/n-amlogic/common/include/linux/path.h \
  /home/xaldey/n-amlogic/common/include/linux/list_lru.h \
  /home/xaldey/n-amlogic/common/include/linux/radix-tree.h \
  /home/xaldey/n-amlogic/common/include/linux/semaphore.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/fiemap.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu-rwsem.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/fs.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/limits.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/asm/ioctl.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/ioctl.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/ioctl.h \
  /home/xaldey/n-amlogic/common/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/dqblk_xfs.h \
  /home/xaldey/n-amlogic/common/include/linux/dqblk_v1.h \
  /home/xaldey/n-amlogic/common/include/linux/dqblk_v2.h \
  /home/xaldey/n-amlogic/common/include/linux/dqblk_qtree.h \
  /home/xaldey/n-amlogic/common/include/linux/projid.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/quota.h \
  /home/xaldey/n-amlogic/common/include/linux/nfs_fs_i.h \
  /home/xaldey/n-amlogic/common/include/linux/fcntl.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/fcntl.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/fcntl.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/fcntl.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/aio_abi.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/ethtool.h \
  /home/xaldey/n-amlogic/common/include/linux/if_ether.h \
  /home/xaldey/n-amlogic/common/include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
    $(wildcard include/config/netfilter/xt/target/trace.h) \
    $(wildcard include/config/nf/tables.h) \
  /home/xaldey/n-amlogic/common/include/linux/kmemcheck.h \
  /home/xaldey/n-amlogic/common/include/linux/net.h \
  /home/xaldey/n-amlogic/common/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/random.h \
  /home/xaldey/n-amlogic/common/include/linux/irqnr.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/irqnr.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/net.h \
  /home/xaldey/n-amlogic/common/include/linux/textsearch.h \
  /home/xaldey/n-amlogic/common/include/net/checksum.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/uaccess.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/compiler.h \
  arch/arm64/include/generated/asm/checksum.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/checksum.h \
  /home/xaldey/n-amlogic/common/include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /home/xaldey/n-amlogic/common/include/linux/dma-attrs.h \
  /home/xaldey/n-amlogic/common/include/linux/dma-direction.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/dma-mapping.h \
  /home/xaldey/n-amlogic/common/include/linux/vmalloc.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/xen/hypervisor.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/../../arm/include/asm/xen/hypervisor.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/dma-mapping-common.h \
  /home/xaldey/n-amlogic/common/include/linux/dma-debug.h \
    $(wildcard include/config/dma/api/debug.h) \
  /home/xaldey/n-amlogic/common/include/linux/netdev_features.h \
  /home/xaldey/n-amlogic/common/include/net/flow_keys.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if_ether.h \
  /home/xaldey/n-amlogic/common/include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/ip/vs.h) \
  /home/xaldey/n-amlogic/common/include/net/netns/core.h \
  /home/xaldey/n-amlogic/common/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  /home/xaldey/n-amlogic/common/include/net/snmp.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/snmp.h \
  /home/xaldey/n-amlogic/common/include/linux/u64_stats_sync.h \
  /home/xaldey/n-amlogic/common/include/net/netns/unix.h \
  /home/xaldey/n-amlogic/common/include/net/netns/packet.h \
  /home/xaldey/n-amlogic/common/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  /home/xaldey/n-amlogic/common/include/net/inet_frag.h \
  /home/xaldey/n-amlogic/common/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /home/xaldey/n-amlogic/common/include/net/dst_ops.h \
  /home/xaldey/n-amlogic/common/include/net/netns/sctp.h \
  /home/xaldey/n-amlogic/common/include/net/netns/dccp.h \
  /home/xaldey/n-amlogic/common/include/net/netns/netfilter.h \
  /home/xaldey/n-amlogic/common/include/linux/proc_fs.h \
  /home/xaldey/n-amlogic/common/include/linux/netfilter.h \
    $(wildcard include/config/nf/nat/needed.h) \
  /home/xaldey/n-amlogic/common/include/linux/in.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/in.h \
  /home/xaldey/n-amlogic/common/include/linux/in6.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/in6.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/libc-compat.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/netfilter.h \
  /home/xaldey/n-amlogic/common/include/net/flow.h \
  /home/xaldey/n-amlogic/common/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
    $(wildcard include/config/ip/nf/target/ulog.h) \
    $(wildcard include/config/bridge/ebt/ulog.h) \
  /home/xaldey/n-amlogic/common/include/net/netns/conntrack.h \
    $(wildcard include/config/nf/conntrack/proc/compat.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  /home/xaldey/n-amlogic/common/include/linux/list_nulls.h \
  /home/xaldey/n-amlogic/common/include/linux/netfilter/nf_conntrack_tcp.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  /home/xaldey/n-amlogic/common/include/net/netns/nftables.h \
  /home/xaldey/n-amlogic/common/include/net/netns/xfrm.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/xfrm.h \
  /home/xaldey/n-amlogic/common/include/linux/seq_file_net.h \
  /home/xaldey/n-amlogic/common/include/net/dsa.h \
  /home/xaldey/n-amlogic/common/include/net/netprio_cgroup.h \
  /home/xaldey/n-amlogic/common/include/linux/cgroup.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/cgroupstats.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/taskstats.h \
  /home/xaldey/n-amlogic/common/include/linux/prio_heap.h \
  /home/xaldey/n-amlogic/common/include/linux/xattr.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/xattr.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu-refcount.h \
  /home/xaldey/n-amlogic/common/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
  /home/xaldey/n-amlogic/common/include/linux/hardirq.h \
  /home/xaldey/n-amlogic/common/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/xaldey/n-amlogic/common/include/linux/vtime.h \
  /home/xaldey/n-amlogic/common/include/linux/context_tracking_state.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/hardirq.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/irq.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/irq.h \
  /home/xaldey/n-amlogic/common/include/linux/irq_cpustat.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/neighbour.h \
  /home/xaldey/n-amlogic/common/include/linux/netlink.h \
  /home/xaldey/n-amlogic/common/include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  /home/xaldey/n-amlogic/common/include/linux/security.h \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/securityfs.h) \
    $(wildcard include/config/security/yama.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/netlink.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/netdevice.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if_packet.h \
  /home/xaldey/n-amlogic/common/include/linux/if_link.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if_link.h \
  /home/xaldey/n-amlogic/common/include/linux/circ_buf.h \
  /home/xaldey/n-amlogic/common/include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  arch/arm64/include/generated/asm/unaligned.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/unaligned.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/le_struct.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/packed_struct.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/be_byteshift.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/generic.h \
  /home/xaldey/n-amlogic/common/include/linux/wireless.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/wireless.h \
  /home/xaldey/n-amlogic/common/include/net/iw_handler.h \
    $(wildcard include/config/wext/priv.h) \
  /home/xaldey/n-amlogic/common/include/linux/if_arp.h \
    $(wildcard include/config/firewire/net.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if_arp.h \
  /home/xaldey/n-amlogic/common/include/linux/rtnetlink.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/rtnetlink.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/if_addr.h \
  /home/xaldey/n-amlogic/common/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/xaldey/n-amlogic/common/include/linux/irqreturn.h \
  /home/xaldey/n-amlogic/common/include/linux/ip.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/ip.h \
  /home/xaldey/n-amlogic/common/include/linux/kthread.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/limits.h \
  /home/xaldey/n-amlogic/common/include/net/ieee80211_radiotap.h \
  /home/xaldey/n-amlogic/common/include/linux/ieee80211.h \
    $(wildcard include/config/timeout.h) \
  /home/xaldey/n-amlogic/common/include/net/cfg80211.h \
    $(wildcard include/config/nl80211/testmode.h) \
    $(wildcard include/config/cfg80211/wext.h) \
  /home/xaldey/n-amlogic/common/include/linux/debugfs.h \
    $(wildcard include/config/debug/fs.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/nl80211.h \
  /home/xaldey/n-amlogic/common/include/net/regulatory.h \
  /home/xaldey/n-amlogic/common/include/linux/earlysuspend.h \
  /home/xaldey/n-amlogic/common/include/linux/wakelock.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_byteorder.h \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/platform/mstar389.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/byteorder/little_endian.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/wlan_bssdef.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/wifi.h \
    $(wildcard include/config/rtl8712fw.h) \
    $(wildcard include/config/error.h) \
    $(wildcard include/config/method/flash.h) \
    $(wildcard include/config/method/ethernet.h) \
    $(wildcard include/config/method/label.h) \
    $(wildcard include/config/method/display.h) \
    $(wildcard include/config/method/e/nfc.h) \
    $(wildcard include/config/method/i/nfc.h) \
    $(wildcard include/config/method/nfc.h) \
    $(wildcard include/config/method/pbc.h) \
    $(wildcard include/config/method/keypad.h) \
    $(wildcard include/config/method/vpbc.h) \
    $(wildcard include/config/method/ppbc.h) \
    $(wildcard include/config/method/vdisplay.h) \
    $(wildcard include/config/method/pdisplay.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/ieee80211.h \
    $(wildcard include/config/rtl8711fw.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/drv_types_linux.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_debug.h \
    $(wildcard include/config/p2p/wowlan.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_rf.h \
    $(wildcard include/config/.h) \
    $(wildcard include/config/1t.h) \
    $(wildcard include/config/2t.h) \
    $(wildcard include/config/1r.h) \
    $(wildcard include/config/2r.h) \
    $(wildcard include/config/1t2r.h) \
    $(wildcard include/config/turbo.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ht.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_cmd.h \
    $(wildcard include/config/event/thread/mode.h) \
    $(wildcard include/config/c2h/wk.h) \
    $(wildcard include/config/h2clbk.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/cmd_osdep.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_security.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_xmit.h \
    $(wildcard include/config/usb/tx/aggregation.h) \
    $(wildcard include/config/platform/arm/sunxi.h) \
    $(wildcard include/config/platform/arm/sun6i.h) \
    $(wildcard include/config/platform/arm/sun7i.h) \
    $(wildcard include/config/platform/arm/sun8i.h) \
    $(wildcard include/config/platform/arm/sun50iw1p1.h) \
    $(wildcard include/config/platform/mstar.h) \
    $(wildcard include/config/single/xmit/buf.h) \
    $(wildcard include/config/sdio/tx/tasklet.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/xmit_osdep.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_recv.h \
    $(wildcard include/config/single/recv/buf.h) \
    $(wildcard include/config/tcp/csum/offload/rx.h) \
    $(wildcard include/config/recv/thread/mode.h) \
    $(wildcard include/config/usb/interrupt/in/pipe.h) \
    $(wildcard include/config/rx/indicate/queue.h) \
    $(wildcard include/config/bsd/rx/use/mbuf.h) \
    $(wildcard include/config/signal/scale/mapping.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/recv_osdep.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_efuse.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_sreset.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_intf.h \
    $(wildcard include/config/support/usb/int.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com.h \
    $(wildcard include/config/background/noise/monitor.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/HalVerDef.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_pg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_phy.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_phy_reg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com_reg.h \
    $(wildcard include/config/usedk.h) \
    $(wildcard include/config/no/usedk.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com_phycfg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/hal_com_c2h.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com_h2c.h \
    $(wildcard include/config/ra/dbg/cmd.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com_led.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/hal_dm.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_qos.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_pwrctrl.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_mlme.h \
    $(wildcard include/config/dfs.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/mlme_osdep.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_io.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ioctl.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ioctl_set.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ioctl_query.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ioctl_rtl.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/osdep_intf.h \
    $(wildcard include/config/r871x/test.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../os_dep/linux/rtw_proc.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../os_dep/linux/ioctl_cfg80211.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../os_dep/linux/rtw_cfgvendor.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_eeprom.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/sta_info.h \
    $(wildcard include/config/atmel/rc/patch.h) \
    $(wildcard include/config/auto/ap/mode.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_event.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_mlme_ext.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_ap.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_version.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_odm.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_types.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_p2p.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_mp.h \
    $(wildcard include/config/txt.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_br_ext.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/ip.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/if_ether.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/ethernet.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/circ_buf.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtw_android.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/drv_types_sdio.h \
    $(wildcard include/config/platform/sprd.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmc/sdio_func.h \
  /home/xaldey/n-amlogic/common/include/linux/mod_devicetable.h \
  /home/xaldey/n-amlogic/common/include/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/linux/mmc/pm.h \
  /home/xaldey/n-amlogic/common/include/linux/mmc/sdio_ids.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/sdio_osintf.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/sdio_ops.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/sdio_ops_linux.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/sdio_hal.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_data.h \
    $(wildcard include/config/single/img.h) \
    $(wildcard include/config/usb/rx/aggregation.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_precomp.h \
    $(wildcard include/config/sfw/supported.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_types.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_features.h \
    $(wildcard include/config/phydm/antenna/diversity.h) \
    $(wildcard include/config/s0s1/sw/antenna/diversity.h) \
    $(wildcard include/config/hl/smart/antenna/type1.h) \
    $(wildcard include/config/path/diversity.h) \
    $(wildcard include/config/ra/dynamic/rty/limit.h) \
    $(wildcard include/config/ant/detection.h) \
    $(wildcard include/config/ra/dynamic/rate/id.h) \
    $(wildcard include/config/rtl/8881a/ant/switch.h) \
    $(wildcard include/config/slot/0/ant/switch.h) \
    $(wildcard include/config/slot/1/ant/switch.h) \
    $(wildcard include/config/no/2g/diversity.h) \
    $(wildcard include/config/2g5g/cg/trx/diversity/8881a.h) \
    $(wildcard include/config/2g/cgcs/rx/diversity.h) \
    $(wildcard include/config/2g/cg/trx/diversity.h) \
    $(wildcard include/config/2g/cg/smart/ant/diversity.h) \
    $(wildcard include/config/no/5g/diversity/8881a.h) \
    $(wildcard include/config/no/5g/diversity.h) \
    $(wildcard include/config/5g/cgcs/rx/diversity/8881a.h) \
    $(wildcard include/config/5g/cgcs/rx/diversity.h) \
    $(wildcard include/config/5g/cg/trx/diversity/8881a.h) \
    $(wildcard include/config/5g/cg/trx/diversity.h) \
    $(wildcard include/config/2g5g/cg/trx/diversity.h) \
    $(wildcard include/config/5g/cg/smart/ant/diversity.h) \
    $(wildcard include/config/not/support/antdiv.h) \
    $(wildcard include/config/2g/support/antdiv.h) \
    $(wildcard include/config/5g/support/antdiv.h) \
    $(wildcard include/config/2g5g/support/antdiv.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm.h \
    $(wildcard include/config/bb/rf.h) \
    $(wildcard include/config/phy/reg/pg/value/type.h) \
    $(wildcard include/config/bb/phy/reg.h) \
    $(wildcard include/config/bb/agc/tab.h) \
    $(wildcard include/config/bb/agc/tab/2g.h) \
    $(wildcard include/config/bb/agc/tab/5g.h) \
    $(wildcard include/config/bb/phy/reg/pg.h) \
    $(wildcard include/config/bb/phy/reg/mp.h) \
    $(wildcard include/config/bb/agc/tab/diff.h) \
    $(wildcard include/config/rf/radio.h) \
    $(wildcard include/config/rf/txpwr/lmt.h) \
    $(wildcard include/config/fw/nic.h) \
    $(wildcard include/config/fw/nic/2.h) \
    $(wildcard include/config/fw/ap.h) \
    $(wildcard include/config/fw/ap/2.h) \
    $(wildcard include/config/fw/mp.h) \
    $(wildcard include/config/fw/wowlan.h) \
    $(wildcard include/config/fw/wowlan/2.h) \
    $(wildcard include/config/fw/ap/wowlan.h) \
    $(wildcard include/config/fw/bt.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_pre_define.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_dig.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_edcaturbocheck.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_pathdiv.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_antdiv.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_antdect.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_dynamicbbpowersaving.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_rainfo.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_dynamictxpower.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_cfotracking.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_acs.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_adaptivity.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_beamforming.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/halcomtxbf.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbfjaguar.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbf8192e.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbf8814a.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbf8821b.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbf8822b.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/txbf/haltxbfinterface.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_noisemonitor.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/halphyrf_ce.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_powertracking_ce.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_hwconfig.h \
    $(wildcard include/config/mp.h) \
    $(wildcard include/config/tc.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_debug.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_regdefine11ac.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_regdefine11n.h \
    $(wildcard include/config/anta/11n.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_interface.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/phydm_reg.h \
    $(wildcard include/config/wlan/hal/8814ae.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/halhwimg8188f_mac.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/halhwimg8188f_rf.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/halhwimg8188f_bb.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/halhwimg8188f_fw.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/hal8188freg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/phydm_rtl8188f.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/phydm_regconfig8188f.h \
    $(wildcard include/config/h/8188f.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/../hal/phydm/rtl8188f/halphyrf_8188f.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_hal.h \
    $(wildcard include/config/check/bt/hang.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_data.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_spec.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_rf.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_dm.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_recv.h \
    $(wildcard include/config/minimal/memory/usage.h) \
    $(wildcard include/config/platform/hisilicon.h) \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_xmit.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_cmd.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_led.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/Hal8188FPwrSeq.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/HalPwrSeqCmd.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/Hal8188FPhyReg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/Hal8188FPhyCfg.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/rtl8188f_sreset.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_com.h \
  /home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/include/hal_sdio.h \

/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/realtek/drivers/8189ftv/rtl8189FS/hal/hal_hci/hal_sdio.o):
