
###############################################################################
# USB
###############################################################################
#USB_MOD_NAME = btmtk_usb
#USB_CFILES := \
#	btmtk_usb_main.c \
#	btmtk_usb_dbgfs.c \
#	btmtk_usb_fifo.c
#$(USB_MOD_NAME)-objs := $(USB_CFILES:.c=.o)

###############################################################################
# SDIO
###############################################################################
#VPATH = /opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux
SDIO_MOD_NAME = btmtksdio
SDIO_CFILES := \
	btmtk_sdio.c btmtk_main.c
$(SDIO_MOD_NAME)-objs := $(SDIO_CFILES:.c=.o)

###############################################################################
# Common
###############################################################################
obj-m :=  $(SDIO_MOD_NAME).o

ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
KDIR ?=

sdio:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	#make -C $(KERNEL_SRC) M=$(PWD) $(SDIO_MOD_NAME).ko
	#make -C /Projects/ZTE/linux M=$(PWD) modules ARCH=arm64 CROSS_COMPILE=/opt/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean



