#ifndef TILE_H
#define TILE_H

#include "utils.h"
#include "game.h"

#define TILE_SHEET "TileSheet.png"
#define IMG_PATH "resources/img/"

enum TileType {
    GrassPathStrait,
    GrassPathCenter,
    GrassPathCorner,
    DirtBlood
};

SDL_Rect * InitTiles();

class Tile {
protected:

    SDL_Texture * texture_;
    SDL_Rect srcbox_;
    SDL_Rect hitbox_;
    SDL_Renderer * renderer_;
    SDL_Point rotate_axis_ = {-1, -1};
    int rotation_ = 0;

public:

    Tile(SDL_Renderer * renderer, TileType type, SDL_Rect * tiles) {
        this->renderer_ = renderer;
        this->LoadTile(type, tiles);
        this->hitbox_.x = 0;
        this->hitbox_.y = 0;
        this->hitbox_.w = this->srcbox_.w;
        this->hitbox_.h = this->srcbox_.h;
    }

    void Destroy() {
        SDL_DestroyTexture(this->texture_);
        this->renderer_ = nullptr;
    }

    void LoadTile(TileType type, SDL_Rect * tiles) {
        string spath = IMG_PATH;
        spath += TILE_SHEET;
        SDL_Surface * surface = IMG_Load(spath.c_str());

        if (surface == NULL) {
            ConsoleOutput("Failed loading image: %s\n", IMG_GetError());
            errno = GAME_ERROR_GENERAL_FAIL;
            return;
        }

        this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, surface);
        SDL_FreeSurface(surface);

        this->srcbox_ = tiles[type];
    }

    void Render() {
        if (this->rotate_axis_.x == -1 && this->rotate_axis_.y == -1) {
            this->rotate_axis_.x = this->hitbox_.w / 2;
            this->rotate_axis_.y = this->hitbox_.h / 2;
        }

        SDL_RenderCopyEx(this->renderer_, this->texture_, &this->srcbox_, &this->hitbox_, this->rotation_, &this->rotate_axis_, SDL_FLIP_NONE);

        this->rotate_axis_ = {-1, -1};
    }

    void Resize(int w, int h) {
        this->hitbox_.w = w;
        this->hitbox_.h = h;
    }

    void Position(int x, int y) {
        this->hitbox_.x = x;
        this->hitbox_.y = y;
    }

    void Rotate(int angle, SDL_Point axis = {-1, -1}) {
        this->rotate_axis_ = axis;
        this->rotation_ = angle;
    }

};

#endif
