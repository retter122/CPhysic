#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "./CPhysic/cphysic.h"


static window_gl *PWindow = 0;

static f32_2t triangle_vert[] = { {-0.2f, -0.2f}, {-0.2f, 0.2f}, {0.2f, 0.2f}, {0.2f, -0.2f} };
static color triangle_color[] = { {1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f} };
static face triangle_face[] = { {0, 1, 2}, {0, 3, 2} };
static figure32_2t triangle = { triangle_vert, triangle_color, triangle_face, 4, 2 };


int main() {
    init_gl();

    PWindow = window_gl_create(800, 800, "test");
    window_gl_clear_color(PWindow, 0.3, 0.6, 0.3, 0.4);

    pipeline_gl* main_line = pipeline_gl_compile(&source_gl_lightless_2d);

    draw_gl *triangle_draw = draw_gl_init_figure32_2t(&triangle);

    uint32_t width, height;

    while (!window_gl_should_close(PWindow)) {
        window_gl_get_size(PWindow, &width, &height);
        glViewport(0, 0, width, height);

        float ratio = (float)width / (float)height;

        f32_4x4t trans;
        f32_4x4t_scale(&trans, 1.f, ratio, 1.f);

        window_gl_draw(PWindow, main_line, triangle_draw, &trans);

        window_gl_clear(PWindow);
        window_gl_poll_events(PWindow);
    }

    return 0;
}
