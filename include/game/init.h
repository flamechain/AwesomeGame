#ifndef INIT_H
#define INIT_H

#include "utils.h"
#include "screen.h"
#include "engine.h"
#include "game.h"
#include "callbacks.h"
#include "generation.h"

#define LOADING_SCREEN 0
#define PAUSE_SCREEN 1
#define TITLE_SCREEN 2
#define GAME_SCREEN 3
#define OPTIONS_SCREEN 4
#define CREDITS_SCREEN 5
#define SAVE_SCREEN 6

extern GameState gameState;
extern vector<SDL_Rect> tileSheet;

/// Updates loading screen bar
/// @param screen   location of loading screen
/// @param renderer global renderer
/// @param change   how much to change the bar (px)
void UpdateLoadingBar(Screen * screen, SDL_Renderer * renderer, int change);

/// Initializes all the game content
/// @param Title    window title
/// @param Width    window width
/// @param Height   window height
/// @param Debug    if the game is running in debug mode
/// @param Screens  where to store all the game screens
/// @param Flags    window and renderer creation data
/// @param Window   where to store global window
/// @return created global renderer
SDL_Renderer * InitializeGame(string Title, int Width, int Height, bool Debug, vector<Screen*>& Screens, int Flags, SDL_Window * Window);

/// Unloads all content
/// @param Screens  all screens
/// @param Renderer global renderer
/// @param Window   global window
void DestroyGame(vector<Screen*>& Screens, SDL_Renderer * Renderer, SDL_Window * Window);

#endif
