#include "callbacks.h"

GAME_START

void DarkenButton(Screen& screen, string uid) {
    screen.Button[uid].TempShade(0.7);
}

void LightenButton(Screen& screen, string uid) {
    screen.Button[uid].TempShade(1);
}

void GotoTitle(Screen& screen, string uid) {
    game_state.SetScreen(TITLE_SCREEN);
}

void GotoGame(Screen& screen, string uid) {
    game_state.SetScreen(GAME_SCREEN);
}

void GotoOptions(Screen& screen, string uid) {
    game_state.SetScreen(OPTIONS_SCREEN);
}

void GotoCredits(Screen& screen, string uid) {
    game_state.SetScreen(CREDITS_SCREEN);
}

void GotoPause(Screen& screen, string uid) {
    game_state.SetScreen(PAUSE_SCREEN);
}

void StopGame(Screen& screen, string uid) {
    game_state.StopGame();
}

GAME_END
