#include "utility.h"
#include <stdio.h>

void print_vector(const char *title, const double *vec, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, vec[i]);
    }
    printf("\n");
}

int is_power_of_two(size_t n) {
    if (n == 0) return 0;
    return (n & (n - 1)) == 0;
}
