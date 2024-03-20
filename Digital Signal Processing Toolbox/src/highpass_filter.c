// highpass_filter.c
#include "highpass_filter.h"

void applyHighPassFilter(float* signal, int numSamples, float cutoff, float sampleRate) {
    float RC = 1.0f / (cutoff * 2 * 3.14f);
    float dt = 1.0f / sampleRate;
    float alpha = RC / (RC + dt);

    for (int i = 1; i < numSamples; i++) {
        signal[i] = alpha * (signal[i - 1] + signal[i] - signal[i - 1]);
    }
}
