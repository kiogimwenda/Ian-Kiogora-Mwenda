// signal_gen.c
#include "signal_gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define M_PI 3.14159265358979323846

Signal generate_signal(const char* signal_type, int length) {
    Signal sig;
    sig.samples = (ComplexNumber*)malloc(length * sizeof(ComplexNumber));
    sig.length = length;

    if (strcmp(signal_type, "sine") == 0) {
        // Generate a sine wave
        for (int i = 0; i < length; i++) {
            sig.samples[i].real = 0.5 * (float)sin((2 * M_PI * i) / length);
            sig.samples[i].imag = 0.5 * (float)cos((2 * M_PI * i) / length);
        }
    } else if (strcmp(signal_type, "square") == 0) {
        // Generate a square wave
        for (int i = 0; i < length; i++) {
            double real = (i % 2 == 0) ? 1.0 : -1.0;
            double imag = 0.0;
        }
    } else if (strcmp(signal_type, "triangle") == 0) {
        // Generate a triangle wave
        for (int i = 0; i < length; i++) {
            double real = (i % 2 == 0) ? (float)i / length : 1.0 - (float)i / length;
            double imag = 0.0;
        }
    }

    return sig;
}

void print_signal(Signal sig) {
    for (int i = 0; i < sig.length; i++) {
        printf("%.4f\n", sig.samples[i]);
    }
}