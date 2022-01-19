#include "game.h"
#include "utils.h"

#include "tile.h"
#include "screen.h"

#define LOADING_SCREEN 0
#define PAUSE_SCREEN 1
#define TITLE_SCREEN 2
#define GAME_SCREEN 3
#define OPTIONS_SCREEN 4
#define CREDITS_SCREEN 5

extern GameState gameState;
extern vector<SDL_Rect> tileSheet;

Level GenerateRandomLevel(int w, int h, int x, int y) {
    Level level = Level(x, y);
    int posx = 0;
    int posy = 0;
    const int tilewidth = w;
    const int tileheight = h;

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

void DarkenButton(Screen * screen) {
    for (int i=0; i<screen->Button.Count(); i++) screen->Button[i].TempShade(0.7);
}

void LightenButton(Screen * screen) {
    for (int i=0; i<screen->Button.Count(); i++) screen->Button[i].TempShade(1);
}

void GotoTitle(Screen * screen) {
    gameState.SetScreen(TITLE_SCREEN);
}

void GotoGame(Screen * screen) {
    gameState.SetScreen(GAME_SCREEN);
}

void GotoOptions(Screen * screen) {
    gameState.SetScreen(OPTIONS_SCREEN);
}

void GotoCredits(Screen * screen) {
    gameState.SetScreen(CREDITS_SCREEN);
}

void GotoPause(Screen * screen) {
    gameState.SetScreen(PAUSE_SCREEN);
}

void StopGame(Screen * screen) {
    gameState.StopGame();
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

    Screen loadingScreen = Screen(renderer, LOADING_SCREEN, 0, 0, Width, Height, {0, 0, 0});
    loadingScreen.Text.AddLine("load", loadingScreen.CENTERED, loadingScreen.CENTERED, "Lato-Regular", 60, {255, 255, 255}, "Loading...");

    SDL_RenderClear(renderer);
    loadingScreen.Render();
    SDL_RenderPresent(renderer);

    // do all game loading here

    tileSheet = InitTiles();

    gameState.SetScreen(TITLE_SCREEN);

    Screen pauseScreen = Screen(renderer, PAUSE_SCREEN, Width / 4, Height / 4, Width / 2, Height / 2, {100, 100, 255});
    pauseScreen.Text.AddLine("title", pauseScreen.CENTERED, 20, "Lato-Bold", 80, {0, 0, 0}, "PAUSED");
    pauseScreen.Text.AddLine("desc", pauseScreen.CENTERED, pauseScreen.Text["title"].GetRect().h + 20, "Lato-Regular", 24, {0, 0, 0}, "Press ESC to resume.");

    pauseScreen.Button.SetDefaultBorder(10, {0, 0, 0});
    pauseScreen.Button.SetDefaultTextAttrib(60, {0, 0, 0}, "Lato-Bold");
    pauseScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    pauseScreen.Button.AddButton("quit", pauseScreen.CENTERED, pauseScreen.GetRect().h - 120, 400, 100, {170, 170, 170}, "QUIT", GotoTitle);

    Screen titleScreen = Screen(renderer, TITLE_SCREEN, 0, 0, Width, Height, {100, 100, 100});
    titleScreen.Text.AddLine("title", titleScreen.CENTERED, 100, "Lato-Bold", 120, {255, 255, 255}, "Adventures of Cliche");

    titleScreen.Button.SetDefaultBorder(10, {0, 0, 0});
    titleScreen.Button.SetDefaultTextAttrib(60, {0, 0, 0}, "Lato-Bold");
    titleScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);

    titleScreen.Button.AddButton("start", titleScreen.CENTERED, 400, 400, 100, {100, 255, 100}, "START", GotoGame);
    titleScreen.Button.AddButton("options", titleScreen.CENTERED, 550, 400, 100, {170, 170, 170}, "OPTIONS", GotoOptions);
    titleScreen.Button.AddButton("credits", titleScreen.CENTERED, 700, 400, 100, {170, 170, 170}, "CREDITS", GotoCredits);
    titleScreen.Button.AddButton("quit", titleScreen.CENTERED, 850, 400, 100, {255, 100, 100}, "QUIT", StopGame);

    Screen optionsScreen = Screen(renderer, OPTIONS_SCREEN, 0, 0, Width, Height, {255, 255, 255});
    optionsScreen.Button.SetDefaultBorder(4, {0, 0, 0});
    optionsScreen.Button.SetDefaultTextAttrib(24, {0, 0, 0}, "Lato-Regular");
    optionsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    optionsScreen.Button.AddButton("back", 200, 200, 150, 50, {100, 100, 100}, "BACK", GotoTitle);

    Screen creditsScreen = optionsScreen; // copy data, now seperate
    creditsScreen.SetId(CREDITS_SCREEN);

    Screen gameScreen = Screen(renderer, GAME_SCREEN, 0, 0, Width, Height, {255, 255, 255});
    gameScreen.CreateBounds(200, 200, 200, 200); // relative (this is 200 px out in all directions);
    gameScreen.Level.AddLevel("default", GenerateRandomLevel(Width / 16, Height / 9, 16, 9)); // AddLevel() will bind renderer later

    gameScreen.Creature.AddCreature("player", TileType::TestPlayer, Width / 16, Height / 9, gameScreen.CENTERED, gameScreen.CENTERED);
    gameScreen.Creature["player"].SetBounds(0, 0, Width, Height);
    gameScreen.Creature["player"].SetPosition(gameScreen.CENTERED, gameScreen.CENTERED);

    SDL_Point mouse;
    map<char, bool> keyboard;

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
                            keyboard['w'] = true;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            keyboard['a'] = true;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            keyboard['s'] = true;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            keyboard['d'] = true;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            if (gameState.CurrentScreen() == gameScreen.GetId()) {
                                gameState.SetScreen(pauseScreen.GetId());
                            } else if (gameState.CurrentScreen() == pauseScreen.GetId()) {
                                gameState.SetScreen(gameScreen.GetId());
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
                            keyboard['w'] = false;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            keyboard['a'] = false;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            keyboard['s'] = false;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            keyboard['d'] = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            switch (gameState.CurrentScreen()) {
                                case PAUSE_SCREEN: pauseScreen.Button.Click(mouse); break;
                                case TITLE_SCREEN: titleScreen.Button.Click(mouse); break;
                                case OPTIONS_SCREEN: optionsScreen.Button.Click(mouse); break;
                                case CREDITS_SCREEN: creditsScreen.Button.Click(mouse); break;
                                case GAME_SCREEN: gameScreen.Button.Click(mouse); break;
                                default: break;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    switch (gameState.CurrentScreen()) {
                        case PAUSE_SCREEN: pauseScreen.Button.Hover(mouse); break;
                        case TITLE_SCREEN: titleScreen.Button.Hover(mouse); break;
                        case OPTIONS_SCREEN: optionsScreen.Button.Hover(mouse); break;
                        case CREDITS_SCREEN: creditsScreen.Button.Hover(mouse); break;
                        case GAME_SCREEN: gameScreen.Button.Hover(mouse); break;
                        default: break;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);

        // game code goes here
        switch (gameState.CurrentScreen()) {
            case GAME_SCREEN: {
                gameScreen.TempShade(1);

                // check player movement
                SDL_Point offset;

                if (keyboard['w']) offset.y = -gameScreen.Creature["player"].Speed.y;
                if (keyboard['s']) offset.y = gameScreen.Creature["player"].Speed.y;
                if (keyboard['a']) offset.x = -gameScreen.Creature["player"].Speed.x;
                if (keyboard['d']) offset.x = gameScreen.Creature["player"].Speed.x;

                if (keyboard['w'] && keyboard['s']) offset.y = 0;
                if (keyboard['a'] && keyboard['d']) offset.x = 0;

                if (gameScreen.Creature["player"].IsCenteredX(&gameScreen)) gameScreen.Move(gameScreen.Creature["player"].Speed.x, 0);
                if (gameScreen.Creature["player"].IsCenteredY(&gameScreen)) gameScreen.Move(0, gameScreen.Creature["player"].Speed.y);
                gameScreen.Creature["player"].Update(offset);

                gameScreen.Render();
            } break;
            case TITLE_SCREEN: {
                titleScreen.Render();
            } break;
            case PAUSE_SCREEN: {
                gameScreen.TempShade(0.7);
                // player.SetOpacity(150, 150, 150);
                gameScreen.Render();
                // player.Render();

                pauseScreen.Render();
            } break;
            case CREDITS_SCREEN: {
                creditsScreen.Render();
            } break;
            case OPTIONS_SCREEN: {
                optionsScreen.Render();
            } break;
        }

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FRAMERATE);
    }

    // player.Destroy();
    titleScreen.Destroy();
    pauseScreen.Destroy();
    loadingScreen.Destroy();
    gameScreen.Destroy();
    optionsScreen.Destroy();
    creditsScreen.Destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
