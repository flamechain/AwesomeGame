#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "text.h"
#include "button.h"
#include "rect.h"
#include "level.h"
#include "creature.h"

class Screen {
private:

    SDL_Renderer * renderer_;
    Color bgcolor_;
    unsigned int uid_;
    SDL_Rect rect_;
    SDL_Rect bounds_;
    bool follow_;

public:

    static const int CENTERED = -1;

    Paragraph Text;
    ButtonGroup Button;
    RectGroup Rect;
    LevelGroup Level;
    CreatureGroup Creature;

    Screen(SDL_Renderer * renderer, unsigned int uid, int x, int y, int w, int h, Color bgcolor, bool follow = false) {
        this->renderer_ = renderer;
        this->uid_ = uid;
        this->rect_ = {x, y, w, h};
        this->bgcolor_ = bgcolor;
        this->follow_ = follow;
        this->Text.SetAttrib(this, this->renderer_);
        this->Button.SetAttrib(this, this->renderer_);
        this->Rect.SetAttrib(this, this->renderer_);
        this->Level.SetAttrib(this, this->renderer_);
        this->Creature.SetAttrib(this, this->renderer_);
    }

    Screen(const Screen& copy) {
        this->renderer_ = copy.GetRenderer();
        this->rect_ = copy.GetRect();
        this->bgcolor_ = copy.GetColor();

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
    }

    void CreateBounds(int x, int y, int w, int h);

    SDL_Renderer * GetRenderer() const;

    SDL_Rect GetRect() const;

    Color GetColor() const;

    unsigned int GetId() const;

    bool GetFollow() const;

    void SetId(unsigned int uid);

    void Render();

    void Destroy();

    void TempShade(float percent);

    void Move(int x, int y);

};

#endif
