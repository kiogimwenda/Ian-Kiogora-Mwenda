#ifndef IIR_FILTER_H
#define IIR_FILTER_H

#include "signal_gen.h"

Signal iir_filter(Signal input, const float* b, const float* a, int order);

#endif //