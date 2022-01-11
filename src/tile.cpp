#include "tile.h"

SDL_Rect * InitTiles() {
    const int tilecount = 10;
    SDL_Rect * tiles = new SDL_Rect[tilecount];

    tiles[(int)TileType::None].x = 0;
    tiles[(int)TileType::None].y = 0;

    tiles[(int)TileType::Grass].x = 16;
    tiles[(int)TileType::Grass].y = 0;

    tiles[(int)TileType::Path].x = 32;
    tiles[(int)TileType::Path].y = 0;

    tiles[(int)TileType::GrassPathStrait].x = 48;
    tiles[(int)TileType::GrassPathStrait].y = 0;

    tiles[(int)TileType::GrassPathCorner].x = 64;
    tiles[(int)TileType::GrassPathCorner].y = 0;

    tiles[(int)TileType::GrassPathT].x = 80;
    tiles[(int)TileType::GrassPathT].y = 0;

    tiles[(int)TileType::GrassPathCross].x = 96;
    tiles[(int)TileType::GrassPathCross].y = 0;

    tiles[(int)TileType::GrassPathEnd].x = 112;
    tiles[(int)TileType::GrassPathEnd].y = 0;

    tiles[(int)TileType::TestPlayer].x = 0;
    tiles[(int)TileType::TestPlayer].y = 16;

    for (int i=0; i<tilecount; i++) {
        tiles[i].w = 16;
        tiles[i].h = 16;
    }

    return tiles;
}
