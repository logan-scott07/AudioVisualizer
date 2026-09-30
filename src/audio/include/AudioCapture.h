#pragma once
#include <vector>
#include <mutex>
#include <string>
#include <miniaudio.h>

constexpr int SAMPLE_RATE = 44100;
constexpr int CHANNELS = 2;
constexpr int FFT_SIZE = 4096;
constexpr int VISUALIZER_SAMPLES = FFT_SIZE * CHANNELS;
constexpr int RING_CAPACITY = VISUALIZER_SAMPLES * 4;

class AudioPlayer {
public:
    explicit AudioPlayer(const std::string & filepath);
    ~AudioPlayer();

    std::vector<float> getSamples();

    void Pause();
    void Resume();
    [[nodiscard]] bool IsPlaying() const;

    void ChangeSong(const std::string& filepath);
private:
    static void data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);

    void writeRing(const float* samples, size_t count);
    void readRingLast(std::vector<float>& dest, size_t count) const;

    ma_decoder_config decoderConfig;
    ma_decoder decoder{};
    ma_device device{};
    std::vector<float> ring;
    size_t ringWrite = 0;
    size_t ringFilled = 0;
    std::mutex bufferMutex;
    float volume = 0.1f;

    bool playing = true;
};
