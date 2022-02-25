#include "game_screen.h"

GAME_START

void HandleGameScreen(Screen& screen) {
    screen.TempShade(1);

    // check player movement
    SDL_Point offset = {0, 0};
    if (game_state.keyboard['w']) offset.y = -screen.Creature["player"].Speed.y;
    if (game_state.keyboard['s']) offset.y = screen.Creature["player"].Speed.y;
    if (game_state.keyboard['a']) offset.x = -screen.Creature["player"].Speed.x;
    if (game_state.keyboard['d']) offset.x = screen.Creature["player"].Speed.x;

    if (game_state.keyboard['w'] && game_state.keyboard['s']) offset.y = 0;
    if (game_state.keyboard['a'] && game_state.keyboard['d']) offset.x = 0;

    SDL_Point gridpos;
    gridpos.x = screen.Creature["player"].GetRect().x / TILE_SIZE + TILE_SIZE;
    gridpos.y = screen.Creature["player"].GetRect().y / TILE_SIZE + TILE_SIZE;

    // screen.Level[screen.Level.GetCurrent()].SetTile(gridpos.x, gridpos.y, TileType::FloorCrack1);

    if (screen.Creature["player"].IsCenteredX(screen)) {
        DebugOutput(" Moved on x-axis\n");
        screen.Move(offset.x, 0);
    }
    if (screen.Creature["player"].IsCenteredY(screen)) {
        DebugOutput(" Moved on y-axis\n");
        screen.Move(0, offset.y);
    }
    screen.Creature["player"].Update(offset, screen.Level[screen.Level.GetCurrent()]);

    screen.Render();
}

GAME_END
