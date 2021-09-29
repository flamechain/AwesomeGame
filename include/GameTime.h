#ifndef GAMETIME_H
#define GAMETIME_H

#include "utils.h"

class GameTime {
public:
    double DeltaTime;
    double TotalElapsedSeconds;

    GameTime() {
        this->DeltaTime = 0;
        this->TotalElapsedSeconds = 0;
    }
};

#endif
