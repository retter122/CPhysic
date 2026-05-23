#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./graphics_gl.h"

#include "../GLFW/glfw3.h"

#ifndef GLAD_GL_H_
#include "../glad/gl.h"
#endif

#include "../geometry/geometry.h"
#include "../physic/physic.h"


uint8_t init_gl() {
    return glfwInit();
}

window_gl *window_gl_create(uint32_t width, uint32_t height, const char *name) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *out = glfwCreateWindow(width, height, name, 0, 0);
    
    glfwMakeContextCurrent(out);
    gladLoadGL(glfwGetProcAddress);
    glClearColor(0, 0, 0, 1.f);

    return out;
}

void window_gl_resize(window_gl *wnd, uint32_t width, uint32_t height) {
    glfwSetWindowSize(wnd, width, height);
}

void window_gl_rename(window_gl *wnd, const char *name) {
    glfwSetWindowTitle(wnd, name);
}

void window_gl_get_size(window_gl *wnd, uint32_t *width, uint32_t *height) {
    glfwGetFramebufferSize(wnd, width, height);
}

bool window_gl_should_close(window_gl *wnd) {
    return glfwWindowShouldClose(wnd);
}

void window_gl_poll_events(window_gl *wnd) {
    glfwMakeContextCurrent(wnd);
    glfwPollEvents();
}

void window_gl_clear_color(window_gl *window, float r, float g, float b, float a) {
    glfwMakeContextCurrent(window);
    glClearColor(r, g, b, a);
}

void window_gl_clear(window_gl *window) {
    glfwMakeContextCurrent(window);
    
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_gl_draw(window_gl *window, const pipeline_gl* pipeline, const draw_gl *figure, const f32_4x4t* transform) {
    glfwMakeContextCurrent(window);
    glUseProgram(pipeline->program);

    glUniformMatrix4fv(pipeline->transform_location, 1, GL_FALSE, (const GLfloat*) transform->elems);
    glBindVertexArray(figure->vertex_arr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, figure->index_buf);
    glDrawElements(GL_TRIANGLES, figure->points, GL_UNSIGNED_INT, 0);
}


draw_gl *draw_gl_init_figure32_2t(const figure32_2t* figure) {
    draw_gl *out = malloc(sizeof(draw_gl));

    glGenBuffers(1, &out->vertex_buf);
    glGenBuffers(1, &out->color_buf);
    glGenBuffers(1, &out->index_buf);
    glGenVertexArrays(1, &out->vertex_arr);
    
    glBindVertexArray(out->vertex_arr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, out->vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, figure->vertex_num * sizeof(f32_2t), figure->vertex, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(f32_2t), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, out->color_buf);
    glBufferData(GL_ARRAY_BUFFER, figure->vertex_num * sizeof(color), figure->colors, GL_STREAM_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(color), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out->index_buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, figure->faces_num * sizeof(face), figure->faces, GL_STREAM_DRAW);

    out->points = figure->faces_num * 3;

    return out;
}


void draw_gl_update_figure32_2t(draw_gl *dst, const figure32_2t *figure) {
    glBindBuffer(GL_ARRAY_BUFFER, dst->vertex_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, figure->vertex_num * sizeof(f32_2t), figure->vertex);

    glBindBuffer(GL_ARRAY_BUFFER, dst->color_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, figure->vertex_num * sizeof(color), figure->colors);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dst->index_buf);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, figure->faces_num * sizeof(face), figure->faces);
}


draw_gl* draw_gl_init_pobj32_2t(const pobj32_2t *obj) {
    return draw_gl_init_figure32_2t(obj->figure);
}


void draw_gl_update_pobj32_2t(draw_gl *dst, const pobj32_2t *obj) {
    draw_gl_update_figure32_2t(dst, obj->figure);
}


draw_gl *draw_gl_init_scene32_2t(const scene32_2t *scene) {
    draw_gl *out = malloc(sizeof(draw_gl));

    uint32_t total_vertex = 0, total_faces = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        total_vertex += scene->objects[i].figure->vertex_num;
        total_faces += scene->objects[i].figure->faces_num;
    }

    glGenBuffers(1, &out->vertex_buf);
    glGenBuffers(1, &out->color_buf);
    glGenBuffers(1, &out->index_buf);
    glGenVertexArrays(1, &out->vertex_arr);
    
    glBindVertexArray(out->vertex_arr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, out->vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, total_vertex * sizeof(f32_2t), 0, GL_STREAM_DRAW);

    uint32_t pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        pobj32_2t *obj = scene->objects + i;
        glBufferSubData(GL_ARRAY_BUFFER, pos_write * sizeof(f32_2t), sizeof(f32_2t) * obj->figure->vertex_num, obj->figure->vertex);
    
        pos_write += obj->figure->vertex_num;
    }  

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(f32_2t), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, out->color_buf);
    glBufferData(GL_ARRAY_BUFFER, total_vertex * sizeof(color), 0, GL_STREAM_DRAW);
    
    pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        pobj32_2t *obj = scene->objects + i;
        glBufferSubData(GL_ARRAY_BUFFER, pos_write * sizeof(color), sizeof(color) * obj->figure->vertex_num, obj->figure->colors);

        pos_write += obj->figure->vertex_num;
    } 

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(color), 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out->index_buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, total_faces * sizeof(face), 0, GL_STREAM_DRAW); 

    pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        pobj32_2t *obj = scene->objects + i;
        glBufferSubData(GL_ARRAY_BUFFER, pos_write * sizeof(face), sizeof(face) * obj->figure->faces_num, obj->figure->faces);

        pos_write += obj->figure->faces_num;
    }

    out->points = total_faces * 3;

    return out;
}


void draw_gl_update_scene32_2t(draw_gl *dst, const scene32_2t *scene) {
    glBindBuffer(GL_ARRAY_BUFFER, dst->vertex_buf);
    uint32_t pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        figure32_2t *figure = scene->objects[i].figure;

        glBufferSubData(GL_ARRAY_BUFFER, pos_write * sizeof(f32_2t), figure->vertex_num * sizeof(f32_2t), figure->vertex);
        pos_write += figure->vertex_num;
    }

    glBindBuffer(GL_ARRAY_BUFFER, dst->color_buf);
    pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        figure32_2t *figure = scene->objects[i].figure;

        glBufferSubData(GL_ARRAY_BUFFER, pos_write * sizeof(color), figure->vertex_num * sizeof(color), figure->colors);
        pos_write += figure->vertex_num;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dst->index_buf);
    pos_write = 0;
    for (uint32_t i = 0; i < scene->objects_num; ++i) {
        figure32_2t *figure = scene->objects[i].figure;

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pos_write * sizeof(face), figure->faces_num * sizeof(color), figure->faces);
        pos_write += figure->faces_num;
    }
}


pipeline_gl *pipeline_gl_compile(const source_gl *source) {
    pipeline_gl *out = malloc(sizeof(pipeline_gl));

    out->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(out->vertex, 1, (const GLchar* const*) &source->vertex, 0);
    glCompileShader(out->vertex);

    out->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(out->fragment, 1, (const GLchar* const*) &source->fragment, 0);
    glCompileShader(out->fragment);

    out->program = glCreateProgram();
    glAttachShader(out->program, out->vertex);
    glAttachShader(out->program, out->fragment);

    if (source->geometry) {
        out->geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(out->geometry, 1, (const GLchar* const*)  &source->geometry, 0);
        glCompileShader(out->geometry);

        glAttachShader(out->program, out->geometry);
    } else out->geometry = 0;

    glLinkProgram(out->program);

    out->transform_location = glGetUniformLocation(out->program, "VTrans");

    return out;
}
