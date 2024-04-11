#include "convolution.h"
#include<stdio.h>

Signal convolution(Signal x, Signal h) {
    Signal y;
    y.length = x.length + h.length - 1;
    y.samples = (ComplexNumber*)malloc(y.length * sizeof(ComplexNumber));

    for (int i = 0; i < y.length; i++) {
        y.samples[i].real = 0;
        y.samples[i].imag = 0;

        for (int j = 0; j < x.length && i - j >= 0; j++) {
            if (i - j < h.length) {
                y.samples[i].real += x.samples[j].real * h.samples[i - j].real - x.samples[j].imag * h.samples[i - j].imag;
                y.samples[i].imag += x.samples[j].real * h.samples[i - j].imag + x.samples[j].imag * h.samples[i - j].real;
            }
        }
    }

    return y;
}