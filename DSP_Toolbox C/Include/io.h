#ifndef IO_H
#define IO_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Write a signal to a CSV file.
 * Each line of the file contains one sample.
 * @param filename Name of the file to write.
 * @param signal Array of signal samples.
 * @param len Number of samples.
 * @return 0 on success, nonzero on error.
 */
int write_signal_to_csv(const char *filename, const double *signal, size_t len);

/**
 * Read a signal from a CSV file.
 * Assumes one sample per line.
 * @param filename Name of the file to read.
 * @param signal Pre-allocated array to store samples (max length max_len).
 * @param max_len Maximum number of samples to read.
 * @param out_len Pointer to a variable to store the number of samples read.
 * @return 0 on success, nonzero on error.
 */
int read_signal_from_csv(const char *filename, double *signal, size_t max_len, size_t *out_len);

#ifdef __cplusplus
}
#endif

#endif /* IO_H */
