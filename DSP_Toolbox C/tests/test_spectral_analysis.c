#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"
#include "spectral_analysis.h"
#include "signal_generator.h"

#define NUM_SAMPLES 128  // Must be power of two

void print_array(const char* title, const double *arr, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, arr[i]);
    }
    printf("\n");
}

int main(void) {
    double time_signal[NUM_SAMPLES];
    Complex fft_data[NUM_SAMPLES];
    double magnitude[NUM_SAMPLES];
    double phase[NUM_SAMPLES];
    double psd[NUM_SAMPLES];

    /* Generate a sine wave */
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, time_signal);

    /* Copy time_signal into fft_data (imaginary parts = 0) */
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
        fft_data[i].re = time_signal[i];
        fft_data[i].im = 0.0;
    }

    /* Compute FFT */
    fft(fft_data, NUM_SAMPLES);

    /* Compute magnitude, phase, and PSD */
    compute_magnitude(fft_data, NUM_SAMPLES, magnitude);
    compute_phase(fft_data, NUM_SAMPLES, phase);
    compute_psd(fft_data, NUM_SAMPLES, psd);

    print_array("FFT Magnitude", magnitude, 10);
    print_array("FFT Phase", phase, 10);
    print_array("PSD", psd, 10);

    return 0;
}
