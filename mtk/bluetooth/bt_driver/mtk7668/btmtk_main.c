/**
 * Mediatek Bluetooth driver
 *
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
#include <linux/module.h>
#include <linux/of.h>
#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>

#include "btmtk_drv.h"
#include "btmtk_sdio.h"




/*
* extern unsigned char probe_counter;
* extern unsigned char *txbuf;
*/

extern u8 probe_ready;


/*
* int fw_dump_buffer_full = 0;
* int fw_dump_total_read_size = 0;
* int fw_dump_total_write_size = 0;
* int fw_dump_buffer_used_size = 0;
* int fw_dump_task_should_stop = 0;
* u8 *fw_dump_ptr = NULL;
* u8 *fw_dump_read_ptr = NULL;
* u8 *fw_dump_write_ptr = NULL;
* struct timeval fw_dump_last_write_time;
* int fw_dump_end_checking_task_should_stop = 0;

* static volatile int is_assert = 0;
*/


/*
 * This function is called by interface specific interrupt handler.
 * It updates Power Save & Host Sleep states, and wakes up the main
 * thread.
 */
void btmtk_interrupt(struct btmtk_private *priv)
{
    priv->adapter->ps_state = PS_AWAKE;

        priv->adapter->wakeup_tries = 0;

        priv->adapter->int_count++;

        wake_up_interruptible(&priv->main_thread.wait_q);
}
EXPORT_SYMBOL_GPL(btmtk_interrupt);

int btmtk_enable_hs(struct btmtk_private *priv)
{
        struct btmtk_adapter *adapter = priv->adapter;
        int ret = 0;

        BTMTK_INFO("%s begin\n", __func__);

        ret = wait_event_interruptible_timeout(adapter->event_hs_wait_q,
                                               adapter->hs_state,
                        msecs_to_jiffies(WAIT_UNTIL_HS_STATE_CHANGED));
        if (ret < 0) {
                BTMTK_ERR("event_hs_wait_q terminated (%d): %d,%d,%d",
                       ret, adapter->hs_state, adapter->ps_state,
                       adapter->wakeup_tries);

        } else {
                BTMTK_DBG("host sleep enabled: %d,%d,%d", adapter->hs_state,
                       adapter->ps_state, adapter->wakeup_tries);
                ret = 0;
        }

        return ret;
}
EXPORT_SYMBOL_GPL(btmtk_enable_hs);

static int btmtk_tx_pkt(struct btmtk_private *priv, struct sk_buff *skb)
{
        int ret = 0;
        u32 sdio_header_len = 0;

        BTMTK_DBG("%s skb->len %d", __func__, skb->len);

        if (!skb) {
                BTMTK_WARN("%s skb is NULL return -EINVAL", __func__);
                return -EINVAL;
        }

        if (!skb->data) {
                BTMTK_WARN("%s skb->data is NULL return -EINVAL", __func__);
                return -EINVAL;
        }

        if (!skb->len || ((skb->len + BTM_HEADER_LEN) > BTM_UPLD_SIZE)) {
                BTMTK_WARN("Tx Error: Bad skb length %d : %d",
                                                skb->len, BTM_UPLD_SIZE);
                return -EINVAL;
        }


        sdio_header_len = skb->len + BTM_HEADER_LEN;
        memset(txbuf, 0, MTK_TXDATA_SIZE);
        txbuf[0] = (sdio_header_len & 0x0000ff);
        txbuf[1] = (sdio_header_len & 0x00ff00) >> 8;
        txbuf[2] = 0;
        txbuf[3] = 0;
        txbuf[4] = bt_cb(skb)->pkt_type;
        memcpy(&txbuf[5], &skb->data[0], skb->len);
        if (priv->hw_host_to_card)
                ret = priv->hw_host_to_card(priv, txbuf, sdio_header_len);

        BTMTK_DBG("%s end", __func__);
        return ret;
}

