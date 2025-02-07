#include "fir_filter.h"
#include <math.h>
#include <stdlib.h>

/* Define PI if not defined */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Apply an FIR filter using a direct convolution method.
   For each output sample n, compute:
       y[n] = sum_{k=0}^{num_coeffs-1} coeffs[k] * x[n-k]
   with x[m] = 0 for m < 0.
*/
void fir_filter_process(const double* input, double* output, size_t input_length,
                        const double* coeffs, size_t num_coeffs)
{
    for (size_t n = 0; n < input_length; n++) {
        double acc = 0.0;
        for (size_t k = 0; k < num_coeffs; k++) {
            if (n >= k) {
                acc += coeffs[k] * input[n - k];
            }
        }
        output[n] = acc;
    }
}

/* Helper: sinc function.
   sinc(x) = sin(pi*x)/(pi*x) for x != 0, and 1 when x == 0.
*/
static double sinc(double x) {
    if (fabs(x) < 1e-8)
        return 1.0;
    return sin(M_PI * x) / (M_PI * x);
}

/* Design a low-pass FIR filter using the windowed-sinc method.
   The ideal low-pass filter impulse response is:
       h[n] = 2*cutoff * sinc(2*cutoff*(n - (num_taps-1)/2))
   This function multiplies the ideal impulse response by the provided window.
*/
void fir_design_lowpass(double cutoff, size_t num_taps, const double* window, double* coeffs_out)
{
    if (num_taps < 1) return;
    double M = (double)(num_taps - 1);
    for (size_t n = 0; n < num_taps; n++) {
        double x = (double)n - M / 2.0;
        double ideal = 2.0 * cutoff * sinc(2.0 * cutoff * x);
        double win = (window != NULL) ? window[n] : 1.0;
        coeffs_out[n] = ideal * win;
    }
}

/* Generate a Hamming window.
   For n = 0,...,num_taps-1:
       w[n] = 0.54 - 0.46*cos(2*pi*n/(num_taps-1))
*/
void generate_hamming_window(size_t num_taps, double* window)
{
    if (num_taps < 1) return;
    for (size_t n = 0; n < num_taps; n++) {
        window[n] = 0.54 - 0.46 * cos((2.0 * M_PI * n) / (num_taps - 1));
    }
}
