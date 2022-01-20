#include "screen.h"

void Screen::CreateBounds(int x, int y, int w, int h) {
    this->bounds_ = {x, y, w, h};
}

SDL_Renderer * Screen::GetRenderer() const {
    return this->renderer_;
}

SDL_Rect Screen::GetRect() const {
    return this->rect_;
}

Color Screen::GetColor() const {
    return this->bgcolor_;
}

unsigned int Screen::GetId() const {
    return this->uid_;
}

void Screen::SetId(unsigned int uid) {
    this->uid_ = uid;
}

void Screen::Render() {
    // add way to set render order, this is good default
    SDL_RenderFillRect(this->renderer_, &this->rect_);
    this->Level.Render();
    this->Rect.Render();
    this->Button.Render();
    this->Text.Render();
    this->Creature.Render();
}

void Screen::Destroy() {
    this->Level.Destroy();
    this->Rect.Destroy();
    this->Button.Destroy();
    this->Text.Destroy();
    this->Creature.Destroy();
}

void Screen::TempShade(float percent) {
    this->Rect.TempShade(percent);
    this->Button.TempShade(percent);
    this->Creature.TempShade(percent);
}

void Screen::Move(int x, int y) {
    if (this->rect_.x + x > this->bounds_.x) this->rect_.x = this->bounds_.x - x;
    if (this->rect_.y + y > this->bounds_.y) this->rect_.y = this->bounds_.y - y;
    if (this->rect_.x + x < 0) this->rect_.x = -x;
    if (this->rect_.y + y < 0) this->rect_.y = -y;

    this->rect_.x += x;
    this->rect_.y += y;
}
