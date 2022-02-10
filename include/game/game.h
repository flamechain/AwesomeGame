#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "engine.h"

/// Runs game
/// @param Width    window width
/// @param Height   window height
/// @param Title    display title
/// @param Debug    run in debug mode
/// @param Flags    display flags
/// @return error
int RunGame(int Width, int Height, string Title, bool Debug, int Flags = GAME_WINDOW_WINDOWED);

class GameState {
private:
    bool running_;
    unsigned int screen_;

public:

    map<char, bool> keyboard;
    SDL_Point mouse;

    GameState() {
        this->running_ = true;
    }

    /// If game is running
    /// @return game running
    bool IsRunning() const {
        return this->running_;
    }

    /// Stops game running var
    void StopGame() {
        this->running_ = false;
    }

    /// Sets current screen
    /// @param type screen uid
    void SetScreen(unsigned int uid) {
        this->screen_ = uid;
    }

    /// Gets curernt screen
    /// @return current screen uid
    unsigned int CurrentScreen() const {
        return this->screen_;
    }

};

#endif
