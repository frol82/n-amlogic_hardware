/*
 * Copyright (C) 2014 The Android Open Source Project
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

#define LOG_TAG "AudioHAL:audio_hal_thunks"
#include <utils/Log.h>

#include <errno.h>
#include <stdlib.h>

#include <hardware/hardware.h>
#include <hardware/audio.h>

#include "AudioHardwareInput.h"
#include "AudioStreamIn.h"

namespace android {

extern AudioHardwareInput gAudioHardwareInput;

struct atv_audio_device {
    struct audio_hw_device device;
    AudioHardwareInput* input;
};

struct atv_stream_in {
    struct audio_stream_in stream;
    AudioStreamIn* impl;
};

/*******************************************************************************
 *
 * Audio input stream implementation
 *
 ******************************************************************************/

static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getSampleRate();
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->setSampleRate(rate);
}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getBufferSize();
}

static uint32_t in_get_channels(const struct audio_stream *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getChannelMask();
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getFormat();
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->setFormat(format);
}

static int in_standby(struct audio_stream *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->standby();
}

static int in_dump(const struct audio_stream *stream, int fd)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->dump(fd);
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->setParameters(stream, kvpairs);
}

static char* in_get_parameters(const struct audio_stream *stream,
                               const char *keys)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getParameters(keys);
}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->setGain(gain);
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->read(buffer, bytes);
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->getInputFramesLost();
}

static int in_add_audio_effect(const struct audio_stream *stream,
                               effect_handle_t effect)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->addAudioEffect(effect);
}

static int in_remove_audio_effect(const struct audio_stream *stream,
                                  effect_handle_t effect)
{
    const struct atv_stream_in* tstream =
        reinterpret_cast<const struct atv_stream_in*>(stream);

    return tstream->impl->removeAudioEffect(effect);
}

/*******************************************************************************
 *
 * Audio device stubs
 *
 ******************************************************************************/

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->setParameters(kvpairs);
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->getParameters(keys);
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    (void) dev;
    (void) volume;
    return 0;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode)
{
    (void) dev;
    (void) mode;
    return 0;
}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<struct atv_audio_device*>(dev);

    return adev->input->setMicMute(state);
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->getMicMute(state);
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const audio_config *config)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->getInputBufferSize(config);
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in
                                  #ifndef __KITKAT__
                                  , audio_input_flags_t flags __unused,
                                  const char *address __unused,
                                  audio_source_t source __unused
                                  #endif
                                  )
{
    (void) handle;
    int ret = 0;
    struct atv_audio_device* adev =
        reinterpret_cast<struct atv_audio_device*>(dev);
    struct atv_stream_in *in = NULL;

    *stream_in = NULL;

    in = reinterpret_cast<struct atv_stream_in*>(
            calloc(1, sizeof(struct atv_stream_in)));
    if (!in)  {
        ret = -ENOMEM;
        goto bailout;
    }

    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;

    in->impl = adev->input->openInputStream(devices,
                                            &config->format,
                                            &config->channel_mask,
                                            &config->sample_rate,
                                            reinterpret_cast<status_t*>(&ret));
    if (NULL == in->impl) {
        ret = -ENOMEM;
        goto bailout;
    }

    if (0 == ret)
        *stream_in = &in->stream;

bailout:
    if ((0 != ret) && (NULL != in)) {
        delete in->impl;
        free(in);
    }

    return ret;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                    struct audio_stream_in *stream)
{
    struct atv_audio_device* adev =
        reinterpret_cast<struct atv_audio_device*>(dev);
    struct atv_stream_in* tstream =
        reinterpret_cast<struct atv_stream_in*>(stream);

    adev->input->closeInputStream(tstream->impl);
    free(stream);
}

static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out
                                   #ifndef __KITKAT__
                                   , const char *address __unused
                                   #endif
                                   )
{
    (void) dev;
    (void) handle;
    (void) devices;
    (void) flags;
    (void) config;
    (void) stream_out;
    return -ENOSYS;
}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
    (void) dev;
    (void) stream;
}

static int adev_init_check(const struct audio_hw_device *dev)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->initCheck();
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    (void) dev;
    (void) volume;
    return 0;
}

/*static int adev_get_master_volume(struct audio_hw_device *dev,
                                  float *volume)
{
    (void) dev;
    (void) volume;
    return -ENOSYS;
}*/

static int adev_set_master_mute(struct audio_hw_device *dev, bool muted)
{
    (void) dev;
    (void) muted;
    return 0;
}

/*static int adev_get_master_mute(struct audio_hw_device *dev,
                                bool *muted)
{
    (void) dev;
    (void) muted;
    return -ENOSYS;
}*/

static int adev_dump(const audio_hw_device* dev, int fd)
{
    const struct atv_audio_device* adev =
        reinterpret_cast<const struct atv_audio_device*>(dev);

    return adev->input->dump(fd);
}

static int adev_close(hw_device_t *device)
{
    struct atv_audio_device* adev =
        reinterpret_cast<struct atv_audio_device*>(device);

    free(device);

    return 0;
}

static int atv_audiodev_open_cpp(
        const hw_module_t* module,
        const char* name,
        hw_device_t** device)
{
    struct atv_audio_device* adev = NULL;
    int ret = 0;

    if (NULL == device) {
        ret = -EINVAL;
        goto bailout;
    }

    *device = NULL;

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0) {
        ret = -EINVAL;
        goto bailout;
    }

    adev = (struct atv_audio_device*)calloc(1,
            sizeof(struct atv_audio_device));
    if (NULL == adev) {
        ret = -ENOMEM;
        goto bailout;
    }

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
    adev->device.get_master_volume = NULL; //adev_get_master_volume;
    adev->device.set_master_mute = adev_set_master_mute;
    adev->device.get_master_mute = NULL; //adev_get_master_mute;
    adev->device.set_mode = adev_set_mode;
    adev->device.set_mic_mute = adev_set_mic_mute;
    adev->device.get_mic_mute = adev_get_mic_mute;
    adev->device.set_parameters = adev_set_parameters;
    adev->device.get_parameters = adev_get_parameters;
    adev->device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->device.open_output_stream = adev_open_output_stream;
    adev->device.close_output_stream = adev_close_output_stream;
    adev->device.open_input_stream = adev_open_input_stream;
    adev->device.close_input_stream = adev_close_input_stream;
    adev->device.dump = adev_dump;

    adev->input = &gAudioHardwareInput;
    *device = &adev->device.common;

bailout:
    if ((0 != ret) && (NULL != adev)) {
        free(adev);
    }

    return 0;
}

}  // namespace android

extern "C" int atv_audiodev_open(const hw_module_t* module,
                             const char* name,
                             hw_device_t** device) {
    return android::atv_audiodev_open_cpp(module, name, device);
}