static void btmtk_init_adapter(struct btmtk_private *priv)
{
        int buf_size;

        skb_queue_head_init(&priv->adapter->tx_queue);
        skb_queue_head_init(&priv->adapter->fops_queue);
        priv->adapter->ps_state = PS_AWAKE;

        buf_size = ALIGN_SZ(SDIO_BLOCK_SIZE, BTSDIO_DMA_ALIGN);
        priv->adapter->hw_regs_buf = kzalloc(buf_size, GFP_KERNEL);
        if (!priv->adapter->hw_regs_buf) {
                priv->adapter->hw_regs = NULL;
                BTMTK_ERR("Unable to allocate buffer for hw_regs.");
        } else {
                priv->adapter->hw_regs =
                        (u8 *)ALIGN_ADDR(priv->adapter->hw_regs_buf,
                                         BTSDIO_DMA_ALIGN);
                BTMTK_DBG("hw_regs_buf=%p hw_regs=%p",
                       priv->adapter->hw_regs_buf, priv->adapter->hw_regs);
        }

        init_waitqueue_head(&priv->adapter->cmd_wait_q);
        init_waitqueue_head(&priv->adapter->event_hs_wait_q);
}

static void btmtk_free_adapter(struct btmtk_private *priv)
{
        skb_queue_purge(&priv->adapter->tx_queue);

        kfree(priv->adapter->hw_regs_buf);
        kfree(priv->adapter);

        priv->adapter = NULL;
}

/*
 * This function handles the event generated by firmware, rx data
 * received from firmware, and tx data sent from kernel.
 */

static int btmtk_service_main_thread(void *data)
{
        struct btmtk_thread *thread = data;
        struct btmtk_private *priv = thread->priv;
        struct btmtk_adapter *adapter = NULL;
        wait_queue_t wait;
        struct sk_buff *skb;
        int ret = 0;
        int i = 0;
        ulong flags;

        BTMTK_WARN("main_thread begin 50");
        //mdelay(50);
        
        for(i=0;i<=1000;i++){
            if (kthread_should_stop()) {
                        BTMTK_WARN("main_thread: break from main thread for probe_ready");
                        break;
            }

            if (probe_ready) {
                break;
            } else {
                BTMTK_WARN("%s probe_ready %d delay 10ms",__func__,probe_ready);
                mdelay(10);
            }

            if(i==1000){
                BTMTK_WARN("%s probe_ready %d i = %d try too many times return",__func__,probe_ready,i);
                return 0;
            }
        }

        if(priv->adapter)
            adapter = priv->adapter;
        else {
            BTMTK_ERR("%s priv->adapter is NULL return",__func__);
            return 0;
        }

        init_waitqueue_entry(&wait, current);
        for (;;) {
                add_wait_queue(&thread->wait_q, &wait);
                set_current_state(TASK_INTERRUPTIBLE);
                if (kthread_should_stop()) {
                        BTMTK_WARN("main_thread: break from main thread");
                        break;
                }

                if (adapter->wakeup_tries ||
                                ((!adapter->int_count) &&
                                (!priv->btmtk_dev.tx_dnld_rdy ||
                                skb_queue_empty(&adapter->tx_queue)))) {
                        BTMTK_DBG("main_thread is sleeping...");
                        schedule();
                }

                set_current_state(TASK_RUNNING);

                remove_wait_queue(&thread->wait_q, &wait);

                if (kthread_should_stop()) {
                        BTMTK_WARN("main_thread: break after wake up");
                        break;
                }

                ret = priv->hw_set_own_back(DRIVER_OWN);
                if (ret) {
                    BTMTK_ERR("%s set driver own return fail", __func__);
                    break;
                }

                spin_lock_irqsave(&priv->driver_lock, flags);
                if (adapter->int_count) {
                        BTMTK_DBG("%s go int\n", __func__);
                        adapter->int_count = 0;
                        spin_unlock_irqrestore(&priv->driver_lock, flags);
                        priv->hw_process_int_status(priv);
                } else if (adapter->ps_state == PS_SLEEP &&
                                        !skb_queue_empty(&adapter->tx_queue)) {
                        BTMTK_DBG("%s go vender, todo\n", __func__);
                        spin_unlock_irqrestore(&priv->driver_lock, flags);
                        adapter->wakeup_tries++;
                        continue;
                } else {
                        BTMTK_DBG("%s go tx\n", __func__);
                        spin_unlock_irqrestore(&priv->driver_lock, flags);
                }

                if (adapter->ps_state == PS_SLEEP) {
                    BTMTK_DBG("%s ps_state == PS_SLEEP, continue\n", __func__);
                    continue;
                }

                if (!priv->btmtk_dev.tx_dnld_rdy) {
                    BTMTK_DBG("%s tx_dnld_rdy == 0, continue\n", __func__);
                    continue;
                }

                spin_lock_irqsave(&priv->driver_lock, flags);
                skb = skb_dequeue(&adapter->tx_queue);
                spin_unlock_irqrestore(&priv->driver_lock, flags);

                if (skb) {
                        if (skb->len < 16)
                            btmtk_print_buffer_conent(skb->data, skb->len);
                        else
                            btmtk_print_buffer_conent(skb->data, 16);

                        btmtk_tx_pkt(priv, skb);

                        if (skb) {
                            BTMTK_DBG("%s after btmtk_tx_pkt kfree_skb", __func__);
                            kfree_skb(skb);
                        }
                }


                if (skb_queue_empty(&adapter->tx_queue)) {
                    ret = priv->hw_set_own_back(FW_OWN);
                    if (ret) {
                        BTMTK_ERR("%s set fw own return fail", __func__);
                        break;
                    }
                }


        }
        BTMTK_INFO("%s  end\n", __func__);
        return 0;
}

