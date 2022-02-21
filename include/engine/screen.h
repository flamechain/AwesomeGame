#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "text.h"
#include "button.h"
#include "rect.h"
#include "level.h"
#include "creature.h"
#include "circle.h"

class Screen {
private:

    SDL_Renderer *renderer_;
    Color bgcolor_;
    Color color_;
    unsigned int uid_;
    SDL_Rect rect_;
    SDL_Rect bounds_;
    bool follow_;
    unsigned char transparent_;

public:

    static const int CENTERED = -1;

    Paragraph Text;
    ButtonGroup Button;
    RectGroup Rect;
    LevelGroup Level;
    CreatureGroup Creature;
    CircleGroup Circle;

    Screen() {
        this->transparent_ = 255;
        this->rect_ = {0, 0, 0, 0};
        this->bgcolor_ = BLACK;
        this->color_ = BLACK;
        this->follow_ = false;
    }

    Screen(SDL_Renderer *renderer, unsigned int uid, int x, int y, int w, int h, Color bgcolor, bool follow = false) {
        this->renderer_ = renderer;
        this->transparent_ = 255;
        this->uid_ = uid;
        this->rect_ = {x, y, w, h};
        this->bgcolor_ = bgcolor;
        this->color_ = bgcolor;
        this->follow_ = follow;
        this->Text.SetAttrib(this, this->renderer_);
        this->Button.SetAttrib(this, this->renderer_);
        this->Rect.SetAttrib(this, this->renderer_);
        this->Level.SetAttrib(this, this->renderer_);
        this->Creature.SetAttrib(this, this->renderer_);
        this->Circle.SetAttrib(this, this->renderer_);
    }

    Screen(const Screen& copy) {
        this->renderer_ = copy.renderer_;
        this->transparent_ = copy.transparent_;
        this->uid_ = copy.uid_;
        this->rect_ = copy.rect_;
        this->bgcolor_ = copy.bgcolor_;
        this->color_ = copy.color_;
        this->follow_ = copy.follow_;

        this->Text = copy.Text;
        this->Text.SetAttrib(this, this->renderer_);
        this->Button = copy.Button;
        this->Button.SetAttrib(this, this->renderer_);
        this->Rect = copy.Rect;
        this->Rect.SetAttrib(this, this->renderer_);
        this->Level = copy.Level;
        this->Level.SetAttrib(this, this->renderer_);
        this->Creature = copy.Creature;
        this->Creature.SetAttrib(this, this->renderer_);
        this->Circle = copy.Circle;
        this->Circle.SetAttrib(this, this->renderer_);
    }

    /// Sets attribs for children
    void ResetAttrib();

    /// Creates artifical bounds when moving
    /// @param x    x extension
    /// @param y    y extension
    /// @param w    x+w extension
    /// @param h    y+h extension
    void CreateBounds(int x, int y, int w, int h);

    /// Gets uid
    /// @return uid
    unsigned int GetId() const;

    /// Gets size
    /// @return dimensions
    SDL_Rect GetRect() const {
        return this->rect_;
    }

    /// Gets if relative or absolute
    /// @return bool if relative
    bool GetFollow() const;

    /// New uid
    /// @param uid  uid
    void SetId(unsigned int uid);

    /// Renders all children
    void Render();

    /// Destroys all children
    void Destroy();

    /// Sets all childrens opacity
    /// @param percent  0 -> 1
    void TempShade(float percent);

    /// Moves screen (relative)
    /// @param x    x relative
    /// @param y    y relative
    void Move(int x, int y);

    /// Sets permanent background color
    /// @param color    color
    void SetColor(Color color);

    /// Sets temporary background color
    /// @param color    color
    void SetRenderColor(Color color);

    /// Gets origin color (ignoring TempShade)
    /// @return color
    Color GetColor() const;

    /// Set alpha channel
    /// @param percent  0 -> 1
    void SetTransparency(float percent);

    /// Gets renderer
    /// @return pointer to renderer, not copy
    SDL_Renderer * GetRenderer() const;

};

#endif
