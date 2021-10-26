#include "display.h"

#include <GL/glew.h>
#include <GL/GL.h>

int DisplayManager::CreateWinC(int width, int height, char * title) {
    this->WindowSize = Vector2(width, height);

    glfwInit();
    glewInit();

    // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    this->Window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!this->Window) {
        return 0;
    }

    int x, y, w, h;
    GLFWmonitor * screen = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(screen, &x, &y, &w, &h);

    glfwSetWindowPos(this->Window, (w-width)/2, (h-height)/2);

    glfwMakeContextCurrent(this->Window);

    glViewport(0, 0, width, height);
    glfwSwapInterval(0); // no vsync

    return 1;
}

void DisplayManager::CloseWinC() {
    glfwTerminate();
}
