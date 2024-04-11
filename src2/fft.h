// fft.h
#ifndef FFT_H
#define FFT_H

#include "signal_gen.h"

Signal fft(Signal x);

typedef struct ComplexNumber {
    float real;
    float imag;
} ComplexNumber;

#endif 