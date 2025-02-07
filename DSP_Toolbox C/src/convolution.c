#include "convolution.h"

void linear_convolution(const double *x, size_t x_len,
                        const double *h, size_t h_len,
                        double *y) {
    size_t y_len = x_len + h_len - 1;
    // Initialize output to zero.
    for (size_t i = 0; i < y_len; i++) {
        y[i] = 0.0;
    }
    // Convolve: y[n] = sum_{k=0}^{x_len-1} x[k]*h[n-k]
    for (size_t n = 0; n < y_len; n++) {
        for (size_t k = 0; k < x_len; k++) {
            if (n >= k && (n - k) < h_len) {
                y[n] += x[k] * h[n - k];
            }
        }
    }
}
