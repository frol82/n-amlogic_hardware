/**
* @file audio_ctrl.h
* @brief  Function prototypes of audio control lib
* @author Zhang Chen <chen.zhang@amlogic.com>
* @version 1.0.0
* @date 2011-02-24
*/
/* Copyright (C) 2007-2011, Amlogic Inc.
* All right reserved
*
*/

#ifndef AUDIO_CTRL_H
#define AUDIO_CTRL_H
void audio_start(void **priv, codec_para_t *pcodec);
void audio_stop(void **priv);
void audio_stop_async(void **priv);
void audio_pause(void *priv);
void audio_resume(void *priv);
void audio_basic_init(void);
int codec_set_track_rate(codec_para_t *p,void *rate);
int codec_get_decoder_enable(codec_para_t *p);
int codec_get_pre_mute(codec_para_t *p, uint *mute);
int codec_set_pre_mute(codec_para_t *p, uint mute);
int codec_get_pre_gain(codec_para_t *p, float *gain);
int codec_set_pre_gain(codec_para_t *p, float gain);
int audio_set_avsync_threshold(void *priv, int threshold);
#endif

