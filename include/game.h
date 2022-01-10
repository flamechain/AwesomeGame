#ifndef GAME_H
#define GAME_H

#include "utils.h"

#define FRAMERATE 60

#define GAME_WINDOW_WINDOWED 0
#define GAME_WINDOW_FULLSCREEN 1
#define GAME_RENDERER_ACCELERATED 2

#define GAME_ERROR_SDL_FAIL 1
#define GAME_ERROR_IMAGE_FAIL 2
#define GAME_ERROR_WINDOW_FAIL 3
#define GAME_ERROR_RENDERER_FAIL 4
#define GAME_ERROR_GENERAL_FAIL 5
#define GAME_ERROR_TTF_FAIL 6

/// Initializes libraries
/// @return error
int InitializeEngine();

/// Creates a window
/// @param Width    window width
/// @param Height   window height
/// @param Title    display title
/// @param Flags    display flags
/// @param Window   window storage
/// @return error
int CreateWindow(int Width, int Height, const char * Title, int Flags, SDL_Window * Window);

/// Creates display renderer
/// @param Window   created window
/// @param Renderer renderer storage
/// @param Flags    render flags
/// @return error
int CreateRenderer(SDL_Window * Window, SDL_Renderer * Renderer, int Flags);

/// Runs game
/// @param Width    window width
/// @param Height   window height
/// @param Title    display title
/// @param Flags    display flags
/// @return error
int RunGame(int Width, int Height, const char * Title, int Flags = GAME_WINDOW_WINDOWED);

enum Menu {
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
