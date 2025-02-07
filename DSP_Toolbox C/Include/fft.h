#ifndef FFT_H
#define FFT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A simple complex number structure.
 */
typedef struct {
    double re;  /**< Real part */
    double im;  /**< Imaginary part */
} Complex;

/**
 * Compute the Fast Fourier Transform (FFT) in-place.
 *
 * The function computes the FFT of an array of Complex numbers.
 * The number of points, n, must be a power of two.
 *
 * @param x Pointer to an array of Complex numbers (length n).
 * @param n Number of points (must be a power of two).
 */
void fft(Complex *x, size_t n);

/**
 * Compute the Inverse Fast Fourier Transform (IFFT) in-place.
 *
 * The function computes the IFFT of an array of Complex numbers.
 * The number of points, n, must be a power of two.
 *
 * @param x Pointer to an array of Complex numbers (length n).
 * @param n Number of points (must be a power of two).
 */
void ifft(Complex *x, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* FFT_H */
