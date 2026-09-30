#define NOMINMAX
#define MINIAUDIO_IMPLEMENTATION
#include "AudioCapture.h"
#include <algorithm>
#include <cstddef>
#include <stdexcept>

AudioPlayer::AudioPlayer(const std::string &filepath)
    : decoderConfig(ma_decoder_config_init(ma_format_f32, CHANNELS, SAMPLE_RATE)),
      ring(RING_CAPACITY, 0.0f) {

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

void AudioPlayer::writeRing(const float* samples, size_t count) {
    if (count == 0) {
        return;
    }

    if (count >= RING_CAPACITY) {
        samples += count - RING_CAPACITY;
        count = RING_CAPACITY;
    }

    const size_t first = (std::min)(count, RING_CAPACITY - ringWrite);
    std::copy(samples, samples + first, ring.begin() + static_cast<std::ptrdiff_t>(ringWrite));
    if (first < count) {
        std::copy(samples + first, samples + count, ring.begin());
    }

    ringWrite = (ringWrite + count) % RING_CAPACITY;
    ringFilled = (std::min)(ringFilled + count, static_cast<size_t>(RING_CAPACITY));
}

void AudioPlayer::readRingLast(std::vector<float>& dest, size_t count) const {
    dest.resize(count);
    const size_t start = (ringWrite + RING_CAPACITY - count) % RING_CAPACITY;
    const size_t first = (std::min)(count, RING_CAPACITY - start);
    std::copy(ring.begin() + static_cast<std::ptrdiff_t>(start),
              ring.begin() + static_cast<std::ptrdiff_t>(start + first),
              dest.begin());
    if (first < count) {
        std::copy(ring.begin(),
                  ring.begin() + static_cast<std::ptrdiff_t>(count - first),
                  dest.begin() + static_cast<std::ptrdiff_t>(first));
    }
}

void AudioPlayer::data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    auto* self = static_cast<AudioPlayer*>(device->pUserData);

    auto* out = static_cast<float*>(output);
    ma_decoder_read_pcm_frames(&self->decoder, out, frameCount, nullptr);

    {
        std::lock_guard<std::mutex> lock(self->bufferMutex);
        self->writeRing(out, static_cast<size_t>(frameCount) * CHANNELS);
    }

    for (ma_uint32 i = 0; i < frameCount * CHANNELS; ++i)
        out[i] *= self->volume;
}

std::vector<float> AudioPlayer::getSamples() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    std::vector<float> samples;
    if (ringFilled < VISUALIZER_SAMPLES) {
        samples.assign(VISUALIZER_SAMPLES, 0.0f);
        return samples;
    }
    readRingLast(samples, VISUALIZER_SAMPLES);
    return samples;
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
    const bool wasPlaying = playing;
    ma_device_stop(&device);

    ma_decoder nextDecoder{};
    if (ma_decoder_init_file(filepath.c_str(), &decoderConfig, &nextDecoder) != MA_SUCCESS) {
        if (wasPlaying) {
            ma_device_start(&device);
        }
        throw std::runtime_error("Failed to open audio file: " + filepath);
    }

    ma_decoder_uninit(&decoder);
    decoder = nextDecoder;

    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        ringWrite = 0;
        ringFilled = 0;
    }

    playing = true;
    if (ma_device_start(&device) != MA_SUCCESS) {
        playing = false;
        throw std::runtime_error("Failed to start audio device");
    }
}
