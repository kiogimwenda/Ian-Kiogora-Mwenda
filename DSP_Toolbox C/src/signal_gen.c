#include "signal_gen.h"
#include <math.h>
#include <stdlib.h>

/* Define PI if not defined */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*-----------------------------------------------------------------------------
 * Function: generate_sine
 * Description: Generates a sine wave.
 *---------------------------------------------------------------------------*/
void generate_sine(double frequency, double amplitude, double phase,
                   double sample_rate, size_t num_samples, double *output)
{
    double dt = 1.0 / sample_rate;
    for (size_t i = 0; i < num_samples; i++) {
        double t = i * dt;
        output[i] = amplitude * sin(2.0 * M_PI * frequency * t + phase);
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_cosine
 * Description: Generates a cosine wave.
 *---------------------------------------------------------------------------*/
void generate_cosine(double frequency, double amplitude, double phase,
                     double sample_rate, size_t num_samples, double *output)
{
    double dt = 1.0 / sample_rate;
    for (size_t i = 0; i < num_samples; i++) {
        double t = i * dt;
        output[i] = amplitude * cos(2.0 * M_PI * frequency * t + phase);
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_square
 * Description: Generates a square wave with specified duty cycle.
 *---------------------------------------------------------------------------*/
void generate_square(double frequency, double amplitude, double duty_cycle,
                     double sample_rate, size_t num_samples, double *output)
{
    double period = sample_rate / frequency;
    for (size_t i = 0; i < num_samples; i++) {
        double pos_in_period = fmod((double)i, period);
        if (pos_in_period < duty_cycle * period) {
            output[i] = amplitude;
        } else {
            output[i] = -amplitude;
        }
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_sawtooth
 * Description: Generates a rising sawtooth wave.
 *---------------------------------------------------------------------------*/
void generate_sawtooth(double frequency, double amplitude,
                       double sample_rate, size_t num_samples, double *output)
{
    double period = sample_rate / frequency;
    for (size_t i = 0; i < num_samples; i++) {
        double pos = fmod((double)i, period);
        output[i] = amplitude * ((2.0 * pos / period) - 1.0);
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_triangle
 * Description: Generates a triangle wave.
 *---------------------------------------------------------------------------*/
void generate_triangle(double frequency, double amplitude,
                       double sample_rate, size_t num_samples, double *output)
{
    double period = sample_rate / frequency;
    for (size_t i = 0; i < num_samples; i++) {
        double pos = fmod((double)i, period);
        double value;
        if (pos < period / 2.0) {
            value = (2.0 * pos / (period)) ;
        } else {
            value = 2.0 - (2.0 * pos / (period));
        }
        output[i] = amplitude * (value - 0.5) * 2.0;  // scales to [-amplitude, amplitude]
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_impulse
 * Description: Generates an impulse signal (all zeros except one sample).
 *---------------------------------------------------------------------------*/
void generate_impulse(size_t num_samples, size_t impulse_index,
                      double amplitude, double *output)
{
    for (size_t i = 0; i < num_samples; i++) {
        output[i] = 0.0;
    }
    if (impulse_index < num_samples) {
        output[impulse_index] = amplitude;
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_step
 * Description: Generates a step function.
 *---------------------------------------------------------------------------*/
void generate_step(size_t num_samples, size_t step_index,
                   double amplitude, double *output)
{
    for (size_t i = 0; i < num_samples; i++) {
        output[i] = (i >= step_index) ? amplitude : 0.0;
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_chirp
 * Description: Generates a linear chirp signal.
 *---------------------------------------------------------------------------*/
void generate_chirp(double f0, double f1, double amplitude,
                    double sample_rate, size_t num_samples, double *output)
{
    double T = num_samples / sample_rate;
    double dt = 1.0 / sample_rate;
    double k = (f1 - f0) / T; // frequency sweep rate (Hz per second)
    for (size_t i = 0; i < num_samples; i++) {
        double t = i * dt;
        /* instantaneous phase = 2*pi*(f0*t + 0.5*k*t*t) */
        double phase = 2.0 * M_PI * (f0 * t + 0.5 * k * t * t);
        output[i] = amplitude * sin(phase);
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_white_noise
 * Description: Generates white noise in the range [-amplitude, amplitude].
 *---------------------------------------------------------------------------*/
void generate_white_noise(double amplitude, size_t num_samples, double *output)
{
    for (size_t i = 0; i < num_samples; i++) {
        /* rand() returns an integer in [0, RAND_MAX] */
        double r = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
        output[i] = amplitude * r;
    }
}

/*-----------------------------------------------------------------------------
 * Function: generate_pink_noise
 * Description: Generates pink noise using an IIR filtering method.
 *              This implementation is based on Paul Kellet's algorithm.
 *---------------------------------------------------------------------------*/
void generate_pink_noise(double amplitude, size_t num_samples, double *output)
{
    /* Static state variables for the IIR filter */
    static double b0 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0;
    for (size_t i = 0; i < num_samples; i++) {
        double white = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
        b0 = 0.99886 * b0 + white * 0.0555179;
        b1 = 0.99332 * b1 + white * 0.0750759;
        b2 = 0.96900 * b2 + white * 0.1538520;
        b3 = 0.86650 * b3 + white * 0.3104856;
        b4 = 0.55000 * b4 + white * 0.5329522;
        b5 = -0.7616 * b5 - white * 0.0168980;
        double pink = b0 + b1 + b2 + b3 + b4 + b5 + b6 + white * 0.5362;
        b6 = white * 0.115926;
        /* Normalize pink noise (the constant here can be tuned) */
        output[i] = amplitude * pink * 0.11;
    }
}
