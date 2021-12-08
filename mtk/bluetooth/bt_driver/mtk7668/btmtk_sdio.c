/**
 * Mediatek BT-over-SDIO driver: SDIO interface related functions.
 * Copyright (C) 2009, Mediatek International Ltd.
 *
 * This software file (the "File") is distributed by Mediatek International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modify this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *
 * THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/
#include <linux/version.h>
#include <linux/firmware.h>
#include <linux/slab.h>

#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/module.h>

#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>

#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/sdio_func.h>
#include <linux/cdev.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/device.h>


#include "btmtk_drv.h"
#include "btmtk_sdio.h"
#define USE_IMMEDIATE
u8 btmtk_log_lvl = BTMTK_LOG_LEVEL_DEFAULT;

static struct class *pBTClass;
static struct device *pBTDev;
static wait_queue_head_t inq;

/* The btmtk_sdio_remove() callback function is called
 * when user removes this module from kernel space or ejects
 * the card from the slot. The driver handles these 2 cases
 * differently.
 * If the user is removing the module, a MODULE_SHUTDOWN_REQ
 * command is sent to firmware and interrupt will be disabled.
 * If the card is removed, there is no need to send command
 * or disable interrupt.
 *
 * The variable 'user_rmmod' is used to distinguish these two
 * scenarios. This flag is initialized as FALSE in case the card
 * is removed, and will be set to TRUE for module removal when
 * module_exit function is called.
 */
typedef void (*register_sdio_early_suspend) (void (*f) (void));
typedef void (*register_sdio_late_resume) (void (*f) (void));
register_sdio_early_suspend register_sdio_early_suspend_func;
register_sdio_late_resume register_sdio_late_resume_func;

/*============================================================================*/
/* Callback Functions */
/*============================================================================*/

static u8 user_rmmod;

struct completion g_done;
unsigned char probe_counter;
struct btmtk_private *g_priv;
#define STR_COREDUMP_END "coredump end\n\n"


static ring_buffer_struct metabuffer;
u8 probe_ready;

static char fw_dump_file_name[FW_DUMP_FILE_NAME_SIZE] = {0};
int fw_dump_buffer_full;
int fw_dump_total_read_size;
int fw_dump_total_write_size;
int fw_dump_buffer_used_size;
int fw_dump_task_should_stop;
u8 *fw_dump_ptr;
u8 *fw_dump_read_ptr;
u8 *fw_dump_write_ptr;
struct timeval fw_dump_last_write_time;
int fw_dump_end_checking_task_should_stop;
int fw_is_doing_coredump;
int fw_is_coredump_end_packet;

#if SAVE_FW_DUMP_IN_KERNEL
    static struct file *fw_dump_file;
#else
    static int    fw_dump_file;
#endif

static const struct btmtk_sdio_card_reg btmtk_reg_6630 = {
        .cfg = 0x03,
        .host_int_mask = 0x04,
        .host_intstatus = 0x05,
        .card_status = 0x20,
        .sq_read_base_addr_a0 = 0x10,
        .sq_read_base_addr_a1 = 0x11,
        .card_fw_status0 = 0x40,
        .card_fw_status1 = 0x41,
        .card_rx_len = 0x42,
        .card_rx_unit = 0x43,
        .io_port_0 = 0x00,
        .io_port_1 = 0x01,
        .io_port_2 = 0x02,
        .int_read_to_clear = false,
    .func_num = 2,
};

static const struct btmtk_sdio_card_reg btmtk_reg_6632 = {
        .cfg = 0x03,
        .host_int_mask = 0x04,
        .host_intstatus = 0x05,
        .card_status = 0x20,
        .sq_read_base_addr_a0 = 0x10,
        .sq_read_base_addr_a1 = 0x11,
        .card_fw_status0 = 0x40,
        .card_fw_status1 = 0x41,
        .card_rx_len = 0x42,
        .card_rx_unit = 0x43,
        .io_port_0 = 0x00,
        .io_port_1 = 0x01,
        .io_port_2 = 0x02,
        .int_read_to_clear = false,
    .func_num = 2,
};

static const struct btmtk_sdio_card_reg btmtk_reg_7668 = {
        .cfg = 0x03,
        .host_int_mask = 0x04,
        .host_intstatus = 0x05,
        .card_status = 0x20,
        .sq_read_base_addr_a0 = 0x10,
        .sq_read_base_addr_a1 = 0x11,
        .card_fw_status0 = 0x40,
        .card_fw_status1 = 0x41,
        .card_rx_len = 0x42,
        .card_rx_unit = 0x43,
        .io_port_0 = 0x00,
        .io_port_1 = 0x01,
        .io_port_2 = 0x02,
        .int_read_to_clear = false,
    .func_num = 2,
};

static const struct btmtk_sdio_card_reg btmtk_reg_7666 = {
        .cfg = 0x03,
        .host_int_mask = 0x04,
        .host_intstatus = 0x05,
        .card_status = 0x20,
        .sq_read_base_addr_a0 = 0x10,
        .sq_read_base_addr_a1 = 0x11,
        .card_fw_status0 = 0x40,
        .card_fw_status1 = 0x41,
        .card_rx_len = 0x42,
        .card_rx_unit = 0x43,
        .io_port_0 = 0x00,
        .io_port_1 = 0x01,
        .io_port_2 = 0x02,
        .int_read_to_clear = false,
    .func_num = 2,
};

static const struct btmtk_sdio_device btmtk_sdio_6630 = {
        .helper         = "mtmk/sd8688_helper.bin",
        .firmware       = "mt6632_patch_e1_hdr.bin",
        .reg            = &btmtk_reg_6630,
        .support_pscan_win_report = false,
        .sd_blksz_fw_dl = 64,
        .supports_fw_dump = false,
};

static const struct btmtk_sdio_device btmtk_sdio_6632 = {
        .helper         = "mtmk/sd8688_helper.bin",
        .firmware       = "mt6632_patch_e1_hdr.bin",
        .reg            = &btmtk_reg_6632,
        .support_pscan_win_report = false,
        .sd_blksz_fw_dl = 64,
        .supports_fw_dump = false,
};

static const struct btmtk_sdio_device btmtk_sdio_7668 = {
        .helper         = "mtmk/sd8688_helper.bin",
#if CFG_THREE_IN_ONE_FIRMWARE
        .firmware       = "MT7668_FW",
#else
        .firmware       = "mt7668_patch_e1_hdr.bin",
        .firmware1       = "mt7668_patch_e2_hdr.bin",
#endif
        .reg            = &btmtk_reg_7668,
        .support_pscan_win_report = false,
        .sd_blksz_fw_dl = 64,
        .supports_fw_dump = false,
};

static const struct btmtk_sdio_device btmtk_sdio_7666 = {
        .helper         = "mtmk/sd8688_helper.bin",
        .firmware       = "mt7668_patch_e1_hdr.bin",
        .reg            = &btmtk_reg_7666,
        .support_pscan_win_report = false,
        .sd_blksz_fw_dl = 64,
        .supports_fw_dump = false,
};


unsigned char *txbuf;
static unsigned char *rxbuf;
static u32 rx_length;
static struct btmtk_sdio_card *g_card;

/*
*add in /include/linux/mmc/sdio_ids.h
*/
#define SDIO_VENDOR_ID_MEDIATEK 0x037A

static const struct sdio_device_id btmtk_sdio_ids[] = {
        /* Mediatek SD8688 Bluetooth device */
        { SDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, 0x6630),
                        .driver_data = (unsigned long) &btmtk_sdio_6630 },

    { SDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, 0x6632),
                        .driver_data = (unsigned long) &btmtk_sdio_6632 },

    { SDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, 0x7668),
                        .driver_data = (unsigned long) &btmtk_sdio_7668 },

    { SDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, 0x7666),
                        .driver_data = (unsigned long) &btmtk_sdio_7666 },

        { }     /* Terminating entry */
};

MODULE_DEVICE_TABLE(sdio, btmtk_sdio_ids);


u32 lock_unsleepable_lock(P_OSAL_UNSLEEPABLE_LOCK pUSL)
{
    spin_lock_irqsave(&(pUSL->lock), pUSL->flag);
    return 0;
}

u32 unlock_unsleepable_lock(P_OSAL_UNSLEEPABLE_LOCK pUSL)
{
    spin_unlock_irqrestore(&(pUSL->lock), pUSL->flag);
    return 0;
}

static int btmtk_sdio_readb(u32 offset, u32 *val)
{
    u32 ret = 0;

    if (g_card->func == NULL) {
        BTMTK_ERR("%s g_card->func is NULL", __func__);
        return -EIO;
    }
    sdio_claim_host(g_card->func);
    *val = sdio_readb(g_card->func, offset, &ret);
    sdio_release_host(g_card->func);
    return ret;
}

static int btmtk_sdio_writel(u32 offset, u32 val)
{
    u32 ret = 0;

    if (g_card->func == NULL) {
        BTMTK_ERR("%s g_card->func is NULL", __func__);
        return -EIO;
    }
    sdio_claim_host(g_card->func);
    sdio_writel(g_card->func, val, offset, &ret);
    sdio_release_host(g_card->func);
    return ret;
}

static int btmtk_sdio_readl(u32 offset,  u32 *val)
{
    u32 ret = 0;

    if (g_card->func == NULL) {
        BTMTK_ERR("g_card->func is NULL");
        return -EIO;
    }
    sdio_claim_host(g_card->func);
    *val = sdio_readl(g_card->func, offset, &ret);
    sdio_release_host(g_card->func);
    return ret;
}
struct sk_buff *btmtk_create_send_data(struct sk_buff *skb)
{
    struct sk_buff *queue_skb = NULL;
    u32 sdio_header_len = skb->len + BTM_HEADER_LEN;

    if (skb_headroom(skb) < (BTM_HEADER_LEN)) {
        queue_skb = bt_skb_alloc(sdio_header_len, GFP_ATOMIC);
        if (queue_skb == NULL) {
                BTMTK_ERR("bt_skb_alloc fail return");
                return 0;
        }

        queue_skb->data[0] = (sdio_header_len & 0x0000ff);
        queue_skb->data[1] = (sdio_header_len & 0x00ff00) >> 8;
        queue_skb->data[2] = 0;
        queue_skb->data[3] = 0;
        queue_skb->data[4] = bt_cb(skb)->pkt_type;
        queue_skb->len = sdio_header_len;
        memcpy(&queue_skb->data[5], &skb->data[0], skb->len);
        kfree_skb(skb);
    } else {
        queue_skb = skb;
        skb_push(queue_skb, BTM_HEADER_LEN);
        queue_skb->data[0] = (sdio_header_len & 0x0000ff);
        queue_skb->data[1] = (sdio_header_len & 0x00ff00) >> 8;
        queue_skb->data[2] = 0;
        queue_skb->data[3] = 0;
        queue_skb->data[4] = bt_cb(skb)->pkt_type;
    }

