#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void dsErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error %u: %s\n", error, description);
}

void dsFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    if (glfwGetCurrentContext() == window) {
        glViewport(0, 0, width, height);
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Error: Failed to initialize GLFW!\n");
        return 1;
    }
    glfwSetErrorCallback(dsErrorCallback);
    glfwDefaultWindowHints();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Dungeon Shop", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Error: Failed to create a window!\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwDestroyWindow(window);
        return 1;
    }
    glfwSetFramebufferSizeCallback(window, dsFramebufferSizeCallback);
    glClearColor(1, 0, 0, 1);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
