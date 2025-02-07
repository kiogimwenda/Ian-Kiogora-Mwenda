#ifndef MODULATION_H
#define MODULATION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform Amplitude Modulation (AM) on a baseband message signal.
 * modulated[n] = (1 + modulation_index * message[n]) * cos(2*pi*carrier_freq*n/sample_rate)
 *
 * @param message Input message signal array.
 * @param len Length of the message signal.
 * @param carrier_freq Carrier frequency in Hz.
 * @param sample_rate Sample rate in Hz.
 * @param modulation_index Modulation index.
 * @param modulated Output array (length len) to store modulated signal.
 */
void am_modulate(const double *message, size_t len, 
                 double carrier_freq, double sample_rate,
                 double modulation_index, double *modulated);

/**
 * Perform Frequency Modulation (FM) on a baseband message signal.
 * For simplicity, we assume discrete integration of the message.
 *
 * modulated[n] = cos(2*pi*carrier_freq*n/sample_rate + 2*pi*freq_dev*integral(message))
 *
 * @param message Input message signal array.
 * @param len Length of the message signal.
 * @param carrier_freq Carrier frequency in Hz.
 * @param sample_rate Sample rate in Hz.
 * @param freq_dev Frequency deviation factor.
 * @param modulated Output array (length len) to store modulated signal.
 */
void fm_modulate(const double *message, size_t len, 
                 double carrier_freq, double sample_rate,
                 double freq_dev, double *modulated);

#ifdef __cplusplus
}
#endif

#endif /* MODULATION_H */
