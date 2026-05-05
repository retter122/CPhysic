#pragma once

#include <stdint.h>

#include "../GLFW/glfw3.h"
#include "../geometry/geometry.h"
#include "../physic/physic.h"


// OPENGL WINDOW STRUCTURE

typedef GLFWwindow window_gl;


// FUNCTIONS FOR WORK WITH OPENGL

uint8_t init_gl();

window_gl *window_gl_create(uint32_t width, uint32_t height, const char *name);

void window_gl_resize(window_gl *wnd, uint32_t width, uint32_t height);

void window_gl_rename(window_gl *wnd, const char *name);

void window_gl_get_size(window_gl *wnd, uint32_t *width, uint32_t *height);

bool window_gl_should_close(window_gl *wnd);


// FUNCTIONS FOR WORK WITH GRAPHIC

void window_gl_set_mode();

void window_gl_clear_color(window_gl *window, float r, float g, float b, float a);

void window_gl_clear(window_gl *window);

void window_gl_draw_figure32_2t(window_gl *window, figure32_2t *figure);

void window_gl_draw_pobj32_2t(window_gl *window, pobj32_2t *object);

void window_gl_draw_scene32_2t(window_gl *window, scene32_2t *scene);
