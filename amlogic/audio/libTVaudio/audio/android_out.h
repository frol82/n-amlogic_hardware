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



#ifndef __TV_ANDROID_OUT_H__
#define __TV_ANDROID_OUT_H__

#ifdef __cplusplus
extern "C" {
#endif

int new_android_audiotrack(void);
int release_android_audiotrack(void);
int amsysfs_get_sysfs_int(const char *path);
int release_raw_audio_track(void);

#ifdef __cplusplus
}
#endif

#endif //__TV_ANDROID_OUT_H__
