#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "utils.h"
#include "screen.h"
#include "game.h"
#include "init.h"

/// Darkens a button bg color
/// @param screen   parent
/// @param uid      button uid
void DarkenButton(Screen * screen, string uid);

/// Lightens a button bg color
/// @param screen   parent
/// @param uid      button uid
void LightenButton(Screen * screen, string uid);

/// Switch to title screen
/// @param screen   parent
/// @param uid      button uid
void GotoTitle(Screen * screen, string uid);

/// Switch to game screen
/// @param screen   parent
/// @param uid      button uid
void GotoGame(Screen * screen, string uid);

/// Switch to options screen
/// @param screen   parent
/// @param uid      button uid
void GotoOptions(Screen * screen, string uid);

/// Switch to credits screen
/// @param screen   parent
/// @param uid      button uid
void GotoCredits(Screen * screen, string uid);

/// Switch to pause screen
/// @param screen   parent
/// @param uid      button uid
void GotoPause(Screen * screen, string uid);

/// Triggers last event loop
/// @param screen   parent
/// @param uid      button uid
void StopGame(Screen * screen, string uid);

#endif
