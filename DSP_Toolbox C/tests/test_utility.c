#include <stdio.h>
#include "utility.h"

#define LEN 8

int main(void) {
    double vec[LEN] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    print_vector("Test Vector", vec, LEN);

    for (size_t i = 0; i < 20; i++) {
        printf("Is %zu a power of two? %s\n", i, is_power_of_two(i) ? "Yes" : "No");
    }
    return 0;
}
