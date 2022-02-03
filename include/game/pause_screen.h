#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include "utils.h"
#include "game.h"
#include "screen.h"

extern GameState gameState;

/// Fades in from white on bg color
/// @param screen   screen
/// @param current  current percentage of color
/// @param decrease percent to get closer to original color
float FadeIn(Screen * screen, float current, float decrease);

/// Handles pause screen events and rendering
/// @param game   game screen
/// @param pause  pause screen
void HandlePauseScreen(Screen * game, Screen * pause);

#endif
