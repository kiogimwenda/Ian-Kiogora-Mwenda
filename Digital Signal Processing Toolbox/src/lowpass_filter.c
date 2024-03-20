// lowpass_filter.c
#include "lowpass_filter.h"

void applyLowPassFilter(float* signal, int numSamples, float cutoff, float sampleRate) {
    float RC = 1.0f / (cutoff * 2 * 3.14f);
    float dt = 1.0f / sampleRate;
    float alpha = dt / (RC + dt);

    for (int i = 1; i < numSamples; i++) {
        signal[i] = signal[i - 1] + alpha * (signal[i] - signal[i - 1]);
    }
}
