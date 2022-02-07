#include "init.h"

void UpdateLoadingBar(Screen& screen, SDL_Renderer * renderer, int change) {
    screen.Rect["bar"].SetDimensions(screen.Rect["bar"].GetRect().x, screen.Rect["bar"].GetRect().y, screen.Rect["bar"].GetRect().w+change, screen.Rect["bar"].GetRect().h);
    SDL_RenderClear(renderer);
    screen.Render();
    SDL_RenderPresent(renderer);
}

SDL_Renderer * InitializeGame(string Title, int Width, int Height, bool Debug, vector<Screen>& screens, int Flags, SDL_Window * Window) {
    string sTitle = Title;

    if (Debug) {
        sTitle = StringFormat("%s: Width: %i, Height: %i, FPS: %i", Title, Width, Height, FRAMERATE);
    }

    Window = CreateWindow(Width, Height, sTitle, Flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());

    SDL_Renderer * renderer = CreateRenderer(Window, Flags);
    if (errno) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());

    screens.reserve(7);

    Screen& loadingScreen = screens[LOADING_SCREEN];
    Screen& pauseScreen = screens[PAUSE_SCREEN];
    Screen& titleScreen = screens[TITLE_SCREEN];
    Screen& gameScreen = screens[GAME_SCREEN];
    Screen& optionsScreen = screens[OPTIONS_SCREEN];
    Screen& creditsScreen = screens[CREDITS_SCREEN];
    Screen& saveScreen = screens[SAVE_SCREEN];

    screens.push_back(Screen(renderer, LOADING_SCREEN, 0, 0, Width, Height, BLACK));
    loadingScreen.Text.AddLine("load", loadingScreen.CENTERED, loadingScreen.CENTERED, "lato/regular", 60, WHITE, "Loading...");
    loadingScreen.Rect.AddRect("border", loadingScreen.CENTERED, 800, 400, 75, BLACK);
    loadingScreen.Rect["border"].SetBorder(15, WHITE);
    loadingScreen.Rect.AddRect("bar", loadingScreen.Rect["border"].GetRect().x + 20, 800+20, 0, 75-40, WHITE);
    printf("init 1\n");

    const int barLen = 360;
    const int barSegment = barLen/6;

    // do all game loading here

    tileSheet = InitTiles();
    gameState.SetScreen(TITLE_SCREEN);

    //Color not final
    screens.push_back(Screen(renderer, PAUSE_SCREEN, Width / 4, Height / 4, Width / 2, Height / 2, RGB(100, 100, 255)));
    pauseScreen.Text.AddLine("title", pauseScreen.CENTERED, 20, "lato/bold", 80, BLACK, "PAUSED");
    pauseScreen.Text.AddLine("desc", pauseScreen.CENTERED, pauseScreen.Text["title"].GetRect().h + 20, "lato/regular", 24, BLACK, "Press ESC to resume.");

    pauseScreen.Button.SetDefaultBorder(10, BLACK);
    pauseScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    pauseScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    pauseScreen.Button.AddButton("quit", pauseScreen.CENTERED, pauseScreen.GetRect().h - 120, 400, 100, GREY, "QUIT", GotoTitle);
    printf("init 2\n");

    UpdateLoadingBar(loadingScreen, renderer, barSegment);

    screens.push_back(Screen(renderer, TITLE_SCREEN, 0, 0, Width, Height, DARK_GREY));
    titleScreen.Text.AddLine("title", titleScreen.CENTERED, 100, "lato/bold", 120, WHITE, "Dissension");

    titleScreen.Button.SetDefaultBorder(10, BLACK);
    titleScreen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    titleScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);

    titleScreen.Button.AddButton("start", titleScreen.CENTERED, 400, 400, 100, RGB(100, 255, 100), "START", GotoGame);
    titleScreen.Button.AddButton("options", titleScreen.CENTERED, 550, 400, 100, GREY, "OPTIONS", GotoOptions);
    titleScreen.Button.AddButton("credits", titleScreen.CENTERED, 700, 400, 100, GREY, "CREDITS", GotoCredits);
    titleScreen.Button.AddButton("quit", titleScreen.CENTERED, 850, 400, 100, RGB(255, 100, 100), "QUIT", StopGame);
    printf("init 3\n");

    UpdateLoadingBar(loadingScreen, renderer, barSegment);

    Tile bgtile = Tile(TileType::Roof, renderer);
    Color bgcolor = bgtile.GetColor();

    screens.push_back(Screen(renderer, GAME_SCREEN, 0, 0, Width, Height, bgcolor, true));
    gameScreen.CreateBounds(200, 200, 200, 200); // relative (this is 200 px out in all directions);
    gameScreen.Level.AddLevel("default", GenerateRandomLevel(16, 9)); // AddLevel() will bind renderer later
    gameScreen.Level.SetCurrent("default");

    gameScreen.Creature.AddCreature("player", TileType::Roof, gameScreen.CENTERED, gameScreen.CENTERED, Width / 16, Height / 9);
    gameScreen.Creature["player"].Speed.x = 10;
    gameScreen.Creature["player"].Speed.y = 10;
    printf("init 4\n");

    UpdateLoadingBar(loadingScreen, renderer, barSegment);

    screens.push_back(Screen(renderer, OPTIONS_SCREEN, 0, 0, Width, Height, WHITE));
    optionsScreen.Button.SetDefaultBorder(4, BLACK);
    optionsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    optionsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    optionsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(loadingScreen, renderer, barSegment);
    printf("init 5\n");

    screens.push_back(Screen(renderer, CREDITS_SCREEN, 0, 0, Width, Height, WHITE));
    creditsScreen.Button.SetDefaultBorder(4, BLACK);
    creditsScreen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    creditsScreen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    creditsScreen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);

    UpdateLoadingBar(loadingScreen, renderer, barSegment);

    screens.push_back(Screen(renderer, SAVE_SCREEN, 0, 0, Width, Height, DARK_GREY));
    saveScreen.Text.AddLine("title", saveScreen.CENTERED, 200, "lato/bold", 80, BLACK, "Select Save");
    saveScreen.Button.SetDefaultBorder(10, BLACK);
    saveScreen.Button.AddButton("save1", saveScreen.CENTERED, 500, 800, 100, LIGHT_GREY, "New Save", nullptr);
    printf("init 6\n");

    UpdateLoadingBar(loadingScreen, renderer, barSegment);

    return renderer;
}

void DestroyGame(vector<Screen>& Screens, SDL_Renderer * Renderer, SDL_Window * Window) {
    for (int i=0; i<Screens.size(); i++) Screens[i].Destroy();

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    TTF_Quit();
    IMG_Quit();
}
