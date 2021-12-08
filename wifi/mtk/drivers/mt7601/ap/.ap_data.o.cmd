cmd_/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o := aarch64-linux-gnu-gcc -Wp,-MD,/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/.ap_data.o.d  -nostdinc -isystem /home/arron/sdk/s802/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/work/xiezx/git/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/work/xiezx/git/common/include -Iinclude -I/home/work/xiezx/git/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/work/xiezx/git/common/include/uapi -Iinclude/generated/uapi -include /home/work/xiezx/git/common/include/linux/kconfig.h   -I/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601 -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO   -I/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include -DANDROID_SUPPORT -DPBF_MONITOR_SUPPORT -DCONFIG_LITTLE_ENDIAN -DUSB_BULK_BUF_ALIGMENT -DUSB_BULK_BUF_PREALLOC -DAGGREGATION_SUPPORT -DPIGGYBACK_SUPPORT -DWMM_SUPPORT -DLINUX -Wall -Wstrict-prototypes -Wno-trigraphs -DSYSTEM_LOG_SUPPORT -DRT28xx_MODE=STA -DCHIPSET=7601U -DRESOURCE_PRE_ALLOC -DCE_BBP_NOISE_ENDURANCE_SUPPORT -DCONFIG_STA_SUPPORT -DSCAN_SUPPORT -DDBG -DADHOC_WPA2PSK_SUPPORT -DWPA_SUPPLICANT_SUPPORT -DNATIVE_WPA_SUPPLICANT_SUPPORT -DDYNAMIC_PD_SUPPORT -DCONFIG_P2P_AUTO_GO_AS_SOFTAP -DDOT11_N_SUPPORT -DP2P_SUPPORT -DAPCLI_SUPPORT -DMAT_SUPPORT -DAP_SCAN_SUPPORT -DSCAN_SUPPORT -DP2P_APCLI_SUPPORT -DCONFIG_AP_SUPPORT -DCONFIG_APSTA_MIXED_SUPPORT -DUAPSD_SUPPORT -DMBSS_SUPPORT -DIAPP_SUPPORT -DDOT1X_SUPPORT -DWSC_AP_SUPPORT -DWSC_STA_SUPPORT -DSTATS_COUNT_SUPPORT -DRT_CFG80211_SUPPORT -DEXT_BUILD_CHANNEL_LIST -DLED_CONTROL_SUPPORT -DMT7601U -DMT7601 -DRLT_MAC -DRLT_RF -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DRX_DMA_SCATTER -DVCORECAL_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE -DRTMP_INTERNAL_TX_ALC -DCONFIG_ANDES_SUPPORT -DCONFIG_RX_CSO_SUPPORT -DRTMP_FREQ_CALIBRATION_SUPPORT  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ap_data)"  -D"KBUILD_MODNAME=KBUILD_STR(mt7601usta)" -c -o /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.c

source_/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o := /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.c

