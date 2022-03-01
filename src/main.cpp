#include "game.h"

std::vector<SDL_Rect> game::tile_sheet;
bool game::debug_mode;
game::GameState game::game_state;

int main(int argc, char **argv) {
    game::debug_mode = true;
    game::RunGame(WINDOW_WIDTH, WINDOW_HEIGHT, "Dissension", GAME_RENDERER_ACCELERATED);

    return 0;
}
