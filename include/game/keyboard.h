#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "game.h"
#include "init.h"

extern GameState gameState;

/// Handles all SDL events
/// @param screens  all screens
void HandleSDLEvents(Screen * screens);

#endif
