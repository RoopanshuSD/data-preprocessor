#include <stdio.h>
#include <stdlib.h>
#include "bmp_parser.h"

#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width, height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerM, yPixelsPerM;
    unsigned int colorsUsed;
    unsigned int importantColors;
} DIBHeader;
#pragma pack(pop)

int process_bmp(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    if (!in) return -1;

    BMPHeader bmp;
    DIBHeader dib;
    fread(&bmp, sizeof(BMPHeader), 1, in);
    fread(&dib, sizeof(DIBHeader), 1, in);

    fseek(in, bmp.offset, SEEK_SET);
    unsigned char *pixels = malloc(dib.imageSize);
    fread(pixels, dib.imageSize, 1, in);
    fclose(in);

    FILE *out = fopen(output_file, "w");
    if (!out) return -1;
    for (int i = 0; i < dib.imageSize; i += 3) {
        float gray = (pixels[i] + pixels[i + 1] + pixels[i + 2]) / 3.0;
        fprintf(out, "%.2f\n", gray);
    }
    fclose(out);
    free(pixels);

    return 0;
}
