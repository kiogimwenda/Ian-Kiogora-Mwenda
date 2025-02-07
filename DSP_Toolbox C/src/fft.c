#include "fft.h"
#include <math.h>

/* Define PI if not already defined */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* 
 * Helper: Bit reversal permutation.
 * Rearranges the elements of x into bit-reversed order.
 */
static void bit_reverse(Complex *x, size_t n) {
    size_t i, j, k;
    for (i = 0, j = 0; i < n; i++) {
        if (i < j) {
            Complex temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
        k = n >> 1;
        while (k <= j && k > 0) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

/*
 * Compute the FFT in-place using an iterative Cooley-Tukey algorithm.
 */
void fft(Complex *x, size_t n) {
    bit_reverse(x, n);
    
    // m is the current sub-FFT size (starting at 2, doubling each stage)
    for (size_t m = 2; m <= n; m *= 2) {
        double theta = -2.0 * M_PI / m;
        Complex wm;
        wm.re = cos(theta);
        wm.im = sin(theta);
        
        for (size_t k = 0; k < n; k += m) {
            Complex w = {1.0, 0.0};
            for (size_t j = 0; j < m / 2; j++) {
                // t = w * x[k+j+m/2]
                Complex t;
                t.re = w.re * x[k + j + m/2].re - w.im * x[k + j + m/2].im;
                t.im = w.re * x[k + j + m/2].im + w.im * x[k + j + m/2].re;
                
                // u = x[k+j]
                Complex u = x[k + j];
                
                // Butterfly computations:
                x[k + j].re = u.re + t.re;
                x[k + j].im = u.im + t.im;
                x[k + j + m/2].re = u.re - t.re;
                x[k + j + m/2].im = u.im - t.im;
                
                // Update w: w = w * wm
                double temp_re = w.re * wm.re - w.im * wm.im;
                w.im = w.re * wm.im + w.im * wm.re;
                w.re = temp_re;
            }
        }
    }
}

/*
 * Compute the inverse FFT (IFFT) in-place.
 * This is done by conjugating the input, performing an FFT, and then conjugating
 * and scaling the result.
 */
void ifft(Complex *x, size_t n) {
    // Take conjugate of the input array.
    for (size_t i = 0; i < n; i++) {
        x[i].im = -x[i].im;
    }
    
    // Compute forward FFT.
    fft(x, n);
    
    // Take conjugate again and scale by 1/n.
    for (size_t i = 0; i < n; i++) {
        x[i].re = x[i].re / n;
        x[i].im = -x[i].im / n;
    }
}
