#include <stdio.h>
#include "convolution.h"

#define X_LEN 5
#define H_LEN 3

void print_signal(const char* title, const double *signal, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, signal[i]);
    }
    printf("\n");
}

int main(void) {
    double x[X_LEN] = {1, 2, 3, 4, 5};
    double h[H_LEN] = {1, 0, -1};
    size_t y_len = X_LEN + H_LEN - 1;
    double y[y_len];

    linear_convolution(x, X_LEN, h, H_LEN, y);
    print_signal("Input Signal x", x, X_LEN);
    print_signal("Impulse Response h", h, H_LEN);
    print_signal("Convolution Output y", y, y_len);

    return 0;
}
