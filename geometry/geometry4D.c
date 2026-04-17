#include <stdint.h>

#include "./geometry4D.h"


// FUNCTIONS FOR OPERATING 4D VECTORS

void f32_4t_add(f32_4t *dst, const f32_4t *src) {
    dst->x += src->x, dst->y += src->y, dst->z += src->y, dst->w += src->w;
}

void f32_4t_sub(f32_4t *dst, const f32_4t *src) {
    dst->x -= src->x, dst->y -= src->y, dst->z -= src->z, dst->w -= src->w;
}

void f32_4t_mul(f32_4t *dst, const f32_4t *src) {
    dst->x *= src->x, dst->y *= src->y, dst->z *= src->z, dst->w *= src->w;
}

void f32_4t_div(f32_4t *dst, const f32_4t *src) {
    dst->x /= src->x, dst->y /= src->y, dst->z /= src->z, dst->w /= src->w;
}

void f32_4t_mad(f32_4t *dst, const f32_4t *src1, const f32_4t *src2) {
    dst->x += src1->x * src2->x, dst->y += src1->y * src2->y, dst->z += src1->z * src2->z, dst->w += src1->w * src2->w;
}

void f32_4t_smad(f32_4t *dst, const f32_4t *src1, f32_t src2) {
    dst->x += src1->x * src2, dst->y += src1->y * src2, dst->z += src1->z * src2, dst->w += src1->w * src2;
}

void sadd(f32_4t *dst, f32_t src) {
    dst->x += src, dst->y += src, dst->z += src, dst->w += src;
}

void ssub(f32_4t *dst, f32_t src) {
    dst->x -= src, dst->y -= src, dst->z -= src, dst->w -= src;
}

void smul(f32_4t *dst, f32_t src) {
    dst->x *= src, dst->y *= src, dst->z *= src, dst->w *= src;
}

void sdiv(f32_4t *dst, f32_t src) {
    dst->x /= src, dst->y /= src, dst->z /= src, dst->w /= src;
}

f32_t f32_4t_dot(const f32_4t *src1, const f32_4t *src2) {
    return src1->x * src2->x + src1->y * src2->y + src1->z * src2->z + src1->w * src2->w;
}
