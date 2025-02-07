#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#include <stddef.h>  // for size_t

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generates a sine wave.
 * @param frequency Frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param phase Initial phase in radians.
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_sine(double frequency, double amplitude, double phase,
                   double sample_rate, size_t num_samples, double *output);

/**
 * Generates a cosine wave.
 * @param frequency Frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param phase Initial phase in radians.
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_cosine(double frequency, double amplitude, double phase,
                     double sample_rate, size_t num_samples, double *output);

/**
 * Generates a square wave.
 * @param frequency Frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param duty_cycle Duty cycle (between 0.0 and 1.0; 0.5 gives a 50% square wave).
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_square(double frequency, double amplitude, double duty_cycle,
                     double sample_rate, size_t num_samples, double *output);

/**
 * Generates a sawtooth wave (rising ramp).
 * @param frequency Frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_sawtooth(double frequency, double amplitude,
                       double sample_rate, size_t num_samples, double *output);

/**
 * Generates a triangle wave.
 * @param frequency Frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_triangle(double frequency, double amplitude,
                       double sample_rate, size_t num_samples, double *output);

/**
 * Generates an impulse signal.
 * @param num_samples Total number of samples.
 * @param impulse_index Index at which the impulse occurs (0 <= impulse_index < num_samples).
 * @param amplitude Amplitude of the impulse.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_impulse(size_t num_samples, size_t impulse_index,
                      double amplitude, double *output);

/**
 * Generates a step function.
 * @param num_samples Total number of samples.
 * @param step_index Index at which the step occurs.
 * @param amplitude Value after the step (the samples before step_index are 0).
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_step(size_t num_samples, size_t step_index,
                   double amplitude, double *output);

/**
 * Generates a linear chirp signal.
 * @param f0 Starting frequency in Hz.
 * @param f1 Ending frequency in Hz.
 * @param amplitude Peak amplitude.
 * @param sample_rate Sample rate in Hz.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_chirp(double f0, double f1, double amplitude,
                    double sample_rate, size_t num_samples, double *output);

/**
 * Generates white noise.
 * @param amplitude Maximum amplitude (the noise will be in the range [-amplitude, amplitude]).
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_white_noise(double amplitude, size_t num_samples, double *output);

/**
 * Generates pink noise using a simple IIR filtering method (Paul Kellet’s algorithm).
 * @param amplitude Scaling factor for the noise.
 * @param num_samples Number of samples to generate.
 * @param output Pointer to an array of at least num_samples doubles.
 */
void generate_pink_noise(double amplitude, size_t num_samples, double *output);

#ifdef __cplusplus
}
#endif

#endif /* SIGNAL_GENERATOR_H */
