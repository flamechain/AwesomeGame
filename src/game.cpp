#include "game.h"
#include "tile.h"
#include "player.h"
#include "objects.h"
#include "utils.h"
#include "camera.h"
#include "rect.h"
#include "text.h"
#include "button.h"

extern GameState gameState;

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

    SDL_Window * window = CreateWindow(Width, Height, Title, Flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());

    SDL_Renderer * renderer = CreateRenderer(window, Flags);
    if (errno) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());

    Rect loadingScreen = Rect(renderer, 0, 0, Width, Height, {0, 0, 0});
    Text loadingText = Text(renderer, "Lato-Regular.ttf", 60, {255, 255, 255}, "Loading...");

    loadingText.SetPosition((Width / 2) - (loadingText.GetRect().w / 2), (Height / 2) - (loadingText.GetRect().h / 2));

    SDL_RenderClear(renderer);
    loadingScreen.Render();
    loadingText.Render();
    SDL_RenderPresent(renderer);

    // do all game loading here

    const int gridx = 16;
    const int gridy = 9;
    const int tilecount = gridx * gridy;
    const int tilewidth = Width / gridx;
    const int tileheight = Height / gridy;

    int posx = 0;
    int posy = 0;

    Camera camera = Camera(0, 0, Width, Height);
    camera.SetBounds(-200, -200, Width + 200, Height + 200);

    vector<Tile> map;
    for (int i=0; i<tilecount; i++) {
        map.push_back(Tile(renderer, TileType::GrassPathCenter, tiles, &camera));
        map[i].Resize(tilewidth, tileheight);
        map[i].SetPosition(posx, posy);
        posx += tilewidth;

        if (posx > Width - tilewidth) {
            posx = 0;
            posy += tileheight;
        }
    }

    Player player = Player(renderer, TileType::DirtBlood, tiles, &camera);
    player.Resize(tilewidth, tileheight);
    player.SetSpeedCap(10, 10);
    player.SetBounds(0, 0, Width, Height);
    // center player on screen
    player.SetPosition((Width / 2) - (player.GetRect().w / 2), (Height / 2) - (player.GetRect().h / 2));

    WASDController movement;

    gameState.SetMenu(Menu::None);
    Rect pauseMenu = Rect(renderer, Width / 4, Height / 4, Width / 2, Height / 2, {100, 100, 255});
    Text pauseText[2];

    pauseText[0] = Text(renderer, "Lato-Bold.ttf", 80, {0, 0, 0}, "PAUSED");
    pauseText[1] = Text(renderer, "Lato-Regular.ttf", 24, {0, 0, 0}, "Press ESC to resume.");
    pauseText[0].SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (pauseText[0].GetRect().w / 2), pauseMenu.GetRect().y + 20);
    pauseText[1].SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (pauseText[1].GetRect().w / 2), pauseMenu.GetRect().y + pauseText[0].GetRect().h + 20);

    Rect background = Rect(renderer, 0, 0, Width, Height, {255, 255, 255});

    Button quitButton = Button(renderer, 0, 0, 400, 100, {200, 200, 200});
    quitButton.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "QUIT", true);
    quitButton.SetBorder(5, {0, 0, 0});
    quitButton.SetActive(false);
    quitButton.SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (quitButton.GetRect().w / 2), pauseMenu.GetRect().y + pauseMenu.GetRect().h - quitButton.GetRect().h - 20);

    SDL_Point mouse;

    while (gameState.IsRunning()) {
        SDL_Event event;
        SDL_GetMouseState(&mouse.x, &mouse.y);

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
                            if (gameState.GetMenu() == Menu::None) {
                                gameState.SetMenu(Menu::Pause);
                                quitButton.SetActive(true);
                            } else if (gameState.GetMenu() == Menu::Pause) {
                                gameState.SetMenu(Menu::None);
                                quitButton.SetActive(false);
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
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
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            if (quitButton.IsActive() && quitButton.IsInside(mouse.x, mouse.y)) gameState.StopGame();
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (quitButton.IsActive() && quitButton.IsInside(mouse.x, mouse.y)) {
                        quitButton.Shadow(50, 50, 50);
                    } else {
                        quitButton.UnShadow();
                    }
                    break;
                default:
                    break;
            }
        }

        // game code goes here

        if (gameState.GetMenu() == Menu::None) {
            if (movement.MovingUp()) player.speed.y = -10;
            else if (movement.MovingDown()) player.speed.y = 10;
            else player.speed.y = 0;
            if (movement.MovingLeft()) player.speed.x = -10;
            else if (movement.MovingRight()) player.speed.x = 10;
            else player.speed.x = 0;

            if (movement.MovingUp() && movement.MovingDown()) player.speed.y = 0;
            if (movement.MovingLeft() && movement.MovingRight()) player.speed.x = 0;

            // checks if players hitbox center is centered with camera
            if ((player.GetRect().x + (player.GetRect().w / 2)) - camera.x == camera.w / 2) camera.Update(player.speed.x, 0);
            if ((player.GetRect().y + (player.GetRect().h / 2)) - camera.y == camera.h / 2) camera.Update(0, player.speed.y);

            player.Update();
        }

        SDL_RenderClear(renderer);
        background.Render();

        if (gameState.GetMenu() > 0 && gameState.GetMenu() < 4) {
            for (int i=0; i<tilecount; i++) {
                map[i].SetExtraColor(150, 150, 150);
                map[i].Render();
            }
            player.SetExtraColor(150, 150, 150);
            player.Render();
        }

        if (gameState.GetMenu() <= 3) {
            for (int i=0; i<tilecount; i++) map[i].Render();
            player.Render();
        }

        if (gameState.GetMenu() == Menu::Pause) {
            pauseMenu.Render();
            pauseText[0].Render();
            pauseText[1].Render();
            quitButton.Render();
        }

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        player.SetExtraColor(255, 255, 255);
        for (int i=0; i<tilecount; i++) map[i].SetExtraColor(255, 255, 255);
        SDL_Delay(1000 / FRAMERATE);
    }

    player.Destroy();
    loadingText.Destroy();
    loadingScreen.Destroy();
    for (int i=0; i<tilecount; i++) map[i].Destroy();
    pauseMenu.Destroy();
    quitButton.Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
