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

    Creature() : Tile() {}

    Creature(TileType type, int x, int y) : Tile(type) {
        this->SetSize(0, 0, this->hitbox_.w, this->hitbox_.h);
        this->SetPosition(x, y);
    }

    void operator=(const Creature& copy);

    /// Gets colllision hitbox
    /// @return hitbox as rect
    SDL_Rect GetHitbox() const;
    /// Sets collision hitbox size
    /// @param x    x offset from render x
    /// @param y    y offset from render y
    /// @param w    width
    /// @param h    height
    void SetSize(int x, int y, int w, int h);

    /// Resizes tiles texture
    /// @param w    width
    /// @param h    height
    void Resize(int w, int h);

    /// Moves tiles texture
    /// @param x    x coord
    /// @param y    y coord
    void SetPosition(int x, int y);

    /// Sets area creature can move
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param w    boundary width
    /// @param h    boundary height
    void SetBounds(int x, int y, int w, int h);

    /// Checks if creature is centered in X
    /// @param screen   camera to check
    /// @return result
    bool IsCenteredX(Screen * screen);

    /// Checks if creature is centered in Y
    /// @param screen   camera to check
    /// @return result
    bool IsCenteredY(Screen * screen);

    /// Moves creature based on speed
    /// @param checkBounds  if to check bounds
    void Update(SDL_Point offset, bool checkBounds = true);

};

class CreatureGroup {
private:

    SDL_Renderer * renderer_;
    Screen * screen_;
    map<string, Creature> creatures_;

public:

    CreatureGroup() {}

    CreatureGroup(const CreatureGroup& copy) {
        this->operator=(copy);
    }

    void SetAttrib(Screen * screen, SDL_Renderer * renderer);

    void operator=(const CreatureGroup& copy);

    void TempShade(float percent);

    void AddCreature(string uid, TileType type, int w, int h, int x, int y);

    void Render(int x = 0, int y = 0, bool f = false);

    void Destroy();

    void Unlock(string uid);

    Creature &operator[](int iterindex);

    Creature &operator[](string uid);

    Creature at(string uid) const;

};

#endif
