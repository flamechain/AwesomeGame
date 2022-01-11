#ifndef LEVEL_H
#define LEVEL_H

#include "utils.h"
#include "tile.h"

class Level {
private:

    Tile * level_;
    int x_;
    int y_;

public:

    Level(SDL_Renderer * renderer, Camera * camera, SDL_Rect * tiles, const int x, const int y) {
        this->level_ = new Tile[x*y]();

        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+x*j] = Tile(renderer, TileType::None, tiles, camera);
            }
        }

        this->x_ = x;
        this->y_ = y;
    }

    /// Sets tiles at coord pair
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param tile object to copy
    void SetTile(int x, int y, TileType type, SDL_Rect * tiles) {
        if (x >= this->x_ || y >= this->y_) return;
        this->level_[x+this->x_*y].LoadTile(type, tiles);
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

#endif
