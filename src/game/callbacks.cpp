#include "callbacks.h"

void DarkenButton(Screen * screen, string uid) {
    screen->Button[uid].TempShade(0.7);
}

void LightenButton(Screen * screen, string uid) {
    screen->Button[uid].TempShade(1);
}

void GotoTitle(Screen * screen, string uid) {
    gameState.SetScreen(TITLE_SCREEN);
}

void GotoGame(Screen * screen, string uid) {
    gameState.SetScreen(GAME_SCREEN);
}

void GotoOptions(Screen * screen, string uid) {
    gameState.SetScreen(OPTIONS_SCREEN);
}

void GotoCredits(Screen * screen, string uid) {
    gameState.SetScreen(CREDITS_SCREEN);
}

void GotoPause(Screen * screen, string uid) {
    gameState.SetScreen(PAUSE_SCREEN);
}

void StopGame(Screen * screen, string uid) {
    gameState.StopGame();
}
