#ifndef CIRCLE_H
#define CIRCLE_H

#include "utils.h"

/// Draws an elipse
/// @param renderer global renderer
/// @param cx       center x
/// @param cy       center y
/// @param rx       radius x
/// @param ry       radius y
void DrawElipse(SDL_Renderer * renderer, int cx, int cy, int rx, int ry) {
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0;

    // precision: 1 -> diamond; 27 -> smooth circle
    const int prec = 27;
    float theta = 0;

    //starting point
    int x  = (float)rx * cos(theta); // x start
    int y  = (float)ry * sin(theta); // y start
    int x1 = x;
    int y1 = y;

    // repeat until theta >= 90
    float step = pih/(float)prec; // degrees

    for (theta=step; theta<=pih; theta+=step) {
        // new point (+.5 is a quick rounding method)
        x1 = (float)rx * cosf(theta) + 0.5;
        y1 = (float)ry * sinf(theta) + 0.5;

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

    SDL_Renderer * renderer_;
    SDL_Point center_;
    int r_;
    Color color_;
    Color color_backup_;

public:

    Circle() {}

    Circle(SDL_Renderer * renderer, int x, int y, int r, Color rgb) {
        this->renderer_ = renderer;
        this->color_ = rgb;
        this->color_backup_ = rgb;
        this->center_.x = x;
        this->center_.y = y;
        this->r_ = r;
    }

    /// Renders circle outline
    /// @param x    relative x
    /// @param y    relative y
    void Render(int x = 0, int y = 0) {
        SDL_SetRenderDrawColor(this->renderer_, this->color_.r, this->color_.g, this->color_.b, 255);
        DrawElipse(this->renderer_, this->center_.x, this->center_.y, this->r_, this->r_);
    }

};

class CircleGroup {
private:

public:

    CircleGroup() {}

};

#endif
