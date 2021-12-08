obj-$(CONFIG_BT_RTKBTUSB)	+= rtk_btusb.o

ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
KDIR ?=

rtk_btusb:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
	$(RM) Module.markers
	$(RM) modules.order
