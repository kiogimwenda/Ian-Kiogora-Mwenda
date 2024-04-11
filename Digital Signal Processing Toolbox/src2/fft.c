#include "fft.h"

#include <complex.h>

Signal fft(Signal x) {
    int N = x.length;
    if (N <= 1) {
        return x;
    }

    Signal even = {.samples = malloc((N / 2) * sizeof(ComplexNumber)), .length = N / 2};
    Signal odd = {.samples = malloc((N / 2) * sizeof(ComplexNumber)), .length = N / 2};

    for (int i = 0; i < N / 2; i++) {
        even.samples[i].real = x.samples[2 * i];
        even.samples[i].imag = 0;
        odd.samples[i].real = x.samples[2 * i + 1];
        odd.samples[i].imag = 0;
    }

    Signal even_fft = fft(even);
    Signal odd_fft = fft(odd);

    for (int k = 0; k < N / 2; k++) {
        ComplexNumber t = cexp(-I * 2 * M_PI * k / N) * odd_fft.samples[k];
        even_fft.samples[k] = even_fft.samples[k] + t;
        odd_fft.samples[k] = even_fft.samples[k] - t;
    }

    for (int i = 0; i < N / 2; i++) {
        x.samples[i] = even_fft.samples[i].real;
        x.samples[i + N / 2] = odd_fft.samples[i].real;
    }

    free(even.samples);
    free(odd.samples);

    return x;
}