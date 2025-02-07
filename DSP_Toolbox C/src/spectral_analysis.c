#include "spectral_analysis.h"
#include <math.h>

void compute_magnitude(const Complex *fft_data, size_t n, double *magnitude) {
    for (size_t i = 0; i < n; i++) {
        magnitude[i] = sqrt(fft_data[i].re * fft_data[i].re + fft_data[i].im * fft_data[i].im);
    }
}

void compute_phase(const Complex *fft_data, size_t n, double *phase) {
    for (size_t i = 0; i < n; i++) {
        phase[i] = atan2(fft_data[i].im, fft_data[i].re);
    }
}

void compute_psd(const Complex *fft_data, size_t n, double *psd) {
    for (size_t i = 0; i < n; i++) {
        double mag = fft_data[i].re * fft_data[i].re + fft_data[i].im * fft_data[i].im;
        psd[i] = mag / n;
    }
}
