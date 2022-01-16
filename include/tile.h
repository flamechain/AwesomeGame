#ifndef TILE_H
#define TILE_H

#include "utils.h"
#include "game.h"
#include "camera.h"

#define TILE_SHEET "TileSheet.png"
#define IMG_PATH "resources/img/"

enum class TileType {
    None,
    Grass,
    Path,
    GrassPathStrait,
    GrassPathCorner,
    GrassPathT,
    GrassPathCross,
    GrassPathEnd,
    TestPlayer
};

/// Defines sizes of all tiles
/// @return tile sizes
vector<SDL_Rect> InitTiles();

extern vector<SDL_Rect> tileSheet;

class Tile {
protected:

    SDL_Texture * texture_;
    vector<SDL_Rect> src_;
    SDL_Rect hitbox_;
    Camera * camera_;
    SDL_Renderer * renderer_;
    SDL_Point rotate_axis_;
    int rotation_;
    unsigned char opacity_;
    SDL_RendererFlip flip_;
    TileType type_;

public:

    Tile() {}

    Tile(TileType type) {
        this->texture_ = NULL;

        this->LoadTile(type);
        this->hitbox_.x = 0;
        this->hitbox_.y = 0;
        this->opacity_ = 255;
        this->rotation_ = 0;
        this->flip_ = SDL_FLIP_NONE;

        if (type == TileType::None) {
            this->hitbox_.w = 0;
            this->hitbox_.h = 0;
        } else {
            this->hitbox_.w = this->src_[0].w;
            this->hitbox_.h = this->src_[0].h;
        }

        this->rotate_axis_ = {this->hitbox_.w / 2, this->hitbox_.h / 2};
    }

    void SetRenderer(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void SetCamera(Camera * camera) {
        this->camera_ = camera;
    }

    void operator=(const Tile& tile) {
        this->camera_ = tile.GetCamera();
        this->renderer_ = tile.GetRenderer();
        this->src_ = {};
        this->texture_ = NULL;
        this->type_ = tile.GetType();
        this->LoadTile(this->type_);
        this->hitbox_.x = 0;
        this->hitbox_.y = 0;
        this->opacity_ = 255;
        this->rotation_ = 0;
        this->flip_ = SDL_FLIP_NONE;

        if (this->type_ == TileType::None) {
            this->hitbox_.w = 0;
            this->hitbox_.h = 0;
        } else {
            this->hitbox_.w = this->src_[0].w;
            this->hitbox_.h = this->src_[0].h;
        }

        this->rotate_axis_ = {this->hitbox_.w / 2, this->hitbox_.h / 2};
    }

    /// Gets camera
    /// @return pointer to camera
    Camera * GetCamera() const {
        return this->camera_;
    }

    /// Gets renderer
    /// @return pointer to renderer
    SDL_Renderer * GetRenderer() const {
        return this->renderer_;
    }

    /// Gets tile type
    /// @return current tile type
    TileType GetType() const {
        return this->type_;
    }

    /// Destroys allocated memory e.g. textures
    void Destroy() {
        SDL_DestroyTexture(this->texture_);
        this->renderer_ = nullptr;
    }

    /// Creates renderable texture from tile
    /// @param type     which tile to use
    void LoadTile(TileType type) {
        this->type_ = type;
        if (type == TileType::None) return;
        string spath = IMG_PATH;
        spath += TILE_SHEET;
        SDL_Surface * surface = IMG_Load(spath.c_str());

        if (surface == NULL) {
            ConsoleOutput("Failed loading image: %s\n", IMG_GetError());
            errno = GAME_ERROR_GENERAL_FAIL;
            return;
        }

        if (this->texture_ != NULL) SDL_DestroyTexture(this->texture_);
        this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, surface);
        SDL_FreeSurface(surface);

        this->src_.clear();
        // order here matters because it defines the order rendering happens
        if (type == TileType::GrassPathCorner || \
            type == TileType::GrassPathStrait || \
            type == TileType::GrassPathCross || \
            type == TileType::GrassPathT || \
            type == TileType::GrassPathEnd)
            this->src_.push_back(tileSheet[(int)TileType::Path]);
        this->src_.push_back(tileSheet[(int)type]);
        this->hitbox_.w = 16;
        this->hitbox_.h = 16;
    }

    /// Renders texture to screen
    void Render() const {
        SDL_Rect dst = {this->hitbox_.x - this->camera_->x, this->hitbox_.y - this->camera_->y, this->hitbox_.w, this->hitbox_.h};
        for (int i=0; i<(int)this->src_.size(); i++) {
            SDL_RenderCopyEx(this->renderer_, this->texture_, &this->src_[i], &dst, this->rotation_, &this->rotate_axis_, this->flip_);
        }
    }

    /// Resizes tiles texture
    /// @param w    width
    /// @param h    height
    void Resize(int w, int h) {
        this->hitbox_.w = w;
        this->hitbox_.h = h;
    }

    /// Gets current flip flags
    /// @return flips flags
    SDL_RendererFlip GetFlip() const {
        return this->flip_;
    }

    /// Flips texture on along x and y axis
    /// @param flip flip flags
    void Flip(int flip) {
        this->flip_ = (SDL_RendererFlip)flip;
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
