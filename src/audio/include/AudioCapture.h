#ifndef AUDIOVISUALIZER_AUDIO_CAPTURE_H
#define AUDIOVISUALIZER_AUDIO_CAPTURE_H

#include <vector>
#include <mutex>
#include <string>

#include <miniaudio.h>

constexpr int SAMPLE_RATE = 44100;
constexpr int CHANNELS = 2;
constexpr int BUFFER_SIZE = 4096;

class AUDIO_PLAYER {
public:
    explicit AUDIO_PLAYER(const std::string & filepath);
    ~AUDIO_PLAYER();

    std::vector<float> getSamples();

private:
    static void data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);

    ma_decoder decoder;
    ma_device device;

    std::vector<float> ringBuffer;
    std::mutex bufferMutex;
    float volume = 0.1f;
};

#endif