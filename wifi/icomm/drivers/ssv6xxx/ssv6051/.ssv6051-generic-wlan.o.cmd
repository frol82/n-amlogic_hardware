cmd_/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o := /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-gcc -Wp,-MD,/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/.ssv6051-generic-wlan.o.d  -nostdinc -isystem /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/../lib/gcc/aarch64-linux-gnu/4.9.2/include -I/home/xaldey/n-amlogic/common/arch/arm64/include -Iarch/arm64/include/generated  -I/home/xaldey/n-amlogic/common/include -Iinclude -I/home/xaldey/n-amlogic/common/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/xaldey/n-amlogic/common/include/uapi -Iinclude/generated/uapi -include /home/xaldey/n-amlogic/common/include/linux/kconfig.h   -I/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051 -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror -Wno-error=cpp -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DCC_HAVE_ASM_GOTO -DCONFIG_SSV_SUPPORT_ANDROID -DCONFIG_FW_ALIGNMENT_CHECK -DCONFIG_PLATFORM_SDIO_OUTPUT_TIMING=3 -DCONFIG_PLATFORM_SDIO_BLOCK_SIZE=128 -DMULTI_THREAD_ENCRYPT -DCONFIG_SSV_OPENFILE_LOADFW -DCONFIG_SSV_MRX_EN3_CTRL -DCONFIG_TRIGGER_LOW_SDIO_LOADING -DCONFIG_SSV_RSSI -DAML_WIFI_MAC -Werror -g -DCONFIG_SSV_CABRIO_E -DCONFIG_SSV6200_CLI_ENABLE -DCONFIG_SSV6XXX_DEBUGFS -DCONFIG_SSV_TX_LOWTHRESHOLD -DRATE_CONTROL_REALTIME_UPDATA -DCONFIG_SSV6200_HAS_RX_WORKQUEUE -DUSE_THREAD_TX -DENABLE_AGGREGATE_IN_TIME -DENABLE_INCREMENTAL_AGGREGATION -DUSE_GENERIC_DECI_TBL -DUSE_LOCAL_CRYPTO -DUSE_LOCAL_WEP_CRYPTO -DUSE_LOCAL_CCMP_CRYPTO -DUSE_LOCAL_SMS4_CRYPTO -DCONFIG_SSV_WAPI -DFW_WSID_WATCH_LIST -DSSV6200_ECO -DHAS_CRYPTO_LOCK -DENABLE_TX_Q_FLOW_CONTROL   -I/home/xaldey/n-amlogic/common/../hardware/wifi/icomm/drivers/ssv6xxx/ssv6051   -I/home/xaldey/n-amlogic/common/../hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/include  -DMODULE    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ssv6051_generic_wlan)"  -D"KBUILD_MODNAME=KBUILD_STR(ssv6051)" -c -o /home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o /home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.c

source_/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o := /home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.c

