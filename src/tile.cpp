#include "tile.h"

SDL_Rect * InitTiles() {
    const int tilecount = 4;
    SDL_Rect * tiles = new SDL_Rect[tilecount];

    tiles[TileType::GrassPathStrait].x = 0;
    tiles[TileType::GrassPathStrait].y = 0;

    tiles[TileType::GrassPathCenter].x = 16;
    tiles[TileType::GrassPathCenter].y = 0;

    tiles[TileType::GrassPathCorner].x = 32;
    tiles[TileType::GrassPathCorner].y = 0;

    tiles[TileType::DirtBlood].x = 48;
    tiles[TileType::DirtBlood].y = 0;

    for (int i=0; i<tilecount; i++) {
        tiles[i].w = 16;
        tiles[i].h = 16;
    }

    return tiles;
}
