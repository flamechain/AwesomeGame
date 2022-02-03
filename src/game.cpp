#include "game.h"
#include "utils.h"

#include "tile.h"
#include "screen.h"
#include "mixer.h"

#define LOADING_SCREEN 0
#define PAUSE_SCREEN 1
#define TITLE_SCREEN 2
#define GAME_SCREEN 3
#define OPTIONS_SCREEN 4
#define CREDITS_SCREEN 5
#define SAVE_SCREEN 6

extern GameState gameState;
extern vector<SDL_Rect> tileSheet;

Level GenerateRandomLevel(int x, int y) {
    Level level = Level(x + 2, y + 3); // level grid size
    level.StartPos(1, 1);
    int posx = 0;
    int posy = 0;

    for (int i=0; i<y+2; i++) {
        for (int j=0; j<x+2; j++) {
            if (i == 0) {
                level.SetTile(j, i, TileType::Roof1);
                level.RotateTile(j, i, 90);
            } else if (i == y + 1) {
                level.SetTile(j, i, TileType::Roof1);
                level.RotateTile(j, i, -90);
            } else if (j == 0) {
                level.SetTile(j, i, TileType::Roof1);
                level.RotateTile(j, i, 0);
            } else if (j == x + 1) {
                level.SetTile(j, i, TileType::Roof1);
                level.RotateTile(j, i, 180);
            } else {
                level.SetTile(j, i, TileType::Floor);
            }
            if ((i == 0 || i == y + 1) && (j == 0 || j == x + 1)) {
                level.SetTile(j, i, TileType::Roof);
            }
            if ((i == 1) && !(j == 0 || j == x + 1)) {
                level.SetTile(j, i, TileType::Brick);
            }
            level.SetTilePosition(j, i, posx, posy);
            level.ResizeTile(j, i, TILE_SIZE, TILE_SIZE);
            posx += TILE_SIZE;
        }
        posy += TILE_SIZE;
        posx = 0;
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
    printf("getting color 1\n");

    if (Debug) {
        sTitle = StringFormat("%s: Width: %i, Height: %i, FPS: %i", Title, Width, Height, FRAMERATE);
    }

    SDL_Window * window = CreateWindow(Width, Height, sTitle, Flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());
    printf("getting color 2\n");

    SDL_Renderer * renderer = CreateRenderer(window, Flags);
    if (errno) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());
    printf("getting color 3\n");

    Screen loadingScreen = Screen(renderer, LOADING_SCREEN, 0, 0, Width, Height, BLACK);
    loadingScreen.Text.AddLine("load", loadingScreen.CENTERED, loadingScreen.CENTERED, "lato/regular", 60, WHITE, "Loading...");
    loadingScreen.Rect.AddRect("border", loadingScreen.CENTERED, 800, 400, 75, BLACK);
    loadingScreen.Rect["border"].SetBorder(15, WHITE);
    loadingScreen.Rect.AddRect("bar", loadingScreen.Rect["border"].GetRect().x + 20, 800+20, 0, 75-40, WHITE);
    printf("getting color 4\n");

    const int barLen = 360;
    const int barSegment = barLen/6;

    // do all game loading here

    printf("getting color 4.2\n");
    tileSheet = InitTiles();

    printf("getting color 4.3\n");
    gameState.SetScreen(TITLE_SCREEN);
    printf("getting color 5\n");

    //Color not final
    Screen pauseScreen = Screen(renderer, PAUSE_SCREEN, Width / 4, Height / 4, Width / 2, Height / 2, RGB(100, 100, 255));
    pauseScreen.Text.AddLine("title", pauseScreen.CENTERED, 20, "lato/bold", 80, BLACK, "PAUSED");
    pauseScreen.Text.AddLine("desc", pauseScreen.CENTERED, pauseScreen.Text["title"].GetRect().h + 20, "lato/regular", 24, BLACK, "Press ESC to resume.");

    pauseScreen.Button.SetDefaultBorder(10, BLACK);
    pauseScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    pauseScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    pauseScreen.Button.AddButton("quit", pauseScreen.CENTERED, pauseScreen.GetRect().h - 120, 400, 100, GREY, "QUIT", GotoTitle);
    printf("getting color 5\n");

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);
    printf("getting color 5\n");

    Screen titleScreen = Screen(renderer, TITLE_SCREEN, 0, 0, Width, Height, DARK_GREY);
    titleScreen.Text.AddLine("title", titleScreen.CENTERED, 100, "lato/bold", 120, WHITE, "Dissension");
    printf("getting color 5\n");

    titleScreen.Button.SetDefaultBorder(10, BLACK);
    titleScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    titleScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    printf("getting color 5\n");

    titleScreen.Button.AddButton("start", titleScreen.CENTERED, 400, 400, 100, RGB(100, 255, 100), "START", GotoGame);
    titleScreen.Button.AddButton("options", titleScreen.CENTERED, 550, 400, 100, GREY, "OPTIONS", GotoOptions);
    titleScreen.Button.AddButton("credits", titleScreen.CENTERED, 700, 400, 100, GREY, "CREDITS", GotoCredits);
    titleScreen.Button.AddButton("quit", titleScreen.CENTERED, 850, 400, 100, RGB(255, 100, 100), "QUIT", StopGame);
    printf("getting color 5\n");

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);
    printf("getting color 5\n");

    Screen optionsScreen = Screen(renderer, OPTIONS_SCREEN, 0, 0, Width, Height, WHITE);
    optionsScreen.Button.SetDefaultBorder(4, BLACK);
    optionsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    optionsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    optionsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);
    printf("getting color 6\n");

    Screen creditsScreen = Screen(renderer, CREDITS_SCREEN, 0, 0, Width, Height, WHITE);
    creditsScreen.Button.SetDefaultBorder(4, BLACK);
    creditsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    creditsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    creditsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);

    printf("getting color\n");
    Tile bgtile = Tile(TileType::Roof, renderer);
    printf("getting color\n");
    Color bgcolor = bgtile.GetColor();
    printf("got color\n");
    Screen gameScreen = Screen(renderer, GAME_SCREEN, 0, 0, Width, Height, bgcolor, true);
    gameScreen.CreateBounds(200, 200, 200, 200); // relative (this is 200 px out in all directions);
    gameScreen.Level.AddLevel("default", GenerateRandomLevel(16, 9)); // AddLevel() will bind renderer later
    gameScreen.Level.SetCurrent("default");
    printf("got color 1\n");

    gameScreen.Creature.AddCreature("player", TileType::Roof, gameScreen.CENTERED, gameScreen.CENTERED, Width / 16, Height / 9);
    gameScreen.Creature["player"].Speed.x = 10;
    gameScreen.Creature["player"].Speed.y = 10;
    printf("got color 2\n");

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);
    printf("got color 3\n");

    Screen saveScreen = Screen(renderer, SAVE_SCREEN, 0, 0, Width, Height, DARK_GREY);
    saveScreen.Text.AddLine("title", saveScreen.CENTERED, 200, "lato/bold", 80, BLACK, "Select Save");
    saveScreen.Button.SetDefaultBorder(10, BLACK);
    printf("got color 4\n");

    // saveScreen.Button.AddButton("save1", saveScreen.CENTERED, 500, 800, 100, LIGHT_GREY, "New Save");

    UpdateLoadingBar(&loadingScreen, renderer, barSegment);
    printf("got color 5\n");

    Mix_Chunk *testAudio = LoadWAV("resources/audio/temp.wav");
    Mix_PlayChannel(-1, testAudio, 0); //-1 sets volume for all channels of audio

    Screen background = Screen(renderer, 0, 0, 0, Width, Height, gameScreen.GetColor());
    printf("got color 6\n");

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

                SDL_Point gridpos;
                gridpos.x = gameScreen.Creature["player"].GetRect().x / TILE_SIZE + TILE_SIZE;
                gridpos.y = gameScreen.Creature["player"].GetRect().y / TILE_SIZE + TILE_SIZE;

                // gameScreen.Level[gameScreen.Level.GetCurrent()].SetTile(gridpos.x, gridpos.y, TileType::FloorCrack1);

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

    titleScreen.Destroy();
    pauseScreen.Destroy();
    loadingScreen.Destroy();
    gameScreen.Destroy();
    optionsScreen.Destroy();
    creditsScreen.Destroy();
    Mix_FreeChunk(testAudio);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
