// convolve.c
#include "convolve.h"

void convolve1D(const float* input, int inputSize, const float* kernel, int kernelSize, float* output) {
    for (int i = 0; i < inputSize; i++) {
        output[i] = 0.0f;
        for (int j = 0; j < kernelSize; j++) {
            int index = i - j + kernelSize / 2;
            if (index >= 0 && index < inputSize) {
                output[i] += input[index] * kernel[j];
            }
        }
    }
}
