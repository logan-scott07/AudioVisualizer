#include "FFT.h"
#include <cmath>
#include <algorithm>

FFT::FFT(int fftSize, int numBars, int sampleRate)
    : fftSize(fftSize), numBars(numBars), sampleRate(sampleRate) {
    cfg = kiss_fft_alloc(fftSize, 0 /* forward FFT */, nullptr, nullptr);
    window.resize(fftSize);
    smoothedBars.assign(numBars, 0.0f);

    computeHannWindow();
    computeLogBuckets();
}

FFT::~FFT() {
    kiss_fft_free(cfg);
}

void FFT::computeHannWindow() {
    for (int i = 0; i < fftSize; ++i)
        window[i] = 0.5f * (1.0f - std::cos(2.0f * static_cast<float>(M_PI) * i / (fftSize - 1)));
}

void FFT::computeLogBuckets() {
    const int numBins = fftSize / 2;
    const float minFreq = 20.0f;
    const float maxFreq = static_cast<float>(sampleRate) / 2.0f;

    const float logMin = std::log10(minFreq);
    const float logMax = std::log10(maxFreq);

    bucketBounds.resize(numBars + 1);

    for (int i = 0; i <= numBars; ++i)
    {
        float t = static_cast<float>(i) / numBars;
        t = std::pow(t, 0.65f);
        float freq = std::pow(10.0f, logMin + t * (logMax - logMin));
        int bin = static_cast<int>(freq / sampleRate * fftSize);
        bucketBounds[i] = std::clamp(bin, 0, numBins - 1);
    }

    // Guarantee strictly increasing bounds so no bucket ends up empty from rounding
    for (int i = 1; i <= numBars; ++i)
    {
        if (bucketBounds[i] <= bucketBounds[i - 1])
            bucketBounds[i] = bucketBounds[i - 1] + 1;
    }
    bucketBounds[numBars] = std::min(bucketBounds[numBars], numBins - 1);
}

std::vector<float> FFT::process(const std::vector<float>& stereoSamples) {

    std::vector<kiss_fft_cpx> in(fftSize);
    std::vector<kiss_fft_cpx> out(fftSize);

    // Downmix stereo -> mono and apply the Hann window
    const int frameCount = std::min(fftSize, static_cast<int>(stereoSamples.size() / 2));
    for (int i = 0; i < frameCount; ++i)
    {
        float left = stereoSamples[i * 2];
        float right = stereoSamples[i * 2 + 1];
        float mono = (left + right) * 0.5f;
        in[i].r = mono * window[i];
        in[i].i = 0.0f;
    }

    for (int i = frameCount; i < fftSize; ++i)
    {
        in[i].r = 0.0f;
        in[i].i = 0.0f;
    }

    kiss_fft(cfg, in.data(), out.data());

    std::vector<float> bars(numBars, 0.0f);

    for (int b = 0; b < numBars; ++b)
    {
        int startBin = bucketBounds[b];
        int endBin = bucketBounds[b + 1];

        float energy = 0.0f;
        int count = 0;

        for (int bin = startBin; bin < endBin; ++bin)
        {
            float mag = std::sqrt(out[bin].r * out[bin].r +
                                  out[bin].i * out[bin].i);

            // Reduce sensitivity to volume changes
            mag = std::log1p(mag);

            energy += mag * mag;
            ++count;
        }

        float avgMag = count > 0
            ? std::sqrt(energy / count)
            : 0.0f;


        // Frequency-based bass attenuation BEFORE normalization
        float centerBin = (startBin + endBin) * 0.5f;
        float freq = centerBin * sampleRate / fftSize;

        // Gentle bass reduction without limiting max bar height
        float bassGain = std::clamp(freq / 180.0f, 0.65f, 1.0f);

        avgMag *= bassGain;

        // Overall FFT gain
        avgMag *= 0.03f;


        constexpr float MIN_DB = -90.0f;
        constexpr float MAX_DB = -10.0f;

        float db = 20.0f * std::log10(avgMag + 1e-9f);
        db = std::clamp(db, MIN_DB, MAX_DB);

        float normalized = (db - MIN_DB) / (MAX_DB - MIN_DB);

        // Compress dynamic range
        normalized = std::pow(normalized, 2.5f);


        // Prevent tiny values from flickering
        if (normalized < 0.02f)
            normalized = 0.0f;


        // Smoothing
        float& smoothed = smoothedBars[b];

        if (normalized < smoothed)
        {
            normalized *= 0.95f;
        }

        float rate = (normalized > smoothed) ? ATTACK : RELEASE;
        smoothed += (normalized - smoothed) * rate;

        bars[b] = smoothed;
    }

    return bars;
}
