#include "game.h"
#include "tile.h"
#include "player.h"
#include "objects.h"
#include "utils.h"
#include "camera.h"
#include "rect.h"
#include "text.h"
#include "button.h"
#include "level.h"

extern GameState gameState;

Level GenerateRandomLevel(int x, int y, int width, int height, vector<SDL_Rect> tiles, SDL_Renderer * renderer, Camera * camera) {
    Level level = Level(renderer, camera, tiles, x, y);
    int posx = 0;
    int posy = 0;
    const int tilewidth = width / 16;
    const int tileheight = height / 9;

    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            level.SetTile(i, j, TileType::Grass);
            level.SetTilePosition(i, j, posx, posy);
            level.ResizeTile(i, j, tilewidth, tileheight);
            posx += tilewidth;

            if (posx > tilewidth * (x - 1)) {
                posx = 0;
                posy += tileheight;
            }
        }
    }

    return level;
}

int RunGame(int Width, int Height, const char * Title, bool Debug, int Flags) {
    gameState = GameState();
    InitializeEngine();

    string sTitle = Title;

    if (Debug) {
        sTitle = StringFormat("%s: Width: %i, Height: %i, FPS: %i", Title, Width, Height, FRAMERATE);
    }

    SDL_Window * window = CreateWindow(Width, Height, sTitle, Flags);
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

    vector<SDL_Rect> tiles = InitTiles();

    const int gridx = 16;
    const int gridy = 9;
    const int tilewidth = Width / gridx;
    const int tileheight = Height / gridy;

    Camera camera = Camera(0, 0, Width, Height);
    camera.SetBounds(-200, -200, Width + 200, Height + 200);

    Level level = GenerateRandomLevel(gridx, gridy, Width, Height, tiles, renderer, &camera);

    Player player = Player(renderer, TileType::TestPlayer, tiles, &camera);
    player.Resize(tilewidth, tileheight);
    player.SetSpeedCap(10, 10);
    player.SetBounds(0, 0, Width, Height);
    // center player on screen
    player.SetPosition((Width / 2) - (player.GetRect().w / 2), (Height / 2) - (player.GetRect().h / 2));

    WASDController movement;

    gameState.SetMenu(Menu::Title);
    // centered on screen
    Rect pauseMenu = Rect(renderer, Width / 4, Height / 4, Width / 2, Height / 2, {100, 100, 255});
    Paragraph pauseText = Paragraph(renderer);
    pauseText.AddLine("Lato-Bold.ttf", 80, {0, 0, 0}, "PAUSED");
    pauseText.AddLine("Lato-Regular.ttf", 24, {0, 0, 0}, "Press ESC to resume.");

    pauseText[0].SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (pauseText[0].GetRect().w / 2), pauseMenu.GetRect().y + 20);
    pauseText[1].SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (pauseText[1].GetRect().w / 2), pauseMenu.GetRect().y + pauseText[0].GetRect().h + 20);

    Rect titleMenu = Rect(renderer, 0, 0, Width, Height, {100, 100, 100});
    // titleMenu.LoadImage("TitleScreen.png");
    Paragraph titleText = Paragraph(renderer);
    titleText.AddLine("Lato-Bold.ttf", 120, {255, 255, 255}, "Adventures of Cliche");
    titleText[0].SetPosition((titleMenu.GetRect().w / 2) - (titleText[0].GetRect().w / 2), 100);

    // add similar_buttons class? lots of duplicate numbers here
    Button titleStart = Button(renderer, (titleMenu.GetRect().w / 2) - 200, 400, 400, 100, {100, 255, 100});
    Button titleCredits = Button(renderer, (titleMenu.GetRect().w / 2) - 200, 550, 400, 100, {170, 170, 170});
    Button titleOptions = Button(renderer, (titleMenu.GetRect().w / 2) - 200, 700, 400, 100, {170, 170, 170});
    Button titleQuit = Button(renderer, (titleMenu.GetRect().w / 2) - 200, 850, 400, 100, {255, 100, 100});
    titleStart.SetBorder(10, {0, 0, 0});
    titleCredits.SetBorder(10, {0, 0, 0});
    titleOptions.SetBorder(10, {0, 0, 0});
    titleQuit.SetBorder(10, {0, 0, 0});
    titleStart.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "START", true);
    titleCredits.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "OPTIONS", true);
    titleOptions.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "CREDITS", true);
    titleQuit.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "QUIT", true);

    Rect background = Rect(renderer, 0, 0, Width, Height, {255, 255, 255});

    Button pauseQuit = Button(renderer, 0, 0, 400, 100, {200, 200, 200});
    pauseQuit.SetText("Lato-Bold.ttf", 60, {0, 0, 0}, "QUIT", true);
    pauseQuit.SetBorder(7, {0, 0, 0});
    // centered to pause menu, padded 20px from the bottom
    pauseQuit.SetPosition(pauseMenu.GetRect().x + (pauseMenu.GetRect().w / 2) - (pauseQuit.GetRect().w / 2), pauseMenu.GetRect().y + pauseMenu.GetRect().h - pauseQuit.GetRect().h - 20);

    Button titleBack = Button(renderer, 200, 200, 150, 50, {170, 170, 170});
    titleBack.SetText("Lato-Regular.ttf", 24, {0, 0, 0}, "Back", true);
    titleBack.SetBorder(5, {0, 0, 0});

    SDL_Point mouse;

    while (gameState.IsRunning()) {
        SDL_Event event;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        // all SDL keyboard/mouse interactions, excluded from game code
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
                                pauseQuit.SetActive(true);
                            } else if (gameState.GetMenu() == Menu::Pause) {
                                gameState.SetMenu(Menu::None);
                                pauseQuit.SetActive(false);
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
                            // add vector of active buttons to save space on checking every possible button
                            if (pauseQuit.IsActive() && pauseQuit.IsInside(mouse.x, mouse.y)) gameState.SetMenu(Menu::Title);
                            if (titleStart.IsActive() && titleStart.IsInside(mouse.x, mouse.y)) gameState.SetMenu(Menu::None);
                            if (titleOptions.IsActive() && titleOptions.IsInside(mouse.x, mouse.y)) gameState.SetMenu(Menu::Options);
                            if (titleCredits.IsActive() && titleCredits.IsInside(mouse.x, mouse.y)) gameState.SetMenu(Menu::Credits);
                            if (titleBack.IsActive() && titleBack.IsInside(mouse.x, mouse.y)) gameState.SetMenu(Menu::Title);
                            if (titleQuit.IsActive() && titleQuit.IsInside(mouse.x, mouse.y)) gameState.StopGame();
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    // shadow buttons method here; pass in vector of active buttons
                    if (pauseQuit.IsActive() && pauseQuit.IsInside(mouse.x, mouse.y)) pauseQuit.Shadow(150, 150, 150);
                    else pauseQuit.UnShadow();

                    if (titleStart.IsActive() && titleStart.IsInside(mouse.x, mouse.y)) titleStart.Shadow(150, 150, 150);
                    else titleStart.UnShadow();
                    if (titleOptions.IsActive() && titleOptions.IsInside(mouse.x, mouse.y)) titleOptions.Shadow(150, 150, 150);
                    else titleOptions.UnShadow();
                    if (titleCredits.IsActive() && titleCredits.IsInside(mouse.x, mouse.y)) titleCredits.Shadow(150, 150, 150);
                    else titleCredits.UnShadow();
                    if (titleBack.IsActive() && titleBack.IsInside(mouse.x, mouse.y)) titleBack.Shadow(150, 150, 150);
                    else titleBack.UnShadow();
                    if (titleQuit.IsActive() && titleQuit.IsInside(mouse.x, mouse.y)) titleQuit.Shadow(150, 150, 150);
                    else titleQuit.UnShadow();

                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);
        background.Render();

        // game code goes here
        switch(gameState.GetMenu()) {
            case Menu::None: {
                // way to do this once and not every game loop?
                titleStart.SetActive(false);
                titleOptions.SetActive(false);
                titleCredits.SetActive(false);
                titleQuit.SetActive(false);

                // check player movement
                // change to use an {x, y} vector movement that calculates next point rather than speed
                if (movement.MovingUp()) player.speed.y = -10;
                else if (movement.MovingDown()) player.speed.y = 10;
                else player.speed.y = 0;
                if (movement.MovingLeft()) player.speed.x = -10;
                else if (movement.MovingRight()) player.speed.x = 10;
                else player.speed.x = 0;

                if (movement.MovingUp() && movement.MovingDown()) player.speed.y = 0;
                if (movement.MovingLeft() && movement.MovingRight()) player.speed.x = 0;

                // checks if players hitbox center is centered with camera
                if ((player.GetHitbox().x + (player.GetHitbox().w / 2)) - camera.x == camera.w / 2) camera.Update(player.speed.x, 0);
                if ((player.GetHitbox().y + (player.GetHitbox().h / 2)) - camera.y == camera.h / 2) camera.Update(0, player.speed.y);
                player.Update();

                level.Render();
                player.Render();
            } break;
            case Menu::Title: {
                titleBack.SetActive(false);
                titleStart.SetActive(true);
                titleOptions.SetActive(true);
                titleCredits.SetActive(true);
                titleQuit.SetActive(true);
                titleMenu.Render();
                titleText.Render();

                titleStart.Render();
                titleOptions.Render();
                titleCredits.Render();
                titleQuit.Render();
            } break;
            case Menu::Pause: {
                level.SetExtraColor(150, 150, 150);
                level.Render();
                player.SetExtraColor(150, 150, 150);
                player.Render();

                pauseMenu.Render();
                pauseText.Render();
                pauseQuit.Render();
            } break;
            case Menu::Credits: {
                titleBack.SetActive(true);
                titleStart.SetActive(false);
                titleOptions.SetActive(false);
                titleCredits.SetActive(false);
                titleQuit.SetActive(false);

                titleBack.Render();
            } break;
            case Menu::Options: {
                titleBack.SetActive(true);
                titleStart.SetActive(false);
                titleOptions.SetActive(false);
                titleCredits.SetActive(false);
                titleQuit.SetActive(false);

                titleBack.Render();
            } break;
        }

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        player.SetExtraColor(255, 255, 255);
        level.SetExtraColor(255, 255, 255);
        SDL_Delay(1000 / FRAMERATE);
    }

    // cleanup, later add everything to vector for organization and easier destruction (tiles e.g.)
    player.Destroy();
    loadingText.Destroy();
    loadingScreen.Destroy();
    level.Destroy();
    pauseMenu.Destroy();
    pauseText.Destroy();
    pauseQuit.Destroy();
    titleStart.Destroy();
    titleOptions.Destroy();
    titleCredits.Destroy();
    titleBack.Destroy();
    titleQuit.Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
