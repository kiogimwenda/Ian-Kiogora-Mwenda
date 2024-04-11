/*Project 9: Digital Signal Processing toolbox
Group 4 Members:
1. Jacob Kirigha    ENE212-0181/2021
2. Keith Maina      ENE212-0176/2021
3. Ian Kiogora      ENE212-0251/2021
4. Oiriga Junior    ENE212-0093/2021
5. Ezra Rono        ENE212-0084/2021
*/
#include "signal_gen.h"
#include "iir_filter.h"
#include "fft.h"
#include "convolution.h"

#include <stdio.h>

int main() {
    // Signal generation
    printf("Enter the signal type (sine, square, or triangle): ");
    char signal_type[20];
    scanf("%s", signal_type);
    printf("Enter the signal length: ");
    int length;
    scanf("%d", &length);
    Signal input = generate_signal(signal_type, length);

    // IIR filter
    printf("Enter the coefficients of the IIR filter (space-separated): ");
    float b[10];
    float a[10];
    for (int i = 0; i < 10; i++) {
        scanf("%f", &b[i]);
    }
    for (int i = 1; i < 10; i++) {
        scanf("%f", &a[i]);
    }
    Signal filtered = iir_filter(input, b, a, 9);

    // Convolution
    printf("Enter the length of the second signal: ");
    int h_length;
    scanf("%d", &h_length);
    Signal h = generate_signal("sine", h_length);
    Signal convolved = convolution(filtered, h);

    // FFT
    Signal fft_result = fft(convolved);
    printf("FFT result: ");
    for (int i = 0; i < fft_result.length; i++) {
        printf("%.4f + %.4fi\n", fft_result.samples[i].real, fft_result.samples[i].imag);
    }

    return 0;
}