    BTMTK_INFO("%s end", __func__);
    return queue_skb;
}
static int btmtk_sdio_set_own_back(int owntype)
{
    /*Set driver own*/
    int ret = 0;
    u32 u32LoopCount = 0;
    u32 u32ReadCRValue = 0;
    u32 ownValue = 0;
    u32 set_checkretry = 30;

    BTMTK_DBG("%s owntype %d", __func__, owntype);

    if(user_rmmod)
        set_checkretry = 1;

    ret = btmtk_sdio_readl(CHLPCR, &u32ReadCRValue);

    BTMTK_DBG("%s btmtk_sdio_readl  CHLPCR done", __func__);
    if (owntype == DRIVER_OWN) {
        if ((u32ReadCRValue&0x100) == 0x100) {
            BTMTK_DBG("%s already driver own 0x%0x, return\n", __func__, u32ReadCRValue);
            return ret;
        }

    } else if (owntype == FW_OWN) {
        if ((u32ReadCRValue&0x100) == 0) {
            BTMTK_DBG("%s already FW own 0x%0x, return\n", __func__, u32ReadCRValue);
            return ret;
        }

    }


setretry:

    if (owntype == DRIVER_OWN)
        ownValue = 0x00000200;
    else
        ownValue = 0x00000100;

    BTMTK_DBG("%s write CHLPCR 0x%x", __func__, ownValue);
    ret = btmtk_sdio_writel(CHLPCR, ownValue);
    if (ret) {
        ret = -EINVAL;
        goto done;
    }
    BTMTK_DBG("%s write CHLPCR 0x%x done", __func__, ownValue);

    u32LoopCount = 200;

    if (owntype == DRIVER_OWN) {
        do {
            udelay(1);
            ret = btmtk_sdio_readl(CHLPCR, &u32ReadCRValue);
            u32LoopCount--;
            BTMTK_DBG("%s DRIVER_OWN btmtk_sdio_readl CHLPCR 0x%x ", __func__, u32ReadCRValue);
        } while ((u32LoopCount > 0) && ((u32ReadCRValue&0x100) != 0x100));

        if ((u32LoopCount == 0) && (0x100 != (u32ReadCRValue&0x100)) && (set_checkretry > 0)) {
            BTMTK_WARN("%s retry set_check driver own", __func__);
            set_checkretry--;
            mdelay(20);
            goto setretry;
        }
    } else {
        do {
        udelay(1);
        ret = btmtk_sdio_readl(CHLPCR, &u32ReadCRValue);
        u32LoopCount--;
        BTMTK_DBG("%s FW_OWN btmtk_sdio_readl CHLPCR 0x%x ", __func__, u32ReadCRValue);
        } while ((u32LoopCount > 0) &&  ((u32ReadCRValue&0x100) != 0));

    }

    BTMTK_DBG("%s CHLPCR(0x%x), is 0x%x\n", __func__, CHLPCR, u32ReadCRValue);

    if (owntype == DRIVER_OWN) {
        if ((u32ReadCRValue&0x100) == 0x100)
            BTMTK_DBG("%s check %04x, is 0x100 driver own success\n", __func__, CHLPCR);
        else {
                BTMTK_DBG("%s check %04x, is %x shuld be 0x100\n", __func__, CHLPCR, u32ReadCRValue);
                ret = EINVAL;
                goto done;
        }
    } else {
        if (0x0 == (u32ReadCRValue&0x100))
            BTMTK_DBG("%s check %04x, bit 8 is 0 FW own success\n", __func__, CHLPCR);
        else{
            BTMTK_DBG("%s bit 8 should be 0, %04x bit 8 is %04x\n", __func__, u32ReadCRValue, (u32ReadCRValue&0x100));
            ret = EINVAL;
            goto done;
        }
    }



done:

    if (owntype == DRIVER_OWN) {
		BTMTK_DBG("%s ret=%d\n", __func__,ret);
        if (ret)
            BTMTK_ERR("%s set driver own fail\n", __func__);
        else
            BTMTK_DBG("%s set driver own success\n", __func__);
    } else if (owntype == FW_OWN) {
        if (ret)
            BTMTK_ERR("%s set FW own fail\n", __func__);
        else
            BTMTK_DBG("%s set FW own success\n", __func__);

    } else
        BTMTK_ERR("%s unknow type %d\n", __func__, owntype);


    return ret;
}
static int btmtk_sdio_enable_interrupt(int enable)
{
    u32 ret = 0;
    u32 cr_value = 0;

    if (enable)
        cr_value |= C_FW_INT_EN_SET;
    else
        cr_value |= C_FW_INT_EN_CLEAR;

    ret = btmtk_sdio_writel(CHLPCR, cr_value);
    BTMTK_DBG("%s enable %d write CHLPCR 0x%08x\n", __func__, enable, cr_value);

    return ret;
}

static int btmtk_sdio_get_rx_unit(struct btmtk_sdio_card *card)
{
        u8 reg;
        int ret;

        reg = sdio_readb(card->func, card->reg->card_rx_unit, &ret);
        if (!ret)
                card->rx_unit = reg;

        return ret;
}

static int btmtk_sdio_enable_host_int_mask(struct btmtk_sdio_card *card,
                                                                u8 mask)
{
        int ret;

        sdio_writeb(card->func, mask, card->reg->host_int_mask, &ret);
        if (ret) {
                BTMTK_ERR("Unable to enable the host interrupt!");
                ret = -EIO;
        }

        return ret;
}

static int btmtk_sdio_disable_host_int_mask(struct btmtk_sdio_card *card,
                                                                u8 mask)
{
        u8 host_int_mask;
        int ret;

        host_int_mask = sdio_readb(card->func, card->reg->host_int_mask, &ret);
        if (ret)
                return -EIO;

        host_int_mask &= ~mask;

        sdio_writeb(card->func, host_int_mask, card->reg->host_int_mask, &ret);
        if (ret < 0) {
                BTMTK_ERR("Unable to disable the host interrupt!");
                return -EIO;
        }

        return 0;
}

/*for debug*/
int btmtk_print_buffer_conent(u8 *buf, u32 Datalen)
{
    int i = 0;
    int print_finish = 0;
    /*Print out txbuf data for debug*/
    for (i = 0; i <= (Datalen-1); i += 16) {
        if ((i+16) <= Datalen) {
            BTMTK_DBG("%s: %02X%02X%02X%02X%02X %02X%02X%02X%02X%02X %02X%02X%02X%02X%02X %02X\n", __func__,
            buf[i], buf[i+1], buf[i+2], buf[i+3], buf[i+4],
            buf[i+5], buf[i+6], buf[i+7], buf[i+8], buf[i+9],
            buf[i+10], buf[i+11], buf[i+12], buf[i+13], buf[i+14],
            buf[i+15]);
        } else {
            for (; i < (Datalen); i++)
                BTMTK_DBG("%s: %02X\n", __func__, buf[i]);

            print_finish = 1;
        }

        if (print_finish)
            break;

    }
    return 0;
}

static int btmtk_sdio_send_tx_data(u8 *buffer, int tx_data_len)
{
    int ret = 0;
    u8 MultiBluckCount = 0;
    u8 redundant = 0;

    MultiBluckCount = tx_data_len/SDIO_BLOCK_SIZE;
    redundant = tx_data_len % SDIO_BLOCK_SIZE;

    if (redundant)
        tx_data_len = (MultiBluckCount+1)*SDIO_BLOCK_SIZE;

    sdio_claim_host(g_card->func);
    ret = sdio_writesb(g_card->func, CTDR, buffer, tx_data_len);
    sdio_release_host(g_card->func);

    return ret;
}

static int btmtk_sdio_recv_rx_data(void)
{
    int ret = 0;
    u32 u32ReadCRValue = 0;
    int retry_count = 5;

    memset(rxbuf, 0, MTK_RXDATA_SIZE);

    do {
        ret = btmtk_sdio_readl(CHISR, &u32ReadCRValue);
        BTMTK_DBG("%s: loop Get CHISR 0x%08X\n", __func__, u32ReadCRValue);
        rx_length = (u32ReadCRValue & RX_PKT_LEN) >> 16;
        if (rx_length == 0xFFFF) {
            BTMTK_WARN("%s: 0xFFFF==rx_length, error return -EIO\n", __func__);
            ret = -EIO;
            break;
        }

        if ((RX_DONE&u32ReadCRValue) && rx_length) {
            BTMTK_DBG("%s: u32ReadCRValue = %08X\n", __func__, u32ReadCRValue);
            u32ReadCRValue &= 0xFFFB;
            ret = btmtk_sdio_writel(CHISR, u32ReadCRValue);
            BTMTK_DBG("%s: write = %08X\n", __func__, u32ReadCRValue);
            

            sdio_claim_host(g_card->func);
            ret = sdio_readsb(g_card->func, rxbuf, CRDR, rx_length);
            sdio_release_host(g_card->func);
            if (rxbuf[0] == 0) {
                BTMTK_WARN("%s: get rx length = %d, but no rx content\n", __func__, rx_length);
                continue;
            }


            break;
        }


        retry_count--;
        if (retry_count <= 0) {
            BTMTK_WARN("%s: retry_count = %d,timeout\n", __func__, retry_count);
            ret = -EIO;
            break;
        }

/*
* msleep(1);
*/
        mdelay(3);
        BTMTK_DBG("%s: retry_count = %d,wait\n", __func__, retry_count);

        if (ret)
            break;

    } while (1);



    if (ret)
        return -EIO;





    return ret;
}

