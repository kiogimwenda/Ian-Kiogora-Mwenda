#ifndef SIGNAL_GEN_H
#define SIGNAL_GEN_H

#include "fft.h"

typedef struct Signal_ {
    int length;
    ComplexNumber *samples;
} Signal;

Signal generate_signal(const char *signal_type, int length);
void print_signal(Signal sig);

#endif