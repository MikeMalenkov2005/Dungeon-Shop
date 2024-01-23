#include "framework.hpp"

#include "scene.hpp"

void ErrorCallback(int error, const char* description);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void CharCallback(GLFWwindow* window, unsigned int codepoint);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

static struct {
    int xpos;
    int ypos;
    int w_width;
    int w_height;
    int f_width;
    int f_height;
    int refreshRate;
    GLFWmonitor* monitor;
} window_state;

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Error: Failed to initialize GLFW!\n");
        return 1;
    }
    glfwSetErrorCallback(ErrorCallback);

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
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

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCharCallback(window, CharCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetWindowUserPointer(window, NULL);
    glfwShowWindow(window);
    glfwSwapInterval(0);

    glClearColor(0, 0, 0, 1);

    clock_t t = clock();
    while (!glfwWindowShouldClose(window)) {
        Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        if (scene) scene->Render();
        clock_t tt = clock();
        if (scene) scene->Update(window, ((double) (tt - t)) / CLOCKS_PER_SEC);
        if (tt - t) t = tt;
        glfwPollEvents();
    }

    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    glfwSetWindowUserPointer(window, NULL);
    if (scene) delete scene;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void ErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error %u: %s\n", error, description);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    if (glfwGetCurrentContext() == window) {
        glViewport(0, 0, width, height);
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    if (action == GLFW_REPEAT && key == GLFW_KEY_F11) {
        ToggleFullscreen(window);
    } else if (scene) {
        switch (action) {
        case GLFW_RELEASE:
            scene->OnButtonRelease(window, KEYBOARD, key, mods);
            break;
        case GLFW_PRESS:
            scene->OnButtonPress(window, KEYBOARD, key, mods);
            break;
        case GLFW_REPEAT:
            scene->OnButtonRepeat(window, KEYBOARD, key, mods);
            break;
        }
    }
}

void CharCallback(GLFWwindow* window, unsigned int codepoint) {
    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    if (scene) scene->OnCharPrint(window, codepoint);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    if (scene) scene->OnMouseScroll(window, xoffset, yoffset);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    if (scene) scene->OnMouseMove(window, xpos, ypos);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Scene* scene = (Scene*) glfwGetWindowUserPointer(window);
    if (scene) {
        switch (action) {
        case GLFW_RELEASE:
            scene->OnButtonRelease(window, MOUSE, button, mods);
            break;
        case GLFW_PRESS:
            scene->OnButtonPress(window, MOUSE, button, mods);
            break;
        case GLFW_REPEAT:
            scene->OnButtonRepeat(window, MOUSE, button, mods);
            break;
        }
    }
}

void ToggleFullscreen(GLFWwindow* window) {
    if (glfwGetWindowMonitor(window)) {
        glfwSetWindowMonitor(window, NULL, window_state.xpos, window_state.ypos, window_state.w_width, window_state.w_height, GLFW_DONT_CARE);
    } else {
        if (!window_state.monitor) window_state.monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidmode = glfwGetVideoMode(window_state.monitor);
        glfwSetWindowMonitor(window, window_state.monitor, 0, 0, window_state.f_width ? window_state.f_width : vidmode->width, window_state.f_height ? window_state.f_height : vidmode->height, window_state.refreshRate ? window_state.refreshRate : vidmode->refreshRate);
    }
}

bool IsFullscreen(GLFWwindow* window) {
    return glfwGetWindowMonitor(window) != NULL;
}
