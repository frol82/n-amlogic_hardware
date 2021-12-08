/*
 * Copyright (C) 2010 Amlogic Corporation.
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



#ifndef _AUDIO_HW_H_

#include <audio_utils/resampler.h>
#include "audio_hwsync.h"

#define _AUDIO_HW_H_
#define _AUDIO_HW_H_
/* ALSA cards for AML */
#define CARD_AMLOGIC_BOARD 0
#define CARD_AMLOGIC_DEFAULT CARD_AMLOGIC_BOARD
/* ALSA ports for AML */
#define PORT_MM 1
/* number of frames per period */
#define DEFAULT_PERIOD_SIZE  1024   //(1024 * 2)
static unsigned PERIOD_SIZE = DEFAULT_PERIOD_SIZE;
/* number of periods for low power playback */
#define PLAYBACK_PERIOD_COUNT 4
/* number of periods for capture */
#define CAPTURE_PERIOD_COUNT 4

/* minimum sleep time in out_write() when write threshold is not reached */
#define MIN_WRITE_SLEEP_US 5000

#define RESAMPLER_BUFFER_FRAMES (PERIOD_SIZE * 6)
#define RESAMPLER_BUFFER_SIZE (4 * RESAMPLER_BUFFER_FRAMES)

static unsigned int DEFAULT_OUT_SAMPLING_RATE = 48000;

/* sampling rate when using MM low power port */
#define MM_LOW_POWER_SAMPLING_RATE 44100
/* sampling rate when using MM full power port */
#define MM_FULL_POWER_SAMPLING_RATE 48000
/* sampling rate when using VX port for narrow band */
#define VX_NB_SAMPLING_RATE 8000

enum {
    TYPE_PCM = 0,
    TYPE_AC3 = 2,
    TYPE_DTS = 3,
    TYPE_EAC3 = 4,
    TYPE_DTS_HD = 5 ,
    TYPE_MULTI_PCM = 6,
    TYPE_TRUE_HD = 7,
    TYPE_DTS_HD_MA = 8,//should not used after we unify DTS-HD&DTS-HD MA
    TYPE_PCM_HIGH_SR = 9,
};

#define AML_HAL_MIXER_BUF_SIZE  64*1024
struct aml_hal_mixer {
    unsigned char start_buf[AML_HAL_MIXER_BUF_SIZE];
    unsigned int wp;
    unsigned int rp;
    unsigned int buf_size;
    unsigned char need_cache_flag;//flag to check if need cache some data before write to mix
    pthread_mutex_t lock;
};

#define MAX_STREAM_NUM   5
#define HDMI_ARC_MAX_FORMAT  20
struct aml_audio_device {
    struct audio_hw_device hw_device;

    pthread_mutex_t lock;       /* see note below on mutex acquisition order */
    pthread_mutex_t pcm_write_lock;
    int mode;
    audio_devices_t in_device;
    audio_devices_t out_device;
    int in_call;
    struct aml_stream_in *active_input;
    struct aml_stream_out *active_output[MAX_STREAM_NUM];
    unsigned char active_output_count;
    bool mic_mute;
    unsigned int card;
    struct audio_route *ar;
    struct echo_reference_itfe *echo_reference;
    bool low_power;
    struct aml_stream_out *hwsync_output;
    struct aml_hal_mixer hal_mixer;
    struct pcm *pcm;
    bool pcm_paused;
    unsigned hdmi_arc_ad[HDMI_ARC_MAX_FORMAT];
    bool hi_pcm_mode;
};

struct aml_stream_out {
    struct audio_stream_out stream;
    /* see note below on mutex acquisition order */
    pthread_mutex_t lock;
    /* config which set to ALSA device */
    struct pcm_config config;
    /* channel mask exposed to AudioFlinger. */
    audio_channel_mask_t hal_channel_mask;
    /* format mask exposed to AudioFlinger. */
    audio_format_t hal_format;
    /* samplerate exposed to AudioFlinger. */
    unsigned int hal_rate;
    audio_output_flags_t flags;
    audio_devices_t out_device;
    struct pcm *pcm;
    struct resampler_itfe *resampler;
    char *buffer;
    size_t buffer_frames;
    bool standby;
    struct echo_reference_itfe *echo_reference;
    struct aml_audio_device *dev;
    int write_threshold;
    bool low_power;
    unsigned multich;
    int codec_type;
    uint64_t frame_write_sum;
    uint64_t frame_skip_sum;
    uint64_t last_frames_postion;
    uint64_t spdif_enc_init_frame_write_sum;
    int skip_frame;
    int32_t *tmp_buffer_8ch;
    int is_tv_platform;
    void *audioeffect_tmp_buffer;
    int has_SRS_lib;
    int has_EQ_lib;
    unsigned char pause_status;
    bool hw_sync_mode;
    int has_aml_IIR_lib;
    int has_Virtualizer;
    float volume_l;
    float volume_r;
    int last_codec_type;
    //as raw audio framesize  is 1 computed by audio_stream_out_frame_size
    //we need divide more when we got 61937 audio package
    int raw_61937_frame_size;//61937 frame size
    unsigned last_dsp_frame;//recorded for wraparound print info
    audio_hwsync_t hwsync;
    struct timespec timestamp;
};

#define MAX_PREPROCESSORS 3 /* maximum one AGC + one NS + one AEC per input stream */
struct aml_stream_in {
    struct audio_stream_in stream;
    pthread_mutex_t lock;       /* see note below on mutex acquisition order */
    struct pcm_config config;
    struct pcm *pcm;
    int device;
    struct resampler_itfe *resampler;
    struct resampler_buffer_provider buf_provider;
    int16_t *buffer;
    size_t frames_in;
    unsigned int requested_rate;
    bool standby;
    int source;
    struct echo_reference_itfe *echo_reference;
    bool need_echo_reference;
    effect_handle_t preprocessors[MAX_PREPROCESSORS];
    int num_preprocessors;
    int16_t *proc_buf;
    size_t proc_buf_size;
    size_t proc_frames_in;
    int16_t *ref_buf;
    size_t ref_buf_size;
    size_t ref_frames_in;
    int read_status;
    struct aml_audio_device *dev;
};
typedef  int (*do_standby_func)(struct aml_stream_out *out);
typedef  int (*do_startup_func)(struct aml_stream_out *out);
#endif
