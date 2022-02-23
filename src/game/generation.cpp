#include "generation.h"

Level GenerateRandomLevel(long long unsigned int x, long long unsigned int y) {

    vector<vector<LevelTile>> test_level = {
        {{TileType::Roof, 0}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof1, 90}, {TileType::Roof, 0}},
        {{TileType::Roof1, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Brick, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof1, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Floor, 0}, {TileType::Roof1, 180}},
        {{TileType::Roof, 0}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof1, 270}, {TileType::Roof, 0}}
    };

    Level level = Level(x + 2, y + 3); // level grid size + walls
    level.StartPos(1, 2);
    DebugOutput(true, "      Making tiles\n");

    for (long long unsigned int i=0; i<x+2; i++) {
        for (long long unsigned int j=0; j<y+3; j++) {
            level.InitTile(i, j, test_level[j][i].type);
            level.SetTilePosition(i, j, i*TILE_SIZE, j*TILE_SIZE);
            level.ResizeTile(i, j, TILE_SIZE, TILE_SIZE);
            level.RotateTile(i, j, test_level[j][i].rot);   
        }
    }

    return level;
}
