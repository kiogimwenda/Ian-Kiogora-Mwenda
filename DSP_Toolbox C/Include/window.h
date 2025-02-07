#ifndef WINDOW_H
#define WINDOW_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generate a Hamming window.
 * w[n] = 0.54 - 0.46*cos(2*pi*n/(N-1)), n = 0,...,N-1.
 */
void generate_hamming_window(size_t N, double *window);

/**
 * Generate a Hanning (Hann) window.
 * w[n] = 0.5 * (1 - cos(2*pi*n/(N-1))), n = 0,...,N-1.
 */
void generate_hanning_window(size_t N, double *window);

/**
 * Generate a Blackman window.
 * w[n] = 0.42 - 0.5*cos(2*pi*n/(N-1)) + 0.08*cos(4*pi*n/(N-1)), n = 0,...,N-1.
 */
void generate_blackman_window(size_t N, double *window);

/**
 * Generate a rectangular window (all ones).
 */
void generate_rectangular_window(size_t N, double *window);

#ifdef __cplusplus
}
#endif

#endif /* WINDOW_H */
