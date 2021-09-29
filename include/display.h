#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "utils.h"

class DisplayManager {
public:
    GLFWwindow * Window;
    Vector2 WindowSize;

    DisplayManager() {}

    int CreateWindow(int width, int height, char * title);
    void CloseWindow();
};

#endif
