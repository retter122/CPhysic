#pragma once

#include <stdint.h>
#include <stdio.h>

#include "./geometry_types.h"


// DATATYPES FOR 4D GEOMETRY

typedef struct { f32_t x, y, z, w; } f32_4t;

typedef struct {
    f32_4t* vertex;
    face* faces;

    uint32_t vertex_num, faces_num;
} figure32_4t;


// FUNCTIONS FOR OPERATING 4D VECTORS

void f32_4t_add(f32_4t *dst, const f32_4t *src);
void f32_4t_add_sse3(f32_4t *dst, const f32_4t *src);

void f32_4t_sub(f32_4t *dst, const f32_4t *src);
void f32_4t_sub_sse3(f32_4t *dst, const f32_4t *src);

void f32_4t_mul(f32_4t *dst, const f32_4t *src);
void f32_4t_mul_sse3(f32_4t *dst, const f32_4t *src);

void f32_4t_div(f32_4t *dst, const f32_4t *src);
void f32_4t_div_sse3(f32_4t *dst, const f32_4t *src);

void f32_4t_mad(f32_4t *dst, const f32_4t *src1, const f32_4t *src2);
void f32_4t_mad_sse3(f32_4t *dst, const f32_4t *src1, const f32_4t *src2);

void f32_4t_smad(f32_4t *dst, const f32_4t *src1, f32_t src2);
void f32_4t_smad_sse3(f32_4t *dst, const f32_4t *src1, f32_t src2);

void f32_4t_sadd(f32_4t *dst, f32_t src);
void f32_4t_sadd_sse3(f32_4t *dst, f32_t src);

void f32_4t_ssub(f32_4t *dst, f32_t src);
void f32_4t_ssub_sse3(f32_4t *dst, f32_t src);

void f32_4t_smul(f32_4t *dst, f32_t src);
void f32_4t_smul_sse3(f32_4t *dst, f32_t src);

void f32_4t_sdiv(f32_4t *dst, f32_t src);
void f32_4t_sdiv_sse3(f32_4t *dst, f32_t src);

f32_t f32_4t_dot(const f32_4t *src1, const f32_4t *src2);
f32_t f32_4t_dot_sse3(const f32_4t *src1, const f32_4t *src2);

// FUNCTIONS FOR OPERATING 4D FIGURES

figure32_4t* figure32_4t_copy(const figure32_4t* src);
figure32_4t* figure32_4t_copy_sse3(const figure32_4t *src);
