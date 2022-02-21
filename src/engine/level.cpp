#include "level.h"

#include "screen.h"

void LevelGroup::SetAttrib(Screen *screen, SDL_Renderer *renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void LevelGroup::operator=(const LevelGroup& copy) {
    this->levels_.clear();
    if (copy.levels_.size() == 0) return;
    long long unsigned int i=0;

    for (map<string, Level>::iterator it = static_cast<map<string, Level>>(copy.levels_).begin(); it != copy.levels_.end(); it++, i++) {
        if (i >= copy.levels_.size()) break;
        this->levels_.insert(std::make_pair(it->first, copy.levels_.at(it->first)));
    }
}

void LevelGroup::Render(int x, int y, bool f) {
    if (this->current_ != "") {
        if (f) this->levels_[this->current_].Render(-x, -y);
        else this->levels_[this->current_].Render();
    }
}

void LevelGroup::SetCurrent(string uid) {
    this->current_ = uid;
}

void LevelGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        this->levels_[it->first].Destroy();
    }
}

void LevelGroup::AddLevel(string uid) {
    Level l;
    this->levels_.insert(std::make_pair(uid, l));
    this->levels_[uid].SetRenderer(this->renderer_);
}

Level& LevelGroup::operator[](long long unsigned int iterindex) {
    vector<string> keys;

    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        keys.push_back(it->first);
    }

    return this->levels_[keys[iterindex]];
}

Level& LevelGroup::operator[](string uid) {
    if (this->levels_.find(uid) != this->levels_.end()) return this->levels_[uid];
    return this->levels_[0];
}

Level LevelGroup::at(string uid) const {
    if (this->levels_.find(uid) != this->levels_.end()) return this->levels_.at(uid);
    return this->levels_.at(0);
}

void LevelGroup::TempShade(float percent) {
    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        this->levels_[it->first].SetExtraColor(255*percent, 255*percent, 255*percent);
    }
}

string LevelGroup::GetCurrent() const {
    return this->current_;
}

void LevelGroup::Finalize(string uid) {
    this->levels_[uid].SetRenderer(this->renderer_);
}
