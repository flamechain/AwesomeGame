#ifndef HANDLERS_H
#define HANDLERS_H

#include "utils.h"
#include "game.h"
#include "screen.h"

extern GameState gameState;

/// Handles options screen events and rendering
/// @param screen   screen
void HandleOptionsScreen(Screen * screen);

/// Handles credits screen events and rendering
/// @param screen   screen
void HandleCreditsScreen(Screen * screen);

/// Handles game screen events and rendering
/// @param screen   screen
void HandleGameScreen(Screen * screen);

/// Handles pause screen events and rendering
/// @param game   game screen
/// @param pause  pause screen
void HandlePauseScreen(Screen * game, Screen * pause);

/// Handles title screen events and rendering
/// @param screen   screen
void HandleTitleScreen(Screen * screen);

#endif
