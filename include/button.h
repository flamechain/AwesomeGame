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

    Button(SDL_Renderer * renderer, int x, int y, int w, int h, Color rgb) : Rect(renderer, x, y, w, h, rgb) {
    }

    void Render() {
        SDL_Rect newRect = {this->rect_.x + this->border_pt_, this->rect_.y + this->border_pt_, this->rect_.w - (this->border_pt_ * 2), this->rect_.h - (this->border_pt_ * 2)};

        SDL_SetRenderDrawColor(this->renderer_, this->border_color_.r, this->border_color_.g, this->border_color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &this->rect_);

        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &newRect);

        this->text_.Render();
    }

    void SetText(const char * font, int pt, Color color, const char * text, bool centered) {
        this->text_ = Text(this->renderer_, font, pt, color, text);
        this->centered_ = centered;
        if (centered) this->CenterText();
    }

    void SetTextPos(int x, int y) {
        this->text_.SetPosition(x, y);
    }

    void SetActive(bool active) {
        this->active_ = active;
    }

    bool IsActive() const {
        return this->active_;
    }

    void SetDimensions(int x, int y, int w, int h) {
        this->rect_.x = x;
        this->rect_.y = y;
        this->rect_.w = w;
        this->rect_.h = h;
        if (this->centered_) this->CenterText();
    }

    void SetPosition(int x, int y) {
        this->rect_.x = x;
        this->rect_.y = y;
        if (this->centered_) this->CenterText();
    }

    bool IsInside(int x, int y) {
        if ( (x >= this->rect_.x && x <= this->rect_.x + this->rect_.w) && \
             (y >= this->rect_.y && y <= this->rect_.y + this->rect_.h))
            return true;

        return false;
    }

};

#endif
