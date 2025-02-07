#include "window.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void generate_hanning_window(size_t N, double *window) {
    if (N < 1) return;
    for (size_t n = 0; n < N; n++) {
        window[n] = 0.5 * (1 - cos((2.0 * M_PI * n) / (N - 1)));
    }
}

void generate_blackman_window(size_t N, double *window) {
    if (N < 1) return;
    for (size_t n = 0; n < N; n++) {
        window[n] = 0.42 - 0.5 * cos((2.0 * M_PI * n) / (N - 1)) + 0.08 * cos((4.0 * M_PI * n) / (N - 1));
    }
}

void generate_rectangular_window(size_t N, double *window) {
    for (size_t n = 0; n < N; n++) {
        window[n] = 1.0;
    }
}
