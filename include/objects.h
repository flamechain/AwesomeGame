#ifndef OBJECTS_H
#define OBJECTS_H

#include "utils.h"
#include "game.h"

class WASDController {
private:

    bool up_;
    bool down_;
    bool left_;
    bool right_;

public:

    WASDController() {
        this->up_ = false;
        this->down_ = false;
        this->left_ = false;
        this->right_ = false;
    }

    void SetUpMovement(bool moving) {
        this->up_ = moving;
    }

    void SetDownMovement(bool moving) {
        this->down_ = moving;
    }

    void SetLeftMovement(bool moving) {
        this->left_ = moving;
    }

    void SetRightMovement(bool moving) {
        this->right_ = moving;
    }

    bool MovingUp() {
        return this->up_;
    }

    bool MovingDown() {
        return this->down_;
    }

    bool MovingLeft() {
        return this->left_;
    }

    bool MovingRight() {
        return this->right_;
    }

};

#endif
