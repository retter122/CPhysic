#include <stdlib.h>
#include <stdint.h>

#include "./geometry2D.h"
#include "./geometry_types.h"


// FUNCTIONS FOR OPERATING 2D VECTORS

void f32_2t_add(f32_2t *dst, const f32_2t *src) { 
    dst->x += src->x, dst->y += src->y;
}

void f32_2t_sub(f32_2t *dst, const f32_2t *src) { 
    dst->x -= src->x, dst->y -= src->y;
}

void f32_2t_mul(f32_2t *dst, const f32_2t *src) { 
    dst->x *= src->x, dst->y *= src->y;
}

void f32_2t_div(f32_2t *dst, const f32_2t *src) { 
    dst->x /= src->x, dst->y /= src->y;
}

void f32_2t_sadd(f32_2t *dst, f32_t src) {
    dst->x += src, dst->y += src;
}

void f32_2t_ssub(f32_2t *dst, f32_t src) {
    dst->x -= src, dst->y -= src;
}

void f32_2t_smul(f32_2t *dst, f32_t src) {
    dst->x *= src, dst->y *= src;
}

void f32_2t_sdiv(f32_2t *dst, f32_t src) {
    dst->x /= src, dst->y /= src;
}

f32_t f32_2t_dot(const f32_2t *src1, const f32_2t *src2) {
    return src1->x * src2->x + src1->y * src2->y;
}

