/* tests/test_filtering.c
 *
 * This test program demonstrates the use of the filtering module.
 * It uses various input signals from the signal generator module and
 * applies FIR and IIR filters (using both Direct Form I and Direct Form II Transposed).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "signal_gen.h"
#include "fir_filter.h"
#include "iir_filter.h"

#define NUM_SAMPLES 128
#define FIR_TAPS 31

/* Helper function to print the first n samples of an array */
void print_array(const char* title, double* arr, size_t n) {
    printf("=== %s ===\n", title);
    for (size_t i = 0; i < n; i++) {
        printf("%3zu: %f\n", i, arr[i]);
    }
    printf("\n");
}

int main(void) {
    double input[NUM_SAMPLES];
    double output_fir[NUM_SAMPLES];
    double output_iir_df1[NUM_SAMPLES];
    double output_iir_df2[NUM_SAMPLES];

    /* State arrays for IIR filtering (for a first-order filter, state length = 1) */
    double state_df1[1] = {0.0};
    double state_df2[1] = {0.0};

    /* FIR Filter design:
       Design a low-pass FIR filter using the windowed-sinc method.
       cutoff: normalized cutoff frequency (0 < cutoff < 0.5). */
    double fir_coeffs[FIR_TAPS];
    double hamming_window[FIR_TAPS];
    double cutoff = 0.1; 
    generate_hamming_window(FIR_TAPS, hamming_window);
    fir_design_lowpass(cutoff, FIR_TAPS, hamming_window, fir_coeffs);

    /* IIR Filter coefficients for a simple first-order low-pass filter:
       The difference equation is:
         y[n] = b[0]*x[n] + b[1]*x[n-1] - a[1]*y[n-1]
       where we use b = {0.2929, 0.2929} and a = {1.0, -0.4142} */
    double iir_b[2] = {0.2929, 0.2929};
    double iir_a[2] = {1.0, -0.4142};

    /* Seed the random number generator for noise functions */
    srand((unsigned int)time(NULL));

    /* Test each type of signal:
       1. Sine, 2. Cosine, 3. Square, 4. Sawtooth, 5. Triangle,
       6. Impulse, 7. Step, 8. Chirp, 9. White Noise, 10. Pink Noise. */

    /* --- 1. Sine Wave --- */
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, input);
    print_array("Input Sine Wave", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Sine Wave", output_fir, 10);
    state_df1[0] = 0.0; state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Sine Wave", output_iir_df1, 10);
    state_df1[0] = 0.0; state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Sine Wave", output_iir_df2, 10);

    /* --- 2. Cosine Wave --- */
    generate_cosine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, input);
    print_array("Input Cosine Wave", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Cosine Wave", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Cosine Wave", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Cosine Wave", output_iir_df2, 10);

    /* --- 3. Square Wave --- */
    generate_square(5.0, 1.0, 0.5, 100.0, NUM_SAMPLES, input);
    print_array("Input Square Wave", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Square Wave", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Square Wave", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Square Wave", output_iir_df2, 10);

    /* --- 4. Sawtooth Wave --- */
    generate_sawtooth(5.0, 1.0, 100.0, NUM_SAMPLES, input);
    print_array("Input Sawtooth Wave", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Sawtooth Wave", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Sawtooth Wave", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Sawtooth Wave", output_iir_df2, 10);

    /* --- 5. Triangle Wave --- */
    generate_triangle(5.0, 1.0, 100.0, NUM_SAMPLES, input);
    print_array("Input Triangle Wave", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Triangle Wave", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Triangle Wave", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Triangle Wave", output_iir_df2, 10);

    /* --- 6. Impulse Signal --- */
    generate_impulse(NUM_SAMPLES, 64, 1.0, input);
    print_array("Input Impulse Signal", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Impulse Signal", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Impulse Signal", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Impulse Signal", output_iir_df2, 10);

    /* --- 7. Step Signal --- */
    generate_step(NUM_SAMPLES, 64, 1.0, input);
    print_array("Input Step Signal", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Step Signal", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Step Signal", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Step Signal", output_iir_df2, 10);

    /* --- 8. Chirp Signal --- */
    generate_chirp(1.0, 10.0, 1.0, 100.0, NUM_SAMPLES, input);
    print_array("Input Chirp Signal", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Chirp Signal", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Chirp Signal", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Chirp Signal", output_iir_df2, 10);

    /* --- 9. White Noise Signal --- */
    generate_white_noise(1.0, NUM_SAMPLES, input);
    print_array("Input White Noise", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered White Noise", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered White Noise", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered White Noise", output_iir_df2, 10);

    /* --- 10. Pink Noise Signal --- */
    generate_pink_noise(1.0, NUM_SAMPLES, input);
    print_array("Input Pink Noise", input, 10);
    fir_filter_process(input, output_fir, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    print_array("FIR Filtered Pink Noise", output_fir, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df1(input, output_iir_df1, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df1);
    print_array("IIR DF1 Filtered Pink Noise", output_iir_df1, 10);
    state_df1[0] = state_df2[0] = 0.0;
    iir_filter_df2(input, output_iir_df2, NUM_SAMPLES, iir_b, 1, iir_a, 1, state_df2);
    print_array("IIR DF2 Filtered Pink Noise", output_iir_df2, 10);

    return 0;
}
