#include "game.h"

GameState gameState;

int main(int argc, char ** argv) {
    RunGame(1920, 1080, "AwesomeGame", GAME_RENDERER_ACCELERATED);

    return 0;
}
