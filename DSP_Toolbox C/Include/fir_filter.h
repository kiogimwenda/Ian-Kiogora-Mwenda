#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Apply an FIR filter to an input signal.
 *
 * This function implements a direct convolution filtering:
 *   y[n] = sum_{k=0}^{num_coeffs-1} coeffs[k] * x[n-k]
 * with the convention that x[n-k] is assumed zero for n < k.
 *
 * @param input Pointer to the input signal array.
 * @param output Pointer to the output signal array (at least input_length elements).
 * @param input_length Length of the input signal.
 * @param coeffs Pointer to the FIR filter coefficients.
 * @param num_coeffs Number of FIR coefficients.
 */
void fir_filter_process(const double* input, double* output, size_t input_length,
                        const double* coeffs, size_t num_coeffs);

/**
 * Design a low-pass FIR filter using the windowed-sinc method.
 *
 * The ideal impulse response for a low-pass filter is:
 *    h[n] = 2*cutoff * sinc(2*cutoff*(n - (num_taps-1)/2))
 * which is then multiplied by a window.
 *
 * @param cutoff Normalized cutoff frequency (0 < cutoff < 0.5, where 1 corresponds to Nyquist).
 * @param num_taps Number of taps (filter coefficients) to design.
 * @param window Pointer to a window array of length num_taps (if NULL, a rectangular window is used).
 * @param coeffs_out Pointer to an array (length num_taps) where coefficients will be stored.
 */
void fir_design_lowpass(double cutoff, size_t num_taps, const double* window, double* coeffs_out);

/**
 * Generate a Hamming window.
 *
 * The Hamming window is defined as:
 *    w[n] = 0.54 - 0.46*cos(2*pi*n/(N-1)) for n=0,...,N-1.
 *
 * @param num_taps Number of points in the window.
 * @param window Pointer to an array (length num_taps) where the window values will be stored.
 */
void generate_hamming_window(size_t num_taps, double* window);

#ifdef __cplusplus
}
#endif

#endif /* FIR_FILTER_H */
