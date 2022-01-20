#ifndef LEVEL_H
#define LEVEL_H

#include "utils.h"
#include "tile.h"
#include "camera.h"

extern vector<SDL_Rect> tileSheet;

class Level {
private:

    Tile * level_;
    Camera * camera_;
    int x_;
    int y_;

public:

    Level() {}

    Level(const int x, const int y) {
        this->level_ = new Tile[x*y]();

        for (int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                this->level_[i+x*j] = Tile(TileType::None);
            }
        }

        this->x_ = x;
        this->y_ = y;
    }

    void SetRenderer(SDL_Renderer * renderer) {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].SetRenderer(renderer);
            }
        }
    }

    /// Sets tiles at coord pair
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param tile object to copy
    void SetTile(int x, int y, TileType type) {
        if (x >= this->x_ || y >= this->y_) return;
        this->level_[x+this->x_*y].LoadTile(type);
    }

    /// Sets tile position
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param px    x-coord loc
    /// @param py    y-coord loc
    void SetTilePosition(int x, int y, int px, int py) {
        this->level_[x+this->x_*y].SetPosition(px, py);
    }

    /// Resizes target tile
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param px    x-coord loc
    /// @param py    y-coord loc
    void ResizeTile(int x, int y, int px, int py) {
        this->level_[x+this->x_*y].Resize(px, py);
    }

    /// Destroys all tiles
    void Destroy() {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].Destroy();
            }
        }

        delete[] this->level_;
    }

    /// Renders all tiles
    void Render() {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].Render();
            }
        }
    }

    /// Sets an contrast level of image (default 255, 255, 255)
    /// @param r    r-channel
    /// @param g    g-channel
    /// @param b    b-channel
    void SetExtraColor(int r, int g, int b) {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].SetExtraColor(r, g, b);
            }
        }
    }

};

class LevelGroup {
private:

    SDL_Renderer * renderer_;
    Screen * screen_;
    map<string, Level> levels_;

public:

    LevelGroup() {}

    LevelGroup(const LevelGroup& copy) {
        this->operator=(copy);
    }

    void SetAttrib(Screen * screen, SDL_Renderer * renderer);

    void operator=(const LevelGroup& copy);

    void Render();

    void Destroy();

    void AddLevel(string uid, Level level);

    Level &operator[](int iterindex);

    Level &operator[](string uid);

    Level at(string uid) const;

};

#endif
