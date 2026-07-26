#pragma once
#include "kiss_fft.h"
#include <vector>

class FFT
{
public:
    explicit FFT(int fftSize = 4096, int numBars = 32, int sampleRate = 44100);
    ~FFT();

    std::vector<float> process(const std::vector<float>& stereoSamples);

private:
    int fftSize;
    int numBars;
    int sampleRate;

    kiss_fft_cfg cfg;
    std::vector<float> window;
    std::vector<int> bucketBounds;
    std::vector<float> smoothedBars;

    static constexpr float MIN_DB = -60.0f;
    static constexpr float MAX_DB = 0.0f;
    static constexpr float ATTACK = 0.1f;
    static constexpr float RELEASE = 0.04f;

    void computeHannWindow();
    void computeLogBuckets();
};