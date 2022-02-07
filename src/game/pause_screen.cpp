#include "pause_screen.h"

float FadeIn(Screen& screen, float current, float decrease) {
    float newCur = current - decrease;
    // also do with children?
    if (newCur < 0) newCur = 0;
    Color origin = screen.GetColor();
    Color next;
    next.r = (255 - origin.r)*(newCur) + origin.r;
    next.g = (255 - origin.g)*(newCur) + origin.g;
    next.b = (255 - origin.b)*(newCur) + origin.b;
    screen.SetRenderColor(next);

    screen.SetTransparency(newCur);

    return newCur;
}

void HandlePauseScreen(Screen& game, Screen& pause, Screen& background) {
    // float decrease = 0.08;

    // if (fadeInLevel > 0) {
    //     fadeInLevel = FadeIn(pause, fadeInLevel, decrease);
    // }

    game.TempShade(0.6);
    background.TempShade(0.6);
    background.Render();
    game.Render();
    pause.Render();
}
