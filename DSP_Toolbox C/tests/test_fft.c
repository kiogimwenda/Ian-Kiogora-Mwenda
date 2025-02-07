#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "signal_gen.h"
#include "fir_filter.h"
#include "fft.h"

#define NUM_SAMPLES 128  // Must be a power of two for our FFT implementation
#define FIR_TAPS 31

/* Helper: Print a complex array's contents (index, real, imag, magnitude) */
void print_fft_output(const Complex *x, size_t n) {
    printf("Index   Real        Imaginary       Magnitude\n");
    for (size_t i = 0; i < n; i++) {
        double mag = sqrt(x[i].re * x[i].re + x[i].im * x[i].im);
        printf("%3zu:   %10.5f   %10.5f   %10.5f\n", i, x[i].re, x[i].im, mag);
    }
    printf("\n");
}

int main(void) {
    double time_signal[NUM_SAMPLES];
    double filtered_signal[NUM_SAMPLES];
    double fir_coeffs[FIR_TAPS];
    double window[FIR_TAPS];
    Complex fft_input[NUM_SAMPLES];

    /* 
     * Step 1: Generate a time-domain signal.
     * For example, create a 5 Hz sine wave (sample rate 100 Hz) 
     */
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, time_signal);
    
    /* 
     * Step 2: Design a low-pass FIR filter using the windowed-sinc method.
     * We first generate a Hamming window and then design the filter.
     */
    double cutoff = 0.1;  // Normalized cutoff frequency (0 < cutoff < 0.5)
    generate_hamming_window(FIR_TAPS, window);
    fir_design_lowpass(cutoff, FIR_TAPS, window, fir_coeffs);
    
    /* 
     * Step 3: Apply the FIR filter to the generated time-domain signal.
     */
    fir_filter_process(time_signal, filtered_signal, NUM_SAMPLES, fir_coeffs, FIR_TAPS);
    
    /*
     * Step 4: Convert the filtered signal into a complex array.
     * For FFT processing, we create an array where each element's real part
     * is the filtered sample and the imaginary part is set to zero.
     */
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
        fft_input[i].re = filtered_signal[i];
        fft_input[i].im = 0.0;
    }
    
    /* 
     * Step 5: Compute the FFT of the filtered (complex) signal.
     */
    fft(fft_input, NUM_SAMPLES);
    
    /* Print the FFT output */
    printf("FFT of the FIR-filtered signal:\n");
    print_fft_output(fft_input, NUM_SAMPLES);
    
    /* 
     * (Optional) Step 6: Perform an inverse FFT to recover the time-domain signal.
     * This should yield a result that closely matches the filtered signal.
     */
    ifft(fft_input, NUM_SAMPLES);
    
    printf("Recovered time-domain signal after IFFT:\n");
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
        printf("%3zu: %f\n", i, fft_input[i].re);
    }
    
    return 0;
}
