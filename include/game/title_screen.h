#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "utils.h"
#include "game.h"
#include "screen.h"

GAME_START

// extern GameState game_state;

/// Handles title screen events and rendering
/// @param screen   screen
void HandleTitleScreen(Screen& screen);

GAME_END

#endif
