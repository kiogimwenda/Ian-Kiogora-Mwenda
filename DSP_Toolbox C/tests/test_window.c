#include <stdio.h>
#include "window.h"

#define N 16

void print_array(const char* title, const double *arr, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, arr[i]);
    }
    printf("\n");
}

int main(void) {
    double hamming[N], hanning[N], blackman[N], rectangular[N];

    generate_hamming_window(N, hamming);
    generate_hanning_window(N, hanning);
    generate_blackman_window(N, blackman);
    generate_rectangular_window(N, rectangular);

    print_array("Hamming Window", hamming, N);
    print_array("Hanning Window", hanning, N);
    print_array("Blackman Window", blackman, N);
    print_array("Rectangular Window", rectangular, N);

    return 0;
}
