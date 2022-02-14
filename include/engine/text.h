#ifndef TEXT_H
#define TEXT_H

#include "utils.h"

class Text {
private:

    SDL_Renderer *renderer_;
    TTF_Font *font_;
    Color color_backup_;
    Color font_color_;
    SDL_Rect rect_;
    SDL_Texture *texture_;


public:

    Text() {}

    Text(SDL_Renderer *renderer, string font, int pt, Color color, string text = "") {
        this->font_ = TTF_OpenFont((string("resources/font/") + font + ".ttf").c_str(), pt);
        if (this->font_ == NULL) ConsoleOutput("%s\n", TTF_GetError());
        this->font_color_ = color;
        this->color_backup_ = color;
        this->rect_.x = 0;
        this->rect_.y = 0;
        this->renderer_ = renderer;

        this->SetText(text);
    }

    /// Changes text to render
    /// @param text new text
    void SetText(string text) {
        if (this->font_ == NULL) return;
        SDL_Color fontColor = {this->font_color_.r, this->font_color_.g, this->font_color_.b, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(this->font_, text.c_str(), fontColor);
        this->texture_ = SDL_CreateTextureFromSurface(this->renderer_, surface);
        TTF_SizeText(this->font_, text.c_str(), &this->rect_.w, &this->rect_.h);
        SDL_FreeSurface(surface);
    }

    /// Sets opacity
    /// @param percent  0 -> 1
    void TempShade(float percent) {
        int r = static_cast<float>(this->color_backup_.r) * percent;
        int g = static_cast<float>(this->color_backup_.g) * percent;
        int b = static_cast<float>(this->color_backup_.b) * percent;
        this->font_color_ = RGB(r, g, b);
    }

    /// Renders texture to screen
    /// @param x    x relative
    /// @param y    y relative
    void Render(int x = 0, int y = 0) const {
        SDL_Rect dstRect = {x + this->rect_.x, y + this->rect_.y, this->rect_.w, this->rect_.h};
        SDL_RenderCopy(this->renderer_, this->texture_, NULL, &dstRect);
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

    /// Destroys text
    void Destroy() {
        SDL_DestroyTexture(this->texture_);
        this->renderer_ = nullptr;
    }
};

class Paragraph {
private:

    SDL_Renderer *renderer_;
    Screen *screen_;
    map<string, Text> lines_;

public:

    Paragraph() {}

    Paragraph(const Paragraph& copy) {
        this->operator=(copy);
    }

    void operator=(const Paragraph& copy);

    Text& operator[](unsigned int iterindex);

    Text& operator[](string uid);

    Text at(string uid) const;

    /// Sets attributes not given by constructor
    /// @param screen   parent
    /// @param renderer global renderer
    void SetAttrib(Screen *screen, SDL_Renderer *renderer);

    /// Destroys all lines
    void Destroy();

    /// Sets opacity
    /// @param percent  0 -> 1
    void TempShade(float percent);

    /// Creatures new line
    /// @param uid      map key
    /// @param x        relative x
    /// @param y        relative y
    /// @param font     ttf font
    /// @param pt       size
    /// @param color    color
    /// @param text     line
    void AddLine(string uid, int x, int y, string font, int pt, Color color, string text);

    /// Renders all lines
    /// @param x    x relative
    /// @param y    y relative
    /// @param f    if screen is relative or absolute
    void Render(int x = 0, int y = 0, bool f = false);

};

#endif