static int btmtk_sdio_send_wmt_reset(void)
{
    int ret = 0;
    u8 wmt_event[8] = {4, 0xE4, 5, 2, 7, 1, 0, 0};
    u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
    u8 mtksdio_wmt_reset[9] = {1, 0x6F, 0xFC, 5, 1, 7, 1, 0, 4};

    BTMTK_INFO("%s:\n", __func__);
    mtksdio_packet_header[0] = sizeof(mtksdio_packet_header) + sizeof(mtksdio_wmt_reset);

    memcpy(txbuf, mtksdio_packet_header, MTK_SDIO_PACKET_HEADER_SIZE);
    memcpy(txbuf+MTK_SDIO_PACKET_HEADER_SIZE, mtksdio_wmt_reset, sizeof(mtksdio_wmt_reset));

    btmtk_sdio_send_tx_data(txbuf, MTK_SDIO_PACKET_HEADER_SIZE+sizeof(mtksdio_wmt_reset));
    btmtk_sdio_recv_rx_data();

    /*compare rx data is wmt reset correct response or not*/
    if (memcmp(wmt_event, rxbuf+MTK_SDIO_PACKET_HEADER_SIZE, sizeof(wmt_event)) != 0) {
        ret = -EIO;
        BTMTK_WARN("%s: fail\n", __func__);
    }

    return ret;
}
static u32 btmtk_sdio_bt_memRegister_read(u32 cr)
{
	int retrytime = 300;
	u32 result = 0;
	u8 wmt_event[15] = {0x04,0xE4,0x10,0x02,0x08,0x0C/*0x1C*/,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x80 };
	u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
	u8 mtksdio_wmt_cmd[16] = {0x1,0x6F,0xFC,0x0C,0x01,0x08,0x08,0x00,0x02,0x01,0x00,0x01,0x00,0x00,0x00,0x00};
	mtksdio_packet_header[0] = sizeof(mtksdio_packet_header) + sizeof(mtksdio_wmt_cmd);
        BTMTK_INFO("%s: read cr %x\n",__func__,cr);
        memcpy(&mtksdio_wmt_cmd[12],&cr,sizeof(cr));
	memcpy(txbuf,mtksdio_packet_header,MTK_SDIO_PACKET_HEADER_SIZE);
	memcpy(txbuf+MTK_SDIO_PACKET_HEADER_SIZE,mtksdio_wmt_cmd,sizeof(mtksdio_wmt_cmd));
	btmtk_sdio_send_tx_data(txbuf,MTK_SDIO_PACKET_HEADER_SIZE+sizeof(mtksdio_wmt_cmd));
	btmtk_print_buffer_conent(txbuf,MTK_SDIO_PACKET_HEADER_SIZE+sizeof(mtksdio_wmt_cmd));
        do{
            msleep(10);
	    btmtk_sdio_recv_rx_data();
            retrytime--;
		if(retrytime<=0)
			break;
		BTMTK_INFO("%s: retrytime %d\n",__func__,retrytime);
	}while(!rxbuf[0]);
	btmtk_print_buffer_conent(rxbuf,rx_length);
	memcpy(&result,rxbuf+MTK_SDIO_PACKET_HEADER_SIZE+sizeof(wmt_event),sizeof(result));
        BTMTK_INFO("%s: ger cr 0x%x value 0x%x\n",__func__,cr,result);
	return result;
}
/*
*1:on ,  0:off
*/
static int btmtk_sdio_bt_set_power(u8 onoff)
{
    int ret = 0;
    int retrytime = 60;
    u8 wmt_event[8] = {4, 0xE4, 5, 2, 6, 1, 0, 0};
    u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
    u8 mtksdio_wmt_cmd[10] = {1, 0x6F, 0xFC, 6, 1, 6, 2, 0, 0, 1};
    if (onoff==0)
        retrytime = 3;

    mtksdio_packet_header[0] = sizeof(mtksdio_packet_header) + sizeof(mtksdio_wmt_cmd);
    BTMTK_INFO("%s: onoff %d\n", __func__, onoff);

    mtksdio_wmt_cmd[9] = onoff;

    memcpy(txbuf, mtksdio_packet_header, MTK_SDIO_PACKET_HEADER_SIZE);
    memcpy(txbuf+MTK_SDIO_PACKET_HEADER_SIZE, mtksdio_wmt_cmd, sizeof(mtksdio_wmt_cmd));

    btmtk_sdio_send_tx_data(txbuf, MTK_SDIO_PACKET_HEADER_SIZE+sizeof(mtksdio_wmt_cmd));


    do {
        msleep(100);
        btmtk_sdio_recv_rx_data();
        retrytime--;
        if (retrytime <= 0)
            break;
        if (retrytime < 40)
            BTMTK_WARN("%s: retry over 2s, retrytime %d\n", __func__, retrytime);

        BTMTK_INFO("%s: retrytime %d\n", __func__, retrytime);
    } while (!rxbuf[0]);


    /*compare rx data is wmt reset correct response or not*/
    if (memcmp(wmt_event, rxbuf+MTK_SDIO_PACKET_HEADER_SIZE, sizeof(wmt_event)) != 0) {
        ret = -EIO;
        BTMTK_INFO("%s: fail\n", __func__);
    }

    return ret;
}
/*
* 1:on ,  0:off
*/
static int btmtk_sdio_set_sleep(void)
{
    int ret = 0;
    u8 wmt_event[8] = {4, 0xE, 4, 1, 0x7A, 0xFC, 0};
    u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
    u8 mtksdio_wmt_cmd[11] = {1, 0x7A, 0xFC, 7, /*3:sdio, 5:usb*/03,
    /*host non sleep duration*/0x80, 0x02, /*host non sleep duration*/0x80, 0x02, 0x0, 0x00};

    mtksdio_packet_header[0] = sizeof(mtksdio_packet_header) + sizeof(mtksdio_wmt_cmd);
    BTMTK_INFO("%s begin\n", __func__);

    memcpy(txbuf, mtksdio_packet_header, MTK_SDIO_PACKET_HEADER_SIZE);
    memcpy(txbuf+MTK_SDIO_PACKET_HEADER_SIZE, mtksdio_wmt_cmd, sizeof(mtksdio_wmt_cmd));

    btmtk_sdio_send_tx_data(txbuf, MTK_SDIO_PACKET_HEADER_SIZE+sizeof(mtksdio_wmt_cmd));
    btmtk_sdio_recv_rx_data();
    btmtk_print_buffer_conent(rxbuf, rx_length);
    /*compare rx data is wmt reset correct response or not*/
    if (memcmp(wmt_event, rxbuf+MTK_SDIO_PACKET_HEADER_SIZE, sizeof(wmt_event)) != 0) {
        ret = -EIO;
        BTMTK_INFO("%s: fail\n", __func__);
    }

    return ret;
}

static int btmtk_send_rom_patch(u8 *fwbuf, u32 fwlen, int mode)
{
    int ret = 0;
    u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
    int stp_len = 0;
    u8 mtkdata_header[MTKDATA_HEADER_SIZE] = {0};

    int copy_len = 0;
    int Datalen = fwlen;
    u32 u32ReadCRValue = 0;


    BTMTK_DBG("%s fwlen %d, mode = %d", __func__, fwlen, mode);
    if (fwlen < Datalen) {
        BTMTK_ERR("%s file size = %d,is not corect", __func__, fwlen);
        return -ENOENT;
    }

    stp_len = Datalen + MTKDATA_HEADER_SIZE;


    mtkdata_header[0] = 0x2;/*ACL data*/
    mtkdata_header[1] = 0x6F;
    mtkdata_header[2] = 0xFC;

    mtkdata_header[3] = ((Datalen+4+1)&0x00FF);
    mtkdata_header[4] = ((Datalen+4+1)&0xFF00)>>8;

    mtkdata_header[5] = 0x1;
    mtkdata_header[6] = 0x1;

    mtkdata_header[7] = ((Datalen+1)&0x00FF);
    mtkdata_header[8] = ((Datalen+1)&0xFF00)>>8;

    mtkdata_header[9] = mode;

/*
* 0 and 1 is packet length, include MTKSTP_HEADER_SIZE
*/
    mtksdio_packet_header[0] = (Datalen+4+MTKSTP_HEADER_SIZE+6)&0xFF;
    mtksdio_packet_header[1] = ((Datalen+4+MTKSTP_HEADER_SIZE+6)&0xFF00)>>8;
    mtksdio_packet_header[2] = 0;
    mtksdio_packet_header[3] = 0;

/*
*mtksdio_packet_header[2] and mtksdio_packet_header[3] are reserved
*/
    BTMTK_DBG("%s result %02x  %02x\n", __func__
    , ((Datalen+4+MTKSTP_HEADER_SIZE+6)&0xFF00)>>8
    , (Datalen+4+MTKSTP_HEADER_SIZE+6));

    memcpy(txbuf+copy_len, mtksdio_packet_header, MTK_SDIO_PACKET_HEADER_SIZE);
    copy_len += MTK_SDIO_PACKET_HEADER_SIZE;

    memcpy(txbuf+copy_len, mtkdata_header, MTKDATA_HEADER_SIZE);
    copy_len += MTKDATA_HEADER_SIZE;



    memcpy(txbuf+copy_len, fwbuf, Datalen);
    copy_len += Datalen;

    BTMTK_DBG("%s txbuf %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", __func__,
    txbuf[0], txbuf[1], txbuf[2], txbuf[3], txbuf[4],
    txbuf[5], txbuf[6], txbuf[7], txbuf[8], txbuf[9]);


    ret = btmtk_sdio_readl(CHIER, &u32ReadCRValue);
    BTMTK_DBG("%s: CHIER u32ReadCRValue %x, ret %d\n", __func__, u32ReadCRValue, ret);

    ret = btmtk_sdio_readl(CHLPCR, &u32ReadCRValue);
    BTMTK_DBG("%s: CHLPCR u32ReadCRValue %x, ret %d\n", __func__, u32ReadCRValue, ret);

    ret = btmtk_sdio_readl(CHISR, &u32ReadCRValue);
    BTMTK_DBG("%s: 0CHISR u32ReadCRValue %x, ret %d\n", __func__, u32ReadCRValue, ret);
    ret = btmtk_sdio_readl(CHISR, &u32ReadCRValue);
    BTMTK_DBG("%s: 00CHISR u32ReadCRValue %x, ret %d\n", __func__, u32ReadCRValue, ret);

    btmtk_sdio_send_tx_data(txbuf, copy_len);


    ret = btmtk_sdio_recv_rx_data();

    return ret;
}



