#include "handlers.h"

void HandlePauseScreen(Screen * game, Screen * pause) {
    // float decrease = 0.08;

    // if (fadeInLevel > 0) {
    //     fadeInLevel = FadeIn(pause, fadeInLevel, decrease);
    // }

    game->TempShade(0.6);
    game->Render();
    pause->Render();
}
