#define LOG_NDEBUG 0
#define LOG_TAG "MULTI_WIFI"

#ifndef SYSFS_PATH_MAX
#define SYSFS_PATH_MAX 256
#endif

#include<unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <asm/ioctl.h>

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <sys/types.h>

#include "hardware_legacy/wifi.h"
#include "libwpa_client/wpa_ctrl.h"

#include "cutils/log.h"
#include "cutils/memory.h"
#include "cutils/properties.h"
#include "cutils/misc.h"
#include "netutils/ifc.h"
#include "private/android_filesystem_config.h"
#ifdef HAVE_LIBC_SYSTEM_PROPERTIES
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#endif
#include "../../amlogic/wifi/dongle_info/dongle_info.h"
#include "../../../external/libusb/libusb/libusb.h"
static const char SYSFS_CLASS_NET[]     = "/sys/class/net";
static const char SYS_MOD_NAME_DIR[]    = "device/driver/module";
static const char DRIVER_PROP_NAME[]    = "wlan.driver.status";



static const char BS8723_MODULE_NAME[]  = "8723bs";
static const char BS8723_MODULE_TAG[]   = "8723bs";
static const char BS8723_MODULE_PATH[]  = "/system/lib/8723bs.ko";
static const char BS8723_MODULE_ARG[]   = "ifname=wlan0 if2name=p2p0";

static const char BS8189_MODULE_NAME[]  = "8189es";
static const char BS8189_MODULE_TAG[]   = "8189es";
static const char BS8189_MODULE_PATH[]  = "/system/lib/8189es.ko";
static const char BS8189_MODULE_ARG[]   = "ifname=wlan0 if2name=p2p0";

static const char CFG80211_MODULE_TAG[]   = "cfg80211";
static const char CFG80211_9377_MODULE_PATH[]  = "/system/lib/cfg80211_9377.ko";
static const char CFG80211_6174_MODULE_PATH[]  = "/system/lib/cfg80211_6174.ko";
static const char CFG80211_MODULE_PATH[]  = "/system/lib/cfg80211.ko";
static const char CFG80211_MODULE_ARG[]   = "";
static const char COMPAT_9377_MODULE_PATH[]  = "/system/lib/compat_9377.ko";
static const char COMPAT_6174_MODULE_PATH[]  = "/system/lib/compat_6174.ko";
static const char COMPAT_MODULE_ARG[]   = "";

static const char BS8822_MODULE_NAME[]  = "8822bs";
static const char BS8822_MODULE_TAG[]   = "8822bs";
static const char BS8822_MODULE_PATH[]  = "/system/lib/8822bs.ko";
static const char BS8822_MODULE_ARG[]   = "ifname=wlan0 if2name=p2p0";
#define USB_POWER_UP    _IO('m',1)
#define USB_POWER_DOWN  _IO('m',2)
#define SDIO_POWER_UP    _IO('m',3)
#define SDIO_POWER_DOWN  _IO('m',4)

static const char FS8189_MODULE_NAME[]  = "8189fs";
static const char FS8189_MODULE_TAG[]   = "8189fs";
static const char FS8189_MODULE_PATH[]  = "/system/lib/8189fs.ko";
static const char FS8189_MODULE_ARG[]   = "ifname=wlan0 if2name=p2p0";