deps_/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o := \
    $(wildcard include/config/ssv/support/aes/asm.h) \
  /home/xaldey/n-amlogic/common/include/linux/irq.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/generic/pending/irq.h) \
    $(wildcard include/config/hardirqs/sw/resend.h) \
  /home/xaldey/n-amlogic/common/include/linux/smp.h \
    $(wildcard include/config/debug/preempt.h) \
  /home/xaldey/n-amlogic/common/include/linux/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/errno.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/errno-base.h \
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
  /home/xaldey/n-amlogic/common/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/xaldey/n-amlogic/common/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/const.h \
  /home/xaldey/n-amlogic/common/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/xaldey/n-amlogic/common/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/lib/gcc/aarch64-linux-gnu/4.9.2/include/stdarg.h \
  /home/xaldey/n-amlogic/common/include/linux/linkage.h \
  /home/xaldey/n-amlogic/common/include/linux/stringify.h \
  /home/xaldey/n-amlogic/common/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
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
  /home/xaldey/n-amlogic/common/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/xaldey/n-amlogic/common/include/linux/bitmap.h \
  /home/xaldey/n-amlogic/common/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  arch/arm64/include/generated/asm/bug.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/xaldey/n-amlogic/common/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/cmpxchg.h \
  /home/xaldey/n-amlogic/common/include/linux/preempt.h \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/context/tracking.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/arm64/include/generated/asm/preempt.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/preempt.h \
  /home/xaldey/n-amlogic/common/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/smp.h \
  /home/xaldey/n-amlogic/common/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/xaldey/n-amlogic/common/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
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
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
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
  /home/xaldey/n-amlogic/common/include/asm-generic/atomic-long.h \
  /home/xaldey/n-amlogic/common/include/linux/gfp.h \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/cma.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/xaldey/n-amlogic/common/include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/current.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/wait.h \
  /home/xaldey/n-amlogic/common/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/xaldey/n-amlogic/common/include/linux/seqlock.h \
  /home/xaldey/n-amlogic/common/include/linux/nodemask.h \
    $(wildcard include/config/movable/node.h) \
  /home/xaldey/n-amlogic/common/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/xaldey/n-amlogic/common/include/linux/page-flags-layout.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/generated/bounds.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/sparsemem.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/page.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable-3level-types.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/pgtable-nopud.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/memory.h \
  arch/arm64/include/generated/asm/sizes.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/sizes.h \
  /home/xaldey/n-amlogic/common/include/linux/sizes.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/memory_model.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/getorder.h \
  /home/xaldey/n-amlogic/common/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/xaldey/n-amlogic/common/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  /home/xaldey/n-amlogic/common/include/linux/completion.h \
  /home/xaldey/n-amlogic/common/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/xaldey/n-amlogic/common/include/linux/rcutree.h \
  /home/xaldey/n-amlogic/common/include/linux/rbtree.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sysctl.h \
  /home/xaldey/n-amlogic/common/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/xaldey/n-amlogic/common/include/linux/notifier.h \
  /home/xaldey/n-amlogic/common/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/xaldey/n-amlogic/common/include/linux/rwsem-spinlock.h \
  /home/xaldey/n-amlogic/common/include/linux/srcu.h \
  /home/xaldey/n-amlogic/common/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/sysfs.h) \
  /home/xaldey/n-amlogic/common/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/xaldey/n-amlogic/common/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/xaldey/n-amlogic/common/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/xaldey/n-amlogic/common/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/div64.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/time.h \
  /home/xaldey/n-amlogic/common/include/linux/jiffies.h \
  /home/xaldey/n-amlogic/common/include/linux/timex.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/timex.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/param.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/param.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/param.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/timex.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/arch_timer.h \
  /home/xaldey/n-amlogic/common/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/xaldey/n-amlogic/common/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/io.h \
  /home/xaldey/n-amlogic/common/include/linux/blk_types.h \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/transparent/hugepage.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/proc-fns.h \
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
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
  /home/xaldey/n-amlogic/common/include/linux/auxvec.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/auxvec.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/auxvec.h \
  /home/xaldey/n-amlogic/common/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/xaldey/n-amlogic/common/include/linux/uprobes.h \
    $(wildcard include/config/uprobes.h) \
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
  /home/xaldey/n-amlogic/common/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/xaldey/n-amlogic/common/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/xaldey/n-amlogic/common/include/linux/pfn.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/percpu.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/percpu.h \
  /home/xaldey/n-amlogic/common/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/topology.h \
    $(wildcard include/config/disable/cpu/sched/domain/balance.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/topology.h \
  /home/xaldey/n-amlogic/common/include/linux/irqreturn.h \
  /home/xaldey/n-amlogic/common/include/linux/irqnr.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/irqnr.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/irq.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/irq.h \
  arch/arm64/include/generated/asm/irq_regs.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/irq_regs.h \
  /home/xaldey/n-amlogic/common/include/linux/irqdesc.h \
    $(wildcard include/config/irq/preflow/fasteoi.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/sparse/irq.h) \
  arch/arm64/include/generated/asm/hw_irq.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/hw_irq.h \
  include/generated/uapi/linux/version.h \
  /home/xaldey/n-amlogic/common/include/linux/module.h \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/xaldey/n-amlogic/common/include/linux/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/uapi/asm/stat.h \
  /home/xaldey/n-amlogic/common/include/uapi/asm-generic/stat.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/compat.h \
  /home/xaldey/n-amlogic/common/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz/common.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
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
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/stack/growsup.h) \
  /home/xaldey/n-amlogic/common/include/uapi/linux/sched.h \
  /home/xaldey/n-amlogic/common/include/linux/capability.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/capability.h \
  /home/xaldey/n-amlogic/common/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  arch/arm64/include/generated/asm/cputime.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/cputime_jiffies.h \
  /home/xaldey/n-amlogic/common/include/linux/sem.h \
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
  /home/xaldey/n-amlogic/common/include/linux/vmalloc.h \
  /home/xaldey/n-amlogic/common/include/linux/gpio.h \
    $(wildcard include/config/gpiolib.h) \
    $(wildcard include/config/arch/have/custom/gpio/h.h) \
  /home/xaldey/n-amlogic/common/include/asm-generic/gpio.h \
    $(wildcard include/config/pinctrl.h) \
  /home/xaldey/n-amlogic/common/include/linux/of.h \
    $(wildcard include/config/sparc.h) \
    $(wildcard include/config/of/dynamic.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/attach/node.h) \
    $(wildcard include/config/detach/node.h) \
    $(wildcard include/config/add/property.h) \
    $(wildcard include/config/remove/property.h) \
    $(wildcard include/config/update/property.h) \
    $(wildcard include/config/proc/devicetree.h) \
  /home/xaldey/n-amlogic/common/include/linux/mod_devicetable.h \
  /home/xaldey/n-amlogic/common/include/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/uapi/linux/uuid.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/pinctrl.h \
  /home/xaldey/n-amlogic/common/include/linux/radix-tree.h \
  /home/xaldey/n-amlogic/common/include/linux/seq_file.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/pinctrl-state.h \
  /home/xaldey/n-amlogic/common/include/linux/gpio/driver.h \
    $(wildcard include/config/of/gpio.h) \
  /home/xaldey/n-amlogic/common/include/linux/gpio/consumer.h \
    $(wildcard include/config/gpio/sysfs.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmc/host.h \
    $(wildcard include/config/mmc/clkgate.h) \
    $(wildcard include/config/mmc/debug.h) \
    $(wildcard include/config/regulator.h) \
    $(wildcard include/config/fail/mmc/request.h) \
  /home/xaldey/n-amlogic/common/include/linux/leds.h \
    $(wildcard include/config/leds/triggers.h) \
    $(wildcard include/config/leds/trigger/ide/disk.h) \
    $(wildcard include/config/leds/trigger/camera.h) \
    $(wildcard include/config/leds/trigger/cpu.h) \
  /home/xaldey/n-amlogic/common/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/xaldey/n-amlogic/common/include/linux/ioport.h \
  /home/xaldey/n-amlogic/common/include/linux/klist.h \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/devinfo.h \
    $(wildcard include/config/pm.h) \
  /home/xaldey/n-amlogic/common/include/linux/pinctrl/consumer.h \
  /home/xaldey/n-amlogic/common/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/xaldey/n-amlogic/common/include/linux/ratelimit.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  /home/xaldey/n-amlogic/common/include/linux/pm_wakeup.h \
  /home/xaldey/n-amlogic/common/include/linux/fault-inject.h \
    $(wildcard include/config/fault/injection/debug/fs.h) \
    $(wildcard include/config/failslab.h) \
  /home/xaldey/n-amlogic/common/include/linux/mmc/core.h \
  /home/xaldey/n-amlogic/common/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/xaldey/n-amlogic/common/include/linux/hardirq.h \
  /home/xaldey/n-amlogic/common/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/xaldey/n-amlogic/common/include/linux/vtime.h \
  /home/xaldey/n-amlogic/common/include/linux/context_tracking_state.h \
  /home/xaldey/n-amlogic/common/arch/arm64/include/asm/hardirq.h \
  /home/xaldey/n-amlogic/common/include/linux/irq_cpustat.h \
  /home/xaldey/n-amlogic/common/include/linux/mmc/card.h \
  /home/xaldey/n-amlogic/common/include/linux/mmc/pm.h \
  /home/xaldey/n-amlogic/common/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/xaldey/n-amlogic/common/include/asm-generic/delay.h \
  /home/xaldey/n-amlogic/common/include/linux/regulator/consumer.h \
  /home/xaldey/n-amlogic/common/include/linux/semaphore.h \
  /home/xaldey/n-amlogic/common/include/linux/cpufreq.h \
    $(wildcard include/config/cpu/freq.h) \
    $(wildcard include/config/cpu/freq/gov/performance.h) \
    $(wildcard include/config/cpu/freq/default/gov/performance.h) \
    $(wildcard include/config/cpu/freq/default/gov/powersave.h) \
    $(wildcard include/config/cpu/freq/default/gov/userspace.h) \
    $(wildcard include/config/cpu/freq/default/gov/ondemand.h) \
    $(wildcard include/config/cpu/freq/default/gov/conservative.h) \
    $(wildcard include/config/cpu/freq/default/gov/interactive.h) \
    $(wildcard include/config/cpu/freq/default/gov/hotplug.h) \
    $(wildcard include/config/cpu/freq/gov/hotplug.h) \
    $(wildcard include/config/amlogic/input/boost.h) \
  /home/xaldey/n-amlogic/common/include/linux/clk.h \
    $(wildcard include/config/common/clk.h) \
    $(wildcard include/config/have/clk/prepare.h) \
    $(wildcard include/config/have/clk.h) \
  /home/xaldey/n-amlogic/common/include/linux/amlogic/aml_thermal_hw.h \

/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o: $(deps_/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o)

$(deps_/home/xaldey/n-amlogic/hardware/wifi/icomm/drivers/ssv6xxx/ssv6051/ssv6051-generic-wlan.o):
