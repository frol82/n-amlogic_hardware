/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "ConsumerIrHal"

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cutils/log.h>
#include <hardware/hardware.h>
#include <hardware/consumerir.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define IR_DEV "/dev/irblaster1"
#define MAX_PLUSE 1024
struct aml_blaster {
	unsigned int consumerir_freqs;
	unsigned int pattern[MAX_PLUSE];
	unsigned int pattern_len;
};
#define CONSUMERIR_TRANSMIT     0x5500
#define GET_CARRIER         0x5501
#define SET_CARRIER         0x5502
#define SET_MODLEVEL         0x5503


static int dev_fd = 0;
static struct aml_blaster gst_aml_br;

static const consumerir_freq_range_t consumerir_freqs[] = {
    {.min = 30000, .max = 30000},
    {.min = 33000, .max = 33000},
    {.min = 36000, .max = 36000},
    {.min = 38000, .max = 38000},
    {.min = 40000, .max = 40000},
    {.min = 56000, .max = 56000},
};

static int consumerir_transmit(struct consumerir_device *dev,
   int carrier_freq, int pattern[], int pattern_len)
{
   	 long i;
        int modlevel = 0;
	int dev_support_carrier_freq = 0;
	struct aml_blaster *abr = &gst_aml_br;
	memset(abr,0, sizeof(struct aml_blaster));

    	for (i = 0; i < pattern_len; i++)
	{
        	//total_time += pattern[i];
		abr->pattern[i] = pattern[i];
		//ALOGD("abr->pattern[%d] : %d \n",i,abr->pattern[i] );
	}

       abr->pattern_len = pattern_len;
       abr->consumerir_freqs = carrier_freq;
    	 /* simulate the time spent transmitting by sleeping */
   	//ALOGD("transmit at %d Hz pattern_len: %d \n", carrier_freq,pattern_len);

	if(dev_fd < 0){
		ALOGD("open ir device error\n");
		return -1;
	}
	
	if(ioctl(dev_fd,GET_CARRIER,&dev_support_carrier_freq) != 0)
	{
		ALOGD("ioctl GET_CARRIER error\n");	
		return -1;
	}
	else{
		ALOGD("GET_CARRIER = %d\n",dev_support_carrier_freq);
	}
       
	if(dev_support_carrier_freq != carrier_freq)
	{
		if(ioctl(dev_fd,SET_CARRIER,&carrier_freq) != 0)
		{
			ALOGD("ioctl SET_CARRIER error\n");
			return -1;
		}
	}

	if(ioctl(dev_fd,SET_MODLEVEL,&modlevel) != 0)
	{
		ALOGD("ioctl SET_MODLEVEL error\n");
		return -1;
	}
	
	if(ioctl(dev_fd,CONSUMERIR_TRANSMIT,abr) != 0)
	{
		ALOGD("ioctl CONSUMERIR_TRANSMIT error\n");
		return -1;
	}

    return 0;
}

static int consumerir_get_num_carrier_freqs(struct consumerir_device *dev)
{
    return ARRAY_SIZE(consumerir_freqs);
}

static int consumerir_get_carrier_freqs(struct consumerir_device *dev,
    size_t len, consumerir_freq_range_t *ranges)
{
    size_t to_copy = ARRAY_SIZE(consumerir_freqs);

    to_copy = len < to_copy ? len : to_copy;
    memcpy(ranges, consumerir_freqs, to_copy * sizeof(consumerir_freq_range_t));
    return to_copy;
}

static int consumerir_close(hw_device_t *dev)
{
	if(dev_fd)
		close(dev_fd);
    free(dev);
    return 0;
}

/*
 * Generic device handling
 */
static int consumerir_open(const hw_module_t* module, const char* name,
        hw_device_t** device)
{
    if (strcmp(name, CONSUMERIR_TRANSMITTER) != 0) {
        ALOGE("strcmp fail !!!");
        return -EINVAL;
    }
    if (device == NULL) {
        ALOGE("NULL device on open");
        return -EINVAL;
    }

    consumerir_device_t *dev = malloc(sizeof(consumerir_device_t));
    memset(dev, 0, sizeof(consumerir_device_t));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*) module;
    dev->common.close = consumerir_close;

    dev->transmit = consumerir_transmit;
    dev->get_num_carrier_freqs = consumerir_get_num_carrier_freqs;
    dev->get_carrier_freqs = consumerir_get_carrier_freqs;

    *device = (hw_device_t*) dev;

	dev_fd = open(IR_DEV, O_RDONLY);
	if(dev_fd < 0){
		ALOGE("open ir device error\n");
		return -1;
	}

    return 0;
}

static struct hw_module_methods_t consumerir_module_methods = {
    .open = consumerir_open,
};

consumerir_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag                = HARDWARE_MODULE_TAG,
        .module_api_version = CONSUMERIR_MODULE_API_VERSION_1_0,
        .hal_api_version    = HARDWARE_HAL_API_VERSION,
        .id                 = CONSUMERIR_HARDWARE_MODULE_ID,
        .name               = "AML IR HAL",
        .author             = "Amlogic Corp.",
        .methods            = &consumerir_module_methods,
    },
};


