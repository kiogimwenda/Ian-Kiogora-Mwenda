#include "fft.h"
#include <complex.h>

#include <complex.h>
#include <math.h>
#define M_PI 3.14159265358979323846


Signal fft(Signal x) {
    int N = x.length;
    if (N <= 1) {
        return x;
    }

    Signal even = {.samples = malloc((N / 2) * sizeof(ComplexNumber)), .length = N / 2};
    Signal odd = {.samples = malloc((N / 2) * sizeof(ComplexNumber)), .length = N / 2};

    for (int i = 0; i < N / 2; i++) {
        even.samples[i].real = x.samples[2 * i].real;
        even.samples[i].imag = x.samples[2 * i].imag;
        odd.samples[i].real = x.samples[2 * i + 1].real;
        odd.samples[i].imag = x.samples[2 * i + 1].imag;
    }

    Signal even_fft = fft(even);
    Signal odd_fft = fft(odd);

    for (int k = 0; k < N / 2; k++) {
        double theta = -2 * M_PI * k / N;
        double t_real = cexp(I * theta) * odd_fft.samples[k].real;
        double t_imag = cexp(I * theta) * odd_fft.samples[k].imag;
        even_fft.samples[k].real = even_fft.samples[k].real + t_real;
        even_fft.samples[k].imag = even_fft.samples[k].imag + t_imag;
        odd_fft.samples[k].real = even_fft.samples[k].real - t_real;
        odd_fft.samples[k].imag = even_fft.samples[k].imag - t_imag;
    }

    for (int i = 0; i < N / 2; i++) {
        x.samples[i].real = even_fft.samples[i].real;
        x.samples[i].imag = even_fft.samples[i].imag;
        x.samples[i + N / 2].real = odd_fft.samples[i].real;
        x.samples[i + N / 2].imag = odd_fft.samples[i].imag;
    }

    free(even.samples);
    free(odd.samples);

    return x;
}
