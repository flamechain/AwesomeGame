#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "display.h"

class GameTime {
private:
    GLuint vao;
    GLuint vbo;

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
    void LoadContent();

    void Update();
    void Render(GameTime gameTime, DisplayManager displayManager);

public:
    void Run();
};

#endif
