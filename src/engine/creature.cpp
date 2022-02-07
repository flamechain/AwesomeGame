#include "creature.h"
#include "screen.h"

void Creature::operator=(const Creature& copy) {
    this->LoadTile(copy.type_);
    this->SetSize(0, 0, this->hitbox_.w, this->hitbox_.h);
    this->SetPosition(copy.hitbox_.x, copy.hitbox_.y);
}

SDL_Rect Creature::GetHitbox() const {
    return this->real_hitbox_;
}

void Creature::SetSize(int x, int y, int w, int h) {
    this->real_offset_.x = x;
    this->real_offset_.y = y;
    this->real_hitbox_.x = this->hitbox_.x + x;
    this->real_hitbox_.y = this->hitbox_.y + y;
    this->real_hitbox_.w = w;
    this->real_hitbox_.h = h;
}

void Creature::Resize(int w, int h) {
    this->hitbox_.w = w;
    this->hitbox_.h = h;
    this->real_hitbox_.w = w;
    this->real_hitbox_.h = h;
}

void Creature::SetPosition(int x, int y) {
    this->hitbox_.x = x;
    this->hitbox_.y = y;
    this->real_hitbox_.x = this->hitbox_.x + this->real_offset_.x;
    this->real_hitbox_.y = this->hitbox_.y + this->real_offset_.y;
}

void Creature::SetBounds(int x, int y, int w, int h) {
    this->bounds_.x = x;
    this->bounds_.y = y;
    this->bounds_.w = w;
    this->bounds_.h = h;
}

bool Creature::IsCenteredX(Screen& screen) {
    if (this->hitbox_.x + this->hitbox_.w / 2 == screen.GetRect().x + screen.GetRect().w / 2) return true;
    return false;
}

bool Creature::IsCenteredY(Screen& screen) {
    if (this->hitbox_.y + this->hitbox_.h / 2 == screen.GetRect().y + screen.GetRect().h / 2) return true;
    return false;
}

void Creature::Update(SDL_Point offset, bool checkBounds) {
    if (!checkBounds) {
        this->hitbox_.x += offset.x;
        this->hitbox_.y += offset.y;
        this->real_hitbox_.x += offset.x;
        this->real_hitbox_.y += offset.y;
        return;
    }

    this->hitbox_.x += offset.x;
    int flipFlags = this->GetFlip();
    if (offset.x < 0) flipFlags |= SDL_FLIP_HORIZONTAL;
    else if (offset.x > 0) flipFlags = SDL_FLIP_NONE;
    this->hitbox_.y += offset.y;
    this->real_hitbox_.x += offset.x;
    this->real_hitbox_.y += offset.y;
    this->Flip(flipFlags);

    if (this->real_hitbox_.x + this->real_hitbox_.w > this->bounds_.w) {
        this->real_hitbox_.x = this->bounds_.w - this->real_hitbox_.w;
        this->hitbox_.x = this->bounds_.w - this->real_hitbox_.w - this->real_offset_.x;
    }
    if (this->hitbox_.x < this->bounds_.x) {
        this->real_hitbox_.x = this->bounds_.x;
        this->hitbox_.x = this->bounds_.x - this->real_offset_.x;
    }
    if (this->hitbox_.y + this->real_hitbox_.h > this->bounds_.h) {
        this->real_hitbox_.y = this->bounds_.h - this->real_hitbox_.h;
        this->hitbox_.y = this->bounds_.h - this->real_hitbox_.h - this->real_offset_.y;
    }
    if (this->hitbox_.y < this->bounds_.y) {
        this->real_hitbox_.y = this->bounds_.y;
        this->hitbox_.y = this->bounds_.y - this->real_offset_.y;
    }
}

void CreatureGroup::SetAttrib(Screen * screen, SDL_Renderer * renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void CreatureGroup::operator=(const CreatureGroup& copy) {
    this->creatures_.clear();
    if (copy.creatures_.size() == 0) return;
    int i=0;
    for (map<string, Creature>::iterator it = ((map<string, Creature>)copy.creatures_).begin(); it != copy.creatures_.end(); it++, i++) {
        if (i >= copy.creatures_.size()) break;
        this->creatures_.insert(std::make_pair(it->first, copy.creatures_.at(it->first)));
    }
}

void CreatureGroup::TempShade(float percent) {
    for (map<string, Creature>::iterator it = this->creatures_.begin(); it != this->creatures_.end(); it++) {
        this->creatures_[it->first].SetExtraColor(255*percent, 255*percent, 255*percent);
    }
}

void CreatureGroup::AddCreature(string uid, TileType type, int x, int y, int w, int h) {
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2) - (w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2) - (h / 2);
    this->creatures_.insert(std::make_pair(uid, Creature(type, x, y)));
    this->creatures_[uid].SetRenderer(this->renderer_);
    this->creatures_[uid].LoadTile(type); // reload with valid renderer
    this->creatures_[uid].Resize(w, h);
}

void CreatureGroup::Render(int x, int y, bool f) {
    for (map<string, Creature>::iterator it = this->creatures_.begin(); it != this->creatures_.end(); it++) {
        if (f) this->creatures_[it->first].Render(-x, -y);
        else this->creatures_[it->first].Render();
    }
}

void CreatureGroup::Destroy() {
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
    for (map<string, Creature>::iterator it = this->creatures_.begin(); it != this->creatures_.end(); it++) {
        this->creatures_[it->first].Destroy();
    }
}

Creature & CreatureGroup::operator[](int iterindex) {
    vector<string> keys;

    for (map<string, Creature>::iterator it = this->creatures_.begin(); it != this->creatures_.end(); it++) {
        keys.push_back(it->first);
    }

    return this->creatures_[keys[iterindex]];
}

Creature & CreatureGroup::operator[](string uid) {
    if (this->creatures_.find(uid) != this->creatures_.end()) return this->creatures_[uid];
    return this->creatures_[0];
}

Creature CreatureGroup::at(string uid) const {
    if (this->creatures_.find(uid) != this->creatures_.end()) return this->creatures_.at(uid);
    return this->creatures_.at(0);
}
