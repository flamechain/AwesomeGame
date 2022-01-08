#include "game.h"
#include "tile.h"
#include "player.h"
#include "objects.h"
#include "utils.h"

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
    SDL_Rect * tiles = InitTiles();

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
    const int tilecount = gridx * gridy;
    const int tilewidth = Width / gridx;
    const int tileheight = Height / gridy;

    int posx = 0;
    int posy = 0;

    vector<Tile> map;
    for (int i=0; i<tilecount; i++) {
        map.push_back(Tile(renderer, TileType::GrassPathCenter, tiles));
        map[i].Resize(tilewidth, tileheight);
        map[i].Position(posx, posy);
        posx += tilewidth;

        if (posx > Width - tilewidth) {
            posx = 0;
            posy += tileheight;
        }
    }

    Player player = Player(renderer, TileType::DirtBlood, tiles);
    player.Resize(tilewidth, tileheight);
    player.SetSpeedCap(10, 10);
    player.SetPositionBounds(0, 0, Width, Height);

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
                        case SDL_SCANCODE_ESCAPE:
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

        if (movement.MovingUp()) player.speed.y = -10;
        else if (movement.MovingDown()) player.speed.y = 10;
        else player.speed.y = 0;
        if (movement.MovingLeft()) player.speed.x = -10;
        else if (movement.MovingRight()) player.speed.x = 10;
        else player.speed.x = 0;

        if (movement.MovingUp() && movement.MovingDown()) player.speed.y = 0;
        if (movement.MovingLeft() && movement.MovingRight()) player.speed.x = 0;

        player.Update();

        SDL_RenderClear(renderer);
        for (int i=0; i<tilecount; i++) map[i].Render();
        player.Render();

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FRAMERATE);
    }

    player.Destroy();
    for (int i=0; i<tilecount; i++) map[i].Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
