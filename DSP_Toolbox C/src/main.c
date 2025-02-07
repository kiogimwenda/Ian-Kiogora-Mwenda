/* src/main.c
 *
 * A complete demonstration of the DSP toolbox.
 * It generates a sine wave, filters it with an FIR low-pass filter,
 * computes its FFT, performs spectral analysis, convolves a signal with itself,
 * modulates a message signal using AM and FM, writes a modulated signal to a CSV file,
 * and finally uses utility functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Include all module headers */
#include "signal_gen.h"
#include "fir_filter.h"
#include "iir_filter.h"
#include "fft.h"
#include "window.h"
#include "spectral_analysis.h"
#include "convolution.h"
#include "modulation.h"
#include "io.h"
#include "utility.h"

#define NUM_SAMPLES 256    // Must be a power of two for FFT
#define FIR_TAPS 31

int main(void) {
    /* --- 1. Signal Generation --- */
    double sine_wave[NUM_SAMPLES];
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, sine_wave);
    printf("=== Generated Sine Wave (first 10 samples) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, sine_wave[i]);
    }
    printf("\n");

    /* --- 2. FIR Filtering --- */
    double fir_coeffs[FIR_TAPS], window_hamming[FIR_TAPS];
    generate_hamming_window(FIR_TAPS, window_hamming);
    /* Design a low-pass FIR filter with a normalized cutoff frequency of 0.1 */
    fir_design_lowpass(0.1, FIR_TAPS, window_hamming, fir_coeffs);

    double filtered_signal[NUM_SAMPLES];
    fir_filter_process(sine_wave, filtered_signal, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    printf("=== FIR Filtered Signal (first 10 samples) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, filtered_signal[i]);
    }
    printf("\n");

    /* --- 3. FFT & Spectral Analysis --- */
    Complex fft_data[NUM_SAMPLES];
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
        fft_data[i].re = filtered_signal[i];
        fft_data[i].im = 0.0;
    }
    fft(fft_data, NUM_SAMPLES);

    double magnitude[NUM_SAMPLES], psd[NUM_SAMPLES];
    compute_magnitude(fft_data, NUM_SAMPLES, magnitude);
    compute_psd(fft_data, NUM_SAMPLES, psd);
    printf("=== FFT Magnitude (first 10 bins) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, magnitude[i]);
    }
    printf("\n");

    /* --- 4. Convolution --- */
    /* Convolve the original sine wave with itself as an example.
       The length of the convolution output is: NUM_SAMPLES + NUM_SAMPLES - 1 */
    size_t conv_len = NUM_SAMPLES + NUM_SAMPLES - 1;
    /*Dynamically allocate the convolution output*/
    double *conv_output = (double *)malloc(conv_len * sizeof(double));
    if (conv_output == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for convolution output.\n");
        return 1;
    }
    /*Perform the convolution*/
    linear_convolution(sine_wave, NUM_SAMPLES, sine_wave, NUM_SAMPLES, conv_output);
    printf("=== Convolution (sine wave with itself) (first 10 samples) ===\n");

    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, conv_output[i]);
    }
    printf("\n");

    /* --- 5. Modulation --- */
    /* Use a low-frequency sine wave as the baseband message signal */
    double message[NUM_SAMPLES];
    generate_sine(2.0, 0.5, 0.0, 100.0, NUM_SAMPLES, message);
    
    double am_signal[NUM_SAMPLES];
    double fm_signal[NUM_SAMPLES];
    am_modulate(message, NUM_SAMPLES, 50.0, 100.0, 0.8, am_signal);
    fm_modulate(message, NUM_SAMPLES, 50.0, 100.0, 5.0, fm_signal);
    printf("=== AM Modulated Signal (first 10 samples) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, am_signal[i]);
    }
    printf("\n");

    /* --- 6. I/O Operations --- */
    const char *filename = "output_am_signal.csv";
    if (write_signal_to_csv(filename, am_signal, NUM_SAMPLES) != 0) {
        fprintf(stderr, "Error writing AM signal to CSV.\n");
    } else {
        printf("AM signal written to %s\n", filename);
    }
    double read_signal[NUM_SAMPLES];
    size_t read_len = 0;
    if (read_signal_from_csv(filename, read_signal, NUM_SAMPLES, &read_len) != 0) {
        fprintf(stderr, "Error reading signal from CSV.\n");
    } else {
        printf("=== Read Signal from CSV (first 10 samples) ===\n");
        for (size_t i = 0; i < 10 && i < read_len; i++) {
            printf("%3zu: %f\n", i, read_signal[i]);
        }
        printf("\n");
    }

    /* --- 7. Utility Functions --- */
    /* Print a portion of the filtered signal using the utility function */
    print_vector("Utility: Filtered Signal", filtered_signal, 10);
    /* Check if several numbers are powers of two */
    for (size_t i = 0; i < 16; i++) {
        printf("Utility: Is %zu a power of two? %s\n", i, is_power_of_two(i) ? "Yes" : "No");
    }
    printf("\n");

    /* --- 8. IIR Filtering Demo (Optional) --- */
    /* Demonstrate an IIR filter (first-order low-pass) on the sine wave.
       Coefficients: b = {0.2929, 0.2929}, a = {1.0, -0.4142} */
    double iir_b[2] = {0.2929, 0.2929};
    double iir_a[2] = {1.0, -0.4142};
    /* Allocate state arrays for Direct Form I and II.
       For a first-order filter, the state length is 1. */
    double state_df1[1] = {0.0};
    double state_df2[1] = {0.0};
    double iir_output_df1[NUM_SAMPLES];
    double iir_output_df2[NUM_SAMPLES];

    iir_filter_df1(sine_wave, iir_output_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    iir_filter_df2(sine_wave, iir_output_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    printf("=== IIR Filter (Direct Form I) Output (first 10 samples) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, iir_output_df1[i]);
    }
    printf("\n");
    printf("=== IIR Filter (Direct Form II) Output (first 10 samples) ===\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%3zu: %f\n", i, iir_output_df2[i]);
    }
    printf("\n");

    return 0;
}
