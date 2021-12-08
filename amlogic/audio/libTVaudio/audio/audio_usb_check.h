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



#ifndef __TV_USB_AUDIO_CHECK_H__
#define __TV_USB_AUDIO_CHECK_H__

#ifdef __cplusplus
extern "C" {
#endif

unsigned int GetUsbAudioCheckFlag(void);
float get_android_stream_volume(void);
int set_parameters(char parameters[], char parm_key[]);
int creat_pthread_for_android_check
                    (pthread_t *android_check_ThreadID);
int exit_pthread_for_android_check
                    (pthread_t android_check_ThreadID);

#ifdef __cplusplus
}
#endif

#endif //__TV_USB_AUDIO_CHECK_H__
