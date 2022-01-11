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

    SDL_Rect real_hitbox_;
    SDL_Rect bounds_;
    Momentum speed_cap_;
    SDL_Point real_offset_;

public:

    Momentum speed;

    Player(SDL_Renderer * renderer, TileType type, SDL_Rect * tiles, Camera * camera) : Tile(renderer, type, tiles, camera) {
        this->SetSize(0, 0, this->hitbox_.w, this->hitbox_.h);
    }

    /// Gets colllision hitbox
    /// @return hitbox as rect
    SDL_Rect GetHitbox() const {
        return this->real_hitbox_;
    }

    /// Sets collision hitbox size
    /// @param x    x offset from render x
    /// @param y    y offset from render y
    /// @param w    width
    /// @param h    height
    void SetSize(int x, int y, int w, int h) {
        this->real_offset_.x = x;
        this->real_offset_.y = y;
        this->real_hitbox_.x = this->hitbox_.x + x;
        this->real_hitbox_.y = this->hitbox_.y + y;
        this->real_hitbox_.w = w;
        this->real_hitbox_.h = h;
    }

    /// Resizes tiles texture
    /// @param w    width
    /// @param h    height
    void Resize(int w, int h) {
        this->hitbox_.w = w;
        this->hitbox_.h = h;
        this->real_hitbox_.w = w;
        this->real_hitbox_.h = h;
    }

    /// Moves tiles texture
    /// @param x    x coord
    /// @param y    y coord
    void SetPosition(int x, int y) {
        this->hitbox_.x = x;
        this->hitbox_.y = y;
        this->real_hitbox_.x = this->hitbox_.x + this->real_offset_.x;
        this->real_hitbox_.y = this->hitbox_.y + this->real_offset_.y;
    }

    /// Set limit on speed
    /// @param x    x-direction speed cap
    /// @param y    y-direction speed cap
    void SetSpeedCap(int x, int y) {
        this->speed_cap_.x = x;
        this->speed_cap_.y = y;
    }

    /// Sets area player can move
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param w    boundary width
    /// @param h    boundary height
    void SetBounds(int x, int y, int w, int h) {
        this->bounds_.x = x;
        this->bounds_.y = y;
        this->bounds_.w = w;
        this->bounds_.h = h;
    }

    /// Moves player based on speed
    /// @param checkBounds  if to check bounds
    void Update(bool checkBounds = true) {
        if (!checkBounds) {
            this->hitbox_.x += this->speed.x;
            this->hitbox_.y += this->speed.y;
            this->real_hitbox_.x += this->speed.x;
            this->real_hitbox_.y += this->speed.y;
            return;
        }

        if (this->speed.x > this->speed_cap_.x) this->speed.x = this->speed_cap_.x;
        if (this->speed.x < -this->speed_cap_.x) this->speed.x = -this->speed_cap_.x;
        if (this->speed.y > this->speed_cap_.y) this->speed.y = this->speed_cap_.y;
        if (this->speed.y < -this->speed_cap_.y) this->speed.y = -this->speed_cap_.y;

        this->hitbox_.x += this->speed.x;
        int flipFlags = this->GetFlip();
        if (this->speed.x < 0) flipFlags |= SDL_FLIP_HORIZONTAL;
        else if (this->speed.x > 0) flipFlags = SDL_FLIP_NONE;
        this->hitbox_.y += this->speed.y;
        this->real_hitbox_.x += this->speed.x;
        this->real_hitbox_.y += this->speed.y;
        this->Flip(flipFlags);

        if (this->real_hitbox_.x + this->real_hitbox_.w > this->bounds_.w) {
            this->real_hitbox_.x = this->bounds_.w - this->real_hitbox_.w;
            this->hitbox_.x = this->bounds_.w - this->real_hitbox_.w - this->real_offset_.x;
        }
        if (this->hitbox_.x < this->bounds_.x) {
            this->real_hitbox_.x = this->bounds_.x;
            this->hitbox_.x = this->bounds_.x - this->real_offset_.x;
        }
        if (this->hitbox_.y + this->real_hitbox_.h > this->bounds_.h) {
            this->real_hitbox_.y = this->bounds_.h - this->real_hitbox_.h;
            this->hitbox_.y = this->bounds_.h - this->real_hitbox_.h - this->real_offset_.y;
        }
        if (this->hitbox_.y < this->bounds_.y) {
            this->real_hitbox_.y = this->bounds_.y;
            this->hitbox_.y = this->bounds_.y - this->real_offset_.y;
        }
    }

};

#endif
