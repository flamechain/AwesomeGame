#ifndef GENERATION_H
#define GENERATION_H

#include "utils.h"
#include "level.h"

/// Generates a random level
/// @param x        x grid size
/// @param y        y grid size
/// @param level    level to store tiles into
void GenerateRandomLevel(int x, int y, Level& level);

#endif
