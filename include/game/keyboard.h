#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "game.h"
#include "init.h"

GAME_START

// extern GameState game_state;

/// Handles all SDL events
/// @param screens  all screens
void HandleSDLEvents(vector<Screen>& screens);

GAME_END

#endif
