#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "signal_generator.h"

#define NUM_SAMPLES 64
#define FILENAME "test_signal.csv"

void print_signal(const char* title, const double *signal, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, signal[i]);
    }
    printf("\n");
}

int main(void) {
    double signal[NUM_SAMPLES];
    double read_signal_buf[NUM_SAMPLES];
    size_t read_len = 0;

    /* Generate a sine wave */
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Generated Signal", signal, NUM_SAMPLES);

    /* Write the signal to a CSV file */
    if (write_signal_to_csv(FILENAME, signal, NUM_SAMPLES) != 0) {
        fprintf(stderr, "Error writing signal to file.\n");
        return -1;
    }
    printf("Signal written to %s\n\n", FILENAME);

    /* Read the signal back from the CSV file */
    if (read_signal_from_csv(FILENAME, read_signal_buf, NUM_SAMPLES, &read_len) != 0) {
        fprintf(stderr, "Error reading signal from file.\n");
        return -1;
    }
    print_signal("Read Signal", read_signal_buf, read_len);

    return 0;
}
