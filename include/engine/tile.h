#ifndef TILE_H
#define TILE_H

#include "utils.h"
#include "game.h"

enum class TileType {
    None,
    Floor,
    FloorCrack1,
    FloorCrack2,
    FloorCrack3,
    Roof,
    Roof1,
    Roof2,
    Roof3,
    Roof4,
    Brick,
    BrickCrack1,
    BrickCrack2,
    BrickCrack3,
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
    SDL_Renderer * renderer_;
    SDL_Point rotate_axis_;
    int rotation_;
    unsigned char opacity_;
    SDL_RendererFlip flip_;
    TileType type_;

public:

    Tile() {}

    Tile(TileType type) {
        this->init(type);
    }

    Tile(TileType type, SDL_Renderer * renderer) {
        this->init(type);
        this->renderer_ = renderer;
        this->LoadTile(type);
    }

    void init(TileType type) {
        this->texture_ = NULL;

        this->hitbox_.x = 0;
        this->hitbox_.y = 0;
        this->hitbox_.w = 0;
        this->hitbox_.h = 0;
        this->opacity_ = 255;
        this->rotation_ = 0;
        this->flip_ = SDL_FLIP_NONE;
        this->rotate_axis_ = {this->hitbox_.w / 2, this->hitbox_.h / 2};
    }

    void operator=(const Tile& tile) {
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

    /// Gets color of tile (assuming its a solid color)
    /// @param x    x-coord
    /// @param y    y-coord
    Color GetColor(int x = 0, int y = 0) {
        if (this->type_ == TileType::None) return {0, 0, 0};
        string spath = IMG_PATH;
        spath += TILE_SHEET;
        SDL_Surface * surface = IMG_Load(spath.c_str());

        if (surface == NULL) {
            ConsoleOutput("Failed loading image: %s\n", IMG_GetError());
            errno = GAME_ERROR_GENERAL_FAIL;
            return {0, 0, 0};
        }

        int bpp = surface->format->BytesPerPixel;
        Uint8 * p = (Uint8*)surface->pixels + (tileSheet[(int)this->type_].y+y) * surface->pitch + (tileSheet[(int)this->type_].x+x) * bpp;
        Uint32 pixel;

        switch (bpp) {
            case 1:
                pixel = *p;
                break;
            case 2:
                pixel = *(Uint16*)p;
                break;
            case 4:
                pixel = *(Uint32*)p;
                break;
            default:
                pixel = 0;
                break;
        }

        Color rgb;
        SDL_GetRGB(pixel, surface->format, &rgb.r, &rgb.g, &rgb.b);
        return rgb;
    }

    /// Sets renderer
    /// @param renderer global renderer
    void SetRenderer(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
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
        int oldw = this->hitbox_.w;
        int oldh = this->hitbox_.h;
        if (this->renderer_ = nullptr) return;
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

        this->src_.clear(); // allowing layered sprites for the future
        this->src_.push_back(tileSheet[(int)type]);

        if (oldw != 0 && oldh != 0) {
            this->hitbox_.w = oldw;
            this->hitbox_.h = oldh;
        }
    }

    /// Renders texture to screen
    /// @param x    x relative
    /// @param y    y relative
    void Render(int x = 0, int y = 0) const {
        SDL_Rect dst = {this->hitbox_.x + x, this->hitbox_.y + y, this->hitbox_.w, this->hitbox_.h};
        if (this->rotate_axis_.x == -1 && this->rotate_axis_.y == -1) {
            SDL_RenderCopyEx(this->renderer_, this->texture_, &this->src_[0], &dst, this->rotation_, NULL, this->flip_);
        } else {
            SDL_RenderCopyEx(this->renderer_, this->texture_, &this->src_[0], &dst, this->rotation_, &this->rotate_axis_, this->flip_);
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
        this->rotate_axis_ = axis;
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