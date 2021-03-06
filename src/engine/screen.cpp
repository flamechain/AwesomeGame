#include "screen.h"

GAME_START

void Screen::CreateBounds(int x, int y, int w, int h) {
    this->bounds_ = {this->rect_.x - x, this->rect_.y - y, this->rect_.x + w, this->rect_.y + h};
}

unsigned int Screen::GetId() const {
    return this->uid_;
}

void Screen::SetId(unsigned int uid) {
    this->uid_ = uid;
}

void Screen::Render() {
    // add way to set render order, this is good default
    SDL_SetRenderDrawColor(this->renderer_, this->bgcolor_.r, this->bgcolor_.g, this->bgcolor_.b, this->transparent_);
    SDL_RenderFillRect(this->renderer_, &this->rect_);

    this->Level.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Rect.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Button.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Text.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Creature.Render(this->rect_.x, this->rect_.y, this->follow_);
    this->Circle.Render(this->rect_.x, this->rect_.y, this->follow_);
}

void Screen::Destroy() {
    this->Level.Destroy();
    this->Rect.Destroy();
    this->Button.Destroy();
    this->Text.Destroy();
    this->Creature.Destroy();
    this->Circle.Destroy();
}

bool Screen::GetFollow() const {
    return this->follow_;
}

void Screen::ResetAttrib() {
    this->Text.SetAttrib(this, this->renderer_);
    this->Button.SetAttrib(this, this->renderer_);
    this->Rect.SetAttrib(this, this->renderer_);
    this->Level.SetAttrib(this, this->renderer_);
    this->Creature.SetAttrib(this, this->renderer_);
    this->Circle.SetAttrib(this, this->renderer_);
}

void Screen::TempShade(float percent) {
    this->bgcolor_.r = this->color_.r*percent;
    this->bgcolor_.g = this->color_.g*percent;
    this->bgcolor_.b = this->color_.b*percent;
    this->Rect.TempShade(percent);
    this->Button.TempShade(percent);
    this->Creature.TempShade(percent);
    this->Level.TempShade(percent);
}

void Screen::Move(int x, int y) {
    if (this->rect_.x + x > this->bounds_.w) this->rect_.x = this->bounds_.w - x;
    if (this->rect_.y + y > this->bounds_.h) this->rect_.y = this->bounds_.h - y;
    if (this->rect_.x + x < this->bounds_.x) this->rect_.x = this->bounds_.x - x;
    if (this->rect_.y + y < this->bounds_.y) this->rect_.y = this->bounds_.y - y;

    this->rect_.x += x;
    this->rect_.y += y;
}

void Screen::SetColor(Color color) {
    this->bgcolor_ = color;
    this->color_ = color;
}

void Screen::SetRenderColor(Color color) {
    this->bgcolor_ = color;
}

Color Screen::GetColor() const {
    return this->color_;
}

void Screen::SetTransparency(float percent) {
    this->transparent_ = 255 - (255 * percent);    
}

SDL_Renderer * Screen::GetRenderer() const {
    return this->renderer_;
}

GAME_END
