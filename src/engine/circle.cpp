#include "circle.h"

#include "screen.h"

GAME_START

void DrawElipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry) {
    double pi = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0;

    // precision: 1 -> diamond; 27 -> smooth circle
    const int prec = 27;
    float theta = 0;

    //starting point
    int x  = static_cast<double>(rx) * cos(theta); // x start
    int y  = static_cast<double>(ry) * sin(theta); // y start
    int x1 = x;
    int y1 = y;

    // repeat until theta >= 90
    float step = pih/static_cast<float>(prec); // degrees

    for (theta=step; theta<=pih; theta+=step) {
        // new point (+.5 is a quick rounding method)
        x1 = static_cast<double>(rx) * cosf(theta) + 0.5;
        y1 = static_cast<double>(ry) * sinf(theta) + 0.5;

        // draw line from previous point to new point, ONLY if point incremented
        if ( (x != x1) || (y != y1) ) {
            SDL_RenderDrawLine(renderer, cx + x, cy - y, cx + x1, cy - y1 ); // quadrant TR
            SDL_RenderDrawLine(renderer, cx - x, cy - y, cx - x1, cy - y1 ); // quadrant TL
            SDL_RenderDrawLine(renderer, cx - x, cy + y, cx - x1, cy + y1 ); // quadrant BL
            SDL_RenderDrawLine(renderer, cx + x, cy + y, cx + x1, cy + y1 ); // quadrant BR
        }

        x = x1;
        y = y1;
    }

    // account for rounding mistakes
    if (x != 0) {
        x = 0;
        SDL_RenderDrawLine(renderer, cx + x, cy - y, cx + x1, cy - y1 ); // quadrant TR
        SDL_RenderDrawLine(renderer, cx - x, cy - y, cx - x1, cy - y1 ); // quadrant TL1
        SDL_RenderDrawLine(renderer, cx - x, cy + y, cx - x1, cy + y1 ); // quadrant BL
        SDL_RenderDrawLine(renderer, cx + x, cy + y, cx + x1, cy + y1 ); // quadrant BR
    }
}

void CircleGroup::SetAttrib(Screen *screen, SDL_Renderer *renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void CircleGroup::operator=(const CircleGroup& copy) {
    this->circles_.clear();
    if (copy.circles_.size() == 0) return;
    long long unsigned int i=0;

    for (map<string, Circle>::iterator it = static_cast<map<string, Circle>>(copy.circles_).begin(); it != copy.circles_.end(); it++, i++) {
        if (i >= copy.circles_.size()) break;
        this->circles_.insert(std::make_pair(it->first, copy.circles_.at(it->first)));
    }
}

Circle& CircleGroup::operator[](long long unsigned int iterindex) {
    return this->circles_[this->order_[iterindex]];
}

Circle& CircleGroup::operator[](string uid) {
    if (this->circles_.find(uid) != this->circles_.end()) return this->circles_.at(uid);
    return this->circles_[0];
}

Circle CircleGroup::at(string uid) const {
    if (this->circles_.find(uid) != this->circles_.end()) return this->circles_.at(uid);
    return this->circles_.at(0);
}

void CircleGroup::Render(int x, int y, bool f) {
    for(string uid : this->order_) {
        if (f) this->circles_[uid].Render();
        else this->circles_[uid].Render(x, y);
    }
}

void CircleGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;

    for (map<string, Circle>::iterator it = this->circles_.begin(); it != this->circles_.end(); it++) {
        this->circles_[it->first].Destroy();
    }
}

void CircleGroup::AddCircle(string uid, int x, int y, int r, Color color) {
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2);
    this->circles_.insert(std::make_pair(uid, Circle(this->renderer_, x, y, r, color)));
    this->order_.push_back(uid);
}

GAME_END
