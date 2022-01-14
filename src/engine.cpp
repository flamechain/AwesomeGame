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

    SDL_setenv("SDL_VIDEODRIVER", "directx", 1); // override
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // linear
    return 0;
}

SDL_Renderer * CreateRenderer(SDL_Window * Window, int Flags) {
    // triggers program that controls graphics hardware
    int renderflags = Flags & GAME_RENDERER_ACCELERATED;
    SDL_Renderer * renderer = SDL_CreateRenderer(Window, -1, renderflags);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    errno = 0;
    return renderer;
}

SDL_Window * CreateWindow(int Width, int Height, string Title, int Flags) {
    SDL_Window * window = SDL_CreateWindow(Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Width, Height, SDL_WINDOW_OPENGL); // SDL_WINDOW_OPENGL replaced 0

    if (window == NULL) {
        errno = GAME_ERROR_WINDOW_FAIL;
        return window;
    }

    if (Flags & GAME_WINDOW_FULLSCREEN) {
        if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN)) {
            errno = GAME_ERROR_WINDOW_FAIL;
            return window;
        }
    }

    errno = 0;
    return window;
}
