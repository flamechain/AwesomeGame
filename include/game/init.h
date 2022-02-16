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

extern GameState game_state;
extern vector<SDL_Rect> tileSheet;

/// Updates loading screen bar
/// @param screen   location of loading screen
/// @param renderer global renderer
/// @param change   how much to change the bar (px)
void UpdateLoadingBar(Screen& screen, SDL_Renderer *renderer, int change);

/// Initializes all the game content
/// @param title    window title
/// @param width    window width
/// @param height   window height
/// @param debug    if the game is running in debug mode
/// @param screens  where to store all the game screens
/// @param flags    window and renderer creation data
/// @param window   where to store global window
/// @return created global renderer
SDL_Renderer * InitializeGame(string title, int width, int height, bool debug, vector<Screen>& screens, int flags, SDL_Window *&window);

/// Unloads all content
/// @param screens  all screens
/// @param renderer global renderer
/// @param window   global window
/// @param debug    if program is in debug mode
void DestroyGame(vector<Screen>& screens, SDL_Renderer *renderer, SDL_Window *window, bool debug);

#endif
