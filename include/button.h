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
    void SetText(string font, int pt, Color color, string text, bool centered) {
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

    /// Checks if button is clicked
    /// @param x    mouse x-coord
    /// @param y    mouse y-coord
    /// @return if clicked
    bool Click(int x, int y) {
        if (this->IsActive() && this->IsInside(x, y)) return true;
        return false;
    }

};

class ButtonGroup {
private:

    SDL_Renderer * renderer_;
    Screen * screen_;
    map<string, Button> buttons_;
    map<string, screen_callback> callbacks_;
    map<string, screen_callback> onhovers_;
    map<string, screen_callback> offhovers_;

    // probably better to make structs?
    // defaults defaults
    int def_border_pt_ = 10;
    Color def_border_color_ = {0, 0, 0};
    int def_text_pt_ = 24;
    Color def_text_color_ = {0, 0, 0};
    string def_text_font_ = "Lato-Regular";
    screen_callback def_onhover_;
    screen_callback def_offhover_;

public:

    ButtonGroup() {}

    ButtonGroup(SDL_Renderer * renderer, Screen * parent) {
        this->renderer_ = renderer;
        this->screen_ = parent;
    }

    void operator=(SDL_Renderer * renderer) {
        this->renderer_ = renderer;
    }

    void operator=(const ButtonGroup& copy) {
        for (const map<string, Button>::iterator it = copy.buttons_.begin(); it != copy.buttons_.end(); ++it) {
            this->buttons_[it->first] = copy.buttons_[it->first];
        }
        this->def_border_pt_ = copy.def_border_pt_;
        this->def_border_color_ = copy.def_border_color_;
        this->def_text_pt_ = copy.def_text_pt_;
        this->def_text_color_ = copy.def_text_color_;
        this->def_text_font_ = copy.def_text_font_;
        this->def_onhover_ = copy.def_onhover_;
        this->def_offhover_ = copy.def_offhover_;
    }

    void Render() {
        for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
            this->buttons_[it->first].Render();
        }
    }

    void Destroy() {
        for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
            this->buttons_[it->first].Destroy();
        }
        this->renderer_ = nullptr;
        this->screen_ = nullptr;
    }

    void SetDefaultBorder(int pt, Color color) {
        this->def_border_pt_ = pt;
        this->def_border_color_ = color;
    }

    void SetDefaultTextAttrib(int pt, Color color, string font) {
        this->def_text_pt_ = pt;
        this->def_text_color_ = color;
        this->def_text_font_ = font;
    }

    void SetDefaultHoverRoutine(screen_callback onHover, screen_callback offHover) {
        this->def_onhover_ = onHover;
        this->def_offhover_ = offHover;
    }

    void AddButton(string uid, int x, int y, int w, int h, Color color, string text, screen_callback onClick) {
        this->buttons_[uid] = Button(this->renderer_, x, y, w, h, color, this->def_border_pt_, this->def_border_color_);
        this->buttons_[uid].SetText(this->def_text_font_, this->def_text_pt_, this->def_text_color_, text, true);
        this->callbacks_[uid] = onClick;
        this->onhovers_[uid] = this->def_onhover_;
        this->offhovers_[uid] = this->def_offhover_;
    }

    void TempShade(float percent) {
        for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
            this->buttons_[it->first].TempShade(percent);
        }
    }

    int Count() const {
        return this->buttons_.size();
    }

    void Hover(SDL_Point mouse) {
        for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
            if (this->buttons_[it->first].IsInside(mouse.x, mouse.y)) this->onhovers_[it->first](this->screen_);
            else this->offhovers_[it->first](this->screen_);
        }
    }

    void Click(SDL_Point mouse) {
    }

    Button &operator[](int iterindex) {
        vector<string> keys;

        for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
            keys.push_back(it->first);
        }

        return this->buttons_[keys[iterindex]];
    }

    Button &operator[](string uid) {
        return this->buttons_[uid];
    }

};

#endif
