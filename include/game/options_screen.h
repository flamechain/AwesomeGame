#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

#include "utils.h"
#include "game.h"
#include "screen.h"

extern GameState game_state;

/// Handles options screen events and rendering
/// @param screen   screen
void HandleOptionsScreen(Screen& screen);

#endif
