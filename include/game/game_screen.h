#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "utils.h"
#include "game.h"
#include "screen.h"

GAME_START

// extern GameState game_state;

/// Handles game screen events and rendering
/// @param screen   screen
void HandleGameScreen(Screen& screen);

GAME_END

#endif
