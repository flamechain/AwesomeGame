#include "rect.h"
#include "screen.h"

void RectGroup::SetAttrib(Screen * screen, SDL_Renderer * renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void RectGroup::operator=(const RectGroup& copy) {
    this->rects_.clear();
    if (copy.rects_.size() == 0) return;
    long long unsigned int i=0;
    for (map<string, Rect>::iterator it = static_cast<map<string, Rect>>(copy.rects_).begin(); it != copy.rects_.end(); it++, i++) {
        if (i >= copy.rects_.size()) break;
        this->rects_.insert(std::make_pair(it->first, copy.rects_.at(it->first)));
    }
}

void RectGroup::Render(int x, int y, bool f) {
    for(string uid : this->order_) {
        if (f) this->rects_[uid].Render();
        else this->rects_[uid].Render(x, y);
    }
}

void RectGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
    for (map<string, Rect>::iterator it = this->rects_.begin(); it != this->rects_.end(); it++) {
        this->rects_[it->first].Destroy();
    }
}

void RectGroup::TempShade(float percent) {
    for (map<string, Rect>::iterator it = this->rects_.begin(); it != this->rects_.end(); it++) {
        this->rects_[it->first].TempShade(percent);
    }
}

void RectGroup::AddRect(string uid, int x, int y, int w, int h, Color color) {
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2) - (w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2) - (h / 2);
    this->rects_.insert(std::make_pair(uid, Rect(this->renderer_, x, y, w, h, color)));
    this->order_.push_back(uid);
}

Rect & RectGroup::operator[](long long unsigned int iterindex) {
    return this->rects_[this->order_[iterindex]];
}

Rect RectGroup::at(string uid) const {
    if (this->rects_.find(uid) != this->rects_.end()) return this->rects_.at(uid);
    return this->rects_.at(0);
}

Rect & RectGroup::operator[](string uid) {
    if (this->rects_.find(uid) != this->rects_.end()) return this->rects_[uid];
    return this->rects_[0];
}
