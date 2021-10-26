#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "utils.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GL.h>

class DisplayManager {
public:
    GLFWwindow * Window;
    Vector2 WindowSize;

    DisplayManager() {}

    int CreateWinC(int width, int height, char * title);
    void CloseWinC();
};

#endif
