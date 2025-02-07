#ifndef IIR_FILTER_H
#define IIR_FILTER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Apply an IIR filter using Direct Form I.
 *
 * The filter difference equation is:
 *   y[n] = (b[0]*x[n] + b[1]*x[n-1] + ... + b[M]*x[n-M]) -
 *          (a[1]*y[n-1] + ... + a[N]*y[n-N])
 * where a[0] is assumed to be 1.0.
 *
 * @param input Pointer to the input signal array.
 * @param output Pointer to the output signal array (at least input_length elements).
 * @param input_length Length of the input signal.
 * @param b Pointer to numerator coefficients (length M+1).
 * @param M Number of numerator coefficients minus one.
 * @param a Pointer to denominator coefficients (length N+1, with a[0] = 1.0).
 * @param N Number of denominator coefficients minus one.
 * @param state Pointer to an array to hold filter state (length >= max(M, N)).
 *              This array must be zero-initialized before the first call.
 */
void iir_filter_df1(const double* input, double* output, size_t input_length,
                    const double* b, size_t M, const double* a, size_t N,
                    double* state);

/**
 * Apply an IIR filter using the Direct Form II Transposed structure.
 *
 * This implementation uses a state vector of length L = max(M, N).
 * It assumes a[0] = 1.0.
 *
 * @param input Pointer to the input signal array.
 * @param output Pointer to the output signal array.
 * @param input_length Length of the input signal.
 * @param b Pointer to numerator coefficients (length M+1).
 * @param M Number of numerator coefficients minus one.
 * @param a Pointer to denominator coefficients (length N+1, with a[0] = 1.0).
 * @param N Number of denominator coefficients minus one.
 * @param state Pointer to an array for the filter state (length L).
 *              Initialize to zero before first call.
 */
void iir_filter_df2(const double* input, double* output, size_t input_length,
                    const double* b, size_t M, const double* a, size_t N,
                    double* state);

#ifdef __cplusplus
}
#endif

#endif /* IIR_FILTER_H */
