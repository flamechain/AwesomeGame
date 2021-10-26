#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "display.h"

#include "GL/glew.h"
#include <GL/GL.h>
// #define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// #include <GL/GLU.h>
// #include <GL/glut.h>
// #include "GL/freeglut.h"

class GameTime {
public:
    double DeltaTime;
    double TotalElapsedSeconds;

    GameTime() {
        this->DeltaTime = 0;
        this->TotalElapsedSeconds = 0;
    }
};

class Game {
private:
    GLuint vao;
    GLuint vbo;
    GLuint shader;

    int InitialWindowWidth;
    int InitialWindowHeight;
    char * InitialWindowTitle;

public:
    Game(int width, int height, const char * title) {
        this->InitialWindowWidth = width;
        this->InitialWindowHeight = height;
        this->InitialWindowTitle = (char *)title;
    }

private:
    void Initalize();
    int LoadContent();

    void Update();
    void Render(GameTime gameTime, DisplayManager displayManager);

public:
    void Run();
};

#endif
