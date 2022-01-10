#ifndef TILE_H
#define TILE_H

#include "utils.h"
#include "game.h"
#include "camera.h"

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
    Camera * camera_;
    SDL_Renderer * renderer_;
    SDL_Point rotate_axis_;
    int rotation_;
    unsigned char opacity_;

public:

    Tile(SDL_Renderer * renderer, TileType type, SDL_Rect * tiles, Camera * camera) {
        this->renderer_ = renderer;
        this->LoadTile(type, tiles);
        this->hitbox_.x = 0;
        this->hitbox_.y = 0;
        this->hitbox_.w = this->srcbox_.w;
        this->hitbox_.h = this->srcbox_.h;
        this->camera_ = camera;
        this->opacity_ = 255;
        this->rotation_ = 0;
        this->rotate_axis_ = {this->hitbox_.w / 2, this->hitbox_.h / 2};
    }

    /// Destroys allocated memory e.g. textures
    void Destroy() {
        SDL_DestroyTexture(this->texture_);
        this->renderer_ = nullptr;
    }

    /// Creates renderable texture from tile
    /// @param type     which tile to use
    /// @param tiles    list of available tiles
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

    /// Renders texture to screen
    void Render() const {
        SDL_Rect dst = {this->hitbox_.x - this->camera_->x, this->hitbox_.y - this->camera_->y, this->hitbox_.w, this->hitbox_.h};
        SDL_RenderCopyEx(this->renderer_, this->texture_, &this->srcbox_, &dst, this->rotation_, &this->rotate_axis_, SDL_FLIP_NONE);
    }

    /// Resizes tiles texture
    /// @param w    width
    /// @param h    height
    void Resize(int w, int h) {
        this->hitbox_.w = w;
        this->hitbox_.h = h;
    }

    /// Moves tiles texture
    /// @param x    x coord
    /// @param y    y coord
    void SetPosition(int x, int y) {
        this->hitbox_.x = x;
        this->hitbox_.y = y;
    }

    /// Rotates texture from an axis
    /// @param angle    degress to rotate
    /// @param axis     center of rotation
    void Rotate(int angle, SDL_Point axis = {-1, -1}) {
        if (axis.x > -1 && axis.y > -1) this->rotate_axis_ = axis;
        this->rotation_ = angle;
    }

    /// Gets hitbox
    /// @return hitbox as rect
    SDL_Rect GetRect() const {
        return this->hitbox_;
    }

    /// Gets the current opacity
    /// @return opacity as int 0 -> 255
    unsigned char GetOpacity() const {
        return this->opacity_;
    }

    /// Sets the current opacity
    /// @param opacity  opacity value 0 -> 255
    void SetOpacity(unsigned char opacity) {
        this->opacity_ = opacity;
        SDL_SetTextureAlphaMod(this->texture_, opacity);
    }

    /// Sets an contrast level of image (default 255, 255, 255)
    /// @param r    r-channel
    /// @param g    g-channel
    /// @param b    b-channel
    void SetExtraColor(char r, char g, char b) {
        SDL_SetTextureColorMod(this->texture_, r, g, b);
    }

};

#endif
