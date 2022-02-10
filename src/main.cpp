#include "game.h"

GameState gameState;
vector<SDL_Rect> tileSheet;

int main(int argc, char ** argv) {
    RunGame(WINDOW_WIDTH, WINDOW_HEIGHT, "Dissension", true, GAME_RENDERER_ACCELERATED);

    return 0;
}
