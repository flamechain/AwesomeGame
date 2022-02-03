#include "handlers.h"

void HandleGameScreen(Screen * screen) {
    screen->TempShade(1);

    // check player movement
    SDL_Point offset = {0, 0};
    if (gameState.keyboard['w']) offset.y = -screen->Creature["player"].Speed.y;
    if (gameState.keyboard['s']) offset.y = screen->Creature["player"].Speed.y;
    if (gameState.keyboard['a']) offset.x = -screen->Creature["player"].Speed.x;
    if (gameState.keyboard['d']) offset.x = screen->Creature["player"].Speed.x;

    if (gameState.keyboard['w'] && gameState.keyboard['s']) offset.y = 0;
    if (gameState.keyboard['a'] && gameState.keyboard['d']) offset.x = 0;

    SDL_Point gridpos;
    gridpos.x = screen->Creature["player"].GetRect().x / TILE_SIZE + TILE_SIZE;
    gridpos.y = screen->Creature["player"].GetRect().y / TILE_SIZE + TILE_SIZE;

    // screen.Level[screen.Level.GetCurrent()].SetTile(gridpos.x, gridpos.y, TileType::FloorCrack1);

    if (screen->Creature["player"].IsCenteredX(screen)) screen->Move(offset.x, 0);
    if (screen->Creature["player"].IsCenteredY(screen)) screen->Move(0, offset.y);
    screen->Creature["player"].Update(offset);

    screen->Render();
}
