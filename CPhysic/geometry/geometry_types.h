#pragma once

#include <stdint.h>


// SCALAR TYPES

typedef float f32_t;


// PRIMITIVES TYPE

typedef struct {
    uint32_t a, b;
    f32_t len;
} edge32_t;

typedef struct {
    uint32_t a, b, c;
} face;


// GRAPHICS TYPES

typedef struct {
    f32_t r, g, b;
} color;
