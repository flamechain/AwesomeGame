#include "game.h"

GameState gameState;

int main(int argc, char ** argv) {
    // actual fullscreen means we have to handle alt+tab, no thanks
    // rendering like this looks like fullscreen but allows fast alt+tab auto handler
    RunGame(1920, 1080, "AwesomeGame", GAME_RENDERER_ACCELERATED);

    return 0;
}
