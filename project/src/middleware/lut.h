#ifndef LUT_H
#define LUT_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    const float* data;
    const int32_t cols;
    const int32_t rows;
} lut_t;

float lut_print(lut_t* instance) {
    for (int32_t row = 0; row < instance->rows; ++row) {
        for (int32_t col = 0; col < instance->cols; ++col) {
            float value = instance->data[row * instance->cols + col];
            printf("%f\n", value);
        }
    }
}

float lut_lookup(lut_t* instance, float x, float y) {
    int32_t ix2;
    for (ix2 = 1; ix2 < instance->cols; ++ix2) { // @todo Binary search
        float value = instance->data[ix2];
        if (value > x) break;
    }
    int32_t ix1 = ix2 - 1;
    if (ix1 <= 0) ix1 = 1;
    if (ix2 >= instance->cols) ix2 = instance->cols - 1;
    //printf("%d/%d\n", index_x_1, index_x_2);
    
    int32_t iy2;
    for (iy2 = 1; iy2 < instance->rows; ++iy2) { // @todo Index search with step width
        float value = instance->data[iy2 * instance->cols];
        if (value > y) break; 
    }
    int32_t iy1 = iy2 - 1;
    if (iy1 <= 0) iy1 = 1;
    if (iy2 >= instance->rows) iy2 = instance->rows - 1;
    //printf("%d\n", row);

    // @todo Linear interpolation!
    float x1 = instance->data[ix1];
    float x2 = instance->data[ix2];
    float y1 = instance->data[instance->cols * iy1];
    float y2 = instance->data[instance->cols * iy2];

    float vx1y1 = instance->data[ix1 + instance->cols * iy1];
    float vx2y1 = instance->data[ix2 + instance->cols * iy1];
    float vx1y2 = instance->data[ix1 + instance->cols * iy2];
    float vx2y2 = instance->data[ix2 + instance->cols * iy2];

    float vxy1;
    float vxy2;
    if (ix1 == ix2) {
        vxy1 = vx1y1;
        vxy2 = vx1y2;
    } else {
        float ky1 = (vx2y1 - vx1y1) / (x2 - x1);
        float dy1 = vx1y1 - ky1 * x1;
        vxy1 = ky1 * x + dy1;

        float ky2 = (vx2y2 - vx1y2) / (x2 - x1);
        float dy2 = vx1y2 - ky2 * x1;
        vxy2 = ky2 * x + dy2;
    }

    float v;
    if (iy1 == iy2) {
        v = vxy1;
    } else {
        float kx = (vxy2 - vxy1) / (y2 - y1);
        float dx = vxy1 - kx * y1;
        v = kx * y + dx;
    }

    return v;
}

#endif
