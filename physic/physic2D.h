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
} pobj2_32t;


typedef struct {
    pobj2_32t *objects;
    uint32_t objects_num;    

} scene2_32t;


// 2D SCENE PROCEDURES

scene2_32t* scene2_32t_create();

void scene2_32t_new(scene2_32t* scene, const figure32_2t* figure);

void scene2_32t_update


// 2D OBJECT PROCEDURES

void pobj2_32t_update_pos(pobj2_32t* obj);

void pobj2_32t_add_pulse(pobj2_32t* obj, const f32_2t* pulse);
