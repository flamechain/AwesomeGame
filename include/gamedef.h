#ifndef GAMEDEF_H
#define GAMEDEF_H

#include "utils.h"
#include "button.h"
#include "level.h"
#include "camera.h"

/// Creates a random level
/// @param x        x size of level
/// @param y        y size of level
/// @param width    width of level
/// @param height   height of level
/// @param tiles    possible tiles
/// @param renderer renderer
/// @param camera   camera
/// @return created level
Level GenerateRandomLevel(int x, int y, int width, int height, vector<SDL_Rect> tiles, SDL_Renderer * renderer, Camera * camera);

/// Activate title screen
/// @param active   list of buttons
void TitleScreen(map<string, Button*> active);

/// Activate options screen
/// @param active   list of buttons
void OptionsScreen(map<string, Button*> active);

/// Activate credits screen
/// @param active   list of buttons
void CreditsScreen(map<string, Button*> active);

/// Activate game screen
/// @param active   list of buttons
void GameScreen(map<string, Button*> active);

/// Activate pause screen
/// @param active   list of buttons
void PauseScreen(map<string, Button*> active);

/// Destroys all buttons
/// @param active   all buttons to destroy
void DestroyButtons(map<string, Button*> active);

#endif