static const char BCM40183_MODULE_NAME[]  = "dhd";
static const char BCM40183_MODULE_TAG[]   = "dhd";
static const char BCM40183_MODULE_PATH[]  = "/system/lib/dhd.ko";
static const char BCM40183_MODULE_ARG[]   ="firmware_path=/etc/wifi/AP6330/Wi-Fi/fw_bcm40183b2.bin nvram_path=/etc/wifi/AP6330/Wi-Fi/nvram_ap6330.txt";
static const char BCM6335_MODULE_ARG[]   ="firmware_path=/etc/wifi/6335/fw_bcm4339a0_ag.bin nvram_path=/etc/wifi/6335/nvram.txt";
static const char BCM6210_MODULE_ARG[]   ="firmware_path=/etc/wifi/40181/fw_bcm40181a2.bin nvram_path=/etc/wifi/40181/nvram.txt";
static const char BCM6234_MODULE_ARG[]   ="firmware_path=/etc/wifi/6234/fw_bcm43341b0_ag.bin nvram_path=/etc/wifi/6234/nvram.txt";
static const char BCM6354_MODULE_ARG[]   ="firmware_path=/etc/wifi/4354/fw_bcm4354a1_ag.bin nvram_path=/etc/wifi/4354/nvram_ap6354.txt";
static const char BCM62x2_MODULE_ARG[]   ="firmware_path=/etc/wifi/62x2/fw_bcm43241b4_ag.bin nvram_path=/etc/wifi/62x2/nvram.txt";
static const char BCM6255_MODULE_ARG[]   ="firmware_path=/etc/wifi/6255/fw_bcm43455c0_ag.bin nvram_path=/etc/wifi/6255/nvram.txt";
static const char BCM6212_MODULE_ARG[]   ="firmware_path=/etc/wifi/6212/fw_bcm43438a0.bin nvram_path=/etc/wifi/6212/nvram.txt";
static const char BCM6356_MODULE_ARG[]   ="firmware_path=/etc/wifi/4356/fw_bcm4356a2_ag.bin nvram_path=/etc/wifi/4356/nvram_ap6356.txt";
static const char BCM4358_MODULE_ARG[]   ="firmware_path=/etc/wifi/4358/fw_bcm4358_ag.bin nvram_path=/etc/wifi/4358/nvram_4358.txt";
static const char BCM6359_MODULE_ARG[]   ="firmware_path=/etc/wifi/6359sa/fw_bcm4359c0_ag.bin nvram_path=/etc/wifi/6359sa/nvram_ap6359sa.txt";

int verbose1 = 0;
extern struct usb_bus *usb_busses;
int bcm6335_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6335_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6335 driver! \n");
    return 0;
}

int bcm6335_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6335 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6335 driver ! \n");
    return 0;
}

int search_bcm6335(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4335")) {
        write_no("bcm6335");
        ALOGE("Found 6335 !!!\n");
        return 1;
    }
    return 0;
}


int bcm40183_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM40183_MODULE_ARG) !=0) {
    ALOGE("Failed to insmod dhd ! \n");
    return -1;
    }
    ALOGD("Success to insmod bcm40183 driver! \n");
    return 0;
}

int bcm40183_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
    ALOGE("Failed to rmmod bcm40183 driver ! \n");
    return -1;
    }
    ALOGD("Success to rmmod bcm40183 driver ! \n");
    return 0;
}

int search_bcm40183(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp) {
        ALOGD("not found  sdio file sdio:0001:1/device\n");
        return -1;
    }
    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4330")) {
        write_no("bcm6330");
        ALOGE("Found 40183 !!!\n");
        return 1;
    }
    return 0;
}

int bcm6210_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6210_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6210 driver! \n");
    return 0;
}

int bcm6210_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6210 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6210 driver ! \n");
    return 0;
}

int search_bcm6210(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp) {
        return 2;
    }
    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"a962")) {
        write_no("bcm6210");
        ALOGE("Found 6210 !!!\n");
        return 1;
    }
    return 0;
}


int bcm6234_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6234_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6234 driver! \n");
    return 0;
}

int bcm6234_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6234 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6234 driver ! \n");
    return 0;
}

int search_bcm6234(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp) {
        return 2;
    }
    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"a94d")) {
        write_no("bcm6234");
        ALOGE("Found 6234 !!!\n");
        return 1;
    }
    return 0;
}

int bcm6354_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6354_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6354 driver! \n");
    return 0;
}

int bcm6354_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6354 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6354 driver ! \n");
    return 0;
}

int search_bcm6354(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4354")) {
        write_no("bcm4354");
        ALOGE("Found 6354 !!!\n");
        return 1;
    }
    return 0;
}


int bcm4358_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM4358_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm4358 driver! \n");
    return 0;
}

int bcm4358_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm4358 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm4358 driver ! \n");
    return 0;
}

