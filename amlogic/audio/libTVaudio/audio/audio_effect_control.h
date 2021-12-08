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



#ifndef __TV_AUDIO_EFFECT_CONTROL_H__
#define __TV_AUDIO_EFFECT_CONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 When aml audio system is open, EQ is init, but not enable. Set EQ band value first, then enable it.
 EQ has 5 bands, the gains are from -12dB to 12dB. When EQ is enabled, the main volume is 6 dB lowered.
 */

int unload_EQ_lib(void);
int load_EQ_lib(void);
int HPEQ_process(short *in, short *out, int framecount);
int HPEQ_init(void);
int HPEQ_setParameter(int band1, int band2, int band3, int band4, int band5);
int HPEQ_getParameter(int EQ_user_config[]);
int HPEQ_enable(bool enable);
int HPEQ_release(void);

/*
 When aml audio system is open, SRS is init, but not enable. Set SRS parameters as default value.
 truebass_spker_size = 2    (40, 60, 100, 150, 200, 250, 300, 400)Hz
 truebass_gain = 0.3        (0.0~1.0)
 dialogclarity_gain = 0.2   (0.0~1.0)
 definition_gain = 0.3      (0.0~1.0)
 surround_gain = 0.5        (0.0~1.0)
 When set srs_truebass_enable(1), srs works in default value. You can set other values before enable.
 SRS works only when framecount is aligned by 64, else it will make noise.
 */

int unload_SRS_lib(void);
int load_SRS_lib(void);
int srs_init(int sample_rate);
int srs_release(void);
int srs_setParameter(int SRS_user_config[]);
int srs_getParameter(int SRS_user_config[]);
int srs_set_gain(int input_gain, int output_gain);
int srs_truebass_enable(int enable);
int srs_dialogclarity_enable(int enable);
int srs_surround_enable(int enable);
int srs_process(short *in, short *out, int framecount);

/*
 IIR Lowpass Filter from amlogic
*/
int unload_aml_IIR_lib(void);
int load_aml_IIR_lib(void);
int aml_IIR_process(int input, int channel);
void aml_IIR_init(int param_index);

#ifdef __cplusplus
}
#endif

#endif //__TV_AUDIO_EFFECT_CONTROL_H__
