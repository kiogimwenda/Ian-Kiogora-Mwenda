// cosine_signal.c
#include "cosine_signal.h"
#include <math.h>

void generateCosineSignal(float* signal, int numSamples, float frequency, float amplitude, float sampleRate) {
    float omega = 2.0f * M_PI * frequency / sampleRate;
    for (int i = 0; i < numSamples; i++) {
        signal[i] = amplitude * cos(omega * i);
    }
}
