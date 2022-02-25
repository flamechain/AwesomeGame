#ifndef TILE_H
#define TILE_H

#include "utils.h"
#include "game.h"

GAME_START

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
    PlayerLeftStill,
    PlayerLeft1,
    PlayerLeft2,
    PlayerRightStill,
    PlayerRight1,
    PlayerRight2,
};

/// Defines sizes of all tiles
/// @return tile sizes
vector<SDL_Rect> InitTiles();

// extern vector<SDL_Rect> tile_sheet;

class Tile {
protected:

    SDL_Texture *texture_;
    SDL_Rect src_;
    SDL_Rect hitbox_;
    SDL_Rect crop_;
    SDL_Renderer *renderer_;
    SDL_Point rotate_axis_;
    int rotation_;
    unsigned char opacity_;
    SDL_RendererFlip flip_;
    TileType type_;

public:

    Tile() {
        this->init(TileType::None);
    }

    Tile(TileType type) {
        this->init(type);
    }

    Tile(TileType type, SDL_Renderer *renderer) {
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
        this->type_ = type;
        this->flip_ = SDL_FLIP_NONE;
        this->rotate_axis_ = {-1, -1};
        this->crop_.x = 0;
        this->crop_.y = 0;
        this->crop_.w = 0;
        this->crop_.h = 0;
        this->src_.x = 0;
        this->src_.y = 0;
        this->src_.w = 0;
        this->src_.h = 0;
    }

    void operator=(const Tile& tile) {
        this->renderer_ = tile.renderer_;
        this->src_ = tile.src_;
        this->crop_ = tile.crop_;
        this->texture_ = tile.texture_;
        this->type_ = tile.type_;
        this->hitbox_ = tile.hitbox_;
        this->opacity_ = tile.opacity_;
        this->rotation_ = tile.rotation_;
        this->flip_ = tile.flip_;

        if (this->type_ == TileType::None) {
            this->hitbox_.w = 0;
            this->hitbox_.h = 0;
        } else {
            this->hitbox_.w = this->src_.w;
            this->hitbox_.h = this->src_.h;
        }

        this->rotate_axis_ = {-1, -1};
    }

    void Crop(int x, int y, int w, int h) {
        this->crop_.x = x;
        this->crop_.y = y;
        this->crop_.w = w;
        this->crop_.h = h;
    }

    /// Gets color of tile (assuming its a solid color)
    /// @param x    x-coord
    /// @param y    y-coord
    Color GetColor(int x = 0, int y = 0) {
        if (this->type_ == TileType::None) return {0, 0, 0};
        string spath = IMG_PATH;
        spath += TILE_SHEET;
        SDL_Surface *surface = IMG_Load(spath.c_str());

        if (surface == NULL) {
            ConsoleOutput("Failed loading image: %s\n", IMG_GetError());
            errno = GAME_ERROR_GENERAL_FAIL;
            return {0, 0, 0};
        }

        int bpp = surface->format->BytesPerPixel;
        Uint8 *p = static_cast<Uint8*>(surface->pixels) + (tile_sheet[static_cast<long long unsigned int>(this->type_)].y+y) * \
            surface->pitch + (tile_sheet[static_cast<long long unsigned int>(this->type_)].x+x) * bpp;
        Uint32 pixel;

        switch (bpp) {
            case 1:
                pixel = *p;
                break;
            case 2:
                pixel = *reinterpret_cast<Uint16*>(p);
                break;
            case 4:
                pixel = *reinterpret_cast<Uint32*>(p);
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
    void SetRenderer(SDL_Renderer *renderer) {
        this->renderer_ = renderer;
        this->LoadTile(this->type_);
    }

    /// Gets renderer
    /// @return pointer to renderer
    SDL_Renderer *GetRenderer() const {
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
        int oldcw = this->crop_.w;
        int oldch = this->crop_.h;
        if (this->renderer_ == nullptr) return;
        this->type_ = type;
        if (type == TileType::None) return;
        string spath = IMG_PATH;
        spath += TILE_SHEET;
        SDL_Surface *surface = IMG_Load(spath.c_str());

        if (surface == NULL) {
            ConsoleOutput("Failed loading image: %s\n", IMG_GetError());
            errno = GAME_ERROR_GENERAL_FAIL;
            return;
        }

        if (this->texture_ != NULL) SDL_DestroyTexture(this->texture_);
        this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, surface);
        SDL_FreeSurface(surface);

        this->src_ = tile_sheet[static_cast<long long unsigned int>(type)];

        if (oldw != 0 && oldh != 0) {
            this->hitbox_.w = oldw;
            this->hitbox_.h = oldh;
            this->crop_.w = oldcw;
            this->crop_.h = oldch;
        }
    }

    /// Renders texture to screen
    /// @param x    x relative
    /// @param y    y relative
    void Render(int x = 0, int y = 0) {
        SDL_Rect dst = {this->hitbox_.x + x, this->hitbox_.y + y, this->hitbox_.w, this->hitbox_.h};
        SDL_Rect src;
        src.x = this->src_.x + this->crop_.x;
        src.y = this->src_.y + this->crop_.y;
        src.w = this->src_.w;
        src.h = this->src_.h;

        if (this->crop_.w != 0) src.w = this->crop_.w;
        if (this->crop_.h != 0) src.h = this->crop_.h; 

        if (this->rotate_axis_.x == -1 && this->rotate_axis_.y == -1) {
            SDL_RenderCopyEx(this->renderer_, this->texture_, &src, &dst, this->rotation_, NULL, this->flip_);
        } else {
            SDL_RenderCopyEx(this->renderer_, this->texture_, &src, &dst, this->rotation_, &this->rotate_axis_, this->flip_);
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
        this->flip_ = static_cast<SDL_RendererFlip>(flip);
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
    void SetExtraColor(unsigned char r, unsigned char g, unsigned char b) {
        SDL_SetTextureColorMod(this->texture_, r, g, b);
    }

};

GAME_END

#endif
