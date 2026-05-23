#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "./CPhysic/cphysic.h"


static window_gl *PWindow = 0;

static f32_2t triangle_vert[] = { {-0.2f, -0.2f}, {-0.2f, 0.2f}, {0.2f, 0.2f}, {0.2f, -0.2f}, {0.f, 0.f} };
static color triangle_color[] = { {1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 0.f} };
static face triangle_face[] = { {0, 3, 4}, {0, 1, 4}, {2, 4, 1}, {2, 4, 3} };
static figure32_2t triangle = { triangle_vert, triangle_color, triangle_face, 5, 4 };


static f32_2t vert_add = {0.01f, 0.f};


int main() {
    init_gl();

    PWindow = window_gl_create(800, 800, "test");
    window_gl_clear_color(PWindow, 0.3, 0.6, 0.3, 0.4);

    scene32_2t *scene = scene32_2t_create();
    scene32_2t_new_obj(scene, &triangle, 1, 1, 1);

    pipeline_gl* main_line = pipeline_gl_compile(&source_gl_lightless_2d);

    draw_gl *triangle_draw = draw_gl_init_scene32_2t(scene);

    uint32_t width, height;
    pobj32_2t_add_pulse(scene->objects, &vert_add);

    while (!window_gl_should_close(PWindow)) {
        window_gl_get_size(PWindow, &width, &height);
        glViewport(0, 0, width, height);

        float ratio = (float)width / (float)height;

        f32_4x4t trans;
        f32_4x4t_scale(&trans, 1.f, ratio, 1.f);

        draw_gl_update_scene32_2t(triangle_draw, scene);

        window_gl_draw(PWindow, main_line, triangle_draw, &trans);

        scene32_2t_update(scene, 0.05);
        window_gl_clear(PWindow);
        window_gl_poll_events(PWindow);
    }

    return 0;
}
