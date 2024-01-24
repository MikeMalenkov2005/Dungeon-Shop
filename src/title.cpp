#include "title.hpp"

void TitleScreen::Render() {
}

void TitleScreen::Update(GLFWwindow* window, double delta) {
}

void TitleScreen::OnButtonRelease(GLFWwindow* window, ButtonSource source, int button, int mods) {
    if (source == KEYBOARD && button == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void TitleScreen::OnButtonPress(GLFWwindow* window, ButtonSource source, int button, int mods) {
}

void TitleScreen::OnButtonRepeat(GLFWwindow* window, ButtonSource source, int button, int mods) {
}

void TitleScreen::OnCharPrint(GLFWwindow* window, unsigned int codepoint) {
}

void TitleScreen::OnMouseScroll(GLFWwindow* window, double x, double y) {
}

void TitleScreen::OnMouseMove(GLFWwindow* window, double x, double y) {
}

