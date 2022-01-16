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
    Camera camera_;

public:

    const int CENTERED = -1;

    Paragraph Text;
    ButtonGroup Button;
    RectGroup Rect;
    LevelGroup Level;
    CreatureGroup Creature;

    Screen(SDL_Renderer * renderer, unsigned int uid, int x, int y, int w, int h, Color bgcolor) {
        this->renderer_ = renderer;
        this->uid_ = uid;
        this->rect_ = {x, y, w, h};
        this->bgcolor_ = bgcolor_;
        this->Text = renderer;
        this->Button = renderer;
        this->Rect = renderer;
        this->Level = renderer;
        this->Creature = renderer;
    }

    Screen(const Screen& copy) {
        this->renderer_ = copy.GetRenderer();
        this->rect_ = copy.GetRect();
        this->bgcolor_ = copy.GetColor();
        this->Text = copy.Text;
        this->Button = copy.Button;
        this->Rect = copy.Rect;
        this->Level = copy.Level;
        this->Creature = copy.Creature;
    }

    void CreateBounds(int x, int y, int w, int h) {
        this->bounds_ = {x, y, w, h};
    }

    SDL_Renderer * GetRenderer() const {
        return this->renderer_;
    }

    SDL_Rect GetRect() const {
        return this->rect_;
    }

    Color GetColor() const {
        return this->bgcolor_;
    }

    unsigned int GetId() const {
        return this->uid_;
    }

    void SetId(unsigned int uid) {
        this->uid_ = uid;
    }

    void Render() {
        // add way to set render order, this is good default
        this->Level.Render();
        this->Rect.Render();
        this->Button.Render();
        this->Text.Render();
        this->Creature.Render();
    }

    void Destroy() {
        this->Level.Destroy();
        this->Rect.Destroy();
        this->Button.Destroy();
        this->Text.Destroy();
        this->Creature.Destroy();
    }

    void SetOpacity(int r, int g, int b) {
        this->Rect.SetOpacity(r, g, b);
        this->Button.SetOpacity(r, g, b);
        this->Creature.SetOpacity(r, g, b);
    }

    void Move(int x, int y) {
        if (this->rect_.x + x > this->bounds_.x) this->rect_.x = this->bounds_.x - x;
        if (this->rect_.y + y > this->bounds_.y) this->rect_.y = this->bounds_.y - y;
        if (this->rect_.x + x < 0) this->rect_.x = -x;
        if (this->rect_.y + y < 0) this->rect_.y = -y;

        this->rect_.x += x;
        this->rect_.y += y;
    }

};

#endif