int btmtk_register_hdev(struct btmtk_private *priv)
{
        struct hci_dev *hdev = NULL;

        BTMTK_INFO("%s\n", __func__);
        hdev = hci_alloc_dev();
        if (!hdev) {
                BTMTK_ERR("Can not allocate HCI device");
                goto err_hdev;
        }

        hci_set_drvdata(hdev, priv);
        return 0;

err_hdev:
        /* Stop the thread servicing the interrupts */
        kthread_stop(priv->main_thread.task);

        btmtk_free_adapter(priv);
        kfree(priv);

        return -ENOMEM;
}
EXPORT_SYMBOL_GPL(btmtk_register_hdev);

struct btmtk_private *btmtk_add_card(void *card)
{
        struct btmtk_private *priv;

        BTMTK_INFO("%s begin", __func__);
        priv = kzalloc(sizeof(*priv), GFP_KERNEL);
        if (!priv) {
                BTMTK_ERR("Can not allocate priv");
                goto err_priv;
        }

        priv->adapter = kzalloc(sizeof(*priv->adapter), GFP_KERNEL);
        if (!priv->adapter) {
                BTMTK_ERR("Allocate buffer for btmtk_adapter failed!");
                goto err_adapter;
        }

        btmtk_init_adapter(priv);

        BTMTK_INFO("Starting kthread...");
        priv->main_thread.priv = priv;
        spin_lock_init(&priv->driver_lock);

        init_waitqueue_head(&priv->main_thread.wait_q);
        priv->main_thread.task = kthread_run(btmtk_service_main_thread,
                                &priv->main_thread, "btmtk_main_service");
        if (IS_ERR(priv->main_thread.task))
                goto err_thread;

        priv->btmtk_dev.card = card;
        priv->btmtk_dev.tx_dnld_rdy = true;

        return priv;

err_thread:
        btmtk_free_adapter(priv);

err_adapter:
        kfree(priv);

err_priv:
        return NULL;
}
EXPORT_SYMBOL_GPL(btmtk_add_card);

int btmtk_remove_card(struct btmtk_private *priv)
{


        BTMTK_INFO("%s begin\n", __func__);


        BTMTK_INFO("%s stop main_thread\n", __func__);
        kthread_stop(priv->main_thread.task);
        BTMTK_INFO("%s stop main_thread done\n", __func__);
#ifdef CONFIG_DEBUG_FS
        /*btmtk_debugfs_remove(hdev);*/
#endif

        btmtk_free_adapter(priv);

        kfree(priv);

        return 0;
}
EXPORT_SYMBOL_GPL(btmtk_remove_card);

MODULE_AUTHOR("Mediatek Ltd.");
MODULE_DESCRIPTION("Mediatek Bluetooth driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL v2");
