#pragma once
#include <vector>
#include <mutex>
#include <string>
#include <miniaudio.h>

constexpr int SAMPLE_RATE = 44100;
constexpr int CHANNELS = 2;
constexpr int BUFFER_SIZE = 4096;

class AudioPlayer {
public:
    explicit AudioPlayer(const std::string & filepath);
    ~AudioPlayer();

    std::vector<float> getSamples();

    void Pause();
    void Resume();
    bool IsPlaying() const;

    void ChangeSong(const std::string& filepath);
private:
    static void data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);

    ma_decoder_config decoderConfig;
    ma_decoder decoder;
    ma_device device;
    std::vector<float> ringBuffer;
    std::mutex bufferMutex;
    float volume = 0.1f;

    bool playing = true;
};
