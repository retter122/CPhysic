#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "./physic2D.h"
#include "./physic_constants.h"

// 2D SCENE PROCEDURES

scene32_2t* scene32_2t_create() {
    scene32_2t *out = malloc(sizeof(scene32_2t));

    out->forces = 0, out->forces_num = 0, out->objects = 0, out->objects_num = 0;
    return out;
}

void scene32_2t_new_obj(scene32_2t* scene, const figure32_2t* figure, f32_t mass, f32_t hardness, f32_t damping) {
    scene->objects = realloc(scene->objects, (scene->objects_num + 1) * sizeof(pobj32_2t));

    uint32_t total_vertex = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) total_vertex += scene->objects[i].figure->vertex_num;

    scene->objects[scene->objects_num].mass = mass, scene->objects[scene->objects_num].hardness = hardness;
    scene->objects[scene->objects_num].damping = damping;

    figure32_2t *copied_figure = figure32_2t_copy(figure);

    scene->objects[scene->objects_num].figure = copied_figure;

    pobj32_2t_generate_edges(scene->objects + scene->objects_num);
    pobj32_2t_init_mass_coofs(scene->objects + scene->objects_num);

    for (uint32_t i = 0; i < copied_figure->faces_num; ++i) {
        copied_figure->faces[i].a += total_vertex;
        copied_figure->faces[i].b += total_vertex;
        copied_figure->faces[i].c += total_vertex;
    }

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

    for (uint32_t i = 0; i < scene->objects_num; ++i) pobj32_2t_update(&scene->objects[i], time);
}


// 2D OBJECT PROCEDURES

pobj32_2t* pobj32_2t_create(const figure32_2t *figure, f32_t mass, f32_t hardness, f32_t damping) {
    pobj32_2t* out = malloc(sizeof(pobj32_2t));
    
    out->figure = figure32_2t_copy(figure);
    out->mass = mass, out->hardness = hardness, out->damping = damping;

    out->vertex_spd = malloc(sizeof(f32_2t) * figure->vertex_num);
    for (uint32_t i = 0; i < figure->vertex_num; ++i) out->vertex_spd[i].x = 0.f, out->vertex_spd[i].y = 0.f;

    pobj32_2t_generate_edges(out);
    pobj32_2t_init_mass_coofs(out);

    return out;
}

void pobj32_2t_add_pulse(pobj32_2t* obj, const f32_2t* pulse) {
    for (uint32_t i = 0; i < obj->figure->vertex_num; ++i) f32_2t_smad(&obj->vertex_spd[i], pulse, 1.f / obj->mass);
}

void pobj32_2t_update(pobj32_2t* obj, f32_t time) {
    figure32_2t *figure = obj->figure;

    for (uint32_t i = 0; i < obj->edges_num; ++i) {
        // GOOKS LAW COUNT
        
        edge32_t* now_edge = obj->edges + i;

        f32_2t force = { figure->vertex[now_edge->b].x, figure->vertex[now_edge->b].y };
        f32_2t_sub(&force, &figure->vertex[now_edge->a]);

        f32_t len = sqrtf(f32_2t_dot(&force, &force));
        f32_2t_smul(&force, (len - now_edge->len) / len * obj->hardness);

        f32_2t_smad(&obj->vertex_spd[now_edge->a], &force, time / (obj->vertex_mass_coof[now_edge->a] * obj->mass));
        f32_2t_smad(&obj->vertex_spd[now_edge->b], &force, -time / (obj->vertex_mass_coof[now_edge->b] * obj->mass));
    }

    for (uint32_t i = 0; i < obj->figure->vertex_num; ++i) f32_2t_smad(&obj->figure->vertex[i], &obj->vertex_spd[i], time);
}

void pobj32_2t_generate_edges(pobj32_2t* object) {
    figure32_2t* figure = object->figure;
    object->edges = malloc(figure->faces_num * 3 * sizeof(edge32_t)), object->edges_num = 0;

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
    } object->edges = realloc(object->edges, object->edges_num * sizeof(edge32_t));
}

void pobj32_2t_init_mass_coofs(pobj32_2t* object) {
    object->vertex_mass_coof = malloc(object->figure->vertex_num * sizeof(f32_t));
    for (uint32_t i = 0; i < object->figure->vertex_num; ++i) object->vertex_mass_coof[i] = 0;

    figure32_2t *figure = object->figure;

    f32_t total_len = 0;
    for (uint32_t i = 0; i < figure->vertex_num; ++i) {
        for (uint32_t j = 0; j < figure->vertex_num; ++j) {
            f32_2t pos1 = { figure->vertex[i].x, figure->vertex[i].y };
            f32_2t_sub(&pos1, &figure->vertex[j]);
            
            f32_t now_len = sqrtf(f32_2t_dot(&pos1, &pos1));
            total_len += now_len;

            object->vertex_mass_coof[i] += now_len, object->vertex_mass_coof[j] += now_len;
        }
    }

    for (uint32_t i = 0; i < object->figure->vertex_num; ++i) {
        object->vertex_mass_coof[i] /= total_len;
    }
}


// BASIC FORCES

void forces32_2t_gravity(scene32_2t *scene, f32_t time) {
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        pobj32_2t *obj_a = &scene->objects[i];

        for (uint32_t j = 0; j < scene->objects_num; ++j) {
            pobj32_2t *obj_b = &scene->objects[j];

            for (uint32_t i_v = 0; i_v < obj_a->figure->vertex_num; ++i_v) {
                for (uint32_t j_v = 0; j_v < obj_b->figure->vertex_num; ++j_v) {
                    if (i == j && i_v == j_v) continue;

                    f32_2t force = { obj_b->figure->vertex[j_v].x, obj_b->figure->vertex[j_v].y };
                    f32_2t_sub(&force, &obj_a->figure->vertex[i_v]);

                    f32_t len = sqrtf(f32_2t_dot(&force, &force));
                    f32_2t_sdiv(&force, len);
                    f32_2t_smul(&force, (obj_a->vertex_mass_coof[i_v] * obj_a->mass * obj_b->vertex_mass_coof[j_v] * obj_b->mass) / (len * len) * G_32);

                    f32_2t_smad(&obj_a->vertex_spd[i_v], &force, time / (obj_a->vertex_mass_coof[i_v] * obj_a->mass));
                    f32_2t_smad(&obj_b->vertex_spd[j_v], &force, -time / (obj_b->vertex_mass_coof[j_v] * obj_b->mass));
                }
            }
        }
    }
}
