#include "tile.h"

GAME_START

vector<SDL_Rect> InitTiles() {
    const int kTileCount = 20;
    vector<SDL_Rect> tiles;

    for (int i=0; i<kTileCount; i++) {
        SDL_Rect temp;
        temp.w = 32;
        temp.h = 32;
        tiles.push_back(temp);
    }

    tiles[static_cast<int>(TileType::None)].x = 0;
    tiles[static_cast<int>(TileType::None)].y = 0;
    tiles[static_cast<int>(TileType::None)].w = 0;
    tiles[static_cast<int>(TileType::None)].h = 0;

    tiles[static_cast<int>(TileType::Floor)].x = 0;
    tiles[static_cast<int>(TileType::Floor)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack1)].x = 32;
    tiles[static_cast<int>(TileType::FloorCrack1)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack2)].x = 64;
    tiles[static_cast<int>(TileType::FloorCrack2)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack3)].x = 96;
    tiles[static_cast<int>(TileType::FloorCrack3)].y = 0;

    tiles[static_cast<int>(TileType::Roof)].x = 128;
    tiles[static_cast<int>(TileType::Roof)].y = 0;

    tiles[static_cast<int>(TileType::Roof1)].x = 160;
    tiles[static_cast<int>(TileType::Roof1)].y = 0;

    tiles[static_cast<int>(TileType::Roof2)].x = 192;
    tiles[static_cast<int>(TileType::Roof2)].y = 0;

    tiles[static_cast<int>(TileType::Roof3)].x = 224;
    tiles[static_cast<int>(TileType::Roof3)].y = 0;

    tiles[static_cast<int>(TileType::Roof4)].x = 256;
    tiles[static_cast<int>(TileType::Roof4)].y = 0;

    tiles[static_cast<int>(TileType::Brick)].x = 288;
    tiles[static_cast<int>(TileType::Brick)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack1)].x = 320;
    tiles[static_cast<int>(TileType::BrickCrack1)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack2)].x = 352;
    tiles[static_cast<int>(TileType::BrickCrack2)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack3)].x = 384;
    tiles[static_cast<int>(TileType::BrickCrack3)].y = 0;

    // TODO rearrange tilesheet so these values aren't all over the place
    tiles[static_cast<int>(TileType::PlayerLeftStill)].x = 128;
    tiles[static_cast<int>(TileType::PlayerLeftStill)].y = 32;

    tiles[static_cast<int>(TileType::PlayerLeft1)].x = 0;
    tiles[static_cast<int>(TileType::PlayerLeft1)].y = 32;

    tiles[static_cast<int>(TileType::PlayerLeft2)].x = 64;
    tiles[static_cast<int>(TileType::PlayerLeft2)].y = 32;

    tiles[static_cast<int>(TileType::PlayerRightStill)].x = 160;
    tiles[static_cast<int>(TileType::PlayerRightStill)].y = 32;

    tiles[static_cast<int>(TileType::PlayerRight1)].x = 32;
    tiles[static_cast<int>(TileType::PlayerRight1)].y = 32;

    tiles[static_cast<int>(TileType::PlayerRight2)].x = 96;
    tiles[static_cast<int>(TileType::PlayerRight2)].y = 32;

    return tiles;
}

GAME_END
