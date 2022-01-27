#include "circle.h"

void CircleGroup::SetAttrib(Screen * screen, SDL_Renderer * renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void CircleGroup::operator=(const CircleGroup& copy) {
    this->circles_.clear();
    if (copy.circles_.size() == 0) return;
    int i=0;
    for (map<string, Circle>::iterator it = ((map<string, circles_>)copy.circles_).begin(); it != copy.circles_.end(); it++, i++) {
        if (i >= copy.circles_.size()) break;
        this->circles_.insert(std::make_pair(it->first, copy.circles_.at(it->first)));
    }
}

Circle &CircleGroup::operator[](int iterindex) {
    return this->circles_[this->order_[iterindex]];
}

Circle &CircleGroup::operator[](string uid) {
    if (this->circles_.find(uid) != this->circles_.end()) return this->circles_.at(uid);
    return this->circles_[0];
}

Circle CircleGroup::at(string uid) const {
    if (this->circles_.find(uid) != this->circles_.end()) return this->circles_.at(uid);
    return this->circles_.at(0);
}

void CircleGroup::Render(int x = 0, int y = 0, bool f = false) {
    for(string uid : this->order_) {
        if (f) this->circles_[uid].Render();
        else this->circles_[uid].Render(x, y);
    }
}

void CircleGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
    for (map<string, Rect>::iterator it = this->circles_.begin(); it != this->circles_.end(); it++) {
        this->circles_[it->first].Destroy();
    }
}

void CircleGroup::AddCircle(string uid, int x, int y, int r, Color color) {
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2) - (w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2) - (h / 2);
    this->circles_.insert(std::make_pair(uid, Circle(this->renderer_, x, y, r, color)));
    this->order_.push_back(uid);
}
