#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "DisplayManager.h"
#include "GameTime.h"

class Game {
protected:
    int InitialWindowWidth;
    int InitialWindowHeight;
    char * InitialWindowTitle;

public:
    Game(int width, int height, const char * title) {
        this->InitialWindowWidth = width;
        this->InitialWindowHeight = height;
        this->InitialWindowTitle = (char *)title;
    }

protected:
    void Initalize();
    void LoadContent();

    void Update();
    void Render(GameTime gameTime, DisplayManager displayManager);

public:
    void Run();
};

#endif
