#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "display.h"

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
    VAO vao;
    VBO vbo;
    EBO ebo;
    Shader shaderProgram;

    int InitialWindowWidth;
    int InitialWindowHeight;
    char * InitialWindowTitle;

public:
    Game(int width, int height, const char * title);

private:
    void Initalize();
    int LoadContent();

    void Update();
    void Render(GameTime gameTime, DisplayManager displayManager);

public:
    void Run();
};

#endif
