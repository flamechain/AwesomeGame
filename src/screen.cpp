#include "screen.h"

void Screen::CreateBounds(int x, int y, int w, int h) {
    this->bounds_ = {this->rect_.x - x, this->rect_.y - y, this->rect_.x + w, this->rect_.y + h};
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
    SDL_SetRenderDrawColor(this->renderer_, this->bgcolor_.r, this->bgcolor_.g, this->bgcolor_.b, 255);
    SDL_RenderFillRect(this->renderer_, &this->rect_);
    this->Level.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Rect.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Button.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Text.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Creature.Render(this->rect_.x, this->rect_.y, this->follow_);
}

void Screen::Destroy() {
    this->Level.Destroy();
    this->Rect.Destroy();
    this->Button.Destroy();
    this->Text.Destroy();
    this->Creature.Destroy();
}

bool Screen::GetFollow() const {
    return this->follow_;
}

void Screen::TempShade(float percent) {
    this->Rect.TempShade(percent);
    this->Button.TempShade(percent);
    this->Creature.TempShade(percent);
}

void Screen::Move(int x, int y) {
    if (this->rect_.x + x > this->bounds_.w) this->rect_.x = this->bounds_.w - x;
    if (this->rect_.y + y > this->bounds_.h) this->rect_.y = this->bounds_.h - y;
    if (this->rect_.x + x < this->bounds_.x) this->rect_.x = 0 - this->bounds_.x -x;
    if (this->rect_.y + y < this->bounds_.y) this->rect_.y = 0 - this->bounds_.y -y;

    this->rect_.x += x;
    this->rect_.y += y;
}
