#ifndef SCENE_HPP
#define SCENE_HPP

#include "framework.hpp"

class Scene {
    public:
    virtual void Render() {}
    virtual void Update(GLFWwindow* window, double delta) {}
    virtual void OnButtonRelease(GLFWwindow* window, ButtonSource source, int button, int mods) {}
    virtual void OnButtonPress(GLFWwindow* window, ButtonSource source, int button, int mods) {}
    virtual void OnButtonRepeat(GLFWwindow* window, ButtonSource source, int button, int mods) {}
    virtual void OnCharPrint(GLFWwindow* window, unsigned int codepoint) {}
    virtual void OnMouseScroll(GLFWwindow* window, double x, double y) {}
    virtual void OnMouseMove(GLFWwindow* window, double x, double y) {}
};

#endif
