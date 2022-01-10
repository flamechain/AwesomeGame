#ifndef RECT_H
#define RECT_H

#include "utils.h"

class Rect {
protected:

    SDL_Renderer * renderer_;
    SDL_Rect rect_;
    int border_pt_;
    Color border_color_;
    Color color_backup_;
    Color color_;

public:

    Rect(SDL_Renderer * renderer, int x, int y, int w, int h, Color rgb) {
        this->renderer_ = renderer;
        this->color_ = rgb;
        this->color_backup_ = rgb;
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
        this->border_color_ = rgb;
        this->border_pt_ = 0;
    }

    void Render() {
        SDL_Rect newRect = {this->rect_.x + this->border_pt_, this->rect_.y + this->border_pt_, this->rect_.w - (this->border_pt_ * 2), this->rect_.h - (this->border_pt_ * 2)};

        SDL_SetRenderDrawColor(this->renderer_, this->border_color_.r, this->border_color_.g, this->border_color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &this->rect_);

        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &newRect);
    }

    void SetColor(Color rgb) {
        if (rgb.r < 0) rgb.r = 0;
        if (rgb.g < 0) rgb.g = 0;
        if (rgb.b < 0) rgb.b = 0;
        this->color_ = rgb;
        this->color_backup_ = rgb;
    }

    Color GetColor() const {
        return this->color_;
    }

    void SetDimensions(int x, int y, int w, int h) {
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
    }

    SDL_Rect GetRect() const {
        return this->rect_;
    }

    void Destroy() {
        this->renderer_ = nullptr;
    }

    void SetBorder(int pt, Color color) {
        this->border_pt_ = pt;
        this->border_color_ = color;
    }

    void Shadow(int r, int g, int b) {
        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        this->color_ = {r, g, b};
    }

    void UnShadow() {
        this->color_ = this->color_backup_;
    }

    void SetPosition(int x, int y) {
        this->rect_.x = x;
        this->rect_.y = y;
    }

};

#endif
