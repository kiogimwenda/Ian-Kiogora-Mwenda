#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modulation.h"
#include "signal_generator.h"  // We'll use a sine wave as a message signal

#define NUM_SAMPLES 128

void print_signal(const char* title, const double *signal, size_t len) {
    printf("%s:\n", title);
    for (size_t i = 0; i < len; i++) {
        printf("%3zu: %f\n", i, signal[i]);
    }
    printf("\n");
}

int main(void) {
    double message[NUM_SAMPLES];
    double am_output[NUM_SAMPLES];
    double fm_output[NUM_SAMPLES];

    /* Generate a baseband message: a 2 Hz sine wave with amplitude 0.5 */
    generate_sine(2.0, 0.5, 0.0, 100.0, NUM_SAMPLES, message);
    print_signal("Message Signal", message, 10);

    /* AM modulation: carrier 50 Hz, modulation index 0.8 */
    am_modulate(message, NUM_SAMPLES, 50.0, 100.0, 0.8, am_output);
    print_signal("AM Modulated Signal", am_output, 10);

    /* FM modulation: carrier 50 Hz, frequency deviation 5 Hz */
    fm_modulate(message, NUM_SAMPLES, 50.0, 100.0, 5.0, fm_output);
    print_signal("FM Modulated Signal", fm_output, 10);

    return 0;
}
