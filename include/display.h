#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "utils.h"

#define GLFW_INCLUDE_NONE
// #define GLEW_STATIC
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// #include <GL/GLU.h>
// #include <GL/glut.h>
// #include "GL/freeglut.h"
// #include "GL/glew.h"
// #include <GL/GL.h>

class DisplayManager {
public:
    GLFWwindow * window;
    Vector2 windowSize;

    DisplayManager() {}

    // create window (context? current?)
    int CreateWinC(int width, int height, char * title);
    void CloseWinC();
};

#endif
