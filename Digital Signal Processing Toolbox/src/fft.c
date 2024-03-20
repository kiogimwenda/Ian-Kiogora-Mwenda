// fft.c
#include "fft.h"
#include <math.h>

static void bitReverse(float* real, float* imag, int n) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit))
            bit >>= 1;
        if (i < j) {
            float temp_real = real[i];
            float temp_imag = imag[i];
            real[i] = real[j];
            imag[i] = imag[j];
            real[j] = temp_real;
            imag[j] = temp_imag;
        }
    }
}

void fft(float* real, float* imag, int n) {
    bitReverse(real, imag, n);

    for (int len = 2; len <= n; len <<= 1) {
        float angle = 2 * M_PI / len;
        float w_real = cos(angle);
        float w_imag = sin(angle);

        for (int i = 0; i < n; i += len) {
            float w_curr_real = 1.0;
            float w_curr_imag = 0.0;

            for (int j = 0; j < len / 2; j++) {
                float u_real = real[i + j];
                float u_imag = imag[i + j];
                float v_real = w_curr_real * real[i + j + len / 2] - w_curr_imag * imag[i + j + len / 2];
                float v_imag = w_curr_real * imag[i + j + len / 2] + w_curr_imag * real[i + j + len / 2];

                real[i + j] = u_real + v_real;
                imag[i + j] = u_imag + v_imag;
                real[i + j + len / 2] = u_real - v_real;
                imag[i + j + len / 2] = u_imag - v_imag;

                float next_w_real = w_curr_real * w_real - w_curr_imag * w_imag;
                w_curr_imag = w_curr_real * w_imag + w_curr_imag * w_real;
                w_curr_real = next_w_real;
            }
        }
    }
}
