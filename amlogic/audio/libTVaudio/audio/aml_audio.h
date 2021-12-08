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



#ifndef __TV_AML_AUDIO_H__
#define __TV_AML_AUDIO_H__

#include "audio_effect_control.h"
#include "audio_usb_check.h"

/*
 In this system, input device is always ALSA_in, but There are 3 devices outpurt.
 For TV application, AMAUDIO OUT is suggested. This mode has low latency.
 IF HMDI/SPDIF has raw data input,  ANDROID OUT is suggested.
 */
#define CC_OUT_USE_AMAUDIO       (0)
#define CC_OUT_USE_ALSA          (1)
#define CC_OUT_USE_ANDROID       (2)

/*
 mix mode:
 DIRECT, input is direct to output, cover the local sound.
 INTER_MIX, left and right input channels mix first as one channel, and then mix with local sound.
 DIRECT_MIX,left input channel mix with local left channel, right input channel mix with local right channel
 */
#define CC_OUT_MODE_DIRECT       (0)
#define CC_OUT_MODE_INTER_MIX    (1)
#define CC_OUT_MODE_DIRECT_MIX   (2)

/*
 There are two input device, spdif or i2s.
 */
#define CC_IN_USE_I2S_DEVICE     (0)
#define CC_IN_USE_SPDIF_DEVICE   (1)

#define CC_SINGLE_OUTPUT     (0)
#define CC_DOUBLE_OUTPUT     (1)

#ifdef __cplusplus
extern "C" {
#endif

struct circle_buffer {
    pthread_mutex_t lock;
    char *start_add;
    char *rd;
    char *wr;
    int size;
};
enum  {
    LPCM = 0,
    AC3,
    EAC3,
    DTS,
    DTSHD,
    TRUEHD,
    MUTE,
};

enum {
    MODEAMAUDIO,
    MODEANDROID,
    MODERAW,
    MODEMAX
};
/*
 In this system, input stream sample rate can be set from 8K-48K, and output sample rate is fixed 48K.
 When input stream sample rate is different from output, inlined reample is in operation. If input stream sr is not set,
 the input stream is default 48K.
 */
int GetOutputdevice(void);
/* input_device: 0:I2S, 1:SPDIF; output_device: 0:amaudio, 1:alsa, 2:android */
int aml_audio_open(unsigned int sr, int input_device, int output_device);
int aml_audio_close(void);
int check_input_stream_sr(unsigned int sr);
int SetDumpDataFlag(int tmp_flag);
int GetDumpDataFlag();
int set_output_mode(int mode);
int set_music_gain(int gain);
int set_left_gain(int left_gain);
int set_right_gain(int right_gain);
int buffer_read(struct circle_buffer *tmp, char* buffer, size_t bytes);
int buffer_write(struct circle_buffer *tmp, char* buffer, size_t bytes);
int set_output_record_enable(int enable);
int set_audio_delay(int delay_ms);
int get_audio_delay(void);
int aml_audio_set_pregain(float gain);
int aml_audio_get_pregain(float *gain);
int aml_audio_set_pre_mute(uint mute);
int aml_audio_get_pre_mute(uint *mute);

#ifdef __cplusplus
}
#endif

#endif //__TV_AML_AUDIO_H__
