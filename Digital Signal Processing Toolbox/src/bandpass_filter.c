// bandpass_filter.c
#include "bandpass_filter.h"

void applyBandPassFilter(float* signal, int numSamples, float lowCutoff, float highCutoff, float sampleRate) {
    // Apply low-pass filter first
    float RC_low = 1.0f / (lowCutoff * 2 * 3.14f);
    float dt = 1.0f / sampleRate;
    float alpha_low = dt / (RC_low + dt);

    for (int i = 1; i < numSamples; i++) {
        signal[i] = signal[i - 1] + alpha_low * (signal[i] - signal[i - 1]);
    }

    // Then apply high-pass filter
    float RC_high = 1.0f / (highCutoff * 2 * 3.14f);
    float alpha_high = RC_high / (RC_high + dt);

    for (int i = 1; i < numSamples; i++) {
        signal[i] = alpha_high * (signal[i - 1] + signal[i] - signal[i - 1]);
    }
}
