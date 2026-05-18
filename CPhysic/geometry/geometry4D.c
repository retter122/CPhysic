#include <stdint.h>
#include <stdlib.h>

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

void f32_4t_sadd(f32_4t *dst, f32_t src) {
    dst->x += src, dst->y += src, dst->z += src, dst->w += src;
}

void f32_4t_ssub(f32_4t *dst, f32_t src) {
    dst->x -= src, dst->y -= src, dst->z -= src, dst->w -= src;
}

void f32_4t_smul(f32_4t *dst, f32_t src) {
    dst->x *= src, dst->y *= src, dst->z *= src, dst->w *= src;
}

void f32_4t_sdiv(f32_4t *dst, f32_t src) {
    dst->x /= src, dst->y /= src, dst->z /= src, dst->w /= src;
}

f32_t f32_4t_dot(const f32_4t *src1, const f32_4t *src2) {
    return src1->x * src2->x + src1->y * src2->y + src1->z * src2->z + src1->w * src2->w;
}


// FUNCTIONS FOR WORKING WITH 4D FIGURES

figure32_4t* figure32_4t_copy(const figure32_4t* src) {
    figure32_4t* out = malloc(sizeof(figure32_4t));
    
    out->vertex = malloc(sizeof(f32_4t) * src->vertex_num), out->vertex_num = src->vertex_num;
    for (uint32_t i = 0; i < src->vertex_num; ++i) {
        out->vertex[i].x = src->vertex[i].x, out->vertex[i].y = src->vertex[i].y;
        out->vertex[i].z = src->vertex[i].z, out->vertex[i].w = src->vertex[i].w;
    }

    out->colors = malloc(sizeof(color) * src->vertex_num);
    for (uint32_t i = 0; i < src->vertex_num; ++i) out->colors[i].r = src->colors[i].r, out->colors[i].g = src->colors[i].g, out->colors[i].b = src->colors[i].b;

    out->faces = malloc(sizeof(face) * src->faces_num);
    for (uint32_t i = 0; i < src->faces_num; ++i) out->faces[i].a = src->faces[i].a, out->faces[i].b = src->faces[i].b, out->faces[i].c = src->faces[i].c;
    
    return out;
}
