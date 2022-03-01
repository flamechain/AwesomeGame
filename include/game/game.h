#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "engine.h"

GAME_START

/// Runs game
/// @param width    window width
/// @param height   window height
/// @param title    display title
/// @param flags    display flags
/// @return error
int RunGame(int width, int height, string title, int flags = GAME_WINDOW_WINDOWED);

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

extern GameState game_state;

GAME_END

#endif
