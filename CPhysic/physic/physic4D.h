#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../geometry/geometry.h"


// 4D PHYSIC OBJECT DATATYPES

typedef struct scene32_4t scene32_4t;
typedef void (*force32_4t)(scene32_4t* scene, f32_t time);


typedef struct {
    figure32_4t* figure;

    f32_t mass, hardness, damping;

    edge32_t* edges;
    uint32_t edges_num;

    f32_t *vertex_mass_coof;
    f32_4t *vertex_spd;
} pobj32_4t;


struct scene32_4t {
    pobj32_4t *objects;
    uint32_t objects_num;

    force32_4t* forces;
    uint32_t forces_num;
};


// 4D SCENE PROCEDURES

scene32_4t* scene32_4t_create();

void scene32_4t_new_obj(scene32_4t* scene, const figure32_4t* figure, f32_t mass, f32_t hardness, f32_t damping);

void scene32_4t_add_force(scene32_4t* scene, force32_4t force);

void scene32_4t_update(scene32_4t* scene, f32_t time);


// 4D OBJECT PROCEDURES

pobj32_4t* pobj32_4t_create(const figure32_4t *figure, f32_t mass, f32_t hardness, f32_t damping);

void pobj32_4t_add_pulse(pobj32_4t* obj, const f32_4t* pulse);

void pobj32_4t_update(pobj32_4t *obj, f32_t time);

void pobj32_4t_generate_edges(pobj32_4t *object);

void pobj32_4t_init_mass_coofs(pobj32_4t *object);
