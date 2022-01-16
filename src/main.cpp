#include "game.h"

GameState gameState;
vector<SDL_Rect> tileSheet;

int main(int argc, char ** argv) {
    RunGame(1920, 1080, "AwesomeGame", true, GAME_RENDERER_ACCELERATED);

    return 0;
}
