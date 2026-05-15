#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./graphics_gl.h"

#include "../GLFW/glfw3.h"
#include "../glad/gl.h"
#include "../geometry/geometry.h"
#include "../physic/physic.h"


uint8_t init_gl() {
    return glfwInit();
}

window_gl *window_gl_create(uint32_t width, uint32_t height, const char *name) {
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

void window_gl_clear_color(window_gl *window, float r, float g, float b, float a) {
    glfwMakeContextCurrent(window);
    glClearColor(r, g, b, a);
}

void window_gl_clear(window_gl *window) {
    glfwMakeContextCurrent(window);
    
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT);
}


