#include "button.h"

#include "screen.h"

GAME_START

void ButtonGroup::SetAttrib(Screen *screen, SDL_Renderer *renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void ButtonGroup::operator=(const ButtonGroup& copy) {
    this->buttons_.clear();
    this->def_border_pt_ = copy.def_border_pt_;
    this->def_border_color_ = copy.def_border_color_;
    this->def_text_pt_ = copy.def_text_pt_;
    this->def_text_color_ = copy.def_text_color_;
    this->def_text_font_ = copy.def_text_font_;
    this->def_onhover_ = copy.def_onhover_;
    this->def_offhover_ = copy.def_offhover_;
    if (copy.buttons_.size() == 0) return;
    long long unsigned int i=0;

    for (map<string, Button>::iterator it = static_cast<map<string, Button>>(copy.buttons_).begin(); it != copy.buttons_.end(); it++, i++) {
        if (i >= copy.buttons_.size()) break;
        this->buttons_.insert(std::make_pair(it->first, copy.buttons_.at(it->first)));
    }
}

void ButtonGroup::Render(int x, int y, bool f) {
    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        if (f) this->buttons_[it->first].Render();
        else this->buttons_[it->first].Render(x, y);
    }
}

void ButtonGroup::Destroy() {
    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        this->buttons_[it->first].Destroy();
    }

    this->renderer_ = nullptr;
    this->screen_ = nullptr;
}

void ButtonGroup::SetDefaultBorder(int pt, Color color) {
    this->def_border_pt_ = pt;
    this->def_border_color_ = color;
}

void ButtonGroup::SetDefaultTextAttrib(int pt, Color color, string font) {
    this->def_text_pt_ = pt;
    this->def_text_color_ = color;
    this->def_text_font_ = font;
}

void ButtonGroup::SetDefaultHoverRoutine(screen_callback onHover, screen_callback offHover) {
    this->def_onhover_ = onHover;
    this->def_offhover_ = offHover;
}

void ButtonGroup::AddButton(string uid, int x, int y, int w, int h, Color color, string text, screen_callback onClick) {
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2) - (w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2) - (h / 2);
    this->buttons_.insert(std::make_pair(uid, Button(this->renderer_, x, y, w, h, color, this->def_border_pt_, this->def_border_color_)));
    this->buttons_[uid].SetText(this->def_text_font_, this->def_text_pt_, this->def_text_color_, text, true);
    this->callbacks_.insert(std::make_pair(uid, onClick));
    this->onhovers_.insert(std::make_pair(uid, this->def_onhover_));
    this->offhovers_.insert(std::make_pair(uid, this->def_offhover_));
}

void ButtonGroup::TempShade(float percent) {
    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        this->buttons_[it->first].TempShade(percent);
    }
}

int ButtonGroup::Count() const {
    return this->buttons_.size();
}

void ButtonGroup::Hover(SDL_Point mouse) {
    int x = mouse.x, y = mouse.y;

    if (!this->screen_->GetFollow()) {
        x -= this->screen_->GetRect().x;
        y -= this->screen_->GetRect().y;
    }

    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        screen_callback btnCallback;

        if (this->buttons_[it->first].IsInside(x, y)) btnCallback = this->onhovers_[it->first];
        else btnCallback = this->offhovers_[it->first];

        if (btnCallback != nullptr) btnCallback(*this->screen_, it->first);
    }
}

void ButtonGroup::Click(SDL_Point mouse) {
    int x = mouse.x, y = mouse.y;

    if (!this->screen_->GetFollow()) {
        x -= this->screen_->GetRect().x;
        y -= this->screen_->GetRect().y;
    }

    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        if (this->buttons_[it->first].IsInside(x, y)) {
            screen_callback btnCallback = this->callbacks_[it->first];
            if (btnCallback != nullptr) btnCallback(*this->screen_, it->first);
        }
    }
}

Button& ButtonGroup::operator[](long long unsigned int iterindex) {
    vector<string> keys;

    for (map<string, Button>::iterator it = this->buttons_.begin(); it != this->buttons_.end(); it++) {
        keys.push_back(it->first);
    }

    return this->buttons_[keys[iterindex]];
}

Button& ButtonGroup::operator[](string uid) {
    if (this->buttons_.find(uid) != this->buttons_.end()) return this->buttons_[uid];
    return this->buttons_[0];
}

Button ButtonGroup::at(string uid) const {
    if (this->buttons_.find(uid) != this->buttons_.end()) return this->buttons_.at(uid);
    return this->buttons_.at(0);
}

GAME_END
