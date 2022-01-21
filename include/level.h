#ifndef LEVEL_H
#define LEVEL_H

#include "utils.h"
#include "tile.h"

extern vector<SDL_Rect> tileSheet;

class Level {
private:

    Tile * level_;
    int x_;
    int y_;
    int w_;
    int h_;

public:

    Level() {}

    Level(const int x, const int y, int w, int h) {
        this->level_ = new Tile[x*y]();
        this->w_ = w;
        this->h_ = h;

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
                this->level_[i+this->x_*j].LoadTile(this->level_[i+this->x_*j].GetType()); // reload with valid renderer
                this->level_[i+this->x_*j].Resize(this->w_, this->h_);
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

    void TempShade(float percent) {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].SetExtraColor(255*percent, 255*percent, 255*percent);
            }
        }
    }

    /// Renders all tiles
    void Render(int x = 0, int y = 0) {
        for (int i=0; i<this->x_; i++) {
            for (int j=0; j<this->y_; j++) {
                this->level_[i+this->x_*j].Render(x, y);
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
    string level_;

public:

    LevelGroup() {}

    LevelGroup(const LevelGroup& copy) {
        this->operator=(copy);
    }

    void SetAttrib(Screen * screen, SDL_Renderer * renderer);

    void operator=(const LevelGroup& copy);

    void Render(int x = 0, int y = 0, bool f = false);

    void Destroy();

    void AddLevel(string uid, Level level);

    Level &operator[](int iterindex);

    Level &operator[](string uid);

    Level at(string uid) const;

    void TempShade(float percent);

};

#endif
