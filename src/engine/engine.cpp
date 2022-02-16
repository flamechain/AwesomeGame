#include "engine.h"

int InitializeEngine() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        errno = GAME_ERROR_SDL_FAIL;
        ConsoleOutput("Failed loading SDL: %s\n", SDL_GetError());
        return errno;
    }

    int imgflags = IMG_INIT_PNG|IMG_INIT_JPG;
    if ((IMG_Init(imgflags)&imgflags) != imgflags) {
        errno = GAME_ERROR_IMAGE_FAIL;
        ConsoleOutput("Failed loading SDL_image: %s\n", IMG_GetError());
        return errno;
    }

    if (TTF_Init() < 0) {
        errno = GAME_ERROR_TTF_FAIL;
        ConsoleOutput("Failed loading SDL_ttf: %s\n", TTF_GetError());
        return errno;
    }

    if (Mix_Init(MIX_INIT_MP3) == 0) {
        errno = GAME_ERROR_MIX_FAIL;
        ConsoleOutput("Failed loading SDL_Mixer: %s\n", Mix_GetError());
        return errno;
    }

    SDL_setenv("SDL_VIDEODRIVER", "directx", 1); // override
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // linear
    return 0;
}

SDL_Renderer *CreateRenderer(SDL_Window *window, int flags) {
    // triggers program that controls graphics hardware
    Uint32 renderflags = flags & GAME_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderflags);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    errno = 0;
    return renderer;
}

SDL_Window *CreateWindow(int width, int height, string title, int flags) {
    SDL_Window *window = SDL_CreateWindow(title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL); // SDL_WINDOW_OPENGL replaced 0

    if (window == NULL) {
        errno = GAME_ERROR_WINDOW_FAIL;
        return window;
    }

    if (flags & GAME_WINDOW_FULLSCREEN) {
        if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN)) {
            errno = GAME_ERROR_WINDOW_FAIL;
            return window;
        }
    }

    errno = 0;
    return window;
}
