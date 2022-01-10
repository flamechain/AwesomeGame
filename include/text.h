#ifndef TEXT_H
#define TEXT_H

#include "utils.h"

class Text {
private:

    SDL_Renderer * renderer_;
    TTF_Font * font_;
    Color font_color_;
    SDL_Rect rect_;
    SDL_Texture * texture_;

public:

    Text() {}

    Text(SDL_Renderer * renderer, const char * font, int pt, Color color, const char * text = "") {
        this->font_ = TTF_OpenFont((string("resources/font/") + font).c_str(), pt);
        if (this->font_ == NULL) ConsoleOutput("%s\n", TTF_GetError());
        this->font_color_ = color;
        this->rect_.x = 0;
        this->rect_.y = 0;
        this->renderer_ = renderer;

        this->SetText(text);
    }

    /// Changes text to render
    /// @param text new text
    void SetText(const char * text) {
        if (this->font_ == NULL) return;
        SDL_Color fontColor = {(unsigned char)this->font_color_.r, (unsigned char)this->font_color_.g, (unsigned char)this->font_color_.b, 255};
        SDL_Surface * surface = TTF_RenderText_Solid(this->font_, text, fontColor);
        this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, surface);
        TTF_SizeText(this->font_, text, &this->rect_.w, &this->rect_.h);
        SDL_FreeSurface(surface);
    }

    /// Renders texture to screen
    void Render() const {
        SDL_RenderCopy(this->renderer_, this->texture_, NULL, &this->rect_);
    }

    /// Moves location of text
    /// @param x    x-coord
    /// @param y    y-coord
    void SetPosition(int x, int y) {
        this->rect_.x = x;
        this->rect_.y = y;
    }

    /// Gets text size
    /// @return text size as rect
    SDL_Rect GetRect() const {
        return this->rect_;
    }

    /// Destroys memory
    void Destroy() {
        SDL_DestroyTexture(this->texture_);
        this->renderer_ = nullptr;
    }
};

#endif
