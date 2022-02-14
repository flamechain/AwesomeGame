#ifndef ENGINE_H
#define ENGINE_H

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
/// @param width    window width
/// @param height   window height
/// @param title    display title
/// @param flags    display flags
/// @return window object
SDL_Window *CreateWindow(int width, int height, string title, int flags);

/// Creates display renderer
/// @param window   created window
/// @param flags    render flags
/// @return renderer object
SDL_Renderer *CreateRenderer(SDL_Window *window, int flags);

#endif
