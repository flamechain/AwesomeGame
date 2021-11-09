#include "display.h"

int DisplayManager::CreateWinC(int width, int height, char * title) {
    // this->WindowSize = Vector2(width, height);

    glfwInit();
    // glewInit();

    // opengl core 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // extra
    glfwWindowHint(GLFW_FOCUSED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    // widht, height, title, fullscreen, extra
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!this->window) {
        return 0;
    }

    // int x, y, w, h;
    // GLFWmonitor * screen = glfwGetPrimaryMonitor();
    // glfwGetMonitorWorkarea(screen, &x, &y, &w, &h);

    // glfwSetWindowPos(this->Window, (w-width)/2, (h-height)/2);

    glfwMakeContextCurrent(this->window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    glfwSwapInterval(0); // no vsync

    return 1;
}

void DisplayManager::CloseWinC() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}
