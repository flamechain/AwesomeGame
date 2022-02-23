#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include "utils.h"
#include "game.h"
#include "screen.h"

extern GameState game_state;

/// Fades in from white on bg color
/// @param screen   screen
/// @param current  current percentage of color
/// @param decrease percent to get closer to original color
double FadeIn(Screen& screen, double current, double decrease);

/// Handles pause screen events and rendering
/// @param game         game screen
/// @param pause        pause screen
/// @param background   background screen
/// @param fade_level   fade rate
void HandlePauseScreen(Screen& game, Screen& pause, Screen& background, double& fade_level);

#endif
