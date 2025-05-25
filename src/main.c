#include <stdio.h>
#include <string.h>
#include "bmp_parser.h"
#include "mnist_parser.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s [bmp|mnist] <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "bmp") == 0) {
        if (process_bmp(argv[2], argv[3]) != 0) {
            fprintf(stderr, "Failed to process BMP file\n");
            return 1;
        }
    } else if (strcmp(argv[1], "mnist") == 0) {
        if (process_mnist(argv[2], argv[3]) != 0) {
            fprintf(stderr, "Failed to process MNIST file\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Unknown format: %s\n", argv[1]);
        return 1;
    }

    printf("File processed successfully.\n");
    return 0;
}