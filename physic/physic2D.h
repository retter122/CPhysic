#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../geometry/geometry.h"


// 2D PHYSIC OBJECT DATATYPES

typedef struct {
    figure32_2t* figure;

    f32_t mass, hardness;

    edge* edges;
    uint32_t edges_num;

    f32_t *edges_len, *vertex_mass_coof, *vertex_spd;
} pobj32_2t;


typedef void (*force32_2t)(pobj32_2t* object, scene32_2t* scene, f32_t time);


typedef struct {
    pobj32_2t *objects;
    uint32_t objects_num;

    force32_2t* forces;

} scene32_2t;


// 2D SCENE PROCEDURES

scene32_2t* scene2_32t_create();

void scene32_2t_new(scene32_2t* scene, const figure32_2t* figure);

void scene32_2t_update(scene32_2t* scene);


// 2D OBJECT PROCEDURES

void pobj32_2t_update_pos(pobj32_2t* obj);

void pobj32_2t_add_pulse(pobj32_2t* obj, const f32_2t* pulse);
