#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

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

void f32_2t_mad(f32_2t *dst, const f32_2t *src1, const f32_2t *src2) {
    dst->x += src1->x * src2->x, dst->y += src1->y * src2->y;
}

void f32_2t_smad(f32_2t *dst, const f32_2t *src1, f32_t src2) {
    dst->x += src1->x * src2, dst->y += src1->y * src2;
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


// FUNCTIONS FOR OPERATING 2D FIGURES

figure32_2t* figure32_2t_copy(const figure32_2t* src) {
    figure32_2t* out = malloc(sizeof(figure32_2t));

    out->vertex = malloc(sizeof(f32_2t) * src->vertex_num), out->vertex_num = src->vertex_num;
    for (uint32_t i = 0; i < src->vertex_num; ++i) out->vertex[i].x = src->vertex[i].x, out->vertex[i].y = src->vertex[i].y;

    out->colors = malloc(sizeof(color) * src->vertex_num);
    for (uint32_t i = 0; i < src->vertex_num; ++i) out->colors[i].r = src->colors[i].r, out->colors[i].g = src->colors[i].g, out->colors[i].b = src->colors[i].b;

    out->faces = malloc(sizeof(face) * src->faces_num); out->faces_num = src->faces_num;
    for (uint32_t i = 0; i < src->faces_num; ++i) out->faces[i].a = src->faces[i].a, out->faces[i].b = src->faces[i].b, out->faces[i].c = src->faces[i].c;

    return out;
}


// FUNCTIONS FOR GENERATING 2D FIGURES

figure32_2t *figure32_2t_circle(f32_t radius, const f32_2t *center, const color *obj_color, uint32_t vertex_num) {
    if (vertex_num < 4) return 0;
    
    figure32_2t *out = malloc(sizeof(figure32_2t));
    out->vertex_num = vertex_num, out->faces_num = vertex_num - 1;

    out->vertex = malloc(sizeof(f32_2t) * vertex_num);
    out->colors = malloc(sizeof(color) * vertex_num);
    out->faces = malloc(sizeof(face) * (vertex_num - 1));

    for (uint32_t i = 0; i < vertex_num; ++i) out->colors[i].r = obj_color->r, out->colors[i].g = obj_color->g, out->colors[i].b = obj_color->b;

    out->vertex[0].x = center->x, out->vertex[0].y = center->y;
    f32_t angle_step = M_PI * 2 / (f32_t)(vertex_num - 1);

    for (uint32_t i = 0; i < vertex_num - 1; ++i) {
        f32_t angle = angle_step * (f32_t)i;
        out->vertex[i + 1].x = cosf(angle) * radius + center->x, out->vertex[i + 1].y = sinf(angle) * radius + center->y;
    }

    for (uint32_t i = 2; i < vertex_num; ++i) {
        out->faces[i - 2].a = 0;
        out->faces[i - 2].b = i - 1, out->faces[i - 2].c = i;
    } 
    
    out->faces[vertex_num - 2].a = 0;
    out->faces[vertex_num - 2].b = 1, out->faces[vertex_num - 2].c = vertex_num - 1;

    return out;
}
