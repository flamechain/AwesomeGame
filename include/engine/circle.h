#ifndef CIRCLE_H
#define CIRCLE_H

#include "utils.h"

/// Draws an elipse
/// @param renderer global renderer
/// @param cx       center x
/// @param cy       center y
/// @param rx       radius x
/// @param ry       radius y
inline void DrawElipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry) {
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

class Circle {
private:

    SDL_Renderer *renderer_;
    SDL_Point center_;
    int r_;
    Color color_;
    Color color_backup_;
    int border_pt_;
    Color border_color_;

public:

    Circle() {}

    Circle(SDL_Renderer *renderer, int x, int y, int r, Color rgb) {
        this->renderer_ = renderer;
        this->color_ = rgb;
        this->color_backup_ = rgb;
        this->center_.x = x;
        this->center_.y = y;
        this->r_ = r;
    }

    void SetBorder(int pt, Color color) {
        this->border_pt_ = pt;
        this->border_color_ = color;
    }

    void Render_BiggestSquare(int x = 0, int y = 0) {
        // biggest square inside circle to reduce amount of calls to DrawElipse
        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        double side = this->r_ * sqrt(2); // biggest square algorithm
        SDL_Rect square = {x + this->center_.x - static_cast<int>(side / 2), y + this->center_.y - static_cast<int>(side / 2), static_cast<int>(side), static_cast<int>(side)};
        SDL_RenderFillRect(this->renderer_, &square);
        for (int i=0; i<(this->r_-side); i++) {
            DrawElipse(this->renderer_, this->center_.x, this->center_.y, this->r_ - i, this->r_);
        }

        // border (rendering on top instead of calculating inside circle to be smaller)
        SDL_SetRenderDrawColor(this->renderer_, this->border_color_.r, this->border_color_.g, this->border_color_.b, 255);
        for (int i=0; i<this->border_pt_; i++) {
            DrawElipse(this->renderer_, this->center_.x, this->center_.y, this->r_-i, this->r_-i);
        }
    }

    void Render_Triangles(int x = 0, int y = 0) {
        
    }

    /// Renders circle outline
    /// @param x    relative x
    /// @param y    relative y
    void Render(int x = 0, int y = 0) {
        this->Render_Triangles(x, y);
    }

    /// Destroys circle
    void Destroy() {
        this->renderer_ = nullptr;
    }

    /// Sets circle position
    /// @param x    x center
    /// @param y    y center
    void SetPosition(int x, int y) {
        this->center_.x = x;
        this->center_.y = y;
    }
};

class CircleGroup {
private:

    SDL_Renderer *renderer_;
    Screen *screen_;
    map<string, Circle> circles_;
    vector<string> order_;

public:

    CircleGroup() {}

    CircleGroup(const CircleGroup& copy) {
        this->operator=(copy);
    }

    void operator=(const CircleGroup& copy);

    Circle& operator[](long long unsigned int iterindex);

    Circle& operator[](string uid);

    Circle at(string uid) const;

    /// Sets attributes needed not given by constructor
    /// @param screen   parent
    /// @param renderer global renderer
    void SetAttrib(Screen *screen, SDL_Renderer *renderer);

    /// Renders all Circles
    /// @param x    relative x
    /// @param y    relative y
    /// @param f    if screen is relative or absolute
    void Render(int x = 0, int y = 0, bool f = false);

    /// Destroys all rects
    void Destroy();

    /// Creates circle
    /// @param x        relative x
    /// @param y        relative y
    /// @param r        circle radius
    /// @param color    circle color
    void AddCircle(string uid, int x, int y, int r, Color color);
};

#endif
