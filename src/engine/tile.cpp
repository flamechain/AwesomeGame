#include "tile.h"

GAME_START

vector<SDL_Rect> InitTiles() {
    const int kTileCount = 20;
    vector<SDL_Rect> tiles;

    for (int i=0; i<kTileCount; i++) {
        SDL_Rect temp;
        temp.w = SPRITE_SIZE;
        temp.h = SPRITE_SIZE;
        tiles.push_back(temp);
    }

    tiles[static_cast<int>(TileType::None)].x = 0;
    tiles[static_cast<int>(TileType::None)].y = 0;
    tiles[static_cast<int>(TileType::None)].w = 0;
    tiles[static_cast<int>(TileType::None)].h = 0;

    tiles[static_cast<int>(TileType::Floor)].x = 0;
    tiles[static_cast<int>(TileType::Floor)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack1)].x = SPRITE_SIZE;
    tiles[static_cast<int>(TileType::FloorCrack1)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack2)].x = SPRITE_SIZE*2;
    tiles[static_cast<int>(TileType::FloorCrack2)].y = 0;

    tiles[static_cast<int>(TileType::FloorCrack3)].x = SPRITE_SIZE*3;
    tiles[static_cast<int>(TileType::FloorCrack3)].y = 0;

    tiles[static_cast<int>(TileType::Roof)].x = SPRITE_SIZE*4;
    tiles[static_cast<int>(TileType::Roof)].y = 0;

    tiles[static_cast<int>(TileType::Roof1)].x = SPRITE_SIZE*5;
    tiles[static_cast<int>(TileType::Roof1)].y = 0;

    tiles[static_cast<int>(TileType::Roof2)].x = SPRITE_SIZE*6;
    tiles[static_cast<int>(TileType::Roof2)].y = 0;

    tiles[static_cast<int>(TileType::Roof3)].x = SPRITE_SIZE*7;
    tiles[static_cast<int>(TileType::Roof3)].y = 0;

    tiles[static_cast<int>(TileType::Roof4)].x = SPRITE_SIZE*8;
    tiles[static_cast<int>(TileType::Roof4)].y = 0;

    tiles[static_cast<int>(TileType::Brick)].x = SPRITE_SIZE*9;
    tiles[static_cast<int>(TileType::Brick)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack1)].x = SPRITE_SIZE*10;
    tiles[static_cast<int>(TileType::BrickCrack1)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack2)].x = SPRITE_SIZE*11;
    tiles[static_cast<int>(TileType::BrickCrack2)].y = 0;

    tiles[static_cast<int>(TileType::BrickCrack3)].x = SPRITE_SIZE*12;
    tiles[static_cast<int>(TileType::BrickCrack3)].y = 0;

    // TODO rearrange tilesheet so these values aren't all over the place
    tiles[static_cast<int>(TileType::PlayerLeftStill)].x = SPRITE_SIZE*4;
    tiles[static_cast<int>(TileType::PlayerLeftStill)].y = SPRITE_SIZE;

    tiles[static_cast<int>(TileType::PlayerLeft1)].x = 0;
    tiles[static_cast<int>(TileType::PlayerLeft1)].y = SPRITE_SIZE;

    tiles[static_cast<int>(TileType::PlayerLeft2)].x = SPRITE_SIZE*2;
    tiles[static_cast<int>(TileType::PlayerLeft2)].y = SPRITE_SIZE;

    tiles[static_cast<int>(TileType::PlayerRightStill)].x = SPRITE_SIZE*5;
    tiles[static_cast<int>(TileType::PlayerRightStill)].y = SPRITE_SIZE;

    tiles[static_cast<int>(TileType::PlayerRight1)].x = SPRITE_SIZE;
    tiles[static_cast<int>(TileType::PlayerRight1)].y = SPRITE_SIZE;

    tiles[static_cast<int>(TileType::PlayerRight2)].x = SPRITE_SIZE*3;
    tiles[static_cast<int>(TileType::PlayerRight2)].y = SPRITE_SIZE;

    return tiles;
}

GAME_END
