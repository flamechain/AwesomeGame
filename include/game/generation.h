#ifndef GENERATION_H
#define GENERATION_H

#include "utils.h"
#include "level.h"

/// Generates a random level
/// @param x        x grid size
/// @param y        y grid size
/// @return "finished" level (need to call Finalize on it after)
Level GenerateRandomLevel(int x, int y);

#endif
