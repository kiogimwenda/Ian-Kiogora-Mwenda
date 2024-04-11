// iir_filter.c
#include "iir_filter.h"

Signal iir_filter(Signal input, const float* b, const float* a, int order) {
    Signal output;
    output.length = input.length;
    output.samples = (float*)malloc(input.length * sizeof(float));

    float* x = input.samples;
    float* y = output.samples;
    const float* b_coef = b;
    const float* a_coef = a;

    y[0] = b_coef[0] * x[0];
    for (int i = 1; i < input.length; i++) {
        y[i] = 0.0;
        for (int j = 0; j <= i; j++) {
            if (i - j < 0) {
                continue;
            }
            if (j == 0) {
                y[i] += b_coef[j] * x[i];
            } else {
                y[i] += b_coef[j] * x[i - j] - a_coef[j] * y[i - j];
            }
        }
    }

    return output;
}