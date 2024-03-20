// sine_signal.c
#include "sine_signal.h"
#include <math.h>

void generateSineSignal(float* signal, int numSamples, float frequency, float amplitude, float sampleRate) {
    float omega = 2.0f * M_PI * frequency / sampleRate;
    for (int i = 0; i < numSamples; i++) {
        signal[i] = amplitude * sin(omega * i);
    }
}
