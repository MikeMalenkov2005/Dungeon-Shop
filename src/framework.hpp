#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <time.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

void ToggleFullscreen(GLFWwindow* window);
bool IsFullscreen(GLFWwindow* window);

enum ButtonSource {
    KEYBOARD,
    MOUSE
};

#endif
