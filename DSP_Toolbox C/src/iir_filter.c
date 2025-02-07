#include "iir_filter.h"

/* Direct Form I IIR filtering.
   For each sample n:
       y[n] = sum_{k=0}^{M} b[k]*x[n-k] - sum_{k=1}^{N} a[k]*y[n-k]
   with the convention that x[] and y[] for indices < 0 are taken from the provided state.
   The state array is assumed to hold previous inputs and outputs for initial conditions.
   (In practice, you should zero-initialize state on the first call.)
*/
void iir_filter_df1(const double* input, double* output, size_t input_length,
                    const double* b, size_t M, const double* a, size_t N,
                    double* state)
{
    size_t state_len = (M > N ? M : N);
    for (size_t n = 0; n < input_length; n++) {
        double acc = b[0] * input[n];
        // Accumulate contributions from past inputs
        for (size_t k = 1; k <= M; k++) {
            double x_val = (n >= k) ? input[n - k] : state[state_len - k];
            acc += b[k] * x_val;
        }
        // Subtract contributions from past outputs
        for (size_t k = 1; k <= N; k++) {
            double y_val = (n >= k) ? output[n - k] : state[state_len - k];
            acc -= a[k] * y_val;
        }
        output[n] = acc;
    }
}

/* Direct Form II Transposed IIR filtering.
   This algorithm uses a state vector d[0...L-1] (L = max(M, N)) and computes for each sample:
       y = b[0]*x + d[0]
       For k = 0 to L-2: d[k] = d[k+1] + b[k+1]*x - a[k+1]*y
       d[L-1] = b[L]*x - a[L]*y
   It is assumed that the state vector is zero-initialized on the first call.
*/
void iir_filter_df2(const double* input, double* output, size_t input_length,
                    const double* b, size_t M, const double* a, size_t N,
                    double* state)
{
    size_t L = (M > N ? M : N);  // Length of state vector
    for (size_t n = 0; n < input_length; n++) {
        double x = input[n];
        double y = b[0] * x + state[0];
        output[n] = y;
        for (size_t k = 0; k < L - 1; k++) {
            double b_next = (k + 1 <= M) ? b[k + 1] : 0.0;
            double a_next = (k + 1 <= N) ? a[k + 1] : 0.0;
            state[k] = state[k + 1] + b_next * x - a_next * y;
        }
        if (L > 0) {
            double b_last = (L <= M) ? b[L] : 0.0;
            double a_last = (L <= N) ? a[L] : 0.0;
            state[L - 1] = b_last * x - a_last * y;
        }
    }
}
