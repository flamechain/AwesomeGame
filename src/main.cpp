#include "game.h"

GameState game_state;
vector<SDL_Rect> tileSheet;

int main(int argc, char **argv) {
    RunGame(WINDOW_WIDTH, WINDOW_HEIGHT, "Dissension", true, GAME_RENDERER_ACCELERATED);

    return 0;
}
