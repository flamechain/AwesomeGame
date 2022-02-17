#include "generation.h"

void GenerateRandomLevel(int x, int y, Level& level) {
    // Level level = Level(x + 2, y + 3); // level grid size
    // level.StartPos(1, 1);
    // int posx = 0;
    // int posy = 0;

    // for (int i=0; i<y+2; i++) {
    //     for (int j=0; j<x+2; j++) {
    //         if (i == 0) {
    //             level.SetTile(j, i, TileType::Roof1);
    //             level.RotateTile(j, i, 90);
    //         } else if (i == y + 1) {
    //             level.SetTile(j, i, TileType::Roof1);
    //             level.RotateTile(j, i, -90);
    //         } else if (j == 0) {
    //             level.SetTile(j, i, TileType::Roof1);
    //             level.RotateTile(j, i, 0);
    //         } else if (j == x + 1) {
    //             level.SetTile(j, i, TileType::Roof1);
    //             level.RotateTile(j, i, 180);
    //         } else {
    //             level.SetTile(j, i, TileType::Floor);
    //         }
    //         if ((i == 0 || i == y + 1) && (j == 0 || j == x + 1)) {
    //             level.SetTile(j, i, TileType::Roof);
    //         }
    //         if ((i == 1) && !(j == 0 || j == x + 1)) {
    //             level.SetTile(j, i, TileType::Brick);
    //         }
    //         level.SetTilePosition(j, i, posx, posy);
    //         level.ResizeTile(j, i, TILE_SIZE, TILE_SIZE);
    //         posx += TILE_SIZE;
    //     }
    //     posy += TILE_SIZE;
    //     posx = 0;
    // }
    printf("r\n");

    level.Resize(5, 5);
    printf("r\n");

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            level.SetTile(i, j, TileType::Floor);
            level.SetTilePosition(i, j, i*TILE_SIZE, j*TILE_SIZE);
            // level.ResizeTile(i, j, TILE_SIZE, TILE_SIZE);
        }
    }
    printf("r\n");
}