/*
* type: cmd:1, ACL:2
* -------------------------------------------------
* mtksdio hedaer 4 byte| wmt header  |
*
*
* data len should less than 512-4-4
*/
static int btmtk_sdio_send_wohci(u8 type, u32 len, u8 *data)
{
    u32 ret = 0;
    u32 push_in_data_len = 0;
    u8 mtk_wmt_header[MTKWMT_HEADER_SIZE] = {0};
    u8 mtksdio_packet_header[MTK_SDIO_PACKET_HEADER_SIZE] = {0};
    u8 mtk_tx_data[512] = {0};

    mtk_wmt_header[0] = type;
    mtk_wmt_header[1] = 0x6F;
    mtk_wmt_header[2] = 0xFC;
    mtk_wmt_header[3] = len;

    mtksdio_packet_header[0] = (len+MTKWMT_HEADER_SIZE+MTK_SDIO_PACKET_HEADER_SIZE)&0xFF;
    mtksdio_packet_header[1] = ((len+MTKWMT_HEADER_SIZE+MTK_SDIO_PACKET_HEADER_SIZE)&0xFF00)>>8;
    mtksdio_packet_header[2] = 0;
    mtksdio_packet_header[3] = 0;
/*
* mtksdio_packet_header[2] and mtksdio_packet_header[3] are reserved
*/

    memcpy(mtk_tx_data, mtksdio_packet_header, sizeof(mtksdio_packet_header));
    push_in_data_len += sizeof(mtksdio_packet_header);

    memcpy(mtk_tx_data+push_in_data_len, mtk_wmt_header, sizeof(mtk_wmt_header));
    push_in_data_len += sizeof(mtk_wmt_header);

    memcpy(mtk_tx_data+push_in_data_len, data, len);
    push_in_data_len += len;

    sdio_claim_host(g_card->func);
    ret = sdio_writesb(g_card->func, CTDR, mtk_tx_data, push_in_data_len);
    sdio_release_host(g_card->func);


    BTMTK_INFO("%s retrun  0x%0x\n", __func__, ret);
    return ret;
}
/*
* data event:
* return
* 0:
* patch download is not complete/get patch semaphore fail
* 1:
* patch download is complete by others
* 2
* patch download is not coplete
* 3:(for debug)
* release patch semaphore success
*/
static int btmtk_sdio_need_load_rom_patch(void)
{
    u32 ret = 0;
    u8 cmd[] = {0x1, 0x17, 0x1, 0x0, 0x1};
    u8 event[] = {0x2, 0x17, 0x1, 0x0};

    do {
        ret = btmtk_sdio_send_wohci(HCI_COMMAND_PKT, sizeof(cmd), cmd);

        if (ret) {
            BTMTK_ERR("%s btmtk_sdio_send_wohci return fail ret %d", __func__, ret);
            break;
        }

        ret = btmtk_sdio_recv_rx_data();
        if (ret)
            break;

        if (rx_length == 12) {
            if (memcmp(rxbuf+7, event, sizeof(event)) == 0)
                return rxbuf[11];
            else{
                BTMTK_ERR("%s receive event content is not correct, print receive data\n", __func__);
                btmtk_print_buffer_conent(rxbuf, rx_length);
            }
        }

    } while (0);

    return ret;
}
static int btmtk_sdio_set_write_clear(void)
{
    u32 u32ReadCRValue = 0;
    u32 ret = 0;

    ret = btmtk_sdio_readl(CHCR, &u32ReadCRValue);
    if (ret) {
       BTMTK_ERR("%s read CHCR error\n", __func__);
       ret = EINVAL;
       return ret;
    }

    u32ReadCRValue |= 0x00000002;
    btmtk_sdio_writel(CHCR, u32ReadCRValue);
    BTMTK_INFO("%s write CHCR 0x%08X\n", __func__, u32ReadCRValue);
    ret = btmtk_sdio_readl(CHCR, &u32ReadCRValue);
    BTMTK_INFO("%s read CHCR 0x%08X\n", __func__, u32ReadCRValue);
    if (u32ReadCRValue&0x00000002)
       BTMTK_INFO("%s write clear\n", __func__);
    else
       BTMTK_INFO("%s read clear\n", __func__);


    return ret;
}
static int btmtk_sdio_download_rom_patch(struct btmtk_sdio_card *card)
{
        const struct firmware *fw_firmware = NULL;
        const u8 *firmware = NULL;
        int firmwarelen, ret = 0;
        void *tmpfwbuf = NULL;
        u8 *fwbuf;
        P_PATCH_HEADER patchHdr;
        u8 *cDateTime = NULL;
        u16 u2HwVer = 0;
        u16 u2SwVer = 0;
        u32 u4PatchVer = 0;
        u32 uhwversion = 0;


        u32 u32ReadCRValue = 0;

        int RedundantSize = 0;
        u32 bufferOffset = 0;
        u8  patch_status = 0;

        ret = btmtk_sdio_set_own_back(DRIVER_OWN);

        if (ret)
            return ret;

        patch_status = btmtk_sdio_need_load_rom_patch();

        BTMTK_DBG("%s patch_status %d\n", __func__, patch_status);

        if (PATCH_IS_DOWNLOAD_BT_OTHER == patch_status || PATCH_READY == patch_status) {
            BTMTK_INFO("%s patch is ready no need load patch again\n", __func__);

            ret = btmtk_sdio_readl(0, &u32ReadCRValue);
            BTMTK_INFO("%s read chipid =  %x\n", __func__, u32ReadCRValue);

            /*Set interrupt output*/
            ret = btmtk_sdio_writel(CHIER, FIRMWARE_INT|TX_FIFO_OVERFLOW |
                FW_INT_IND_INDICATOR | TX_COMPLETE_COUNT |
                TX_UNDER_THOLD | TX_EMPTY | RX_DONE);

            if (ret) {
                BTMTK_ERR("Set interrupt output fail(%d)\n", ret);
                ret = -EIO;
            }


            /*enable interrupt output*/
            ret = btmtk_sdio_writel(CHLPCR, C_FW_INT_EN_SET);



            if (ret) {
                BTMTK_ERR("enable interrupt output fail(%d)\n", ret);
                ret = -EIO;
                        goto done;
            }

            ret = btmtk_sdio_bt_set_power(1);
            if (ret)
                return ret;

            ret = btmtk_sdio_set_sleep();
        btmtk_sdio_set_write_clear();
            return ret;
        }

        uhwversion = btmtk_sdio_bt_memRegister_read(HW_VERSION);
        BTMTK_INFO("%s uhwversion 0x%x\n",__func__,uhwversion);
        if (uhwversion == 0x8A00){
        BTMTK_INFO("%s request_firmware(firmware name %s)\n", __func__, card->firmware);
        ret = request_firmware(&fw_firmware, card->firmware,
                                                        &card->func->dev);
        if ((ret < 0) || !fw_firmware) {
                BTMTK_ERR("request_firmware(firmware name %s) failed, error code = %d",
                                                                        card->firmware,
                                    ret);
                ret = -ENOENT;
                goto done;
            }
        }
        else {
            BTMTK_INFO("%s request_firmware(firmware name %s)\n",__func__,card->firmware1);
	    ret = request_firmware(&fw_firmware, card->firmware1,
                                                        &card->func->dev);
            if ((ret < 0) || !fw_firmware) {
                BTMTK_ERR("request_firmware(firmware name %s) failed, error code = %d",
                                                                        card->firmware1,
									ret);
                ret = -ENOENT;
                goto done;
            }
        }

        firmware = fw_firmware->data;
        firmwarelen = fw_firmware->size;

        BTMTK_DBG("Downloading FW image (%d bytes)", firmwarelen);

        tmpfwbuf = kzalloc(firmwarelen, GFP_KERNEL);

        if (!tmpfwbuf) {
                    BTMTK_ERR("%s Unable to allocate buffer for firmware. Terminating download"
                    , __func__);
                    ret = -ENOMEM;
                    goto done;
        }

        /* Ensure aligned firmware buffer */
        memcpy(tmpfwbuf, firmware, firmwarelen);
        fwbuf = tmpfwbuf;

        /*Display rom patch info*/
        patchHdr =  (P_PATCH_HEADER)fwbuf;
        cDateTime = patchHdr->ucDateTime;
        u2HwVer = patchHdr->u2HwVer;
        u2SwVer = patchHdr->u2SwVer;
        u4PatchVer = patchHdr->u4PatchVer;

        BTMTK_DBG("=====================================\n");
        BTMTK_INFO("===============Patch Info============\n");
        BTMTK_INFO("Built Time = %s\n", cDateTime);
        BTMTK_INFO("Hw Ver = 0x%x\n",
                  ((u2HwVer & 0x00ff) << 8) | ((u2HwVer & 0xff00) >> 8));
        BTMTK_INFO("Sw Ver = 0x%x\n",
                  ((u2SwVer & 0x00ff) << 8) | ((u2SwVer & 0xff00) >> 8));
        BTMTK_INFO("Patch Ver = 0x%04x\n",
                  ((u4PatchVer & 0xff000000) >> 24) | ((u4PatchVer & 0x00ff0000) >>
                                   16));
        BTMTK_INFO("Platform = %c%c%c%c\n", patchHdr->ucPlatform[0],
                  patchHdr->ucPlatform[1], patchHdr->ucPlatform[2], patchHdr->ucPlatform[3]);
        BTMTK_INFO("Patch start addr = %02x\n", patchHdr->u2PatchStartAddr);
        BTMTK_INFO("=====================================\n");


        fwbuf += sizeof(PATCH_HEADER);
        BTMTK_DBG("%s PATCH_HEADER size %zd\n", __func__, sizeof(PATCH_HEADER));
        firmwarelen -= sizeof(PATCH_HEADER);



        ret = btmtk_sdio_readl(0, &u32ReadCRValue);
        BTMTK_INFO("%s read chipid =  %x\n", __func__, u32ReadCRValue);

        /*Set interrupt output*/
        ret = btmtk_sdio_writel(CHIER, FIRMWARE_INT|TX_FIFO_OVERFLOW |
            FW_INT_IND_INDICATOR | TX_COMPLETE_COUNT |
            TX_UNDER_THOLD | TX_EMPTY | RX_DONE);

        if (ret) {
            BTMTK_ERR("Set interrupt output fail(%d)\n", ret);
            ret = -EIO;
                    goto done;
        }

        /*enable interrupt output*/
        ret = btmtk_sdio_writel(CHLPCR, C_FW_INT_EN_SET);



        if (ret) {
            BTMTK_ERR("enable interrupt output fail(%d)\n", ret);
            ret = -EIO;
                    goto done;
        }

        RedundantSize = firmwarelen;
        BTMTK_DBG("%s firmwarelen %d\n", __func__, firmwarelen);


        do {
            bufferOffset = firmwarelen - RedundantSize;

            if (RedundantSize == firmwarelen && PATCH_DOWNLOAD_SIZE <= RedundantSize)
                ret = btmtk_send_rom_patch(fwbuf+bufferOffset, PATCH_DOWNLOAD_SIZE, SDIO_PATCH_DOWNLOAD_FIRST);
            else if (RedundantSize == firmwarelen)
                ret = btmtk_send_rom_patch(fwbuf+bufferOffset, RedundantSize, SDIO_PATCH_DOWNLOAD_FIRST);
            else if (RedundantSize < PATCH_DOWNLOAD_SIZE) {
                ret = btmtk_send_rom_patch(fwbuf+bufferOffset, RedundantSize, SDIO_PATCH_DOWNLOAD_END);
                BTMTK_DBG("%s patch downoad last patch part\n", __func__);
            } else
                ret = btmtk_send_rom_patch(fwbuf+bufferOffset, PATCH_DOWNLOAD_SIZE, SDIO_PATCH_DOWNLOAD_CON);

            RedundantSize -= PATCH_DOWNLOAD_SIZE;

            if (ret) {
                BTMTK_ERR("%s btmtk_send_rom_patch fail\n", __func__);
                goto done;
            }
            BTMTK_DBG("%s RedundantSize %d", __func__, RedundantSize);
            if (RedundantSize <= 0) {
                BTMTK_DBG("%s patch downoad finish\n", __func__);
                break;
            }

        } while (1);

        btmtk_sdio_set_write_clear();


        if (btmtk_sdio_need_load_rom_patch() == PATCH_READY)
            BTMTK_INFO("%s patch is ready\n", __func__);


        ret = btmtk_sdio_send_wmt_reset();

        if (ret)
            goto done;


        ret = btmtk_sdio_bt_set_power(1);

        if (ret){
            ret = EINVAL;
            goto done;
        }

        ret = btmtk_sdio_set_sleep();


done:

        kfree(tmpfwbuf);
            release_firmware(fw_firmware);




        if (!ret)
            BTMTK_INFO("%s success\n", __func__);
        else
            BTMTK_INFO("%s fail\n", __func__);


        return ret;
}


