#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

// consider making subclass of Rect
class Camera {
private:

    SDL_Rect bounds_;

public:

    int x; // not struct for easier access
    int y;
    int w;
    int h;

    Camera(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void SetBounds(int x, int y, int w, int h) {
        this->bounds_.x = x;
        this->bounds_.y = y;
        this->bounds_.w = w;
        this->bounds_.h = h;
    }

    void Update(int x, int y) {
        this->x += x;
        this->y += y;

        if (this->x < this->bounds_.x) this->x = this->bounds_.x;
        if (this->x + this->w > this->bounds_.w) this->x = this->bounds_.w - this->w;
        if (this->y < this->bounds_.y) this->y = this->bounds_.y;
        if (this->y + this->h > this->bounds_.h) this->y = this->bounds_.h - this->h;
    }

};

#endif
