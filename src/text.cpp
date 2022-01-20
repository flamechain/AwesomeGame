#include "text.h"
#include "screen.h"

void Paragraph::SetAttrib(Screen * screen, SDL_Renderer * renderer) {
    this->renderer_ = renderer;
    this->screen_ = screen;
}

void Paragraph::operator=(const Paragraph& copy) {
    this->lines_.clear();
    if (copy.lines_.size() == 0) return;
    int i=0;
    for (map<string, Text>::iterator it = ((map<string, Text>)copy.lines_).begin(); it != copy.lines_.end(); it++, i++) {
        if (i >= copy.lines_.size()) break;
        this->lines_[it->first] = copy.lines_.at(it->first);
    }
}

void Paragraph::Destroy() {
    for (map<string, Text>::iterator it = this->lines_.begin(); it != this->lines_.end(); it++) {
        this->lines_[it->first].Destroy();
    }
    this->renderer_ = nullptr;
    this->screen_ = nullptr;
}

void Paragraph::TempShade(float percent) {
    for (map<string, Text>::iterator it = this->lines_.begin(); it != this->lines_.end(); it++) {
        this->lines_[it->first].TempShade(percent);
    }
}

void Paragraph::AddLine(string uid, int x, int y, string font, int pt, Color color, string text) {
    this->lines_[uid] = Text(this->renderer_, font, pt, color, text);
    if (x == Screen::CENTERED) x = (this->screen_->GetRect().w / 2) - (this->lines_[uid].GetRect().w / 2);
    if (y == Screen::CENTERED) y = (this->screen_->GetRect().h / 2) - (this->lines_[uid].GetRect().h / 2);
    this->lines_[uid].SetPosition(x, y);
}

Text & Paragraph::operator[](unsigned int iterindex) {
    vector<string> keys;

    for (map<string, Text>::iterator it = this->lines_.begin(); it != this->lines_.end(); it++) {
        keys.push_back(it->first);
    }

    return this->lines_[keys[iterindex]];
}

Text & Paragraph::operator[](string uid) {
    if (this->lines_.find(uid) != this->lines_.end()) return this->lines_[uid];
}

Text Paragraph::at(string uid) const {
    if (this->lines_.find(uid) != this->lines_.end()) return this->lines_.at(uid);
}

void Paragraph::Render() {
    for (map<string, Text>::iterator it = this->lines_.begin(); it != this->lines_.end(); it++) {
        this->lines_[it->first].Render();
    }
}
