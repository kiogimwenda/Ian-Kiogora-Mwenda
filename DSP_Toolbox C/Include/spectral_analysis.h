#ifndef SPECTRAL_ANALYSIS_H
#define SPECTRAL_ANALYSIS_H

#include <stddef.h>
#include "fft.h"  // Uses the Complex type defined in fft.h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compute the magnitude of each element in the FFT array.
 * @param fft_data Array of Complex numbers (length n).
 * @param n Number of points.
 * @param magnitude Output array (length n) to store magnitudes.
 */
void compute_magnitude(const Complex *fft_data, size_t n, double *magnitude);

/**
 * Compute the phase (in radians) of each element in the FFT array.
 * @param fft_data Array of Complex numbers (length n).
 * @param n Number of points.
 * @param phase Output array (length n) to store phase values.
 */
void compute_phase(const Complex *fft_data, size_t n, double *phase);

/**
 * Compute the power spectral density (PSD) from the FFT data.
 * PSD is computed as (magnitude^2)/n.
 * @param fft_data Array of Complex numbers (length n).
 * @param n Number of points.
 * @param psd Output array (length n) to store PSD values.
 */
void compute_psd(const Complex *fft_data, size_t n, double *psd);

#ifdef __cplusplus
}
#endif

#endif /* SPECTRAL_ANALYSIS_H */
