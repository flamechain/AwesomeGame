#ifndef RECT_H
#define RECT_H

#include "utils.h"

class Rect {
private:

    SDL_Renderer * renderer_;
    SDL_Rect rect_;
    char r_;
    char g_;
    char b_;

public:

    Rect(SDL_Renderer * renderer, int x, int y, int w, int h, char r, char g, char b) {
        this->renderer_ = renderer;
        this->r_ = r;
        this->g_ = g;
        this->b_ = b;
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
    }

    void Render() {
        SDL_SetRenderDrawColor(this->renderer_, this->r_, this->g_, this->b_, 255);
        SDL_RenderFillRect(this->renderer_, &this->rect_);
    }

    void SetColor(char r, char g, char b) {
        this->r_ = r;
        this->g_ = g;
        this->b_ = b;
    }

    void SetDimension(int x, int y, int w, int h) {
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
    }

    SDL_Rect GetDimension() const {
        return this->rect_;
    }

    // create color struct
};

#endif
