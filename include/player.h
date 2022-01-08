#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "game.h"
#include "tile.h"

struct Momentum {
    int x;
    int y;
};

class Player : public Tile {
private:

    SDL_Rect bounds_;
    Momentum speed_cap_;

public:

    Momentum speed;

    Player(SDL_Renderer * renderer, TileType type, SDL_Rect * tiles) : Tile(renderer, type, tiles) {
    }

    void SetSpeedCap(int x, int y) {
        this->speed_cap_.x = x;
        this->speed_cap_.y = y;
    }

    void SetPositionBounds(int x, int y, int w, int h) {
        this->bounds_.x = x;
        this->bounds_.y = y;
        this->bounds_.w = w;
        this->bounds_.h = h;
    }

    void Update() {
        if (this->speed.x > this->speed_cap_.x) this->speed.x = this->speed_cap_.x;
        if (this->speed.x < -this->speed_cap_.x) this->speed.x = -this->speed_cap_.x;
        if (this->speed.y > this->speed_cap_.y) this->speed.y = this->speed_cap_.y;
        if (this->speed.y < -this->speed_cap_.y) this->speed.y = -this->speed_cap_.y;

        this->hitbox_.x += this->speed.x;
        this->hitbox_.y += this->speed.y;

        if (this->hitbox_.x + this->hitbox_.w > this->bounds_.w) this->hitbox_.x = this->bounds_.w - this->hitbox_.w;
        if (this->hitbox_.x < this->bounds_.x) this->hitbox_.x = this->bounds_.x;
        if (this->hitbox_.y + this->hitbox_.h > this->bounds_.h) this->hitbox_.y = this->bounds_.h - this->hitbox_.h;
        if (this->hitbox_.y < this->bounds_.y) this->hitbox_.y = this->bounds_.y;
    }

};

#endif
