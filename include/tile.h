#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"

class PhysicsEngine {
public:

    PhysicsEngine() {
    }

};

class MovingTile : public PhysicsEngine {
private:

    int width_bound_;
    int height_bound_;

public:

    int PosX;
    int PosY;
    int MomentX;
    int MomentY;

    MovingTile(int posX, int posY, int speed, int widthBound = 0, int heightBound = 0) {
        this->PosX = posX;
        this->PosY = posY;
        this->MomentX = speed;
        this->MomentY = speed;
        this->width_bound_ = widthBound;
        this->height_bound_ = heightBound;
    }
}

class Object {
private:

    SDL_Surface surface_;
    SDL_Texture texture_;
    SDL_Rect hitbox_;
    int texture_width_;
    int texture_height_;

public:

    PhysicsEngine Physics;

    Object() {

    }

    void SetPhysicsEngine(PhysicsEngine engine) {
        this->Physics = engine;
    }

    void Render(SDL_Renderer * renderer) {
        SDL_RenderCopy(renderer, &this->texture_, NULL, &this->hitbox_);
    }

    void CreateImageSurface(const char * path) {
    }

    void LoadTextureFromSurface() {
    }

    void CreateHitbox(int width, int height) {
    }

};

Object CreateObjectFromImage(const char * path, int width = 0, int height = 0) {
    Object object;
    object.CreateImageSurface(path);
    if (width != 0 && height != 0) object.ResizeSurface(width, height);
    object.LoadTextureFromSurface();
    object.CreateHitbox(this->texture_width_, this->texture_height_);

    return object;
}

#endif