static int btmtk_sdio_card_to_host(struct btmtk_private *priv)
{
        u16 buf_len = 0;
        int ret = 0, num_blocks = 0, blksz = 0;
        struct sk_buff *skb = NULL;
        struct sk_buff *fops_skb = NULL;
        u32 type;
        u8 *payload = NULL;
        u32 fourbalignment_len = 0;
        struct btmtk_sdio_card *card = priv->btmtk_dev.card;
        u32 dump_len = 0;
        char *core_dump_end = NULL;

        if (!card || !card->func) {
                BTMTK_ERR("card or function or is NULL!");
                ret = -EINVAL;
                goto exit;
        }

#if SUPPORT_FW_DUMP
    fw_is_coredump_end_packet = false;
    if (rx_length > (SDIO_HEADER_LEN+8)) {
        if (rxbuf[SDIO_HEADER_LEN] == 0x80) {
            dump_len = (rxbuf[SDIO_HEADER_LEN+1]&0x0F)*256 + rxbuf[SDIO_HEADER_LEN+2];
            BTMTK_WARN("%s get dump length %d", __func__, dump_len);
            if (rxbuf[SDIO_HEADER_LEN+5] == 0x6F && rxbuf[SDIO_HEADER_LEN+6] == 0xFC) {

                fw_is_doing_coredump = true;

                if ((fw_dump_total_read_size == 0) && (fw_dump_file == NULL)) {

                #if SAVE_FW_DUMP_IN_KERNEL
                    memset(fw_dump_file_name, 0, sizeof(fw_dump_file_name));
                    snprintf(fw_dump_file_name, sizeof(fw_dump_file_name),
                            FW_DUMP_FILE_NAME"_%d", probe_counter);
                    BTMTK_WARN("%s : open file %s\n", __func__, fw_dump_file_name);
                    fw_dump_file = filp_open(fw_dump_file_name, O_RDWR | O_CREAT, 0644);
					BTMTK_WARN("%s: fw_dump_file :%p\n",__func__,fw_dump_file);
                    if (fw_dump_file)
                         BTMTK_WARN("%s : open file %s success\n", __func__, fw_dump_file_name);
                    else
                        BTMTK_WARN("%s : open file %s fail\n", __func__, fw_dump_file_name);
                #endif

                }

                fw_dump_total_read_size += dump_len;
                if (fw_dump_file->f_op == NULL)
                    BTMTK_WARN("%s : fw_dump_file->f_op is NULL\n", __func__);

                if (fw_dump_file->f_op->write == NULL)
                    BTMTK_WARN("%s : fw_dump_file->f_op->write is NULL\n", __func__);


                if ((dump_len > 0) && fw_dump_file)
                    fw_dump_file->f_op->write(fw_dump_file, &rxbuf[SDIO_HEADER_LEN+10], dump_len, &fw_dump_file->f_pos);


                if (dump_len >= sizeof(FW_DUMP_END_EVENT)) {
                    core_dump_end = strstr(&rxbuf[SDIO_HEADER_LEN+10], FW_DUMP_END_EVENT);
                    BTMTK_WARN("%s : core_dump_end %d\n", __func__, SDIO_HEADER_LEN);
                    if (core_dump_end) {
                        BTMTK_INFO("%s  vfs_fsync ", __func__);
                        vfs_fsync(fw_dump_file, 0);
                        if (fw_dump_file) {
                            BTMTK_INFO("%s : close file  %s\n", __func__, fw_dump_file_name);
                            filp_close(fw_dump_file, NULL);
                            fw_dump_file = NULL;
                            fw_is_doing_coredump = false;
                            fw_is_coredump_end_packet = true;
                        } else
                            BTMTK_INFO("%s : fw_dump_file is NULL can't close file %s", __func__, fw_dump_file_name);
                    }

                }

            }

        }
    }
#endif





        type = rxbuf[MTK_SDIO_PACKET_HEADER_SIZE];


        btmtk_print_buffer_conent(rxbuf, rx_length);

        /* Read the length of data to be transferred , not include pkt type*/
        buf_len = rx_length-(MTK_SDIO_PACKET_HEADER_SIZE+1);


        BTMTK_DBG("buf_len : %d", buf_len);
        if (rx_length <= SDIO_HEADER_LEN) {
                BTMTK_WARN("invalid packet length: %d", buf_len);
                ret = -EINVAL;
                goto exit;
        }

        /* Allocate buffer */
        skb = bt_skb_alloc(rx_length/*num_blocks * blksz + BTSDIO_DMA_ALIGN*/, GFP_ATOMIC);
        if (skb == NULL) {
                BTMTK_WARN("No free skb");
                ret = -ENOMEM;
                goto exit;
        }

        payload = rxbuf;
        BTMTK_DBG("%s rx_length %d,buf_len %d", __func__, rx_length, buf_len);

        memcpy(skb->data, &rxbuf[MTK_SDIO_PACKET_HEADER_SIZE+1], buf_len);

        switch (type) {
        case HCI_ACLDATA_PKT:
                BTMTK_DBG("%s data[2] 0x%02x, data[3] 0x%02x\n", __func__, skb->data[2], skb->data[3]);
                buf_len = skb->data[2] + skb->data[3]*256 + 4;
                BTMTK_DBG("%s acl buf_len %d\n", __func__, buf_len);
                break;
        case HCI_SCODATA_PKT:
                buf_len = skb->data[3] + 3;
                break;
        case HCI_EVENT_PKT:
                buf_len = skb->data[1] + 2;
                break;
        }

        lock_unsleepable_lock(&(metabuffer.spin_lock));
        if (priv->adapter->fops_mode & (!fw_is_doing_coredump) & (!fw_is_coredump_end_packet)) {
            fops_skb = bt_skb_alloc(buf_len, GFP_ATOMIC);
            bt_cb(fops_skb)->pkt_type = type;
            memcpy(fops_skb->data, skb->data, buf_len);
            fops_skb->len = buf_len;
            skb_queue_tail(&g_priv->adapter->fops_queue, fops_skb);
            BTMTK_DBG("%s push fops_queue\n", __func__);
            if (skb_queue_empty(&g_priv->adapter->fops_queue))
                BTMTK_INFO("%s fops_queue is empty\n", __func__);

            kfree_skb(skb);
            unlock_unsleepable_lock(&(metabuffer.spin_lock));
            BTMTK_DBG("%s call inq wake up\n", __func__);
            wake_up_interruptible(&inq);
            goto exit;
        }
        unlock_unsleepable_lock(&(metabuffer.spin_lock));

        switch (type) {
        case HCI_ACLDATA_PKT:
        case HCI_SCODATA_PKT:
        case HCI_EVENT_PKT:
                bt_cb(skb)->pkt_type = type;

                skb_put(skb, buf_len);

                break;

        case MTK_VENDOR_PKT:
                BTMTK_WARN("%s, MTK_VENDOR_PKT no handle now, break\n", __func__);
                kfree_skb(skb);
                break;

                bt_cb(skb)->pkt_type = HCI_VENDOR_PKT;
                skb_put(skb, buf_len);
                skb_pull(skb, SDIO_HEADER_LEN);


/*
* if kernel < 3, 11, 0, should use hci_recv_frame(skb);
*/

                break;

        default:
                BTMTK_WARN("Unknown packet type:%d", type);
                BTMTK_WARN("hex: %*ph", blksz * num_blocks, payload);

                kfree_skb(skb);
                skb = NULL;
                break;
        }

exit:
        if (ret) {
                BTMTK_DBG("%s fail free skb\n", __func__);
                kfree_skb(skb);
        }


        buf_len += 1;
        if (buf_len%4)
            fourbalignment_len = buf_len + 4 - buf_len%4;
        else
            fourbalignment_len = buf_len;

        rx_length -= fourbalignment_len;

        if (rx_length > (MTK_SDIO_PACKET_HEADER_SIZE)) {
            memcpy(&rxbuf[MTK_SDIO_PACKET_HEADER_SIZE],
            &rxbuf[MTK_SDIO_PACKET_HEADER_SIZE+fourbalignment_len],
            rx_length-MTK_SDIO_PACKET_HEADER_SIZE);
        }

        BTMTK_DBG("%s ret %d, rx_length, %d,fourbalignment_len %d <--\n", __func__, ret, rx_length, fourbalignment_len);

        return ret;
}

static int btmtk_sdio_process_int_status(struct btmtk_private *priv)
{
        int ret = 0;
        u32 u32rxdatacount = 0;
        u32 u32ReadCRValue = 0;

        ret = btmtk_sdio_readl(CHISR, &u32ReadCRValue);
        BTMTK_DBG("%s check TX_EMPTY CHISR 0x%08x\n", __func__, u32ReadCRValue);
        if (TX_EMPTY&u32ReadCRValue) {
            ret = btmtk_sdio_writel(CHISR, TX_EMPTY);
            priv->btmtk_dev.tx_dnld_rdy = true;
            BTMTK_DBG("%s set tx_dnld_rdy 1\n", __func__);
        }

        if (RX_DONE&u32ReadCRValue)
            ret = btmtk_sdio_recv_rx_data();


        if (ret == 0)
            while (rx_length > (MTK_SDIO_PACKET_HEADER_SIZE)) {
                btmtk_sdio_card_to_host(priv);
                u32rxdatacount++;
                BTMTK_DBG("%s u32rxdatacount %d\n", __func__, u32rxdatacount);
            }

        btmtk_sdio_enable_interrupt(1);

        return 0;
}

int hci_recv_fragment(struct hci_dev *hdev, int type, void *data, int count)
{
        int rem = 0;



        return rem;
}

static void btmtk_sdio_interrupt(struct sdio_func *func)
{
    struct btmtk_private *priv;
    struct btmtk_sdio_card *card;


    card = sdio_get_drvdata(func);

    if (!card)
            return;


    if (!card->priv)
            return;

    priv = card->priv;
    btmtk_sdio_enable_interrupt(0);


    btmtk_interrupt(priv);

    return;
}

