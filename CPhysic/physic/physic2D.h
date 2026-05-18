#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../geometry/geometry.h"


// 2D PHYSIC OBJECT DATATYPES

typedef struct scene32_2t scene32_2t;
typedef void (*force32_2t)(scene32_2t* scene, f32_t time);


typedef struct {
    figure32_2t* figure;

    f32_t mass, hardness, damping;

    edge32_t* edges;
    uint32_t edges_num;

    f32_t *vertex_mass_coof;
    f32_2t *vertex_spd;
} pobj32_2t;


struct scene32_2t {
    pobj32_2t *objects;
    uint32_t objects_num;

    force32_2t* forces;
    uint32_t forces_num;
};


// 2D SCENE PROCEDURES

scene32_2t* scene32_2t_create();

void scene32_2t_new_obj(scene32_2t* scene, const figure32_2t* figure, f32_t mass, f32_t hardness, f32_t damping);

void scene32_2t_add_force(scene32_2t* scene, force32_2t force);

void scene32_2t_update(scene32_2t* scene, f32_t time);


// 2D OBJECT PROCEDURES

pobj32_2t* pobj32_2t_create(const figure32_2t *figure, f32_t mass, f32_t hardness, f32_t damping);

void pobj32_2t_add_pulse(pobj32_2t* obj, const f32_2t* pulse);

void pobj32_2t_update(pobj32_2t *obj, f32_t time);

void pobj32_2t_generate_edges(pobj32_2t *object);

void pobj32_2t_init_mass_coofs(pobj32_2t *object);
