#ifndef GENERATION_H
#define GENERATION_H

#include "utils.h"
#include "level.h"

GAME_START

struct LevelTile {
    TileType type;
    int rot;
};

/// Generates a random level
/// @param x        x grid size
/// @param y        y grid size
/// @return "finished" level (need to call Finalize on it after)
Level GenerateRandomLevel(long long unsigned int x, long long unsigned int y);

GAME_END

#endif
