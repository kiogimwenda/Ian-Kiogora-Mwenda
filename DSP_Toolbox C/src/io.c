#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int write_signal_to_csv(const char *filename, const double *signal, size_t len) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;
    for (size_t i = 0; i < len; i++) {
        if (fprintf(fp, "%f\n", signal[i]) < 0) {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

int read_signal_from_csv(const char *filename, double *signal, size_t max_len, size_t *out_len) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;
    size_t count = 0;
    while (count < max_len && fscanf_s(fp, "%lf", &signal[count]) == 1) {
        count++;
    }
    fclose(fp);
    if (out_len) *out_len = count;
    return 0;
}
