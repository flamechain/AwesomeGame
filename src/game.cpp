#include "game.h"
#include "tile.h"

extern GameState gameState;

int InitializeEngine() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        errno = GAME_ERROR_SDL_FAIL;
        return errno;
    }

    int imgflags = IMG_INIT_PNG|IMG_INIT_JPG;
    if ((IMG_Init(imgflags)&imgflags) != imgflags) {
        errno = GAME_ERROR_IMAGE_FAIL;
        return errno;
    }

    SDL_setenv("SDL_VIDEODRIVER", "directx", 1);
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

SDL_Window * CreateWindow(int Width, int Height, const char * Title, int Flags) {
    SDL_Window * window = SDL_CreateWindow(Title,
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

int RunGame(int Width, int Height, const char * Title, int Flags) {
    gameState = GameState();
    InitializeEngine();

    switch (errno) {
        case GAME_ERROR_SDL_FAIL:
            ConsoleOutput("Failed loading SDL: %s\n", SDL_GetError());
            return errno;
        case GAME_ERROR_IMAGE_FAIL:
            ConsoleOutput("Failed loading SDL_image: %s\n", IMG_GetError());
            return errno;
        default:
            break;
    }

    SDL_Window * window = CreateWindow(Width, Height, Title, Flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());

    SDL_Renderer * renderer = CreateRenderer(window, Flags);
    if (errno) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());

    const int gridx = 16;
    const int gridy = 9;
    int tileSize = 120;
    GameObject tiles[gridx*gridy];

    int posx = 0;
    int posy = 0;

    for (int i=0; i<gridx*gridy; i++) {
        // gcf(width, height) = 120
        tiles[i] = CreateObjectFromImage(renderer, "TileSheet1.png", tileSize, tileSize, 0, 0, 16, 16);
        tiles[i].SetMomentBounds(0, 0, 0, 0);
        tiles[i].Rotate(90);
        tiles[i].Position(posx, posy);
        posx += tileSize;

        if (posx > tileSize * gridx) {
            posx = 0;
            posy += tileSize;
        }
    }

    GameObject testTile = CreateObjectFromImage(renderer, "TileSheet1.png", tileSize, tileSize, 16, 0, 16, 16);
    testTile.Rotate(90);
    testTile.SetMomentBounds(-10, 10, -10, 10);

    WASDController movement;

    while (gameState.IsRunning()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameState.StopGame();
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            movement.SetUpMovement(true);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            movement.SetLeftMovement(true);
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            movement.SetDownMovement(true);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            movement.SetRightMovement(true);
                            break;
                        case SDL_SCANCODE_Q:
                            gameState.StopGame();
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            movement.SetUpMovement(false);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            movement.SetLeftMovement(false);
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            movement.SetDownMovement(false);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            movement.SetRightMovement(false);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // if (movement.MovingUp()) testTile.MomentY = -10;
        // else if (movement.MovingDown()) testTile.MomentY = 10;
        // else testTile.MomentY = 0;
        // if (movement.MovingLeft()) testTile.MomentX = -10;
        // else if (movement.MovingRight()) testTile.MomentX = 10;
        // else testTile.MomentX = 0;

        // if (movement.MovingUp() && movement.MovingDown()) testTile.MomentY = 0;
        // if (movement.MovingLeft() && movement.MovingRight()) testTile.MomentX = 0;

        // testTile.CheckMomentBounds();
        // testTile.UpdatePosition();
        // testTile.CheckPositionBounds(Width, Height);

        SDL_RenderClear(renderer);
        // testTile.Render();

        for (int i=0; i<gridx*gridy; i++) {
            tiles[i].CheckMomentBounds();
            tiles[i].UpdatePosition();
            tiles[i].CheckPositionBounds(Width, Height);
            tiles[i].Render();
        }

        // triggers the double buffers for multiple rendering
        SDL_RenderPresent(renderer);
 
        // 60 fps (milliseconds)
        SDL_Delay(1000 / 60);
    }

    // cleanup
    // testTile.Destroy();
    for (int i=0; i<gridx*gridy; i++) {
        tiles[i].Destroy();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