static int btmtk_sdio_register_dev(struct btmtk_sdio_card *card)
{
        struct sdio_func *func;
        u32    u32ReadCRValue = 0;
        u8 reg;
        int ret = 0;

        if (!card || !card->func) {
                BTMTK_ERR("Error: card or function is NULL!");
                ret = -EINVAL;
                goto failed;
        }

        func = card->func;

        sdio_claim_host(func);

        ret = sdio_enable_func(func);
        if (ret) {
                BTMTK_ERR("sdio_enable_func() failed: ret=%d", ret);
                ret = -EIO;
                goto release_host;
        }


        btmtk_sdio_readb(SDIO_CCCR_IENx, &u32ReadCRValue);
        BTMTK_INFO("before claim irq read SDIO_CCCR_IENx %x, func num %d\n", u32ReadCRValue, func->num);


        ret = sdio_claim_irq(func, btmtk_sdio_interrupt);
        if (ret) {
                BTMTK_ERR("sdio_claim_irq failed: ret=%d", ret);
                ret = -EIO;
                goto disable_func;
        }
        BTMTK_INFO("sdio_claim_irq success: ret=%d", ret);

        btmtk_sdio_readb(SDIO_CCCR_IENx, &u32ReadCRValue);
        BTMTK_INFO("after claim irq read SDIO_CCCR_IENx %x\n", u32ReadCRValue);

        ret = sdio_set_block_size(card->func, SDIO_BLOCK_SIZE);
        if (ret) {
                BTMTK_ERR("cannot set SDIO block size");
                ret = -EIO;
                goto release_irq;
        }

        reg = sdio_readb(func, card->reg->io_port_0, &ret);
        if (ret < 0) {
                ret = -EIO;
                goto release_irq;
        }

        card->ioport = reg;

        reg = sdio_readb(func, card->reg->io_port_1, &ret);
        if (ret < 0) {
                ret = -EIO;
                goto release_irq;
        }

        card->ioport |= (reg << 8);

        reg = sdio_readb(func, card->reg->io_port_2, &ret);
        if (ret < 0) {
                ret = -EIO;
                goto release_irq;
        }

        card->ioport |= (reg << 16);

        BTMTK_INFO("SDIO FUNC%d IO port: 0x%x", func->num, card->ioport);

        if (card->reg->int_read_to_clear) {
                reg = sdio_readb(func, card->reg->host_int_rsr, &ret);
                if (ret < 0) {
                        ret = -EIO;
                        goto release_irq;
                }
                sdio_writeb(func, reg | 0x3f, card->reg->host_int_rsr, &ret);
                if (ret < 0) {
                        ret = -EIO;
                        goto release_irq;
                }

                reg = sdio_readb(func, card->reg->card_misc_cfg, &ret);
                if (ret < 0) {
                        ret = -EIO;
                        goto release_irq;
                }
                sdio_writeb(func, reg | 0x10, card->reg->card_misc_cfg, &ret);
                if (ret < 0) {
                        ret = -EIO;
                        goto release_irq;
                }
        }

        sdio_set_drvdata(func, card);

        sdio_release_host(func);

        return 0;

release_irq:
        sdio_release_irq(func);

disable_func:
        sdio_disable_func(func);

release_host:
        sdio_release_host(func);

failed:
        BTMTK_INFO("%s fail\n", __func__);
        return ret;
}

static int btmtk_sdio_unregister_dev(struct btmtk_sdio_card *card)
{
        if (card && card->func) {
                sdio_claim_host(card->func);
                sdio_release_irq(card->func);
                sdio_disable_func(card->func);
                sdio_release_host(card->func);
                sdio_set_drvdata(card->func, NULL);
        }

        return 0;
}

static int btmtk_sdio_enable_host_int(struct btmtk_sdio_card *card)
{
        int ret;
        u32 read_data = 0;

        if (!card || !card->func)
                return -EINVAL;

        sdio_claim_host(card->func);

        ret = btmtk_sdio_enable_host_int_mask(card, HIM_ENABLE);

        btmtk_sdio_get_rx_unit(card);

if (0) {
                typedef int (*fp_sdio_hook)(struct mmc_host *host, unsigned int width);
                fp_sdio_hook func_sdio_hook = (fp_sdio_hook) kallsyms_lookup_name("mmc_set_bus_width");
                unsigned char data = 0;

                data = sdio_f0_readb(card->func, SDIO_CCCR_IF, &ret);
                if (ret)
                    BTMTK_INFO("%s sdio_f0_readb ret %d\n", __func__, ret);

                BTMTK_INFO("%s sdio_f0_readb data 0x%X!\n", __func__, data);

                data  &= ~SDIO_BUS_WIDTH_MASK;
                data  |= SDIO_BUS_ASYNC_INT;
                card->func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

                sdio_f0_writeb(card->func, data, SDIO_CCCR_IF, &ret);
                if (ret)
                    BTMTK_INFO("%s sdio_f0_writeb ret %d\n", __func__, ret);

                BTMTK_INFO("%s func_sdio_hook at 0x%p!\n", __func__, func_sdio_hook);
                if (func_sdio_hook)
                    func_sdio_hook(card->func->card->host, MMC_BUS_WIDTH_1);


                data = sdio_f0_readb(card->func, SDIO_CCCR_IF, &ret);
                if (ret)
                BTMTK_INFO("%s sdio_f0_readb 2 ret %d\n", __func__, ret);


                BTMTK_INFO("%s sdio_f0_readb2 data 0x%X\n", __func__, data);
}

        sdio_release_host(card->func);


/*
* workaround for some platfrom no host clock sometimes
*/

        btmtk_sdio_readl(CSDIOCSR, &read_data);
        BTMTK_INFO("%s read CSDIOCSR is 0x%X\n", __func__, read_data);
        read_data |= 0x4;
        btmtk_sdio_writel(CSDIOCSR, read_data);
        BTMTK_INFO("%s write CSDIOCSR is 0x%X\n", __func__, read_data);



        return ret;
}

static int btmtk_sdio_disable_host_int(struct btmtk_sdio_card *card)
{
        int ret;

        if (!card || !card->func)
                return -EINVAL;

        sdio_claim_host(card->func);

        ret = btmtk_sdio_disable_host_int_mask(card, HIM_DISABLE);

        sdio_release_host(card->func);

        return ret;
}

static int btmtk_sdio_host_to_card(struct btmtk_private *priv,
                                u8 *payload, u16 nb)
{
        struct btmtk_sdio_card *card = priv->btmtk_dev.card;
        int ret = 0;
        int i = 0;
        u8 MultiBluckCount = 0;
        u8 redundant = 0;


        if (!card || !card->func) {
                BTMTK_ERR("card or function is NULL!");
                return -EINVAL;
        }

        MultiBluckCount = nb/SDIO_BLOCK_SIZE;
        redundant = nb % SDIO_BLOCK_SIZE;

        if (redundant)
           nb = (MultiBluckCount+1)*SDIO_BLOCK_SIZE;


       

       if (nb < 16)
            btmtk_print_buffer_conent(txbuf, nb);
       else
            btmtk_print_buffer_conent(txbuf, 16);

       do {
                 /* Transfer data to card */
                 sdio_claim_host(card->func);
                 ret = sdio_writesb(card->func, CTDR, txbuf,
                                    nb);
                 sdio_release_host(card->func);
                 if (ret < 0) {
                         i++;
                         BTMTK_ERR("i=%d writesb failed: %d", i, ret);
                         BTMTK_ERR("hex: %*ph", nb, txbuf);
                         ret = -EIO;
                         if (i > MAX_WRITE_IOMEM_RETRY)
                                 goto exit;
                 }
         } while (ret);

         if (priv)
            priv->btmtk_dev.tx_dnld_rdy = false;

 exit:
         


         return ret;
 }

 static int btmtk_sdio_download_fw(struct btmtk_sdio_card *card)
 {
         int ret;

         BTMTK_INFO("%s begin", __func__);
         if (!card || !card->func) {
                 BTMTK_ERR("card or function is NULL!");
                 return -EINVAL;
         }



         sdio_claim_host(card->func);

         if (btmtk_sdio_download_rom_patch(card)) {
                         BTMTK_ERR("Failed to download firmware!");
                         ret = -EIO;
                         goto done;
         }

         /*
          * winner or not, with this test the FW synchronizes when the
          * module can continue its initialization
          */
         sdio_release_host(card->func);

         return 0;

 done:
         sdio_release_host(card->func);
         return ret;
 }

 static int btmtk_sdio_probe(struct sdio_func *func,
                                         const struct sdio_device_id *id)
 {
    int ret = 0;
    struct btmtk_private *priv = NULL;
    struct btmtk_sdio_card *card = NULL;
    struct btmtk_sdio_device *data = (void *) id->driver_data;
    u32 u32ReadCRValue = 0;

    probe_counter++;
    pr_warn("WWWWW");
    BTMTK_INFO("%s Mediatek Bluetooth driver Version=%s", __func__, VERSION);
    BTMTK_INFO("vendor=0x%x, device=0x%x, class=%d, fn=%d, support func_num %d",
                        id->vendor, id->device, id->class, func->num, data->reg->func_num);

    if (func->num != data->reg->func_num) {
        BTMTK_INFO("func num is not match");
        return -ENODEV;
    }


        card = devm_kzalloc(&func->dev, sizeof(*card), GFP_KERNEL);
        if (!card)
                return -ENOMEM;

        card->func = func;
        g_card = card;

        if (id->driver_data) {

                card->helper = data->helper;
                card->firmware = data->firmware;
                card->firmware1 = data->firmware1;
                card->reg = data->reg;
                card->sd_blksz_fw_dl = data->sd_blksz_fw_dl;
                card->support_pscan_win_report = data->support_pscan_win_report;
                card->supports_fw_dump = data->supports_fw_dump;
        }

        BTMTK_INFO("%s func device %X\n", __func__, card->func->device);
        BTMTK_INFO("%s Call btmtk_sdio_register_dev\n", __func__);
        if (btmtk_sdio_register_dev(card) < 0) {
                BTMTK_ERR("Failed to register BT device!");
                return -ENODEV;
        } else
            BTMTK_INFO("%s btmtk_sdio_register_dev success\n", __func__);


        /* Disable the interrupts on the card */
        btmtk_sdio_enable_host_int(card);
        BTMTK_INFO("call btmtk_sdio_enable_host_int done");
        if (btmtk_sdio_download_fw(card)) {
            BTMTK_ERR("Downloading firmware failed!");
            ret = -ENODEV;
            goto unreg_dev;
        }





         priv = btmtk_add_card(card);
         if (!priv) {
                 BTMTK_ERR("Initializing card failed!");
                 ret = -ENODEV;
                 goto unreg_dev;
         }
         BTMTK_INFO("btmtk_add_card success");
         card->priv = priv;
         BTMTK_INFO("assign priv done");
         /* Initialize the interface specific function pointers */
         priv->hw_host_to_card = btmtk_sdio_host_to_card;
         priv->hw_process_int_status = btmtk_sdio_process_int_status;
         priv->hw_set_own_back =  btmtk_sdio_set_own_back;
         if (btmtk_register_hdev(priv)) {
                 BTMTK_ERR("Register hdev failed!");
                 ret = -ENODEV;
                 goto unreg_dev;
         }
        g_priv = priv;
        if (fw_dump_ptr == NULL)
            fw_dump_ptr = kmalloc(FW_DUMP_BUF_SIZE, GFP_ATOMIC);


        if (fw_dump_ptr == NULL) {
            BTMTK_ERR("%s : alloc fw_dump_ptr fail\n", __func__);
            ret = -ENODEV;
            return ret;
        }

        memset(&metabuffer.buffer, 0, META_BUFFER_SIZE);
        memset(fw_dump_ptr, 0, FW_DUMP_BUF_SIZE);
        fw_dump_task_should_stop = 0;

        fw_dump_file = NULL;
        fw_dump_read_ptr = fw_dump_ptr;
        fw_dump_write_ptr = fw_dump_ptr;
        fw_dump_total_read_size = 0;
        fw_dump_total_write_size = 0;
        fw_dump_buffer_used_size = 0;
        fw_dump_buffer_full = 0;

        ret = btmtk_sdio_readl(CHLPCR, &u32ReadCRValue);
        BTMTK_INFO("%s read CHLPCR (0x%08X)\n", __func__, u32ReadCRValue);
        BTMTK_INFO("%s normal end\n", __func__);
        probe_ready = true;
        return 0;

 unreg_dev:
         btmtk_sdio_unregister_dev(card);

         BTMTK_ERR("%s fail end\n", __func__);
         return ret;
 }

 static void btmtk_sdio_remove(struct sdio_func *func)
 {
         struct btmtk_sdio_card *card;

         BTMTK_INFO("%s begin user_rmmod %d\n", __func__,user_rmmod);
         probe_ready = false;

         if (func) {
                 card = sdio_get_drvdata(func);
                 if (card) {
                         /* Send SHUTDOWN command & disable interrupt
                          * if user removes the module.
                          */
                         if (user_rmmod) {
                                 BTMTK_INFO("%s begin user_rmmod %d in user mode\n", __func__,user_rmmod);
                                 btmtk_sdio_set_own_back(DRIVER_OWN);
                                 btmtk_sdio_enable_interrupt(0);
                                 btmtk_sdio_bt_set_power(0);
                                 btmtk_sdio_set_own_back(FW_OWN);

                                 btmtk_sdio_disable_host_int(card);
                         }
                         BTMTK_DBG("unregester dev");
                         card->priv->surprise_removed = true;
                         btmtk_sdio_unregister_dev(card);
                         btmtk_remove_card(card->priv);



                 }
         }
         BTMTK_INFO("%s end\n", __func__);
 }

 static int btmtk_sdio_suspend(struct device *dev)
 {
         struct sdio_func *func = dev_to_sdio_func(dev);
         struct btmtk_sdio_card *card;
         struct btmtk_private *priv;
         mmc_pm_flag_t pm_flags;
         struct hci_dev *hcidev;
         u8 ret = 0;

         BTMTK_INFO("%s begin return 0, do nothing", __func__);
         return sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);

         btmtk_sdio_bt_set_power(0);
         ret = btmtk_sdio_set_own_back(FW_OWN);
         if (ret) {
            BTMTK_ERR("%s set DRIVER_FW fail", __func__);
            return -EBUSY;
         }

         if (func) {
                 pm_flags = sdio_get_host_pm_caps(func);
                 BTMTK_DBG("%s: suspend: PM flags = 0x%x", sdio_func_id(func),
                        pm_flags);
                 if (!(pm_flags & MMC_PM_KEEP_POWER)) {
                         BTMTK_ERR("%s: cannot remain alive while suspended",
                                sdio_func_id(func));
                         return -EINVAL;
                 }
                 card = sdio_get_drvdata(func);
                 if (!card || !card->priv) {
                         BTMTK_ERR("card or priv structure is not valid");
                         return 0;
                 }
         } else {
                 BTMTK_ERR("sdio_func is not specified");
                 return 0;
         }

         priv = card->priv;
         hcidev = priv->btmtk_dev.hcidev;
         BTMTK_DBG("%s: SDIO suspend", hcidev->name);
         skb_queue_purge(&priv->adapter->tx_queue);




         if (priv->adapter->hs_state != HS_ACTIVATED) {
                 if (btmtk_enable_hs(priv)) {
                         BTMTK_ERR("HS not actived, suspend failed!");
                         return -EBUSY;
                 }
         }


         priv->adapter->is_suspended = true;


         if (priv->adapter->hs_state == HS_ACTIVATED) {
                 BTMTK_DBG("suspend with MMC_PM_KEEP_POWER");
                 return sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
         } else {
                 BTMTK_DBG("suspend without MMC_PM_KEEP_POWER");
                 return 0;
         }
 }

 static int btmtk_sdio_resume(struct device *dev)
 {

         struct sdio_func *func = dev_to_sdio_func(dev);
         struct btmtk_sdio_card *card;
         struct btmtk_private *priv;
         mmc_pm_flag_t pm_flags;
         struct hci_dev *hcidev;

         BTMTK_INFO("%s begin return 0, do nothing", __func__);
         return 0;

         if (func) {
                 pm_flags = sdio_get_host_pm_caps(func);
                 BTMTK_DBG("%s: resume: PM flags = 0x%x", sdio_func_id(func),
                        pm_flags);
                 card = sdio_get_drvdata(func);
                 if (!card || !card->priv) {
                         BTMTK_ERR("card or priv structure is not valid");
                         return 0;
                 }
         } else {
                 BTMTK_ERR("sdio_func is not specified");
                 return 0;
         }
         priv = card->priv;

         if (!priv->adapter->is_suspended)
                 BTMTK_DBG("device already resumed");

         priv->adapter->hs_state = HS_DEACTIVATED;
         hcidev = priv->btmtk_dev.hcidev;
         BTMTK_DBG("%s: HS DEACTIVATED in resume!", hcidev->name);
         priv->adapter->is_suspended = false;
         BTMTK_DBG("%s: SDIO resume", hcidev->name);

         return 0;
 }

 static const struct dev_pm_ops btmtk_sdio_pm_ops = {
         .suspend        = btmtk_sdio_suspend,
         .resume         = btmtk_sdio_resume,
 };

 static struct sdio_driver bt_mtk_sdio = {
         .name           = "btmtk_sdio",
         .id_table       = btmtk_sdio_ids,
         .probe          = btmtk_sdio_probe,
         .remove         = btmtk_sdio_remove,
         .drv = {
                 .owner = THIS_MODULE,
                 .pm = &btmtk_sdio_pm_ops,
         }
 };


