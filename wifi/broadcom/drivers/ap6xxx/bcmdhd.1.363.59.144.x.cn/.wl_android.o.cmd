cmd_/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/.wl_android.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -Wall -Wstrict-prototypes -Dlinux -DBCMDRIVER -DSDTEST -DBCMDONGLEHOST -DUNRELEASEDCHIP -DBCMDMA32 -DBCMFILEIMAGE -DDHDTHREAD -DDHD_DEBUG -DSHOW_EVENTS -DBCMDBG -DGET_OTP_MAC_ENABLE -DWIFI_ACT_FRAME -DARP_OFFLOAD_SUPPORT -DSUPPORT_PM2_ONLY -DKEEP_ALIVE -DPKT_FILTER_SUPPORT -DPNO_SUPPORT -DDHDTCPACK_SUPPRESS -DDHD_DONOT_FORWARD_BCMEVENT_AS_NETWORK_PKT -DRXFRAME_THREAD -DTSQ_MULTIPLIER -DBCMSDIOH_TXGLOM_EXT -DWL_EXT_IAPSTA -DENABLE_INSMOD_NO_FW_LOAD   -I/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn   -I/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include -DBCMSDIO -DMMC_SDIO_ABORT -DBCMLXSDMMC -DUSE_SDIOFIFO_IOVAR -DBDC -DDHD_USE_IDLECOUNT -DBCMSDIOH_TXGLOM -DCUSTOM_SDIO_F2_BLKSIZE=256 -DDCUSTOM_DPC_PRIO_SETTING=-1 -DCUSTOM_RXF_CPUCORE=2 -DDHD_FIRSTREAD=256 -DMAX_HDR_READ=256 -DOOB_INTR_ONLY -DCUSTOMER_OOB -DHW_OOB -DPROP_TXSTATUS -DPROP_TXSTATUS_VSDB -DCUSTOMER_HW -DDHD_OF_SUPPORT -DCUSTOMER_HW_AMLOGIC -DCONFIG_DHD_USE_STATIC_BUF -DSTATIC_WL_PRIV_STRUCT -DENHANCED_STATIC_BUF -DSOFTAP -DWL_WIRELESS_EXT -DUSE_IW -DWL_ESCAN -DWL_CFG80211 -DWLP2P -DWL_CFG80211_STA_EVENT -DWL_ENABLE_P2P_IF -DWL_IFACE_COMB_NUM_CHANNELS -DCUSTOM_ROAM_TRIGGER_SETTING=-65 -DCUSTOM_ROAM_DELTA_SETTING=15 -DCUSTOM_KEEP_ALIVE_SETTING=28000 -DCUSTOM_PNO_EVENT_LOCK_xTIME=7 -DWL_SUPPORT_AUTO_CHANNEL -DWL_SUPPORT_BACKPORTED_KPATCHES -DESCAN_RESULT_PATCH -DVSDB -DWL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST -DWLTDLS -DMIRACAST_AMPDU_SIZE=8 -DMULTIPLE_SUPPLICANT  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(wl_android)"  -D"KBUILD_MODNAME=KBUILD_STR(dhd)" -c -o /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.c

source_/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o := /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.c

