#include "pause_screen.h"

GAME_START

double FadeIn(Screen& screen, double current, double decrease) {
    double new_current = current - decrease;
    // also do with children?
    if (new_current < 0) new_current = 0;
    Color origin = screen.GetColor();
    Color next;
    next.r = (255 - origin.r)*(new_current) + origin.r;
    next.g = (255 - origin.g)*(new_current) + origin.g;
    next.b = (255 - origin.b)*(new_current) + origin.b;
    screen.SetRenderColor(next);

    screen.SetTransparency(new_current);

    return new_current;
}

void HandlePauseScreen(Screen& game, Screen& pause, Screen& background, double& fade_level) {
    float decrease = 0.08;

    if (fade_level > 0) {
        fade_level = FadeIn(pause, fade_level, decrease);
    }

    game.TempShade(0.6);
    background.TempShade(0.6);
    background.Render();
    game.Render();
    pause.Render();
}

GAME_END
