#pragma once

#define GLFW_INCLUDE_NONE

#include <stdint.h>

#include "./graphics_math.h"

#include "../GLFW/glfw3.h"

#ifndef GLAD_GL_H_
#include "../glad/gl.h"
#endif

#include "../geometry/geometry.h"
#include "../physic/physic.h"


// OPENGL WINDOW STRUCTURE

typedef GLFWwindow window_gl;


// OPENGL SHADERS STRUCTURE

typedef struct {
    char *vertex, *geometry, *fragment;
} source_gl;

typedef struct {
    GLuint vertex, geometry, fragment;
    GLint transform_location;
    GLuint program;
} pipeline_gl; 


// OPENGL DRAW STRUCTURE

typedef struct {
    GLuint vertex_buf, color_buf, index_buf;
    GLuint vertex_arr;

    uint32_t points;
} draw_gl;


// FUNCTIONS FOR WORK WITH OPENGL

uint8_t init_gl();

window_gl *window_gl_create(uint32_t width, uint32_t height, const char *name);

void window_gl_resize(window_gl *wnd, uint32_t width, uint32_t height);

void window_gl_rename(window_gl *wnd, const char *name);

void window_gl_get_size(window_gl *wnd, uint32_t *width, uint32_t *height);

bool window_gl_should_close(window_gl *wnd);

void window_gl_poll_events(window_gl *wnd);


// FUNCTIONS FOR WORK WITH GRAPHIC

void window_gl_clear_color(window_gl *window, float r, float g, float b, float a);

void window_gl_clear(window_gl *window);

void window_gl_draw(window_gl *window, const pipeline_gl* pipeline, const draw_gl *figure, const f32_4x4t* transform);


// FUNCTIONS FOR DRAW

draw_gl *draw_gl_init_figure32_2t(const figure32_2t *figure);
void draw_gl_update_figure32_2t(draw_gl *dst, const figure32_2t *figure);
void draw_gl_realloc_figure32_2t(draw_gl *dst, const figure32_2t *figure);

draw_gl *draw_gl_init_pobj32_2t(const pobj32_2t *pobj);
void draw_gl_update_pobj32_2t(draw_gl *dst, const pobj32_2t *pobj);
void draw_gl_realloc_pobj32_2t(draw_gl *dst, const pobj32_2t *pobj);

draw_gl *draw_gl_init_scene32_2t(const scene32_2t *scene);
void draw_gl_update_scene32_2t(draw_gl *dst, const scene32_2t *scene);
void draw_gl_realloc_scene32_2t(draw_gl *dst, const scene32_2t *scene);

draw_gl *draw_gl_init_figure32_4t(const figure32_4t *figure);
void draw_gl_update_figure32_4t(draw_gl *dst, const figure32_4t *figure);
void draw_gl_realloc_figure32_4t(draw_gl *dst, const figure32_4t *figure);

draw_gl *draw_gl_init_pobj32_4t(const pobj32_4t *pobj);
void draw_gl_update_pobj32_4t(draw_gl *dst, const pobj32_4t *pobj);
void draw_gl_realloc_pobj32_4t(draw_gl *dst, const pobj32_4t *pobj);

draw_gl *draw_gl_init_scene32_4t(const scene32_4t *scene);
void draw_gl_update_scene32_4t(draw_gl *dst, const scene32_4t *scene);
void draw_gl_realloc_scene32_4t(draw_gl *dst, const scene32_4t *scene);


// FUNCTIONS FOR WORK WITH SHADERS

pipeline_gl *pipeline_gl_compile(const source_gl *source);


// DEFAULT SHADERS

static source_gl source_gl_lightless_2d = {
    .vertex = 
    "#version 330\n"
    "layout (location = 0) in vec2 VPos;\n"
    "layout (location = 1) in vec3 VCol;\n"
    "uniform mat4 VTrans;\n"
    "out vec3 FColor;\n"
    "void main() {\n"
    "   gl_Position = VTrans * vec4(VPos, 0.f, 1.f);\n"
    "   FColor = VCol;\n"
    "}",

    .geometry = 0,

    .fragment = 
    "#version 330\n"
    "in vec3 FColor;\n"
    "out vec4 fragment;\n"
    "void main() {\n"
    "   fragment = vec4(FColor, 1.f);\n"
    "}"
};

static source_gl source_gl_lightless_3d = {
    .vertex =
    "#version 330\n"
    "layout (location = 0) in vec3 VPos;\n"
    "layout (location = 1) in vec3 VCol;\n"
    "uniform mat4 VTrans;\n"
    "out vec3 FColor;\n"
    "void main() {\n"
    "   gl_Position = VTrans * vec4(VPos, 1.f);\n"
    "   FColor = VCol;\n"
    "}",

    .geometry = 0,

    .fragment =
    "#version 330\n"
    "in vec3 FColor;\n"
    "out vec4 fragment;\n"
    "void main() {\n"
    "   fragment = vec4(FColor, 1.f)'\n"
    "}"
};
