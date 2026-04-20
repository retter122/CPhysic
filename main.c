#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./CPhysic/cphysic.h"


// WINDOW DATA

static GLFWwindow *glfw_wnd = 0;
static uint32_t wnd_width = 300, wnd_height = 300;


// WINDOW CALLBACKS

void wnd_resize(GLFWwindow *wnd, int width, int height) {
    wnd_width = (uint32_t)width, wnd_height = (uint32_t)height;
    glViewport(0, 0, wnd_width, wnd_height);
}


// MAIN FUNCTION

int main() {
    // INIT OPEN GL

    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    // CREATE WINDOW

    glfw_wnd = glfwCreateWindow(wnd_width, wnd_height, "test", 0, 0);
    
    glfwMakeContextCurrent(glfw_wnd);
    gladLoadGL(glfwGetProcAddress);

    glClearColor(0, 0, 0, 1.f);
    glViewport(0, 0, wnd_width, wnd_height);

    // INITIALIZE EVENTS

    glfwSetFramebufferSizeCallback(glfw_wnd, wnd_resize);

    // MAIN CYCLE

    while (!glfwWindowShouldClose(glfw_wnd)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(glfw_wnd);
    }

    glfwTerminate();
    return 0;
}
