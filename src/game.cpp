/*
testing for branch
*/
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
#define SAVE_SCREEN 6

extern GameState gameState;
extern vector<SDL_Rect> tileSheet;

Level GenerateRandomLevel(int w, int h, int x, int y) {
    Level level = Level(x, y, w, h);
    int posx = 0;
    int posy = 0;

    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            level.SetTile(i, j, TileType::Grass);
            level.SetTilePosition(i, j, posx, posy);
            posx += w;

            if (posx > w * (x - 1)) {
                posx = 0;
                posy += h;
            }
        }
    }

    return level;
}

void DarkenButton(Screen * screen, string uid) {
    screen->Button[uid].TempShade(0.7);
}

void LightenButton(Screen * screen, string uid) {
    screen->Button[uid].TempShade(1);
}

void GotoTitle(Screen * screen, string uid) {
    gameState.SetScreen(TITLE_SCREEN);
}

void GotoGame(Screen * screen, string uid) {
    gameState.SetScreen(GAME_SCREEN);
}

void GotoOptions(Screen * screen, string uid) {
    gameState.SetScreen(OPTIONS_SCREEN);
}

void GotoCredits(Screen * screen, string uid) {
    gameState.SetScreen(CREDITS_SCREEN);
}

void GotoPause(Screen * screen, string uid) {
    gameState.SetScreen(PAUSE_SCREEN);
}

void StopGame(Screen * screen, string uid) {
    gameState.StopGame();
}

float FadeIn(Screen * screen, float current, float decrease) {
    float newCur = current - decrease;
    // also do with children?
    if (newCur < 0) newCur = 0;
    Color origin = screen->GetColor();
    Color next;
    next.r = (255 - origin.r)*(newCur) + origin.r;
    next.g = (255 - origin.g)*(newCur) + origin.g;
    next.b = (255 - origin.b)*(newCur) + origin.b;
    screen->SetRenderColor(next);

    screen->SetTransparency(newCur);

    return newCur;
}

