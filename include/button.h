#ifndef BUTTON_H
#define BUTTON_H

#include "utils.h"
#include "text.h"
#include "rect.h"

class Button : public Rect {
private:

    Text text_;
    bool centered_;
    bool active_;

    void CenterText() {
        this->text_.SetPosition(this->rect_.x + (this->rect_.w / 2) - (this->text_.GetRect().w / 2), this->rect_.y + (this->rect_.h / 2) - (this->text_.GetRect().h / 2));
    }

public:

    Button() {}

    Button(SDL_Renderer * renderer, int x, int y, int w, int h, Color rgb, int bpt, Color brgb) : Rect(renderer, x, y, w, h, rgb) {
        this->active_ = false;
        this->SetBorder(bpt, brgb);
    }

    /// Renders text and rect
    void Render() {
        SDL_Rect newRect = {this->rect_.x + this->border_pt_, this->rect_.y + this->border_pt_, this->rect_.w - (this->border_pt_ * 2), this->rect_.h - (this->border_pt_ * 2)};

        SDL_SetRenderDrawColor(this->renderer_, this->border_color_.r, this->border_color_.g, this->border_color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &this->rect_);

        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &newRect);

        this->text_.Render();
    }

    /// Sets text attributes
    /// @param font     ttf font name
    /// @param pt       size
    /// @param color    font color
    /// @param text     display text
    /// @param centered if to center on rect
    void SetText(const char * font, int pt, Color color, const char * text, bool centered) {
        this->text_ = Text(this->renderer_, font, pt, color, text);
        this->centered_ = centered;
        if (centered) this->CenterText();
    }

    /// Moves text
    /// @param x    x-coord
    /// @param y    y-coord
    void SetTextPos(int x, int y) {
        this->text_.SetPosition(x, y);
    }

    /// Sets activity
    /// @param active   if to display
    void SetActive(bool active) {
        this->active_ = active;
    }

    /// Gets acitivity
    /// @return if to display
    bool IsActive() const {
        return this->active_;
    }

    /// Sets dimensions
    /// @param x    x-coord
    /// @param y    y-coord
    /// @param w    width
    /// @param h    height
    void SetDimensions(int x, int y, int w, int h) {
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
        if (this->centered_) this->CenterText();
    }

    /// Moves button
    /// @param x    x-coord
    /// @param y    y-coord
    void SetPosition(int x, int y) {
        this->rect_.x = x;
        this->rect_.y = y;
        if (this->centered_) this->CenterText();
    }

    /// If coord pair is inside the button area (usally mouse position)
    /// @param x    x-coord
    /// @param y    y-coord
    bool IsInside(int x, int y) {
        if ( (x >= this->rect_.x && x <= this->rect_.x + this->rect_.w) && \
             (y >= this->rect_.y && y <= this->rect_.y + this->rect_.h))
            return true;

        return false;
    }

    /// If button is clicked
    /// @param x    mouse x-coord
    /// @param y    mouse y-coord
    bool Clicked(int x, int y) {
        if (this->IsActive() && this->IsInside(x, y)) return true;
        return false;
    }

};

class ButtonGroup {
private:

    SDL_Renderer * renderer_;

public:

    ButtonGroup() {}

    ButtonGroup(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void operator=(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void operator=(const ButtonGroup& copy) {
    }

    void Render() {
    }

    void Destroy() {
        this->renderer_ = nullptr;
    }

    void SetDefaultBorder(int pt, Color color) {
    }

    void SetDefaultTextAttrib(int pt, Color color, string font) {
    }

    void SetDefaultHoverRoutine(screen_callback onHover, screen_callback offHover) {
    }

    void AddButton(string uid, int x, int y, int w, int h, Color color, string text, screen_callback onClick) {
    }

    void SetOpacity(int r, int g, int b) {
    }

    int Count() const {
    }

    void Hover(SDL_Point mouse) {
    }

    void Click(SDL_Point mouse) {
    }

    Button &operator[](int iterindex) {
    }

    Button &operator[](string uid) {
    }

};

#endif