deps_/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o := \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/has/earlysuspend.h) \
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
  /home/xaldey/n-amlogic/common/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/const.h \
  /home/xaldey/n-amlogic/common/include/linux/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/stat.h \
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
  /home/xaldey/n-amlogic/common/include/net/netlink.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wldev_common.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/wlioctl.h \
    $(wildcard include/config/params/version.h) \
    $(wildcard include/config/usbrndis/retail.h) \
    $(wildcard include/config/item.h) \
    $(wildcard include/config/version.h) \
    $(wildcard include/config/ver/0.h) \
    $(wildcard include/config/ver/1.h) \
    $(wildcard include/config/cur/ver.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/typedefs.h \
  include/generated/uapi/linux/version.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmdefs.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/ethernet.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/packed_section_start.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/packed_section_end.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/bcmip.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/bcmeth.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/bcmevent.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/802.11.h \
    $(wildcard include/config/policy/violn.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/wpa.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/802.1d.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/bcmwifi_channels.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/bcmwifi_rates.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/devctrl_if/wlioctl_defs.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/bcmipv6.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcm_mpool_pub.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmcdc.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmutils.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/osl.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/osl_decl.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/linux_osl.h \
    $(wildcard include/config/arch/msm8996.h) \
    $(wildcard include/config/soc/exynos8890.h) \
    $(wildcard include/config/mmc/msm7x00a.h) \
    $(wildcard include/config/dhd/use/static/buf.h) \
    $(wildcard include/config/nf/conntrack/mark.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmsdh.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/linuxver.h \
    $(wildcard include/config/net/radio.h) \
    $(wildcard include/config/rfkill.h) \
  /home/xaldey/n-amlogic/common/include/linux/pci.h \
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
  /home/xaldey/n-amlogic/common/include/linux/mod_devicetable.h \
  /home/xaldey/n-amlogic/common/include/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/linux/io.h \
  /home/xaldey/n-amlogic/common/include/linux/irqreturn.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/pci.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/pci_regs.h \
  /home/xaldey/n-amlogic/common/include/linux/pci_ids.h \
  arch/arm64/include/generated/asm/pci.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/pci.h \
  /home/xaldey/n-amlogic/common/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/xaldey/n-amlogic/common/include/linux/kthread.h \
  /home/xaldey/n-amlogic/common/include/linux/sched/rt.h \
  /home/xaldey/n-amlogic/common/include/net/lib80211.h \
  /home/xaldey/n-amlogic/common/include/linux/ieee80211.h \
    $(wildcard include/config/timeout.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/hnd_pktq.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/osl_ext.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/hnd_pktpool.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd_dbg.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/dhdioctl.h \
    $(wildcard include/config/val.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dngl_stats.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd.h \
    $(wildcard include/config/has/wakelock.h) \
    $(wildcard include/config/bcmdhd/vendor/ext.h) \
    $(wildcard include/config/android.h) \
    $(wildcard include/config/bcmdhd/clm/path.h) \
    $(wildcard include/config/mach/universal5433.h) \
    $(wildcard include/config/mach/universal7420.h) \
  /home/xaldey/n-amlogic/common/include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  arch/arm64/include/generated/asm/unaligned.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/unaligned.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/le_struct.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/packed_struct.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/be_byteshift.h \
  /home/xaldey/n-amlogic/common/include/linux/unaligned/generic.h \
  /home/xaldey/n-amlogic/common/include/linux/wakelock.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd_buzzz.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/wlfc_proto.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd_config.h \
    $(wildcard include/config/path/auto/select.h) \
    $(wildcard include/config/country/list/size.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmdevs.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd_pno.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/bcmsdbus.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_cfg80211.h \
  /home/xaldey/n-amlogic/common/include/linux/wireless.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/wireless.h \
  /home/xaldey/n-amlogic/common/include/net/cfg80211.h \
    $(wildcard include/config/nl80211/testmode.h) \
    $(wildcard include/config/cfg80211/wext.h) \
  /home/xaldey/n-amlogic/common/include/linux/debugfs.h \
    $(wildcard include/config/debug/fs.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/nl80211.h \
  /home/xaldey/n-amlogic/common/include/net/regulatory.h \
  /home/xaldey/n-amlogic/common/include/linux/rfkill.h \
    $(wildcard include/config/rfkill/leds.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/rfkill.h \
  /home/xaldey/n-amlogic/common/include/linux/leds.h \
    $(wildcard include/config/leds/triggers.h) \
    $(wildcard include/config/leds/trigger/ide/disk.h) \
    $(wildcard include/config/leds/trigger/camera.h) \
    $(wildcard include/config/leds/trigger/cpu.h) \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_cfgp2p.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/include/proto/p2p.h \
  /home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/dhd_ip.h \

/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/broadcom/drivers/ap6xxx/bcmdhd.1.363.59.144.x.cn/wl_android.o):
