/* test_signal_generator.c
 *
 * This test program demonstrates the use of the signal generation module.
 * It calls each signal generator function and prints the first NUM_SAMPLES
 * of each generated signal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "signal_gen.h"

#define NUM_SAMPLES 500

/* Helper function to print a signal array */
void print_signal(const char *title, double *signal, size_t num_samples) {
    printf("=== %s ===\n", title);
    for (size_t i = 0; i < num_samples; i++) {
        printf("%3zu: %f\n", i, signal[i]);
    }
    printf("\n");
}

int main(void) {
    double signal[NUM_SAMPLES];

    /* Seed the random number generator for noise functions */
    srand((unsigned int)time(NULL));

    /* Sine wave: 5 Hz sine with amplitude 1, sample rate 100 Hz */
    generate_sine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Sine Wave", signal, NUM_SAMPLES);

    /* Cosine wave: 5 Hz cosine with amplitude 1, sample rate 100 Hz */
    generate_cosine(5.0, 1.0, 0.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Cosine Wave", signal, NUM_SAMPLES);

    /* Square wave: 5 Hz, amplitude 1, 50% duty cycle */
    generate_square(5.0, 1.0, 0.5, 100.0, NUM_SAMPLES, signal);
    print_signal("Square Wave", signal, NUM_SAMPLES);

    /* Sawtooth wave: 5 Hz rising sawtooth, amplitude 1 */
    generate_sawtooth(5.0, 1.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Sawtooth Wave", signal, NUM_SAMPLES);

    /* Triangle wave: 5 Hz, amplitude 1 */
    generate_triangle(5.0, 1.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Triangle Wave", signal, NUM_SAMPLES);

    /* Impulse: an impulse at index 50 of a 100-sample signal */
    generate_impulse(NUM_SAMPLES, 50, 1.0, signal);
    print_signal("Impulse Signal", signal, NUM_SAMPLES);

    /* Step: a step occurring at index 50 */
    generate_step(NUM_SAMPLES, 50, 1.0, signal);
    print_signal("Step Signal", signal, NUM_SAMPLES);

    /* Chirp: frequency sweeping linearly from 1 Hz to 10 Hz */
    generate_chirp(1.0, 10.0, 1.0, 100.0, NUM_SAMPLES, signal);
    print_signal("Chirp Signal", signal, NUM_SAMPLES);

    /* White Noise: random values in [-1, 1] scaled by amplitude 1 */
    generate_white_noise(1.0, NUM_SAMPLES, signal);
    print_signal("White Noise", signal, NUM_SAMPLES);

    /* Pink Noise: using the simple IIR approach */
    generate_pink_noise(1.0, NUM_SAMPLES, signal);
    print_signal("Pink Noise", signal, NUM_SAMPLES);

    return 0;
}
