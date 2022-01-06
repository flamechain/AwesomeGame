#ifndef GAME_H
#define GAME_H

#include "utils.h"

#define GAME_WINDOW_WINDOWED 0
#define GAME_WINDOW_FULLSCREEN 1
#define GAME_RENDERER_ACCELERATED 2

#define GAME_ERROR_SDL_FAIL 1
#define GAME_ERROR_IMAGE_FAIL 2
#define GAME_ERROR_WINDOW_FAIL 3
#define GAME_ERROR_RENDERER_FAIL 4
#define GAME_ERROR_GENERAL_FAIL 5

void ConsoleOutput(char * Message);

int InitializeEngine();

int CreateWindow(int Width, int Height, const char * Title, int Flags, SDL_Window * Window);

int CreateRenderer(SDL_Window * Window, SDL_Renderer * Renderer, int Flags);

int RunGame(int Width, int Height, const char * Title, int Flags = GAME_WINDOW_WINDOWED);

class GameState {
private:
    bool running_;

public:

    GameState() {
        this->running_ = true;
    }

    bool IsRunning() {
        return this->running_;
    }

    void StopGame() {
        this->running_ = false;
    }

};

#endif
