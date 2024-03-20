// bandpass_filter.h
#ifndef BANDPASS_FILTER_H
#define BANDPASS_FILTER_H

void applyBandPassFilter(float* signal, int numSamples, float lowCutoff, float highCutoff, float sampleRate);

#endif
