#include <stdint.h>
#include <stdlib.h>

#include "./graphics_math.h"


void f32_4x4t_identity(f32_4x4t* dst) {
    dst->elems[0] = 1.f, dst->elems[1] = 0.f, dst->elems[2] = 0.f, dst->elems[3] = 0.f;
    dst->elems[4] = 0.f, dst->elems[5] = 1.f, dst->elems[6] = 0.f, dst->elems[7] = 0.f;
    dst->elems[8] = 0.f, dst->elems[9] = 0.f, dst->elems[10] = 1.f, dst->elems[11] = 0.f;
    dst->elems[12] = 0.f, dst->elems[13] = 0.f, dst->elems[14] = 0.f, dst->elems[15] = 1.f; 
}

void f32_4x4t_scale(f32_4x4t* dst, f32_t scale_x, f32_t scale_y, f32_t scale_z) {
    dst->elems[0] = scale_x, dst->elems[1] = 0.f, dst->elems[2] = 0.f, dst->elems[3] = 0.f;
    dst->elems[4] = 0.f, dst->elems[5] = scale_y, dst->elems[6] = 0.f, dst->elems[7] = 0.f;
    dst->elems[8] = 0.f, dst->elems[9] = 0.f, dst->elems[10] = scale_z, dst->elems[11] = 0.f;
    dst->elems[12] = 0.f, dst->elems[13] = 0.f, dst->elems[14] = 0.f, dst->elems[15] = 1.f;
}
