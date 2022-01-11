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
/// @param Width    window width
/// @param Height   window height
/// @param Title    display title
/// @param Flags    display flags
/// @return window object
SDL_Window * CreateWindow(int Width, int Height, const char * Title, int Flags);

/// Creates display renderer
/// @param Window   created window
/// @param Flags    render flags
/// @return renderer object
SDL_Renderer * CreateRenderer(SDL_Window * Window, int Flags);

#endif
