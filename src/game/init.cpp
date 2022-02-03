#include "init.h"

void UpdateLoadingBar(Screen * screen, SDL_Renderer * renderer, int change) {
    screen->Rect["bar"].SetDimensions(screen->Rect["bar"].GetRect().x, screen->Rect["bar"].GetRect().y, screen->Rect["bar"].GetRect().w+change, screen->Rect["bar"].GetRect().h);
    SDL_RenderClear(renderer);
    screen->Render();
    SDL_RenderPresent(renderer);
}

SDL_Renderer * InitializeGame(string Title, int Width, int Height, bool Debug, Screen * screens, int Flags, SDL_Window * Window) {
    string sTitle = Title;
    printf("getting color 1\n");

    if (Debug) {
        sTitle = StringFormat("%s: Width: %i, Height: %i, FPS: %i", Title, Width, Height, FRAMERATE);
    }

    Window = CreateWindow(Width, Height, sTitle, Flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());
    printf("getting color 2\n");

    SDL_Renderer * renderer = CreateRenderer(Window, Flags);
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

    return renderer;
}

void DestroyGame(Screen * Screens, SDL_Renderer * Renderer, SDL_Window * Window) {
    Screens[TITLE_SCREEN].Destroy();
    Screens[GAME_SCREEN].Destroy();
    Screens[OPTIONS_SCREEN].Destroy();
    Screens[CREDITS_SCREEN].Destroy();
    Screens[PAUSE_SCREEN].Destroy();
    Screens[LOADING_SCREEN].Destroy();

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    TTF_Quit();
    IMG_Quit();
}
