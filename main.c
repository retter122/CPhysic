#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "./CPhysic/cphysic.h"


#define DST_COOF 2.5f


static window_gl *PWindow = 0;

static f32_2t earth_center = { 0.f, 0.f }, moon_center = { 0.4f, 0.f };
static color earth_color = { 0.2f, 0.2f, 1.f }, moon_color = { 0.3f, 0.3f, 0.3f };

static f32_t earth_mass = 120000000, moon_mass = 1;
static f32_t earth_radius = 0.12f, moon_radius = 0.06f;

static f32_2t moon_pulse = { 0.f, 0.28f };

int main() {
    init_gl();

    PWindow = window_gl_create(800, 800, "test");
    window_gl_clear_color(PWindow, 0.05, 0.05, 0.05, 1.f);

    figure32_2t *earth = figure32_2t_circle(earth_radius, &earth_center, &earth_color, 36);
    figure32_2t *moon = figure32_2t_circle(moon_radius, &moon_center, &moon_color, 36);

    earth->colors[1].r = 1.f, moon->colors[1].b = 1.f;

    scene32_2t *scene = scene32_2t_create();
    scene32_2t_new_obj(scene, earth, earth_mass, 4000000000, 1);
    scene32_2t_new_obj(scene, moon, moon_mass, 30, 1);

    pobj32_2t_add_pulse(&scene->objects[1], &moon_pulse);

    scene32_2t_add_force(scene, forces32_2t_gravity);

    pipeline_gl* main_line = pipeline_gl_compile(&source_gl_lightless_2d);

    draw_gl *triangle_draw = draw_gl_init_scene32_2t(scene);

    uint32_t width, height;

    while (!window_gl_should_close(PWindow)) {
        window_gl_get_size(PWindow, &width, &height);
        glViewport(0, 0, width, height);

        float ratio = (float)width / (float)height;

        f32_4x4t trans;
        f32_4x4t_scale(&trans, 1.f, ratio, 1.f);

        draw_gl_update_scene32_2t(triangle_draw, scene);

        window_gl_draw(PWindow, main_line, triangle_draw, &trans);

        scene32_2t_update(scene, 0.004);

        window_gl_clear(PWindow);
        window_gl_poll_events(PWindow);
    }

    return 0;
}
