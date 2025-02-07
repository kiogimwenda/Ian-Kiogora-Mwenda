#include "modulation.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void am_modulate(const double *message, size_t len, 
                 double carrier_freq, double sample_rate,
                 double modulation_index, double *modulated) {
    for (size_t n = 0; n < len; n++) {
        double t = (double)n / sample_rate;
        modulated[n] = (1.0 + modulation_index * message[n]) * cos(2.0 * M_PI * carrier_freq * t);
    }
}

void fm_modulate(const double *message, size_t len, 
                 double carrier_freq, double sample_rate,
                 double freq_dev, double *modulated) {
    double phase = 0.0;
    double dt = 1.0 / sample_rate;
    for (size_t n = 0; n < len; n++) {
        phase += 2.0 * M_PI * freq_dev * message[n] * dt;
        double t = (double)n / sample_rate;
        modulated[n] = cos(2.0 * M_PI * carrier_freq * t + phase);
    }
}