static int btmtk_fops_open(struct inode *inode, struct file *file)
{
    BTMTK_INFO("%s begin", __func__);

    if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return -EFAULT;
    }
    /*if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return -EFAULT;
    }
	*/

    spin_lock_init(&(metabuffer.spin_lock.lock));
    BTMTK_INFO("%s spin_lock_init end", __func__);
    if (g_priv == NULL) {
        BTMTK_ERR("%s g_priv is NULL", __func__);
        return -ENOENT;
    }

    if (g_priv->adapter == NULL) {
        BTMTK_ERR("%s g_priv->adapter is NULL", __func__);
        return -ENOENT;
    }

    if (g_priv)
        g_priv->adapter->fops_mode = true;

    BTMTK_INFO("%s fops_mode=%d end", __func__, g_priv->adapter->fops_mode);
    return 0;
}

static int btmtk_fops_close(struct inode *inode, struct file *file)
{
    struct sk_buff *skb = NULL;

    BTMTK_INFO("%s begin", __func__);

    if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return -EFAULT;
    }

    spin_lock_init(&(metabuffer.spin_lock.lock));
    if (g_priv)
        g_priv->adapter->fops_mode = false;

    lock_unsleepable_lock(&(metabuffer.spin_lock));


    if (!skb_queue_empty(&g_priv->adapter->fops_queue)) {
       BTMTK_INFO("%s clean data in fops_queue", __func__);
       do {
            skb = skb_dequeue(&g_priv->adapter->fops_queue);
            if (skb == NULL) {
                BTMTK_INFO("%s skb=NULL error break", __func__);
                break;
            }

           kfree_skb(skb);
        } while (!skb_queue_empty(&g_priv->adapter->fops_queue));

    }


    unlock_unsleepable_lock(&(metabuffer.spin_lock));

    BTMTK_INFO("%s fops_mode=%d end", __func__, g_priv->adapter->fops_mode);
    return 0;
}

ssize_t btmtk_fops_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    int retval = 0;
    struct sk_buff *skb = NULL;
    u32 crAddr = 0, crValue = 0, crMask = 0;
    struct sk_buff *queue_skb = NULL;
    /*int i = 0;*/

    if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return -EFAULT;
    }

    if (g_priv == NULL) {
        BTMTK_INFO("%s g_priv is NULL", __func__);
        return -EFAULT;
    }

    if (g_priv->adapter->fops_mode == 0) {
        BTMTK_INFO("%s fops_mode is 0", __func__);
        return -EFAULT;
    }


	/*BTMTK_INFO("%s : (%d) %02X %02X %02X %02X %02X %02X %02X %02X\n", __func__, (int)count,
			buf[0],
			buf[1],
			buf[2],
			buf[3],
			buf[4],
			buf[5],
			buf[6],
			buf[7]);*/

    /*
    BTMTK_INFO("%s print write data", __func__);
    if (count > 10)
        BTMTK_INFO("  %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9]);
    else {
        for(i=0;i<count;i++)
            BTMTK_INFO("%d %02X",i,buf[i]);
    }*/

    if (buf[0] == 0x7) {
/*
* write CR
*/
        if (count < 15) {
            BTMTK_INFO("%s count=%zd less than 15, error", __func__, count);
            return -EFAULT;
        }

        crAddr = (buf[3]&0xff) + ((buf[4]&0xff)<<8) + ((buf[5]&0xff)<<16) + ((buf[6]&0xff)<<24);
        crValue = (buf[7]&0xff) + ((buf[8]&0xff)<<8) + ((buf[9]&0xff)<<16) + ((buf[10]&0xff)<<24);
        crMask = (buf[11]&0xff) + ((buf[12]&0xff)<<8) + ((buf[13]&0xff)<<16) + ((buf[14]&0xff)<<24);

        BTMTK_INFO("%s crAddr=0x%08x crValue=0x%08x crMask=0x%08x", __func__, crAddr, crValue, crMask);
        crValue &= crMask;


        BTMTK_INFO("%s write crAddr=0x%08x crValue=0x%08x", __func__, crAddr, crValue);
        btmtk_sdio_writel(crAddr, crValue);
        retval = count;
    } else if (buf[0] == 0x8) {
/*
* read CR
*/
        if (count < 16) {
            BTMTK_INFO("%s count=%zd less than 15, error", __func__, count);
            return -EFAULT;
        }

        crAddr = (buf[3]&0xff) + ((buf[4]&0xff)<<8) + ((buf[5]&0xff)<<16) + ((buf[6]&0xff)<<24);
        crMask = (buf[11]&0xff) + ((buf[12]&0xff)<<8) + ((buf[13]&0xff)<<16) + ((buf[14]&0xff)<<24);

        btmtk_sdio_readl(crAddr, &crValue);
        BTMTK_INFO("%s read crAddr=0x%08x crValue=0x%08x crMask=0x%08x", __func__, crAddr, crValue, crMask);
        retval = count;
    } else {

        skb = bt_skb_alloc(count-1, GFP_ATOMIC);
        bt_cb(skb)->pkt_type = buf[0];
        memcpy(&skb->data[0], &buf[1], count-1);
        skb->len = count-1;
        queue_skb = skb;
        skb_queue_tail(&g_priv->adapter->tx_queue, queue_skb);
        wake_up_interruptible(&g_priv->main_thread.wait_q);

        retval = count;
    }
    BTMTK_DBG("%s end", __func__);
    return retval;
}

