#include "game.h"

void ConsoleOutput(const char * Format, ...) {
    va_list argptr;
    va_start(argptr, Format);
    vfprintf(stderr, Format, argptr);
    va_end(argptr);
}

int InitializeEngine() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return GAME_ERROR_SDL_FAIL;
    }

    int imgflags = IMG_INIT_PNG|IMG_INIT_JPG;
    if ((IMG_Init(imgflags)&imgflags) != imgflags) {
        return GAME_ERROR_IMAGE_FAIL;
    }

    return 0;
}

SDL_Renderer * CreateRenderer(SDL_Window * Window, int Flags, int * Error) {
    // triggers program that controls graphics hardware
    int renderflags = Flags & GAME_RENDERER_ACCELERATED;
    SDL_Renderer * renderer = SDL_CreateRenderer(Window, -1, renderflags);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    *Error = 0;
    return renderer;
}

SDL_Window * CreateWindow(int Width, int Height, const char * Title, int Flags, int * Error) {
    SDL_Window * window = SDL_CreateWindow(Title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Width, Height, SDL_WINDOW_OPENGL); // SDL_WINDOW_OPENGL replaced 0

    if (window == NULL) {
        *Error = GAME_ERROR_WINDOW_FAIL;
        return window;
    }

    if (Flags & GAME_WINDOW_FULLSCREEN) {
        if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN)) {
            *Error = GAME_ERROR_WINDOW_FAIL;
            return window;
        }
    }

    *Error = 0;
    return window;
}

int RunGame(int Width, int Height, const char * Title, int Flags) {
    int error = 0;
    error = InitializeEngine();

    switch (error) {
        case GAME_ERROR_SDL_FAIL:
            ConsoleOutput("Failed loading SDL: %s\n", SDL_GetError());
            return error;
        case GAME_ERROR_IMAGE_FAIL:
            ConsoleOutput("Failed loading SDL_image: %s\n", IMG_GetError());
            return error;
        default:
            break;
    }

    SDL_Window * window = CreateWindow(Width, Height, Title, Flags, &error);
    if (error) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());

    SDL_Renderer * renderer = CreateRenderer(window, Flags, &error);
    if (error) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());

    bool running = true;

    SDL_Surface * surface; // surface to load sprites
    surface = IMG_Load("img/sprites/test.png"); // temp
    if (surface == NULL) {
        ConsoleOutput("Failed loading images: %s\n", IMG_GetError());
        return GAME_ERROR_GENERAL_FAIL;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface); // make image usable
    SDL_FreeSurface(surface);

    SDL_Rect hitbox; // rectangle that we control
    SDL_QueryTexture(texture, NULL, NULL, &hitbox.w, &hitbox.h);

    // change size of hitbox
    hitbox.w /= 6;
    hitbox.h /= 6;

    // position hitbox on the screen
    hitbox.x = (Width - hitbox.w) / 2;
    hitbox.y = (Height - hitbox.h) / 2;

    int speed = 10;
    int x_moment = 0;
    int y_moment = 0;

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
                            y_moment = speed;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            x_moment = -speed;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            y_moment = -speed;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            x_moment = speed;
                            break;
                        case SDL_SCANCODE_Q:
                            running = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            y_moment = 0;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            x_moment = 0;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            y_moment = 0;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            x_moment = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        hitbox.x += x_moment;
        hitbox.y -= y_moment;

        // right boundary
        if (hitbox.x + hitbox.w > Width)
            hitbox.x = Width - hitbox.w;
 
        // left boundary
        if (hitbox.x < 0)
            hitbox.x = 0;
 
        // bottom boundary
        if (hitbox.y + hitbox.h > Height)
            hitbox.y = Height - hitbox.h;
 
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
