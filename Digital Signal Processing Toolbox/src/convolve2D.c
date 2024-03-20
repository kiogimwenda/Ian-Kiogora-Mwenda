// convolve2D.c
#include "convolve2D.h"

void convolve2D(const float* inputImage, int numRows, int numCols, const float* kernel, int kernelSize, float* outputImage) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            outputImage[i * numCols + j] = 0.0f;
            for (int m = 0; m < kernelSize; m++) {
                for (int n = 0; n < kernelSize; n++) {
                    int rowIdx = i - m + kernelSize / 2;
                    int colIdx = j - n + kernelSize / 2;
                    if (rowIdx >= 0 && rowIdx < numRows && colIdx >= 0 && colIdx < numCols) {
                        outputImage[i * numCols + j] += inputImage[rowIdx * numCols + colIdx] * kernel[m * kernelSize + n];
                    }
                }
            }
        }
    }
}
