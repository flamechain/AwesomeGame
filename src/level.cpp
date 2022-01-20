#include "level.h"
#include "screen.h"

void LevelGroup::SetAttrib(Screen * screen, SDL_Renderer * renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void LevelGroup::operator=(const LevelGroup& copy) {
    this->levels_.clear();
    if (copy.levels_.size() == 0) return;
    int i=0;
    for (map<string, Level>::iterator it = ((map<string, Level>)copy.levels_).begin(); it != copy.levels_.end(); it++, i++) {
        if (i >= copy.levels_.size()) break;
        this->levels_[it->first] = copy.levels_.at(it->first);
    }
}

void LevelGroup::Render() {
    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        this->levels_[it->first].Render();
    }
}

void LevelGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        this->levels_[it->first].Destroy();
    }
}

void LevelGroup::AddLevel(string uid, Level level) {
    this->levels_[uid] = level;
}

Level & LevelGroup::operator[](int iterindex) {
    vector<string> keys;

    for (map<string, Level>::iterator it = this->levels_.begin(); it != this->levels_.end(); it++) {
        keys.push_back(it->first);
    }

    return this->levels_[keys[iterindex]];
}

Level & LevelGroup::operator[](string uid) {
    if (this->levels_.find(uid) != this->levels_.end()) return this->levels_[uid];
}

Level LevelGroup::at(string uid) const {
    if (this->levels_.find(uid) != this->levels_.end()) return this->levels_.at(uid);
}
