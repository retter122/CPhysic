#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "./physic2D.h"


// WORK FUNCTIONS

void create_edges_32_2t(pobj32_2t* object, const figure32_2t* figure) {
    object->edges = malloc(figure->faces_num * 3 * sizeof(edge)), object->edges_num = 0;

    for (uint32_t i = 0; i < figure->faces_num; ++i) {
        uint8_t edge_1 = 1, edge_2 = 1, edge_3 = 1;

        for (uint32_t j = 0; j < object->edges_num; ++j) {
            if ((object->edges[j].a == figure->faces[i].a && object->edges[j].b == figure->faces[i].b) || (object->edges[j].b == figure->faces[i].a && object->edges[j].a == figure->faces[i].b)) edge_1 = 0;
            if ((object->edges[j].a == figure->faces[i].b && object->edges[j].b == figure->faces[i].c) || (object->edges[j].b == figure->faces[i].b && object->edges[j].a == figure->faces[i].c)) edge_2 = 0;
            if ((object->edges[j].a == figure->faces[i].a && object->edges[j].b == figure->faces[i].c) || (object->edges[j].b == figure->faces[i].a && object->edges[j].a == figure->faces[i].c)) edge_3 = 0;
        }

        if (edge_1) {
            uint32_t point_a = figure->faces[i].a, point_b = figure->faces[i].b;
            object->edges[object->edges_num].a = point_a, object->edges[object->edges_num].b = point_b;

            f32_t lx = figure->vertex[point_a].x - figure->vertex[point_b].x, ly = figure->vertex[point_a].y - figure->vertex[point_b].y; 
            object->edges[object->edges_num].len = sqrtf(lx * lx + ly * ly);

            ++object->edges_num;
        } if (edge_2) {
            uint32_t point_a = figure->faces[i].b, point_b = figure->faces[i].c;
            object->edges[object->edges_num].a = point_a, object->edges[object->edges_num].b = point_b;

            f32_t lx = figure->vertex[point_a].x - figure->vertex[point_b].x, ly = figure->vertex[point_a].y - figure->vertex[point_b].y; 
            object->edges[object->edges_num].len = sqrtf(lx * lx + ly * ly);

            ++object->edges_num;
        } if (edge_3) {
            uint32_t point_a = figure->faces[i].a, point_b = figure->faces[i].c;
            object->edges[object->edges_num].a = point_a, object->edges[object->edges_num].b = point_b;

            f32_t lx = figure->vertex[point_a].x - figure->vertex[point_b].x, ly = figure->vertex[point_a].y - figure->vertex[point_b].y; 
            object->edges[object->edges_num].len = sqrtf(lx * lx + ly * ly);

            ++object->edges_num;
        }
    } object->edges = realloc(object->edges, object->edges_num * sizeof(edge));
}


void init_mass_coofs(pobj32_2t* object) {
    object->vertex_mass_coof = malloc(object->figure->vertex_num * sizeof(f32_t));
    for (uint32_t i = 0; i < object->figure->vertex_num; ++i) object->vertex_mass_coof[i] = 0;

    f32_t total_len = 0;
    for (uint32_t i = 0; i < object->edges_num; ++i) {
        total_len += object->edges[i].len;

        object->vertex_mass_coof[object->edges[i].a] += object->edges[i].len;
        object->vertex_mass_coof[object->edges[i].b] += object->edges[i].len;
    }

    for (uint32_t i = 0; i < object->figure->vertex_num; ++i) object->vertex_mass_coof[i] /= total_len;
}


// 2D SCENE PROCEDURES

scene32_2t* scene2_32t_create() {
    scene32_2t *out = malloc(sizeof(scene32_2t));

    out->forces = 0, out->objects = 0, out->objects_num = 0;
    return out;
}


void scene32_2t_new_obj(scene32_2t* scene, const figure32_2t* figure, f32_t mass, f32_t hardness) {
    scene->objects = realloc(scene->objects, (scene->objects_num + 1) * sizeof(pobj32_2t));

    scene->objects[scene->objects_num].mass = mass, scene->objects[scene->objects_num].hardness = hardness;
    scene->objects[scene->objects_num].figure = figure32_2t_copy(figure);

    create_edges_32_2t(scene->objects + scene->objects_num, figure);
    init_mass_coofs(scene->objects + scene->objects_num);

    scene->objects[scene->objects_num].vertex_spd = malloc(figure->vertex_num * sizeof(f32_2t));
    for (uint32_t i = 0; i < figure->vertex_num; ++i) {
        scene->objects[scene->objects_num].vertex_spd[i].x = scene->objects[scene->objects_num].vertex_spd[i].y = 0;
    }

    ++scene->objects_num;
}


void scene32_2t_add_force(scene32_2t* scene, force32_2t force) {
    scene->forces = realloc(scene->forces, scene->forces_num * sizeof(force32_2t));
    scene->forces[scene->forces_num++] = force;
}


void scene32_2t_update(scene32_2t* scene, f32_t time) {
    for (uint32_t i = 0; i < scene->forces_num; ++i) scene->forces[i](scene, time);

    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        pobj32_2t* obj = scene->objects + i;

        for (uint32_t j = 0; j < scene->objects[i].edges_num; ++j) {
            edge* edge = scene->objects[i].edges + j;

            f32_2t force = { obj->figure->vertex[edge->b].x, obj->figure->vertex[edge->b].y };
            f32_2t_sub(&force, &obj->figure->vertex[edge->a]);

            f32_t len_edge = sqrtf(force.x * force.x + force.y * force.y);
            f32_2t_sdiv(&force, len_edge);
            f32_2t_smul(&force, (len_edge - edge->len) * obj->hardness * time);
            
            f32_2t_smad(&obj->vertex_spd[edge->a], &force, obj->vertex_mass_coof[edge->a]);
            f32_2t_smad(&obj->vertex_spd[edge->b], &force, -obj->vertex_mass_coof[edge->b]);
        }
    }

    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        for (uint32_t j = 0; j < scene->objects->figure->vertex_num; ++j) {
            f32_2t_smad(&scene->objects->figure->vertex[i], &scene->objects->vertex_spd[i], time);
        }
    }
}


// 2D OBJECT PROCEDURES

void pobj32_2t_add_pulse(pobj32_2t* obj, const f32_2t* pulse) {
    for (uint32_t i = 0; i < obj->figure->vertex_num; ++i) f32_2t_smad(&obj->vertex_spd[i], pulse, 1.f / obj->mass);
}
