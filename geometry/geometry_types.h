#pragma once

#include <stdint.h>


// SCALAR TYPES

typedef float f32_t;


// PRIMITIVES TYPE

typedef struct {
    uint32_t a, b, c;
} face;

typedef struct {
    uint32_t a, b;
    f32_t len;
} edge;