ssize_t btmtk_fops_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int copyLen = 0;
    struct sk_buff *skb = NULL;
    unsigned long ret = 0;

    if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return -EFAULT;
    }

    if (g_priv == NULL) {
        BTMTK_INFO("%s g_priv is NULL", __func__);
        return -EFAULT;
    }

    if (g_priv->adapter->fops_mode == 0) {
        BTMTK_INFO("%s fops_mode is 0", __func__);
        return -EFAULT;
    }

    lock_unsleepable_lock(&(metabuffer.spin_lock));


    if (skb_queue_empty(&g_priv->adapter->fops_queue)) {
        if (filp->f_flags & O_NONBLOCK) {
            unlock_unsleepable_lock(&(metabuffer.spin_lock));
            return 0;
        }
    }

    do {
        skb = skb_dequeue(&g_priv->adapter->fops_queue);
        if (skb == NULL) {
            BTMTK_INFO("%s skb=NULL error break", __func__);
            break;
        }
        //BTMTK_DBG("%s pkt_type %d metabuffer.buffer %d", __func__, bt_cb(skb)->pkt_type, metabuffer.buffer[copyLen]);
        btmtk_print_buffer_conent(skb->data, skb->len);

        if (((copyLen + 1 + skb->len) > META_BUFFER_SIZE) || ((copyLen + 1 + skb->len) > count)) {
            BTMTK_ERR("%s copy copyLen %d > META_BUFFER_SIZE(%d), push back to queue", __func__,
            (copyLen + 1 + skb->len), META_BUFFER_SIZE);
            skb_queue_head(&g_priv->adapter->fops_queue, skb);
            break;
        }

        metabuffer.buffer[copyLen] = bt_cb(skb)->pkt_type;
        copyLen++;

        memcpy(&metabuffer.buffer[copyLen], skb->data, skb->len);
        copyLen += skb->len;

        kfree_skb(skb);

    } while (!skb_queue_empty(&g_priv->adapter->fops_queue));
    unlock_unsleepable_lock(&(metabuffer.spin_lock));


    ret = copy_to_user(buf, metabuffer.buffer, copyLen);
    if (ret) {
        BTMTK_ERR("%s copy to user fail, ret %d", __func__, (int)ret);
        copyLen = (copyLen - ret);
    }/* else {
    	BTMTK_INFO("%s : (%d) %02X %02X %02X %02X %02X %02X %02X %02X\n", __func__, copyLen, 
    			metabuffer.buffer[0],
    			metabuffer.buffer[1],
    			metabuffer.buffer[2],
    			metabuffer.buffer[3],
    			metabuffer.buffer[4],
    			metabuffer.buffer[5],
    			metabuffer.buffer[6],
    			metabuffer.buffer[7]);
    }*/

    //BTMTK_DBG("%s copyLen %d", __func__, copyLen);
    return copyLen;
}

unsigned int btmtk_fops_poll(struct file *filp, poll_table *wait)
{
    unsigned int mask = 0;

    if (!probe_ready) {
        BTMTK_ERR("%s probe_ready is %d return", __func__,probe_ready);
        return mask;
    }

    if (g_priv == NULL) {
        BTMTK_ERR("%s g_priv is NULL", __func__);
        return -ENODEV;
    }

    if (skb_queue_empty(&g_priv->adapter->fops_queue)) {
        poll_wait(filp, &inq, wait);

        if (!skb_queue_empty(&g_priv->adapter->fops_queue)) {
            mask |= (POLLIN | POLLRDNORM);
            //BTMTK_INFO("%s poll done\n", __func__);
	}
    } else
        mask |= (POLLIN | POLLRDNORM);

    mask |= (POLLOUT | POLLWRNORM);

    //BTMTK_INFO("%s poll mask 0x%x\n", __func__,mask);
    return mask;
}

long btmtk_fops_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    u32 retval = 0;

    return retval;
}

 static int btmtk_fops_openfwlog(struct inode *inode, struct file *file)
 {
     if (g_priv == NULL) {
         BTMTK_ERR("%s: ERROR, g_data is NULL!", __func__);
         return -ENODEV;
     }

     BTMTK_ERR("%s: OK", __func__);
     return 0;
 }

 static int btmtk_fops_closefwlog(struct inode *inode, struct file *file)
 {
     if (g_priv == NULL) {
         BTMTK_ERR("%s: ERROR, g_data is NULL!", __func__);
         return -ENODEV;
     }


     BTMTK_ERR("%s: OK", __func__);
     return 0;
 }

 static ssize_t btmtk_fops_readfwlog(struct file *filp, char __user *buf,
                    size_t count, loff_t *f_pos)
 {
     int copyLen = 0;

     if (g_priv == NULL)
         return -ENODEV;


     return copyLen;
 }

 static ssize_t btmtk_fops_writefwlog(struct file *filp, const char __user *buf,
                     size_t count, loff_t *f_pos)
 {
     int retval = 0;
     return retval;
 }

 static unsigned int btmtk_fops_pollfwlog(struct file *file, poll_table *wait)
 {
     unsigned int mask = 0;
     return mask;
 }

 static long btmtk_fops_unlocked_ioctlfwlog(struct file *filp, unsigned int cmd,
                       unsigned long arg)
 {
     int retval = 0;

     BTMTK_INFO("%s: ->", __func__);
     if (g_priv == NULL) {
         BTMTK_ERR("%s: ERROR, g_data is NULL!", __func__);
         return -ENODEV;
     }

     return retval;
 }


 static int BTMTK_major;
 static struct cdev BTMTK_cdev;
 static int BTMTK_devs = 1;

static wait_queue_head_t inq;
const struct file_operations BTMTK_fops = {
    .open = btmtk_fops_open,
    .release = btmtk_fops_close,
    .read = btmtk_fops_read,
    .write = btmtk_fops_write,
    .poll = btmtk_fops_poll,
    .unlocked_ioctl = btmtk_fops_unlocked_ioctl
};


const struct file_operations BT_fopsfwlog = {
    .open = btmtk_fops_openfwlog,
    .release = btmtk_fops_closefwlog,
    .read = btmtk_fops_readfwlog,
    .write = btmtk_fops_writefwlog,
    .poll = btmtk_fops_pollfwlog,
    .unlocked_ioctl = btmtk_fops_unlocked_ioctlfwlog

};

static int BTMTK_init(void)
{
    dev_t devID = MKDEV(BTMTK_major, 0);
    int ret = 0;
    int cdevErr = 0;
    int major = 0;

    BTMTK_INFO("BTMTK_init\n");

    g_card = NULL;
    txbuf = NULL;
    rxbuf = NULL;
    rx_length = 0;

#if SAVE_FW_DUMP_IN_KERNEL
    fw_dump_file = NULL;
#else
    fw_dump_file = 0;
#endif
    g_priv = NULL;


    fw_dump_buffer_full = 0;
    fw_dump_total_read_size = 0;
    fw_dump_total_write_size = 0;
    fw_dump_buffer_used_size = 0;
    fw_dump_task_should_stop = 0;
    fw_dump_ptr = NULL;
    fw_dump_read_ptr = NULL;
    fw_dump_write_ptr = NULL;
    probe_counter = 0;
    fw_dump_end_checking_task_should_stop = 0;
    fw_is_doing_coredump = 0;


    ret = alloc_chrdev_region(&devID, 0, 1, BT_DRIVER_NAME);
    if (ret) {
        BTMTK_ERR("fail to allocate chrdev\n");
        return ret;
    }

    BTMTK_major = major = MAJOR(devID);
    BTMTK_INFO("major number:%d", BTMTK_major);

    cdev_init(&BTMTK_cdev, &BTMTK_fops);
    BTMTK_cdev.owner = THIS_MODULE;

    cdevErr = cdev_add(&BTMTK_cdev, devID, BTMTK_devs);
    if (cdevErr)
        goto error;

    BTMTK_INFO("%s driver(major %d) installed.\n", BT_DRIVER_NAME, BTMTK_major);

    pBTClass = class_create(THIS_MODULE, BT_DRIVER_NAME);
    if (IS_ERR(pBTClass)) {
        BTMTK_ERR("class create fail, error code(%ld)\n", PTR_ERR(pBTClass));
        goto err1;
    }

    pBTDev = device_create(pBTClass, NULL, devID, NULL, BT_NODE);
    if (IS_ERR(pBTDev)) {
        BTMTK_ERR("device create fail, error code(%ld)\n", PTR_ERR(pBTDev));
        goto err2;
    }

    init_waitqueue_head(&(inq));

    return 0;

 err2:
    if (pBTClass) {
        class_destroy(pBTClass);
        pBTClass = NULL;
    }

 err1:

 error:
    if (cdevErr == 0)
        cdev_del(&BTMTK_cdev);

    if (ret == 0)
        unregister_chrdev_region(devID, BTMTK_devs);

    return -1;
}

static void BTMTK_exit(void)
{
    dev_t dev = MKDEV(BTMTK_major, 0);

    BTMTK_INFO("BTMTK_exit\n");
	BTMTK_ERR("BTMTK_exit\n");
    if (pBTDev) {
        device_destroy(pBTClass, dev);
        pBTDev = NULL;
    }

    if (pBTClass) {
        class_destroy(pBTClass);
        pBTClass = NULL;
    }

    cdev_del(&BTMTK_cdev);
    unregister_chrdev_region(dev, 1);
    BTMTK_INFO("%s driver removed.\n", BT_DRIVER_NAME);
	BTMTK_ERR("%s driver removed.\n", BT_DRIVER_NAME);
}

 static int __init btmtk_sdio_init_module(void)
{
     BTMTK_init();

     if (txbuf == NULL) {
        txbuf = kmalloc(MTK_TXDATA_SIZE, GFP_ATOMIC);
        memset(txbuf, 0, MTK_TXDATA_SIZE);
     }

     if (rxbuf == NULL) {
        rxbuf = kmalloc(MTK_RXDATA_SIZE, GFP_ATOMIC);
        memset(rxbuf, 0, MTK_RXDATA_SIZE);
     }


     if (sdio_register_driver(&bt_mtk_sdio) != 0) {
                 BTMTK_ERR("SDIO Driver Registration Failed");
                 return -ENODEV;
     } else
         BTMTK_INFO("SDIO Driver Registration Success");
		BTMTK_ERR("SDIO Driver Registration Success");
         /* Clear the flag in case user removes the card. */
         user_rmmod = 0;

         return 0;
 }

 static void __exit btmtk_sdio_exit_module(void)
 {
     /* Set the flag as user is removing this module. */
     user_rmmod = 1;
	 BTMTK_INFO("btmtk_sdio_exit_module1");
	 BTMTK_ERR("btmtk_sdio_exit_module1");
     BTMTK_exit();

     sdio_unregister_driver(&bt_mtk_sdio);
	 BTMTK_INFO("btmtk_sdio_exit_module2");
	 BTMTK_ERR("btmtk_sdio_exit_module2");
     kfree(txbuf);
		
     kfree(rxbuf);

 }

 module_init(btmtk_sdio_init_module);
 module_exit(btmtk_sdio_exit_module);