int search_bcm4358(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"aa31")) {
        write_no("bcm4358");
        ALOGE("Found 4358 !!!\n");
        return 1;
    }
    return 0;
}

int bcm6359_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6359_MODULE_ARG) !=0) {
       ALOGE("Failed to insmod dhd ! \n");
       return -1;
    }
    ALOGD("Success to insmod bcm6359 driver! \n");
    return 0;
}

int bcm6359_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6359 driver ! \n");
    }
    ALOGD("Success to rmmod bcm6359 driver ! \n");
    return 0;
}

int search_bcm6359(unsigned int x,unsigned int y)
{
	int fd,len;
    char sdio_buf[128];

    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4359")) {
        write_no("bcm6359");
        ALOGE("Found 6359 !!!\n");
        property_set("persist.sys.wifi.model", "6359");
        return 1;
    }
    return 0;
}

int bcm6356_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6356_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6356 driver! \n");
    return 0;
}

int bcm6356_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6356 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6356 driver ! \n");
    return 0;
}

int search_bcm6356(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4356")) {
        write_no("bcm6356");
        ALOGE("Found 6356 !!!\n");
        property_set("persist.sys.wifi.model", "6356");
        return 1;
    }
    return 0;
}


int bcm62x2_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM62x2_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm62x2 driver! \n");
    return 0;
}

int bcm62x2_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm62x2 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm62x2 driver ! \n");
    return 0;
}

int search_bcm62x2(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"4324")) {
        write_no("bcm62x2");
        ALOGE("Found 62x2 !!!\n");
        return 1;
    }
    return 0;
}


int bcm6255_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6255_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6255 driver! \n");
    return 0;
}

int bcm6255_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6255 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6255 driver ! \n");
    return 0;
}

int search_bcm6255(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;


    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"a9bf")) {
        write_no("bcm6255");
        ALOGE("Found 6255 !!!\n");
        property_set("persist.sys.wifi.model", "6255");
        return 1;
    }
    return 0;
}


