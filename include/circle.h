#ifndef CIRCLE_H
#define CIRCLE_H

#include "utils.h"

//draw one quadrant arc, and mirror the other 4 quadrants
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
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}

class Circle {
private:

    SDL_Renderer * renderer_;

public:

    Circle() {}

};

class CircleGroup {
private:

public:

    CircleGroup() {}
};

#endif
