#ifndef UTILITY_H
#define UTILITY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a vector of doubles.
 */
void print_vector(const char *title, const double *vec, size_t len);

/**
 * Check if a number is a power of two.
 * Returns 1 if true, 0 otherwise.
 */
int is_power_of_two(size_t n);

#ifdef __cplusplus
}
#endif

#endif /* UTILITY_H */