int bcm6212_load_driver()
{
    if (wifi_insmod(BCM40183_MODULE_PATH, BCM6212_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod dhd ! \n");
        return -1;
    }
    ALOGD("Success to insmod bcm6212 driver! \n");
    return 0;
}

int bcm6212_unload_driver()
{
    if (wifi_rmmod(BCM40183_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bcm6212 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bcm6212 driver ! \n");
    return 0;
}

int search_bcm6212(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"a9a6")) {
        write_no("bcm6212");
        ALOGE("Found 6212 !!!\n");
        return 1;
    }
    return 0;
}


int bs8723_load_driver()
{
    if (wifi_insmod(BS8723_MODULE_PATH, BS8723_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod 8723 ! \n");
        return -1;
    }
    ALOGD("Success to insmod bs8723 driver! \n");
    return 0;
}

int bs8723_unload_driver()
{
    if (wifi_rmmod(BS8723_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bs8723 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bs8723 driver ! \n");
    return 0;
}

int search_bs8723(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"b723")) {
        write_no("rtl8723bs");
        ALOGE("Found 8723bs !!!\n");
        return 1;
    }
    return 0;
}


int es8189_load_driver()
{
    if (wifi_insmod(BS8189_MODULE_PATH, BS8189_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod 8189 ! \n");
        return -1;
    }
    ALOGD("Success to insmod bs8189 driver! \n");
    return 0;
}

int es8189_unload_driver()
{
    if (wifi_rmmod(BS8189_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bs8189 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bs8189 driver ! \n");
    return 0;
}

int search_es8189(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"8179")) {
        write_no("rtl8189es");
        ALOGE("Found 8189bs !!!\n");
        return 1;
    }
    return 0;
}



int bs8822_load_driver()
{
    if (wifi_insmod(BS8822_MODULE_PATH, BS8822_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod 8822bs ! \n");
        return -1;
    }
    ALOGD("Success to insmod bs8822 driver! \n");
    return 0;
}

int bs8822_unload_driver()
{
    if (wifi_rmmod(BS8822_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bs8822 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bs8822 driver ! \n");
    return 0;
}

int search_bs8822(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"b822")) {
        write_no("rtl8822bs");
        ALOGE("Found 8822bs !!!\n");
        return 1;
    }
    return 0;
}

int fs8189_load_driver()
{
    if (wifi_insmod(FS8189_MODULE_PATH, FS8189_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod 8189 ! \n");
        return -1;
    }
    ALOGD("Success to insmod bs8189 driver! \n");
    return 0;
}

int fs8189_unload_driver()
{
    if (wifi_rmmod(FS8189_MODULE_NAME) != 0) {
        ALOGE("Failed to rmmod bs8189 driver ! \n");
        return -1;
    }
    ALOGD("Success to rmmod bs8189 driver ! \n");
    return 0;
}

int search_fs8189(unsigned int x,unsigned int y)
{
    int fd,len;
    char sdio_buf[128];
    FILE *fp = fopen(file_name,"r");
    if (!fp)
        return -1;

    memset(sdio_buf,0,sizeof(sdio_buf));
    if (fread(sdio_buf, 1,128,fp) < 1) {
        ALOGE("Read error for\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    if (strstr(sdio_buf,"f179")) {
        write_no("rtl8189ftv");
        ALOGE("Found 8189fs !!!\n");
        return 1;
    }
    return 0;
}

static int cur_vid = 0;
static int cur_pid = 0;
typedef struct load_info{
	int (*load)();
	int (*unload)();
	int (*search)(unsigned int,unsigned int);
}dongle_info;

#define SDIO_WIFI_COUNT 2
static const dongle_info dongle_registerd[]={\
	{bcm40183_load_driver,bcm40183_unload_driver,search_bcm40183},\
	{bcm6210_load_driver,bcm6210_unload_driver,search_bcm6210},\
	{bcm6335_load_driver,bcm6335_unload_driver,search_bcm6335},\
	{bcm6234_load_driver,bcm6234_unload_driver,search_bcm6234},\
	{bcm6354_load_driver,bcm6354_unload_driver,search_bcm6354},\
	{bcm62x2_load_driver,bcm62x2_unload_driver,search_bcm62x2},\
	{bcm6255_load_driver,bcm6255_unload_driver,search_bcm6255},\
	{bcm6212_load_driver,bcm6212_unload_driver,search_bcm6212},\
	{bcm6356_load_driver,bcm6356_unload_driver,search_bcm6356},\
	{bcm4358_load_driver,bcm4358_unload_driver,search_bcm4358},\
	{bcm6359_load_driver,bcm6359_unload_driver,search_bcm6359},\
	{qca9377_load_driver,qca9377_unload_driver,search_qca9377},\
	{qca6174_load_driver,qca6174_unload_driver,search_qca6174},\
	{bs8723_load_driver,bs8723_unload_driver,search_bs8723},\
	{es8189_load_driver,es8189_unload_driver,search_es8189},\
	{bs8822_load_driver,bs8822_unload_driver,search_bs8822},\
	{fs8189_load_driver,fs8189_unload_driver,search_fs8189},\
	{es8192_load_driver,es8192_unload_driver,search_es8192},\
	{eu8188_load_driver,eu8188_unload_driver,search_8188eu},\
	{bu8723_load_driver,bu8723_unload_driver,search_8723bu},\
	{du8723_load_driver,du8723_unload_driver,search_8723du},\
	{ds8723_load_driver,ds8723_unload_driver,search_ds8723},\
	{au8821_load_driver,au8821_unload_driver,search_8821au},\
	{au8812_load_driver,au8812_unload_driver,search_8812au},\
	{ftv8188_load_driver,ftv8188_unload_driver,search_8188ftv},\
	{cu8192_load_driver,cu8192_unload_driver,search_cu},\
	{du8192_load_driver,du8192_unload_driver,search_du},\
	{eu8192_load_driver,eu8192_unload_driver,search_8192eu},\
	{mt7601_load_driver,mt7601_unload_driver,search_mt7601},\
	{mt7662_load_driver,mt7662_unload_driver,search_mt7662},\
	{mt7668_load_driver,mt7668_unload_driver,search_mt7668},\
	{mt7603_load_driver,mt7603_unload_driver,search_mt7603}, \
	{bu8822_load_driver,bu8822_unload_driver,search_8822bu}, \
	{bcm43569_load_driver,bcm43569_unload_driver,search_bcm43569}};

static int load_dongle_index = -1;

static int indent_usb_table = 0;
static struct usb_detail_table usb_table[10] = {};
static void print_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0;

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }
        usb_table[indent_usb_table].vid = desc.idVendor;
        usb_table[indent_usb_table].pid = desc.idProduct;
        indent_usb_table++;
    }
}
static int get_driver_info()
{
    DIR  *netdir;
    struct dirent *de;
    char path[SYSFS_PATH_MAX];
    char link[SYSFS_PATH_MAX];
    int ret = 0;
    if ((netdir = opendir(SYSFS_CLASS_NET)) != NULL) {
        while ((de = readdir(netdir)) != NULL) {
            struct dirent **namelist = NULL;
            int cnt;
            if ((!strcmp(de->d_name,".")) || (!strcmp(de->d_name,"..")))
                continue;
            snprintf(path, SYSFS_PATH_MAX, "%s/%s/wireless", SYSFS_CLASS_NET, de->d_name);
            if (access(path, F_OK)) {
                snprintf(path, SYSFS_PATH_MAX, "%s/%s/phy80211", SYSFS_CLASS_NET, de->d_name);
                if (access(path, F_OK))
                    continue;
            } else
                ret = 1;

        }
    }
    closedir(netdir);
    return ret;
}

int is_driver_loaded(const char *module_tag)
{
    FILE *proc;
    char line[sizeof(module_tag)+10];

    /*
     * If the property says the driver is loaded, check to
     * make sure that the property setting isn't just left
     * over from a previous manual shutdown or a runtime
     * crash.
     */
    if ((proc = fopen("/proc/modules", "r")) == NULL) {
        ALOGW("Could not open %s", strerror(errno));
        return 0;
    }
    while ((fgets(line, sizeof(line), proc)) != NULL) {
        if (strncmp(line, module_tag, strlen(module_tag)) == 0) {
            fclose(proc);
            return 1;
        }
    }
    fclose(proc);
    return 0;
}

int qca_cfg80211_load_driver()
{
    if (strstr(get_wifi_vendor_name(), "9377")) {

        if (wifi_insmod(COMPAT_9377_MODULE_PATH, COMPAT_MODULE_ARG) !=0) {
            ALOGE("Failed to insmod qca compat ko ! \n");
            return -1;
        }
        if (wifi_insmod(CFG80211_9377_MODULE_PATH, CFG80211_MODULE_ARG) !=0) {
            ALOGE("Failed to insmod qca cfg80211 ! \n");
            return -1;
        }
        ALOGD("Success to insmod 9377 cfg80211 driver! \n");
    } else {
        if (wifi_insmod(COMPAT_6174_MODULE_PATH, COMPAT_MODULE_ARG) !=0) {
            ALOGE("Failed to insmod qca compat ko ! \n");
            return -1;
        }
        if (wifi_insmod(CFG80211_6174_MODULE_PATH, CFG80211_MODULE_ARG) !=0) {
            ALOGE("Failed to insmod qca cfg80211 ! \n");
            return -1;
        }
        ALOGD("Success to insmod 6174 cfg80211 driver! \n");
    }
    return 0;
}

int cfg80211_load_driver()
{
    if (wifi_insmod(CFG80211_MODULE_PATH, CFG80211_MODULE_ARG) !=0) {
        ALOGE("Failed to insmod  cfg80211 ! \n");
        return -1;
    }
    ALOGD("Success to insmod cfg80211 driver! \n");
    return 0;
}
int usb_wifi_load_driver()
{
    int unsigned i,j;
    int unsigned usb_vidpid_count=0;
    int count = 100;
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init(NULL);
    if (r < 0)
        return r;

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0)
        return (int) cnt;

    print_devs(devs);
    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);
    usb_vidpid_count = indent_usb_table;
    indent_usb_table = 0;
    load_dongle_index = -1;
    for (i = 0;i < usb_vidpid_count; i ++) {
        for (j = 0;j < sizeof(dongle_registerd)/sizeof(dongle_info);j ++) {
            if (dongle_registerd[j].search(usb_table[i].vid,usb_table[i].pid) == 1) {
                if (!is_driver_loaded(CFG80211_MODULE_TAG)) {
                if (strncmp(get_wifi_vendor_name(), "qca", 3) == 0)
                    qca_cfg80211_load_driver();
                else
                    cfg80211_load_driver();
                }

                cur_vid = usb_table[i].vid;
                cur_pid = usb_table[i].pid;
                load_dongle_index = j;
                ALOGD("The matched dongle no. is %d\n",j);
                if (dongle_registerd[j].load() != 0) {
                    ALOGD("Load Wi-Fi driver error !!!\n");
                    return 1;
                }
                return 0;
            }
        }
    }

    if (load_dongle_index == -1) {
        ALOGD("Not find matched usb wifi dongle!!!\n");
        return -1;
    }
    return 0;
}

int sdio_wifi_load_driver()
{
    int i;
    int ret =0;
    load_dongle_index = -1;
    for (i=0;i < sizeof(dongle_registerd)/sizeof(dongle_info); i++) {
        ret=dongle_registerd[i].search(0,0);
        if (ret ==1) {
            load_dongle_index = i;
            if (!is_driver_loaded(CFG80211_MODULE_TAG)) {
                if (strncmp(get_wifi_vendor_name(), "qca", 3) == 0)
                    qca_cfg80211_load_driver();
                else
                    cfg80211_load_driver();
            }
            if (is_driver_loaded(BCM40183_MODULE_TAG) && strncmp(get_wifi_vendor_name(), "bcm", 3) == 0) {
                wifi_rmmod(BCM40183_MODULE_NAME);
                ALOGE("dhd driver is load ,unload first\n");
                usleep(2000000);
            }
            ALOGD("The matched dongle no. is %d\n", i);
            if (dongle_registerd[i].load() != 0) {
                ALOGD("Load Wi-Fi driver error !!!\n");
                return -1;
            }
            return 0;
        } else if(ret == -1) {
            ALOGD("NO sdio device!!!\n");
            return -1;
        } else if (ret ==0){
            continue;
        }
    }
    if (load_dongle_index == -1) {
        ALOGD("Didn't find matched sdio wifi dongle!!!\n");
        return -1;
    }
    return 0;
}
const char *get_wifi_vendor_name()
{
    char wifi_type[10];
    read_no(wifi_type);
    if (strstr(wifi_type, "bcm6330") != NULL) {
        return "bcm6330";
    } else if(strstr(wifi_type, "bcm6210") != NULL) {
        return "bcm6210";
    } else if(strstr(wifi_type, "bcm6335") != NULL) {
        return "bcm6335";
    } else if(strstr(wifi_type, "bcm6234") != NULL) {
        return "bcm6234";
    } else if(strstr(wifi_type, "bcm4354") != NULL) {
        return "bcm4354";
    } else if(strstr(wifi_type, "bcm62x2") != NULL) {
        return "bcm62x2";
    } else if(strstr(wifi_type, "bcm6255") != NULL) {
        return "bcm6255";
    } else if(strstr(wifi_type, "bcm6212") != NULL) {
        return "bcm6212";
    } else if(strstr(wifi_type, "bcm6356") != NULL) {
        return "bcm6356";
    } else if(strstr(wifi_type, "bcm4358") != NULL) {
        return "bcm4358";
    } else if (strstr(wifi_type, "bcm6359") != NULL) {
        return "bcm6359";
    } else if(strstr(wifi_type, "qca9377") != NULL) {
        return "qca9377";
    } else if(strstr(wifi_type, "qca6174") != NULL) {
        return "qca6174";
    } else if(strstr(wifi_type, "rtl8723bs") != NULL) {
        return "rtl8723bs";
    } else if(strstr(wifi_type, "rtl8189es") != NULL) {
        return "rtl8189es";
    } else if(strstr(wifi_type, "rtl8822bs") != NULL) {
        return "rtl8822bs";
    } else if(strstr(wifi_type, "rtl8822bu") != NULL) {
        return "rtl8822bu";
    } else if(strstr(wifi_type, "rtl8189ftv") != NULL) {
        return "rtl8189ftv";
    } else if(strstr(wifi_type, "rtl8192es") != NULL) {
        return "rtl8192es";
    } else if(strstr(wifi_type, "rtl8188eu") != NULL) {
        return "rtl8188eu";
    } else if(strstr(wifi_type, "rtl8723bu") != NULL) {
        return "rtl8723bu";
    } else if(strstr(wifi_type, "rtl8723du") != NULL) {
        return "rtl8723du";
    } else if(strstr(wifi_type, "rtl8723ds") != NULL) {
        return "rtl8723ds";
    } else if(strstr(wifi_type, "rtl8821au") != NULL) {
        return "rtl8821au";
    } else if(strstr(wifi_type, "rtl8812au") != NULL) {
        return "rtl8812au";
    } else if(strstr(wifi_type, "rtl8188ftv") != NULL) {
        return "rtl8188ftv";
    } else if(strstr(wifi_type, "rtl8192cu") != NULL) {
        return "rtl8192cu";
    } else if(strstr(wifi_type, "rtl8192du") != NULL) {
        return "rtl8192du";
    } else if(strstr(wifi_type, "rtl8192eu") != NULL) {
        return "rtl8192eu";
    } else if(strstr(wifi_type, "mtk7601") != NULL) {
        return "mtk7601";
    } else if(strstr(wifi_type, "mtk7662") != NULL) {
        return "mtk7662";
    } else if(strstr(wifi_type, "mtk7668") != NULL) {
        return "mtk7668";
    } else if(strstr(wifi_type, "mtk7603") != NULL) {
        return "mtk7603";
    } else if(strstr(wifi_type, "bcm43569") != NULL) {
        return "bcm43569";
    } else {
        ALOGE("can not found manch wifi\n");
        return NULL;
    }
}

int multi_wifi_load_driver()
{
    int wait_time=0,ret;
    set_wifi_power(SDIO_POWER_UP);
    char dev_type[10] = {'\0'};
    get_wifi_dev_type(dev_type);
    sprintf(file_name, "/sys/bus/mmc/devices/%s:0001/%s:0001:1/device", dev_type, dev_type);
    ALOGD("sdio device file path = %s", file_name);
    if (load_dongle_index >= 0) {
        if (!is_driver_loaded(CFG80211_MODULE_TAG)) {
            if (strncmp(get_wifi_vendor_name(), "qca", 3) == 0)
                qca_cfg80211_load_driver();
            else
                cfg80211_load_driver();
        }
        ALOGD("The matched load_dongle_index. is %d\n", load_dongle_index);
        if (dongle_registerd[load_dongle_index].load() != 0) {
                ALOGD("Load Wi-Fi driver error !!!\n");
                return -1;
        }
        ALOGD("wifi driver load ok\n");
        return 0;
    }
    if (!sdio_wifi_load_driver()) {
        return 0;
    }
    do {
        ret = usb_wifi_load_driver();
        if (!ret)
            return 0;
        else if (ret> 0)
            break;
        else {
        wait_time++;
        usleep(50000);
        ALOGD("wait usb ok\n");
        }
    }while(wait_time<300);

    ALOGE("Wifi load fail\n");
    return -1;
}

int multi_wifi_unload_driver()
{
    usleep(200000);
    if (load_dongle_index >= 0) {
        ALOGE("Start to unload driver ...\n");
        if (strncmp(get_wifi_vendor_name(), "mtk", 3) == 0) {
            ifc_init();
            ifc_down("wlan0");
        }
        if (dongle_registerd[load_dongle_index].unload() != 0) {
            ALOGE("Failed to unload driver !\n");
            return -1;
        }
        ALOGE("Unload driver OK !\n");
    } else
        return -1;

    return 0;
}
