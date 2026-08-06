#define MINIAUDIO_IMPLEMENTATION
#include "include/AudioCapture.h"

#include <iostream>
#include <stdexcept>

AudioPlayer::AudioPlayer(const std::string &filepath) {
    decoderConfig = ma_decoder_config_init(ma_format_f32, CHANNELS, SAMPLE_RATE);

    if (ma_decoder_init_file(filepath.c_str(), &decoderConfig, &decoder) != MA_SUCCESS)
        throw std::runtime_error("Failed to open audio file: " + filepath);

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;
    config.playback.channels = CHANNELS;
    config.sampleRate        = SAMPLE_RATE;
    config.dataCallback      = data_callback;
    config.pUserData         = this;

    if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS)
        throw std::runtime_error("Failed to init audio device");

    if (ma_device_start(&device) != MA_SUCCESS)
        throw std::runtime_error("Failed to start audio device");
}

AudioPlayer::~AudioPlayer() {
    ma_device_stop(&device);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}

void AudioPlayer::data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    auto* self = static_cast<AudioPlayer*>(device->pUserData);

    float* out = static_cast<float*>(output);
    ma_decoder_read_pcm_frames(&self->decoder, out, frameCount, nullptr);

    {
        std::lock_guard<std::mutex> lock(self->bufferMutex);
        self->ringBuffer.insert(self->ringBuffer.end(), out, out + frameCount * CHANNELS);
        if (self->ringBuffer.size() > BUFFER_SIZE * 4)
            self->ringBuffer.erase(self->ringBuffer.begin(),
                                   self->ringBuffer.end() - BUFFER_SIZE * 4);
    }

    // Apply volume scaling to the actual playback output only, after visualizer copy
    for (ma_uint32 i = 0; i < frameCount * CHANNELS; ++i)
        out[i] *= self->volume;
}

std::vector<float> AudioPlayer::getSamples() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    if (ringBuffer.size() < BUFFER_SIZE)
        return std::vector<float>(BUFFER_SIZE, 0.0f);
    return std::vector<float>(ringBuffer.end() - BUFFER_SIZE, ringBuffer.end());
}

void AudioPlayer::Pause() {
    if (playing) {
        ma_device_stop(&device);
        playing = false;
    }

}

void AudioPlayer::Resume() {
    if (!playing) {
        ma_device_start(&device);
        playing = true;
    }
}

bool AudioPlayer::IsPlaying() const {
    return playing;
}

void AudioPlayer::ChangeSong(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    ma_decoder_uninit(&decoder);

    ma_result result = ma_decoder_init_file(filepath.c_str(), &decoderConfig, &decoder);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("Failed to open audio file: " + filepath);
    }

    ringBuffer.clear();
    this->playing = true;
    ma_device_start(&device);
}