void UpdateLoadingBar(Screen * screen, SDL_Renderer * renderer, int change) {
    screen->Rect["bar"].SetDimensions(screen->Rect["bar"].GetRect().x, screen->Rect["bar"].GetRect().y, screen->Rect["bar"].GetRect().w+change, screen->Rect["bar"].GetRect().h);
    SDL_RenderClear(renderer);
    screen->Render();
    SDL_RenderPresent(renderer);
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

    Screen loadingScreen = Screen(renderer, LOADING_SCREEN, 0, 0, Width, Height, BLACK);
    loadingScreen.Text.AddLine("load", loadingScreen.CENTERED, loadingScreen.CENTERED, "lato/regular", 60, WHITE, "Loading...");
    loadingScreen.Rect.AddRect("border", loadingScreen.CENTERED, 800, 400, 75, BLACK);
    loadingScreen.Rect["border"].SetBorder(15, WHITE);
    loadingScreen.Rect.AddRect("bar", loadingScreen.Rect["border"].GetRect().x + 20, 800+20, 0, 75-40, WHITE);

    const int barLen = 360;
    const int barSegment = barLen/6;
    UpdateLoadingBar(&loadingScreen, renderer, 0);

    // do all game loading here

    tileSheet = InitTiles();

    gameState.SetScreen(TITLE_SCREEN);

    //Color not final
    Screen pauseScreen = Screen(renderer, PAUSE_SCREEN, Width / 4, Height / 4, Width / 2, Height / 2, RGB(100, 100, 255));
    pauseScreen.Text.AddLine("title", pauseScreen.CENTERED, 20, "lato/bold", 80, BLACK, "PAUSED");
    pauseScreen.Text.AddLine("desc", pauseScreen.CENTERED, pauseScreen.Text["title"].GetRect().h + 20, "lato/regular", 24, BLACK, "Press ESC to resume.");

    pauseScreen.Button.SetDefaultBorder(10, BLACK);
    pauseScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    pauseScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    pauseScreen.Button.AddButton("quit", pauseScreen.CENTERED, pauseScreen.GetRect().h - 120, 400, 100, GREY, "QUIT", GotoTitle);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    Screen titleScreen = Screen(renderer, TITLE_SCREEN, 0, 0, Width, Height, DARK_GREY);
    titleScreen.Text.AddLine("title", titleScreen.CENTERED, 100, "lato/bold", 120, WHITE, "Dissension");

    titleScreen.Button.SetDefaultBorder(10, BLACK);
    titleScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    titleScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);

    titleScreen.Button.AddButton("start", titleScreen.CENTERED, 400, 400, 100, RGB(100, 255, 100), "START", GotoGame);
    titleScreen.Button.AddButton("options", titleScreen.CENTERED, 550, 400, 100, GREY, "OPTIONS", GotoOptions);
    titleScreen.Button.AddButton("credits", titleScreen.CENTERED, 700, 400, 100, GREY, "CREDITS", GotoCredits);
    titleScreen.Button.AddButton("quit", titleScreen.CENTERED, 850, 400, 100, RGB(255, 100, 100), "QUIT", StopGame);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    Screen optionsScreen = Screen(renderer, OPTIONS_SCREEN, 0, 0, Width, Height, WHITE);
    optionsScreen.Button.SetDefaultBorder(4, BLACK);
    optionsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    optionsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    optionsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    Screen creditsScreen = Screen(renderer, CREDITS_SCREEN, 0, 0, Width, Height, WHITE);
    creditsScreen.Button.SetDefaultBorder(4, BLACK);
    creditsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    creditsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    creditsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    Screen gameScreen = Screen(renderer, GAME_SCREEN, 0, 0, Width, Height, WHITE, true);
    gameScreen.CreateBounds(200, 200, 200, 200); // relative (this is 200 px out in all directions);
    gameScreen.Level.AddLevel("default", GenerateRandomLevel(Width / 16, Height / 9, 16, 9)); // AddLevel() will bind renderer later

    gameScreen.Creature.AddCreature("player", TileType::TestPlayer, gameScreen.CENTERED, gameScreen.CENTERED, Width / 16, Height / 9);
    gameScreen.Creature["player"].SetBounds(0, 0, Width, Height);
    gameScreen.Creature["player"].Speed.x = 10;
    gameScreen.Creature["player"].Speed.y = 10;

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    Screen saveScreen = Screen(renderer, SAVE_SCREEN, 0, 0, Width, Height, DARK_GREY);
    saveScreen.Text.AddLine("title", saveScreen.CENTERED, 200, "lato/bold", 80, BLACK, "Select Save");
    saveScreen.Button.SetDefaultBorder(10, BLACK);

    // saveScreen.Button.AddButton("save1", saveScreen.CENTERED, 500, 800, 100, LIGHT_GREY, "New Save");

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    // purely as background if screens move
    // in the future levels will be designed so the screen always covers the entire window
    Screen background = Screen(renderer, 0, 0, 0, Width, Height, WHITE);

    SDL_Point mouse;
    map<char, bool> keyboard;
    float fadeInLevel = 1;

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
                                fadeInLevel = 1;
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
        background.TempShade(1);
        background.Render();

        // game code goes here
        switch (gameState.CurrentScreen()) {
            case GAME_SCREEN: {
                gameScreen.TempShade(1);

                // check player movement
                SDL_Point offset = {0, 0};

                if (keyboard['w']) offset.y = -gameScreen.Creature["player"].Speed.y;
                if (keyboard['s']) offset.y = gameScreen.Creature["player"].Speed.y;
                if (keyboard['a']) offset.x = -gameScreen.Creature["player"].Speed.x;
                if (keyboard['d']) offset.x = gameScreen.Creature["player"].Speed.x;

                if (keyboard['w'] && keyboard['s']) offset.y = 0;
                if (keyboard['a'] && keyboard['d']) offset.x = 0;

                if (gameScreen.Creature["player"].IsCenteredX(&gameScreen)) gameScreen.Move(offset.x, 0);
                if (gameScreen.Creature["player"].IsCenteredY(&gameScreen)) gameScreen.Move(0, offset.y);
                gameScreen.Creature["player"].Update(offset);

                gameScreen.Render();
            } break;
            case TITLE_SCREEN: {
                titleScreen.Render();
            } break;
            case PAUSE_SCREEN: {
                float decrease = 0.08;

                if (fadeInLevel > 0) {
                    fadeInLevel = FadeIn(&pauseScreen, fadeInLevel, decrease);
                }

                background.TempShade(0.6);
                gameScreen.TempShade(0.6);
                background.Render();
                gameScreen.Render();
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
