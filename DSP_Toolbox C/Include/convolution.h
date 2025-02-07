#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform linear convolution of two signals.
 * The output length will be x_len + h_len - 1.
 * @param x Input signal array of length x_len.
 * @param x_len Length of input signal.
 * @param h Impulse response array of length h_len.
 * @param h_len Length of impulse response.
 * @param y Output array (should be allocated with length at least x_len + h_len - 1).
 */
void linear_convolution(const double *x, size_t x_len,
                        const double *h, size_t h_len,
                        double *y);

#ifdef __cplusplus
}
#endif

#endif /* CONVOLUTION_H */
