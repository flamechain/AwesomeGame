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
int RunGame(int Width, int Height, const char * Title, bool Debug, int Flags = GAME_WINDOW_WINDOWED);

enum class Menu {
    None = 0,
    Pause = 1,
    Lose = 2,
    Win = 3,
    Title,
    Options,
    Credits
};

class GameState {
private:
    bool running_;
    Menu menu_type_;

public:

    GameState() {
        this->running_ = true;
        this->menu_type_ = Menu::None;
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

    /// Sets current menu
    /// @param type menu type based on enum Menu
    void SetMenu(Menu type) {
        this->menu_type_ = type;
    }

    /// Gets curernt menu
    /// @return current menu entry in Menu enum
    Menu GetMenu() const {
        return this->menu_type_;
    }

};

#endif
