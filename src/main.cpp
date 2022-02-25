#include "game.h"

// GAME_START

int main(int argc, char **argv) {
    game::debug_mode = true;
    game::RunGame(WINDOW_WIDTH, WINDOW_HEIGHT, "Dissension", GAME_RENDERER_ACCELERATED);

    return 0;
}

// GAME_END
