#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "../geometry/geometry.h"


// MATRIX STRUCTURES

typedef struct { 
    f32_t elems[16];
} f32_4x4t;


// FUNCTIONS TO TRANSFORM

void f32_4x4t_identity(f32_4x4t* dst);

void f32_4x4t_scale(f32_4x4t* dst, f32_t scale_x, f32_t scale_y, f32_t scale_z);

void f32_4x4t_rotate_x(f32_4x4t* dst, f32_t angle);
void f32_4x4t_rotate_y(f32_4x4t* dst, f32_t angle);
void f32_4x4t_rotate_z(f32_4x4t* dst, f32_t angle);


// ARITHMETIC FUNCTIONS

void f32_4x4t_add_f32_4x4t(f32_4x4t* dst, const f32_4x4t* src);
void f32_4x4t_sub_f32_4x4t(f32_4x4t* dst, const f32_4x4t* src);
void f32_4x4t_vmul_f32_4x4t(f32_4x4t* dst, const f32_4x4t* src1, const f32_4x4t *src2);

