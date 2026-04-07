#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "./geometry_types.h"


// DATATYPES FOR 2D GEOMETRY

typedef struct { f32_t x, y; } f32_2t;

typedef struct {
    f32_2t* vertex;
    face* faces;

    uint32_t vertex_num, faces_num;
} figure32_2t;


// FUNCTIONS FOR OPERATING 2D VECTORS

void f32_2t_add(f32_2t *dst, const f32_2t *src);

void f32_2t_sub(f32_2t *dst, const f32_2t *src);

void f32_2t_mul(f32_2t *dst, const f32_2t *src);

void f32_2t_div(f32_2t *dst, const f32_2t *src);

void f32_2t_mad(f32_2t *dst, const f32_2t *src1, const f32_2t *src2);

void f32_2t_smad(f32_2t *dst, const f32_2t *src1, f32_t src2);

void f32_2t_sadd(f32_2t *dst, f32_t src);

void f32_2t_ssub(f32_2t *dst, f32_t src);

void f32_2t_smul(f32_2t *dst, f32_t src);

void f32_2t_sdiv(f32_2t *dst, f32_t src);

f32_t f32_2t_dot(const f32_2t *src1, const f32_2t *src2);


// FUNCTIONS FOR OPERATING 2D FIGURES

figure32_2t* figure32_2t_copy(const figure32_2t* src);
