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
    /// @param x    relative x
    /// @param y    relative y
    void Render(int x = 0, int y = 0) {
        SDL_Rect dstRect = {x + this->rect_.x, y + this->rect_.y, this->rect_.w, this->rect_.h};
        SDL_Rect newRect = {x + this->rect_.x + this->border_pt_, y + this->rect_.y + this->border_pt_, this->rect_.w - (this->border_pt_ * 2), this->rect_.h - (this->border_pt_ * 2)};

        SDL_SetRenderDrawColor(this->renderer_, this->border_color_.r, this->border_color_.g, this->border_color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &dstRect);

        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        SDL_RenderFillRect(this->renderer_, &newRect);

        this->text_.Render(x, y);
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

    /// Checks if x y inside button
    /// @param x    x
    /// @param y    y
    /// @return true if inside
    bool IsInside(int x, int y) const {
        if ( (x >= this->rect_.x && x <= this->rect_.x + this->rect_.w) && \
             (y >= this->rect_.y && y <= this->rect_.y + this->rect_.h))
            return true;

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
    string def_text_font_ = "lato/regular";
    screen_callback def_onhover_;
    screen_callback def_offhover_;

public:

    ButtonGroup() {}

    ButtonGroup(const ButtonGroup& copy) {
        this->operator=(copy);
    }

    void operator=(const ButtonGroup& copy);

    Button &operator[](long long unsigned int iterindex);

    Button &operator[](string uid);

    Button at(string uid) const;

    /// Sets needed attributes not gotten from constructor
    /// @param screen   parent
    /// @param renderer global renderer
    void SetAttrib(Screen * screen, SDL_Renderer * renderer);

    /// Renders all buttons
    /// @param x    relative x
    /// @param y    relative y
    /// @param f    if the parent is relative or absolute
    void Render(int x = 0, int y = 0, bool f = false);

    /// Destroys all buttons
    void Destroy();

    /// Sets default border
    /// @param pt       thickness (px)
    /// @param color    color (rgb)
    void SetDefaultBorder(int pt, Color color);

    /// Sets text defaults
    /// @param pt       thickness (px)
    /// @param color    color (rgb)
    /// @param font     ttf font
    void SetDefaultTextAttrib(int pt, Color color, string font);

    /// Sets button hover defaults
    /// @param onHover  callback when mouse is over button
    /// @param offHover callback when mouse is not over button
    void SetDefaultHoverRoutine(screen_callback onHover, screen_callback offHover);

    /// Creates a new button
    /// @param uid      map key
    /// @param x        relative x
    /// @param y        relative y
    /// @param w        width
    /// @param h        height
    /// @param color    fill color
    /// @param text     centered text
    /// @param onClick  callback when clicked
    void AddButton(string uid, int x, int y, int w, int h, Color color, string text, screen_callback onClick);

    /// Changes opacity
    /// @param percent  0 -> 1
    void TempShade(float percent);

    /// Gets number of buttons
    /// @return count
    int Count() const;

    /// Checks all buttons if hovered and calling callbacks
    /// @param mouse    mouse position
    void Hover(SDL_Point mouse);

    /// Checks all buttons if clicked and calling callbacks
    /// @param mouse    mouse position
    void Click(SDL_Point mouse);

};

#endif
