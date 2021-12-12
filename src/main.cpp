#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    int imgflags = IMG_INIT_PNG|IMG_INIT_JPG;
    if ((IMG_Init(imgflags)&imgflags) != imgflags) {
        printf("error initializing SDL_image: %s\n", IMG_GetError());
        return 2;
    }

    const int SCREEN_HEIGHT = 1000;
    const int SCREEN_WIDTH = 1000;

    SDL_Window* window = SDL_CreateWindow("AwesomeGame",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_OPENGL); // SDL_WINDOW_OPENGL replaced 0

    // triggers program that controls graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    // background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Surface* surface; // surface to load sprites
    surface = IMG_Load("img/sprites/test.png"); // temp
    if (surface == NULL) {
        printf("error finding images\n");
        return 3;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // make image usable
    SDL_FreeSurface(surface);

    SDL_Rect hitbox; // rectangle that we control
    SDL_QueryTexture(texture, NULL, NULL, &hitbox.w, &hitbox.h);

    // change size of hitbox
    hitbox.w /= 6;
    hitbox.h /= 6;

    // position hitbox on the screen
    hitbox.x = (SCREEN_WIDTH - hitbox.w) / 2;
    hitbox.y = (SCREEN_HEIGHT - hitbox.h) / 2;

    int speed = 300;

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            hitbox.y -= speed / 30;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            hitbox.x -= speed / 30;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            hitbox.y += speed / 30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            hitbox.x += speed / 30;
                            break;
                        default:
                            break;
                    }
            }
        }
        
        // right boundary
        if (hitbox.x + hitbox.w > SCREEN_WIDTH)
            hitbox.x = SCREEN_WIDTH - hitbox.w;
 
        // left boundary
        if (hitbox.x < 0)
            hitbox.x = 0;
 
        // bottom boundary
        if (hitbox.y + hitbox.h > SCREEN_HEIGHT)
            hitbox.y = SCREEN_HEIGHT - hitbox.h;
 
        // upper boundary
        if (hitbox.y < 0)
            hitbox.y = 0;

        // clear the screen
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &hitbox);
 
        // triggers the double buffers for multiple rendering
        SDL_RenderPresent(renderer);
 
        // 60 fps (milliseconds)
        SDL_Delay(1000 / 60);
    }


    // cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
