#ifndef CREATURE_H
#define CREATURE_H

#include "utils.h"
#include "game.h"
#include "tile.h"

class Creature : public Tile {
private:

    SDL_Rect real_hitbox_;
    SDL_Rect bounds_;
    SDL_Point real_offset_;

public:

    SDL_Point Speed;

    Creature(TileType type) : Tile(type) {
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

    /// Sets area creature can move
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

    /// Checks if creature is centered in X
    /// @param screen   camera to check
    /// @return result
    bool IsCenteredX(Screen * screen) {
    }

    /// Checks if creature is centered in Y
    /// @param screen   camera to check
    /// @return result
    bool IsCenteredY(Screen * screen) {
    }

    /// Moves creature based on speed
    /// @param checkBounds  if to check bounds
    void Update(SDL_Point offset, bool checkBounds = true) {
        if (!checkBounds) {
            this->hitbox_.x += offset.x;
            this->hitbox_.y += offset.y;
            this->real_hitbox_.x += offset.x;
            this->real_hitbox_.y += offset.y;
            return;
        }

        this->hitbox_.x += offset.x;
        int flipFlags = this->GetFlip();
        if (offset.x < 0) flipFlags |= SDL_FLIP_HORIZONTAL;
        else if (offset.x > 0) flipFlags = SDL_FLIP_NONE;
        this->hitbox_.y += offset.y;
        this->real_hitbox_.x += offset.x;
        this->real_hitbox_.y += offset.y;
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

class CreatureGroup {
private:

    SDL_Renderer * renderer_;

public:

    CreatureGroup() {}

    CreatureGroup(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void operator=(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void operator=(const CreatureGroup& copy) {
    }

    void SetOpacity(int r, int g, int b) {
    }

    void AddCreature(string uid, TileType type, int w, int h) {
    }

    void Render() {
    }

    void Destroy() {
        this->renderer_ = nullptr;
    }

    Creature &operator[](int iterindex) {
    }

    Creature &operator[](string uid) {
    }

};

#endif
