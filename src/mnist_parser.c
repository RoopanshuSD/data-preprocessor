#include <stdio.h>
#include <stdlib.h>
#include "mnist_parser.h"

int read_int(FILE *f) {
    unsigned char bytes[4];
    fread(bytes, sizeof(bytes), 1, f);
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

int process_mnist(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    if (!in) return -1;

    int magic = read_int(in);
    int num_images = read_int(in);
    int rows = read_int(in);
    int cols = read_int(in);

    FILE *out = fopen(output_file, "w");
    if (!out) return -1;

    unsigned char *image = malloc(rows * cols);
    for (int i = 0; i < num_images; i++) {
        fread(image, rows * cols, 1, in);
        for (int j = 0; j < rows * cols; j++) {
            fprintf(out, "%d%s", image[j], (j + 1 == rows * cols) ? "\n" : ",");
        }
    }

    fclose(in);
    fclose(out);
    free(image);

    return 0;
}