deps_/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o := \
    $(wildcard include/config/ap/support.h) \
    $(wildcard include/config/sta/support.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rt_config.h \
    $(wildcard include/config/h//.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_comm.h \
    $(wildcard include/config/opmode/on/ap.h) \
    $(wildcard include/config/opmode/on/sta.h) \
    $(wildcard include/config/if/opmode/on/ap.h) \
    $(wildcard include/config/if/opmode/on/sta.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_type.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_os.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/os/rt_linux.h \
    $(wildcard include/config/has/earlysuspend.h) \
    $(wildcard include/config/apsta/mixed/support.h) \
    $(wildcard include/config/5vt/enhance.h) \
    $(wildcard include/config/cso/support.h) \
    $(wildcard include/config/rx/cso/support.h) \
  /home/work/xiezx/git/common/include/linux/module.h \
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
  /home/work/xiezx/git/common/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/work/xiezx/git/common/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/work/xiezx/git/common/include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/types.h \
  /home/work/xiezx/git/common/include/asm-generic/int-ll64.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/int-ll64.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/work/xiezx/git/common/include/asm-generic/bitsperlong.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/bitsperlong.h \
  /home/work/xiezx/git/common/include/uapi/linux/posix_types.h \
  /home/work/xiezx/git/common/include/linux/stddef.h \
  /home/work/xiezx/git/common/include/uapi/linux/stddef.h \
  /home/work/xiezx/git/common/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/work/xiezx/git/common/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/work/xiezx/git/common/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  arch/arm64/include/generated/asm/posix_types.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/posix_types.h \
  /home/work/xiezx/git/common/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/work/xiezx/git/common/include/uapi/linux/const.h \
  /home/work/xiezx/git/common/include/linux/stat.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/stat.h \
    $(wildcard include/config/compat.h) \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/stat.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/stat.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/compat.h \
  /home/work/xiezx/git/common/include/linux/sched.h \
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
  /home/work/xiezx/git/common/include/uapi/linux/sched.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/param.h \
  /home/work/xiezx/git/common/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/work/xiezx/git/common/include/uapi/asm-generic/param.h \
  /home/work/xiezx/git/common/include/linux/capability.h \
  /home/work/xiezx/git/common/include/uapi/linux/capability.h \
  /home/work/xiezx/git/common/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/work/xiezx/git/common/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
  /home/arron/sdk/s802/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/lib/gcc/aarch64-linux-gnu/4.9.2/include/stdarg.h \
  /home/work/xiezx/git/common/include/linux/linkage.h \
  /home/work/xiezx/git/common/include/linux/stringify.h \
  /home/work/xiezx/git/common/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/linkage.h \
  /home/work/xiezx/git/common/include/linux/bitops.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/bitops.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/barrier.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/builtin-__ffs.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/builtin-ffs.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/builtin-__fls.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/builtin-fls.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/ffz.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/fls64.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/work/xiezx/git/common/include/asm-generic/bitops/sched.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/hweight.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/arch_hweight.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/const_hweight.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/lock.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/non-atomic.h \
  /home/work/xiezx/git/common/include/asm-generic/bitops/le.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/byteorder.h \
  /home/work/xiezx/git/common/include/linux/byteorder/little_endian.h \
  /home/work/xiezx/git/common/include/uapi/linux/byteorder/little_endian.h \
  /home/work/xiezx/git/common/include/linux/swab.h \
  /home/work/xiezx/git/common/include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/swab.h \
  /home/work/xiezx/git/common/include/linux/byteorder/generic.h \
  /home/work/xiezx/git/common/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/work/xiezx/git/common/include/linux/typecheck.h \
  /home/work/xiezx/git/common/include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/work/xiezx/git/common/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
  /home/work/xiezx/git/common/include/linux/kern_levels.h \
  /home/work/xiezx/git/common/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/work/xiezx/git/common/include/uapi/linux/kernel.h \
  /home/work/xiezx/git/common/include/uapi/linux/sysinfo.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/cache.h \
  /home/work/xiezx/git/common/include/linux/dynamic_debug.h \
  /home/work/xiezx/git/common/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/work/xiezx/git/common/include/uapi/linux/string.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/string.h \
  /home/work/xiezx/git/common/include/linux/errno.h \
  /home/work/xiezx/git/common/include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/errno.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/errno-base.h \
  /home/work/xiezx/git/common/include/linux/timex.h \
  /home/work/xiezx/git/common/include/uapi/linux/timex.h \
  /home/work/xiezx/git/common/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/work/xiezx/git/common/include/linux/seqlock.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/work/xiezx/git/common/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/work/xiezx/git/common/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
  arch/arm64/include/generated/asm/preempt.h \
  /home/work/xiezx/git/common/include/asm-generic/preempt.h \
  /home/work/xiezx/git/common/include/linux/thread_info.h \
  /home/work/xiezx/git/common/include/linux/bug.h \
  arch/arm64/include/generated/asm/bug.h \
  /home/work/xiezx/git/common/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
  /home/work/xiezx/git/common/include/linux/irqflags.h \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/irqflags.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/ptrace.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/ptrace.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/hwcap.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/hwcap.h \
  /home/work/xiezx/git/common/include/linux/bottom_half.h \
  /home/work/xiezx/git/common/include/linux/preempt_mask.h \
  /home/work/xiezx/git/common/include/linux/spinlock_types.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/spinlock_types.h \
  /home/work/xiezx/git/common/include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
  /home/work/xiezx/git/common/include/linux/rwlock_types.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/spinlock.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/processor.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/fpsimd.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
  /home/work/xiezx/git/common/include/linux/rwlock.h \
  /home/work/xiezx/git/common/include/linux/spinlock_api_smp.h \
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
  /home/work/xiezx/git/common/include/linux/rwlock_api_smp.h \
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
  /home/work/xiezx/git/common/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/atomic.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/cmpxchg.h \
  /home/work/xiezx/git/common/include/asm-generic/atomic-long.h \
  /home/work/xiezx/git/common/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  /home/work/xiezx/git/common/include/asm-generic/div64.h \
  /home/work/xiezx/git/common/include/uapi/linux/time.h \
  /home/work/xiezx/git/common/include/uapi/linux/param.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/timex.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/arch_timer.h \
  /home/work/xiezx/git/common/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/work/xiezx/git/common/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/work/xiezx/git/common/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/work/xiezx/git/common/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/work/xiezx/git/common/include/linux/jiffies.h \
  /home/work/xiezx/git/common/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/io.h \
  /home/work/xiezx/git/common/include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/transparent/hugepage.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/proc-fns.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/page.h \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/pgtable-3level-types.h \
  /home/work/xiezx/git/common/include/asm-generic/pgtable-nopud.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/memory.h \
  arch/arm64/include/generated/asm/sizes.h \
  /home/work/xiezx/git/common/include/asm-generic/sizes.h \
  /home/work/xiezx/git/common/include/linux/sizes.h \
  /home/work/xiezx/git/common/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/work/xiezx/git/common/include/asm-generic/getorder.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/pgtable-hwdef.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/pgtable-3level-hwdef.h \
  /home/work/xiezx/git/common/include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
    $(wildcard include/config/arch/uses/numa/prot/none.h) \
  /home/work/xiezx/git/common/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/compaction.h) \
  /home/work/xiezx/git/common/include/linux/auxvec.h \
  /home/work/xiezx/git/common/include/uapi/linux/auxvec.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/auxvec.h \
  /home/work/xiezx/git/common/include/linux/rbtree.h \
  /home/work/xiezx/git/common/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/work/xiezx/git/common/include/linux/rwsem-spinlock.h \
  /home/work/xiezx/git/common/include/linux/completion.h \
  /home/work/xiezx/git/common/include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  /home/work/xiezx/git/common/include/asm-generic/current.h \
  /home/work/xiezx/git/common/include/uapi/linux/wait.h \
  /home/work/xiezx/git/common/include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/work/xiezx/git/common/include/linux/bitmap.h \
  /home/work/xiezx/git/common/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/work/xiezx/git/common/include/linux/uprobes.h \
  /home/work/xiezx/git/common/include/linux/page-flags-layout.h \
  /home/work/xiezx/git/common/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/generated/bounds.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/sparsemem.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/mmu.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  /home/work/xiezx/git/common/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  /home/work/xiezx/git/common/include/xen/xen.h \
    $(wildcard include/config/xen.h) \
    $(wildcard include/config/xen/dom0.h) \
    $(wildcard include/config/xen/pvh.h) \
  /home/work/xiezx/git/common/include/asm-generic/iomap.h \
    $(wildcard include/config/has/ioport.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/generic/iomap.h) \
  /home/work/xiezx/git/common/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /home/work/xiezx/git/common/include/asm-generic/timex.h \
  /home/work/xiezx/git/common/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/work/xiezx/git/common/include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/movable/node.h) \
  arch/arm64/include/generated/asm/cputime.h \
  /home/work/xiezx/git/common/include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /home/work/xiezx/git/common/include/asm-generic/cputime_jiffies.h \
  /home/work/xiezx/git/common/include/linux/smp.h \
  /home/work/xiezx/git/common/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/smp.h \
  /home/work/xiezx/git/common/include/linux/sem.h \
  /home/work/xiezx/git/common/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  /home/work/xiezx/git/common/include/linux/rcutree.h \
  /home/work/xiezx/git/common/include/uapi/linux/sem.h \
  /home/work/xiezx/git/common/include/linux/ipc.h \
  /home/work/xiezx/git/common/include/linux/uidgid.h \
    $(wildcard include/config/user/ns.h) \
  /home/work/xiezx/git/common/include/linux/highuid.h \
  /home/work/xiezx/git/common/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/asm/ipcbuf.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/asm/sembuf.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/sembuf.h \
  /home/work/xiezx/git/common/include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
  /home/work/xiezx/git/common/include/uapi/linux/signal.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/signal.h \
  /home/work/xiezx/git/common/include/asm-generic/signal.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/signal.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/signal-defs.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/sigcontext.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/siginfo.h \
  /home/work/xiezx/git/common/include/asm-generic/siginfo.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/siginfo.h \
  /home/work/xiezx/git/common/include/linux/pid.h \
  /home/work/xiezx/git/common/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/work/xiezx/git/common/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/work/xiezx/git/common/include/linux/pfn.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/percpu.h \
  /home/work/xiezx/git/common/include/asm-generic/percpu.h \
  /home/work/xiezx/git/common/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/work/xiezx/git/common/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  /home/work/xiezx/git/common/include/linux/mmzone.h \
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
  /home/work/xiezx/git/common/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/work/xiezx/git/common/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/work/xiezx/git/common/include/uapi/linux/sysctl.h \
  /home/work/xiezx/git/common/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/work/xiezx/git/common/include/linux/notifier.h \
  /home/work/xiezx/git/common/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /home/work/xiezx/git/common/include/linux/srcu.h \
  /home/work/xiezx/git/common/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/topology.h \
    $(wildcard include/config/disable/cpu/sched/domain/balance.h) \
  /home/work/xiezx/git/common/include/asm-generic/topology.h \
  /home/work/xiezx/git/common/include/linux/proportions.h \
  /home/work/xiezx/git/common/include/linux/percpu_counter.h \
  /home/work/xiezx/git/common/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/seccomp/filter.h) \
  /home/work/xiezx/git/common/include/uapi/linux/seccomp.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/seccomp.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/unistd.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/unistd.h \
  /home/work/xiezx/git/common/include/asm-generic/unistd.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/unistd.h \
  /home/work/xiezx/git/common/include/asm-generic/seccomp.h \
  /home/work/xiezx/git/common/include/linux/rculist.h \
  /home/work/xiezx/git/common/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/work/xiezx/git/common/include/linux/resource.h \
  /home/work/xiezx/git/common/include/uapi/linux/resource.h \
  arch/arm64/include/generated/asm/resource.h \
  /home/work/xiezx/git/common/include/asm-generic/resource.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/resource.h \
  /home/work/xiezx/git/common/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/work/xiezx/git/common/include/linux/timerqueue.h \
  /home/work/xiezx/git/common/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/work/xiezx/git/common/include/linux/latencytop.h \
  /home/work/xiezx/git/common/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  /home/work/xiezx/git/common/include/linux/key.h \
  /home/work/xiezx/git/common/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /home/work/xiezx/git/common/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/work/xiezx/git/common/include/linux/gfp.h \
    $(wildcard include/config/pm/sleep.h) \
  /home/work/xiezx/git/common/include/linux/ptrace.h \
  /home/work/xiezx/git/common/include/linux/err.h \
  /home/work/xiezx/git/common/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /home/work/xiezx/git/common/include/linux/mm.h \
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
  /home/work/xiezx/git/common/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/work/xiezx/git/common/include/linux/migrate_mode.h \
  /home/work/xiezx/git/common/include/linux/range.h \
  /home/work/xiezx/git/common/include/linux/bit_spinlock.h \
  /home/work/xiezx/git/common/include/linux/shrinker.h \
  /home/work/xiezx/git/common/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
  /home/work/xiezx/git/common/include/linux/huge_mm.h \
  /home/work/xiezx/git/common/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
  /home/work/xiezx/git/common/include/linux/vm_event_item.h \
    $(wildcard include/config/migration.h) \
  /home/work/xiezx/git/common/include/linux/nsproxy.h \
  /home/work/xiezx/git/common/include/linux/kref.h \
  /home/work/xiezx/git/common/include/uapi/linux/ptrace.h \
  /home/work/xiezx/git/common/include/uapi/linux/stat.h \
  /home/work/xiezx/git/common/include/linux/kmod.h \
  /home/work/xiezx/git/common/include/linux/elf.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/elf.h \
  arch/arm64/include/generated/asm/user.h \
  /home/work/xiezx/git/common/include/asm-generic/user.h \
  /home/work/xiezx/git/common/include/uapi/linux/elf.h \
  /home/work/xiezx/git/common/include/uapi/linux/elf-em.h \
  /home/work/xiezx/git/common/include/linux/kobject.h \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/work/xiezx/git/common/include/linux/sysfs.h \
  /home/work/xiezx/git/common/include/linux/kernfs.h \
  /home/work/xiezx/git/common/include/linux/idr.h \
  /home/work/xiezx/git/common/include/linux/kobject_ns.h \
  /home/work/xiezx/git/common/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /home/work/xiezx/git/common/include/linux/tracepoint.h \
  /home/work/xiezx/git/common/include/linux/static_key.h \
  /home/work/xiezx/git/common/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/jump_label.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/insn.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/module.h \
  /home/work/xiezx/git/common/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  include/generated/uapi/linux/version.h \
  /home/work/xiezx/git/common/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/debug/slab.h) \
  /home/work/xiezx/git/common/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/work/xiezx/git/common/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/memcg/kmem.h) \
  /home/work/xiezx/git/common/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/work/xiezx/git/common/include/linux/irqreturn.h \
  /home/work/xiezx/git/common/include/linux/irqnr.h \
  /home/work/xiezx/git/common/include/uapi/linux/irqnr.h \
  /home/work/xiezx/git/common/include/linux/hardirq.h \
  /home/work/xiezx/git/common/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/work/xiezx/git/common/include/linux/vtime.h \
  /home/work/xiezx/git/common/include/linux/context_tracking_state.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/hardirq.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/irq.h \
  /home/work/xiezx/git/common/include/asm-generic/irq.h \
  /home/work/xiezx/git/common/include/linux/irq_cpustat.h \
  /home/work/xiezx/git/common/include/linux/pci.h \
    $(wildcard include/config/pci/iov.h) \
    $(wildcard include/config/pcieaspm.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/pci/ats.h) \
    $(wildcard include/config/pcieportbus.h) \
    $(wildcard include/config/pcieaer.h) \
    $(wildcard include/config/pcie/ecrc.h) \
    $(wildcard include/config/ht/irq.h) \
    $(wildcard include/config/pci/domains.h) \
    $(wildcard include/config/pci/quirks.h) \
    $(wildcard include/config/hibernate/callbacks.h) \
    $(wildcard include/config/pci/mmconfig.h) \
    $(wildcard include/config/hotplug/pci.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/eeh.h) \
  /home/work/xiezx/git/common/include/linux/mod_devicetable.h \
  /home/work/xiezx/git/common/include/linux/uuid.h \
  /home/work/xiezx/git/common/include/uapi/linux/uuid.h \
  /home/work/xiezx/git/common/include/linux/ioport.h \
  /home/work/xiezx/git/common/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/work/xiezx/git/common/include/linux/klist.h \
  /home/work/xiezx/git/common/include/linux/pinctrl/devinfo.h \
    $(wildcard include/config/pm.h) \
  /home/work/xiezx/git/common/include/linux/pinctrl/consumer.h \
  /home/work/xiezx/git/common/include/linux/seq_file.h \
  /home/work/xiezx/git/common/include/linux/pinctrl/pinctrl-state.h \
  /home/work/xiezx/git/common/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/work/xiezx/git/common/include/linux/ratelimit.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  /home/work/xiezx/git/common/include/linux/pm_wakeup.h \
  /home/work/xiezx/git/common/include/linux/io.h \
  /home/work/xiezx/git/common/include/uapi/linux/pci.h \
  /home/work/xiezx/git/common/include/uapi/linux/pci_regs.h \
  /home/work/xiezx/git/common/include/linux/pci_ids.h \
  arch/arm64/include/generated/asm/pci.h \
  /home/work/xiezx/git/common/include/asm-generic/pci.h \
  /home/work/xiezx/git/common/include/linux/netdevice.h \
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
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/net/dsa/tag/dsa.h) \
    $(wildcard include/config/net/dsa/tag/trailer.h) \
    $(wildcard include/config/netpoll/trap.h) \
    $(wildcard include/config/net/flow/limit.h) \
  /home/work/xiezx/git/common/include/linux/pm_qos.h \
  /home/work/xiezx/git/common/include/linux/miscdevice.h \
  /home/work/xiezx/git/common/include/uapi/linux/major.h \
  /home/work/xiezx/git/common/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/work/xiezx/git/common/include/asm-generic/delay.h \
  /home/work/xiezx/git/common/include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /home/work/xiezx/git/common/include/linux/uio.h \
  /home/work/xiezx/git/common/include/uapi/linux/uio.h \
  /home/work/xiezx/git/common/include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/scatterlist.h \
    $(wildcard include/config/arm64/has/sg/chain.h) \
  /home/work/xiezx/git/common/include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/work/xiezx/git/common/include/linux/dynamic_queue_limits.h \
  /home/work/xiezx/git/common/include/linux/ethtool.h \
  /home/work/xiezx/git/common/include/linux/compat.h \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /home/work/xiezx/git/common/include/linux/socket.h \
  arch/arm64/include/generated/asm/socket.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/asm/sockios.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/sockios.h \
  /home/work/xiezx/git/common/include/uapi/linux/sockios.h \
  /home/work/xiezx/git/common/include/uapi/linux/socket.h \
  /home/work/xiezx/git/common/include/uapi/linux/if.h \
  /home/work/xiezx/git/common/include/uapi/linux/hdlc/ioctl.h \
  /home/work/xiezx/git/common/include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
  /home/work/xiezx/git/common/include/linux/kdev_t.h \
  /home/work/xiezx/git/common/include/uapi/linux/kdev_t.h \
  /home/work/xiezx/git/common/include/linux/dcache.h \
  /home/work/xiezx/git/common/include/linux/rculist_bl.h \
  /home/work/xiezx/git/common/include/linux/list_bl.h \
  /home/work/xiezx/git/common/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /home/work/xiezx/git/common/include/linux/path.h \
  /home/work/xiezx/git/common/include/linux/list_lru.h \
  /home/work/xiezx/git/common/include/linux/radix-tree.h \
  /home/work/xiezx/git/common/include/linux/semaphore.h \
  /home/work/xiezx/git/common/include/uapi/linux/fiemap.h \
  /home/work/xiezx/git/common/include/linux/percpu-rwsem.h \
  /home/work/xiezx/git/common/include/uapi/linux/fs.h \
  /home/work/xiezx/git/common/include/uapi/linux/limits.h \
  /home/work/xiezx/git/common/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/asm/ioctl.h \
  /home/work/xiezx/git/common/include/asm-generic/ioctl.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/ioctl.h \
  /home/work/xiezx/git/common/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/work/xiezx/git/common/include/uapi/linux/dqblk_xfs.h \
  /home/work/xiezx/git/common/include/linux/dqblk_v1.h \
  /home/work/xiezx/git/common/include/linux/dqblk_v2.h \
  /home/work/xiezx/git/common/include/linux/dqblk_qtree.h \
  /home/work/xiezx/git/common/include/linux/projid.h \
  /home/work/xiezx/git/common/include/uapi/linux/quota.h \
  /home/work/xiezx/git/common/include/linux/nfs_fs_i.h \
  /home/work/xiezx/git/common/include/linux/fcntl.h \
  /home/work/xiezx/git/common/include/uapi/linux/fcntl.h \
  /home/work/xiezx/git/common/arch/arm64/include/uapi/asm/fcntl.h \
  /home/work/xiezx/git/common/include/uapi/asm-generic/fcntl.h \
  /home/work/xiezx/git/common/include/uapi/linux/aio_abi.h \
  /home/work/xiezx/git/common/include/uapi/linux/ethtool.h \
  /home/work/xiezx/git/common/include/linux/if_ether.h \
  /home/work/xiezx/git/common/include/linux/skbuff.h \
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
  /home/work/xiezx/git/common/include/linux/kmemcheck.h \
  /home/work/xiezx/git/common/include/linux/net.h \
  /home/work/xiezx/git/common/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /home/work/xiezx/git/common/include/uapi/linux/random.h \
  /home/work/xiezx/git/common/include/uapi/linux/net.h \
  /home/work/xiezx/git/common/include/linux/textsearch.h \
  /home/work/xiezx/git/common/include/net/checksum.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/uaccess.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/compiler.h \
  arch/arm64/include/generated/asm/checksum.h \
  /home/work/xiezx/git/common/include/asm-generic/checksum.h \
  /home/work/xiezx/git/common/include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /home/work/xiezx/git/common/include/linux/dma-attrs.h \
  /home/work/xiezx/git/common/include/linux/dma-direction.h \
  /home/work/xiezx/git/common/arch/arm64/include/asm/dma-mapping.h \
  /home/work/xiezx/git/common/include/linux/vmalloc.h \
  /home/work/xiezx/git/common/include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  /home/work/xiezx/git/common/arch/arm64/include/asm/xen/hypervisor.h \
  /home/work/xiezx/git/common/arch/arm64/include/../../arm/include/asm/xen/hypervisor.h \
  /home/work/xiezx/git/common/include/asm-generic/dma-mapping-common.h \
  /home/work/xiezx/git/common/include/linux/dma-debug.h \
    $(wildcard include/config/dma/api/debug.h) \
  /home/work/xiezx/git/common/include/linux/netdev_features.h \
  /home/work/xiezx/git/common/include/net/flow_keys.h \
  /home/work/xiezx/git/common/include/uapi/linux/if_ether.h \
  /home/work/xiezx/git/common/include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/ip/vs.h) \
  /home/work/xiezx/git/common/include/net/netns/core.h \
  /home/work/xiezx/git/common/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  /home/work/xiezx/git/common/include/net/snmp.h \
  /home/work/xiezx/git/common/include/uapi/linux/snmp.h \
  /home/work/xiezx/git/common/include/linux/u64_stats_sync.h \
  /home/work/xiezx/git/common/include/net/netns/unix.h \
  /home/work/xiezx/git/common/include/net/netns/packet.h \
  /home/work/xiezx/git/common/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  /home/work/xiezx/git/common/include/net/inet_frag.h \
  /home/work/xiezx/git/common/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /home/work/xiezx/git/common/include/net/dst_ops.h \
  /home/work/xiezx/git/common/include/net/netns/sctp.h \
  /home/work/xiezx/git/common/include/net/netns/dccp.h \
  /home/work/xiezx/git/common/include/net/netns/netfilter.h \
  /home/work/xiezx/git/common/include/linux/proc_fs.h \
  /home/work/xiezx/git/common/include/linux/netfilter.h \
    $(wildcard include/config/nf/nat/needed.h) \
  /home/work/xiezx/git/common/include/linux/in.h \
  /home/work/xiezx/git/common/include/uapi/linux/in.h \
  /home/work/xiezx/git/common/include/linux/in6.h \
  /home/work/xiezx/git/common/include/uapi/linux/in6.h \
  /home/work/xiezx/git/common/include/uapi/linux/libc-compat.h \
  /home/work/xiezx/git/common/include/uapi/linux/netfilter.h \
  /home/work/xiezx/git/common/include/net/flow.h \
  /home/work/xiezx/git/common/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
    $(wildcard include/config/ip/nf/target/ulog.h) \
    $(wildcard include/config/bridge/ebt/ulog.h) \
  /home/work/xiezx/git/common/include/net/netns/conntrack.h \
    $(wildcard include/config/nf/conntrack/proc/compat.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  /home/work/xiezx/git/common/include/linux/list_nulls.h \
  /home/work/xiezx/git/common/include/linux/netfilter/nf_conntrack_tcp.h \
  /home/work/xiezx/git/common/include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  /home/work/xiezx/git/common/include/net/netns/nftables.h \
  /home/work/xiezx/git/common/include/net/netns/xfrm.h \
  /home/work/xiezx/git/common/include/uapi/linux/xfrm.h \
  /home/work/xiezx/git/common/include/linux/seq_file_net.h \
  /home/work/xiezx/git/common/include/net/dsa.h \
  /home/work/xiezx/git/common/include/net/netprio_cgroup.h \
  /home/work/xiezx/git/common/include/linux/cgroup.h \
  /home/work/xiezx/git/common/include/uapi/linux/cgroupstats.h \
  /home/work/xiezx/git/common/include/uapi/linux/taskstats.h \
  /home/work/xiezx/git/common/include/linux/prio_heap.h \
  /home/work/xiezx/git/common/include/linux/xattr.h \
  /home/work/xiezx/git/common/include/uapi/linux/xattr.h \
  /home/work/xiezx/git/common/include/linux/percpu-refcount.h \
  /home/work/xiezx/git/common/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
  /home/work/xiezx/git/common/include/uapi/linux/neighbour.h \
  /home/work/xiezx/git/common/include/linux/netlink.h \
  /home/work/xiezx/git/common/include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  /home/work/xiezx/git/common/include/linux/security.h \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/securityfs.h) \
    $(wildcard include/config/security/yama.h) \
  /home/work/xiezx/git/common/include/uapi/linux/netlink.h \
  /home/work/xiezx/git/common/include/uapi/linux/netdevice.h \
  /home/work/xiezx/git/common/include/uapi/linux/if_packet.h \
  /home/work/xiezx/git/common/include/linux/if_link.h \
  /home/work/xiezx/git/common/include/uapi/linux/if_link.h \
  /home/work/xiezx/git/common/include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  arch/arm64/include/generated/asm/unaligned.h \
  /home/work/xiezx/git/common/include/asm-generic/unaligned.h \
  /home/work/xiezx/git/common/include/linux/unaligned/le_struct.h \
  /home/work/xiezx/git/common/include/linux/unaligned/packed_struct.h \
  /home/work/xiezx/git/common/include/linux/unaligned/be_byteshift.h \
  /home/work/xiezx/git/common/include/linux/unaligned/generic.h \
  /home/work/xiezx/git/common/include/linux/wireless.h \
  /home/work/xiezx/git/common/include/uapi/linux/wireless.h \
  /home/work/xiezx/git/common/include/linux/if_arp.h \
    $(wildcard include/config/firewire/net.h) \
  /home/work/xiezx/git/common/include/uapi/linux/if_arp.h \
  /home/work/xiezx/git/common/include/linux/ctype.h \
  /home/work/xiezx/git/common/include/linux/usb.h \
    $(wildcard include/config/usb/mon.h) \
  /home/work/xiezx/git/common/include/linux/usb/ch9.h \
  /home/work/xiezx/git/common/include/uapi/linux/usb/ch9.h \
    $(wildcard include/config/size.h) \
    $(wildcard include/config/att/one.h) \
    $(wildcard include/config/att/selfpower.h) \
    $(wildcard include/config/att/wakeup.h) \
    $(wildcard include/config/att/battery.h) \
  /home/work/xiezx/git/common/include/linux/pm_runtime.h \
  /home/work/xiezx/git/common/include/net/iw_handler.h \
    $(wildcard include/config/wext/priv.h) \
  /home/work/xiezx/git/common/include/uapi/linux/unistd.h \
  /home/work/xiezx/git/common/include/net/mac80211.h \
    $(wildcard include/config/mac80211/debugfs.h) \
    $(wildcard include/config/nl80211/testmode.h) \
    $(wildcard include/config/mac80211/leds.h) \
  /home/work/xiezx/git/common/include/linux/ieee80211.h \
    $(wildcard include/config/timeout.h) \
  /home/work/xiezx/git/common/include/net/cfg80211.h \
    $(wildcard include/config/cfg80211/wext.h) \
  /home/work/xiezx/git/common/include/linux/debugfs.h \
    $(wildcard include/config/debug/fs.h) \
  /home/work/xiezx/git/common/include/uapi/linux/nl80211.h \
  /home/work/xiezx/git/common/include/net/regulatory.h \
  /home/work/xiezx/git/common/include/linux/ip.h \
  /home/work/xiezx/git/common/include/uapi/linux/ip.h \
  /home/work/xiezx/git/common/include/linux/kthread.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/os/rt_linux_cmm.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/cfg80211.h \
  /home/work/xiezx/git/common/include/linux/earlysuspend.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/os/rt_os.h \
    $(wildcard include/config/elian/support.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/link_list.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_cmd.h \
    $(wildcard include/config/value.h) \
    $(wildcard include/config/init.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/iface/iface_util.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_def.h \
    $(wildcard include/config/desp/entry/size.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/oid.h \
    $(wildcard include/config/status.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_chip.h \
    $(wildcard include/config/andes/support.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/pbf.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/nmac/ral_nmac_pbf.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/eeprom.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/rtmp_mac.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/nmac/ral_nmac.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_type.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/omac/ral_omac_rxwi.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/nmac/ral_nmac_txwi.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/mac_usb.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/nmac/ral_nmac_usb.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/rtmp_mac.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/chip/rtmp_phy.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/rf_ctrl.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/phy/rlt_phy.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_iface.h \
    $(wildcard include/config/.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/iface/rtmp_usb.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtusb_io.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/wpa_cmm.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/dot11i_wpa.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_dot11.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_mcu.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/chip/mt7601.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_timer.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/cfg80211extr.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mlme.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_dot11.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_md5.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_sha2.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_hmac.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rt_config.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_aes.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_arc4.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp.h \
    $(wildcard include/config/t.h) \
    $(wildcard include/config/p2p/auto/go/as/softap.h) \
    $(wildcard include/config/multi/channel.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/spectrum_def.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_autoChSel_cmm.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/wsc.h \
    $(wildcard include/config/req.h) \
    $(wildcard include/config/methods.h) \
    $(wildcard include/config/methods/usba.h) \
    $(wildcard include/config/methods/ethernet.h) \
    $(wildcard include/config/methods/label.h) \
    $(wildcard include/config/methods/display.h) \
    $(wildcard include/config/methods/ent.h) \
    $(wildcard include/config/methods/int.h) \
    $(wildcard include/config/methods/nfci.h) \
    $(wildcard include/config/methods/pbc.h) \
    $(wildcard include/config/methods/keypad.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mat.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/p2p_cmm.h \
    $(wildcard include/config/mode/disable/p2p/wpse.h) \
    $(wildcard include/config/mode/disable/wifi/direct/wpse.h) \
    $(wildcard include/config/mode/enable/p2p.h) \
    $(wildcard include/config/mode/p2p/scan.h) \
    $(wildcard include/config/mode/connect/p2p.h) \
    $(wildcard include/config/mode/activate/wifi/direct.h) \
    $(wildcard include/config/mode/activate/wpse.h) \
    $(wildcard include/config/mode/delete/active/p2p.h) \
    $(wildcard include/config/mode/delete/actived/wifi/direct.h) \
    $(wildcard include/config/mode/disconnect/p2p.h) \
    $(wildcard include/config/mode/disconnect/wifi/direct.h) \
    $(wildcard include/config/mode/delete/perst/p2p.h) \
    $(wildcard include/config/mode/delete/perst/wifi/direct.h) \
    $(wildcard include/config/mode/provision/this.h) \
    $(wildcard include/config/mode/set/go/wps.h) \
    $(wildcard include/config/mode/service/discovery.h) \
    $(wildcard include/config/mhd.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/wfa_p2p.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/drs_extr.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_M51.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rtmp_and.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/radar.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rt_led.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/frq_cal.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/wpa.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/chlist.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/spectrum.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_autoChSel.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rt_os_util.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/rt_os_net.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/chip/chip_id.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/uapsd.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_mbss.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_apcli.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_ids.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/ap_cfg.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_biginteger.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/crypt_dh.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/wsc_tlv.h \
    $(wildcard include/config/error.h) \
    $(wildcard include/config/fail.h) \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/p2p.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/p2pcli.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/sta_cfg.h \
  /home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/include/mac_ral/fce.h \

/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o: $(deps_/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o)

$(deps_/home/work/xiezx/git/hardware/wifi/mtk/drivers/mt7601/ap/ap_data.o):
