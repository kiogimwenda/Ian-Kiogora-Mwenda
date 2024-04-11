// convolution.c
#include "convolution.h"

Signal convolution(Signal x, Signal h) {
    Signal y;
    y.length = x.length + h.length - 1;
    y.samples = (float*)malloc(y.length * sizeof(float));

    for (int i = 0; i < y.length; i++) {
        y.samples[i] = 0;
        for (int j = 0; j < x.length && i - j >= 0; j++) {
            if (i - j < h.length) {
                y.samples[i] += x.samples[j] * h.samples[i - j];
            }
        }
    }

    return y;
}