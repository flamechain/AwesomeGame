#include "init.h"

void UpdateLoadingBar(Screen& screen, SDL_Renderer *renderer, int change) {
    screen.Rect["bar"].SetDimensions(screen.Rect["bar"].GetRect().x, screen.Rect["bar"].GetRect().y, screen.Rect["bar"].GetRect().w+change, screen.Rect["bar"].GetRect().h);
    SDL_RenderClear(renderer);
    screen.Render();
    SDL_RenderPresent(renderer);
}

SDL_Renderer *InitializeGame(string title, int width, int height, bool debug, vector<Screen>& screens, int flags, SDL_Window *&window) {
    string title_s = title;

    if (debug) {
        title_s = StringFormat("%s: width: %i, height: %i, FPS: %i", title.c_str(), width, height, FRAMERATE);
    }

    window = CreateWindow(width, height, title_s, flags);
    if (errno) ConsoleOutput("Failed creating window: %s\n", SDL_GetError());

    SDL_Renderer *renderer = CreateRenderer(window, flags);
    if (errno) ConsoleOutput("Failed creating renderer: %s\n", SDL_GetError());

    screens.reserve(7);

    Screen& loading_screen = screens[LOADING_SCREEN];
    Screen& pause_screen = screens[PAUSE_SCREEN];
    Screen& title_screen = screens[TITLE_SCREEN];
    Screen& game_screen = screens[GAME_SCREEN];
    Screen& options_screen = screens[OPTIONS_SCREEN];
    Screen& credits_screen = screens[CREDITS_SCREEN];
    Screen& save_screen = screens[SAVE_SCREEN];

    screens.push_back(Screen(renderer, LOADING_SCREEN, 0, 0, width, height, BLACK));
    loading_screen.Text.AddLine("load", loading_screen.CENTERED, loading_screen.CENTERED, "lato/regular", 60, WHITE, "Loading...");
    loading_screen.Rect.AddRect("border", loading_screen.CENTERED, 800, 400, 75, BLACK);
    loading_screen.Rect["border"].SetBorder(15, WHITE);
    loading_screen.Rect.AddRect("bar", loading_screen.Rect["border"].GetRect().x + 20, 800+20, 0, 75-40, WHITE);
    DebugOutput(debug, "  Created loading screen\n");

    const int barLen = 360;
    const int barSegment = barLen/6;

    tileSheet = InitTiles();
    game_state.SetScreen(TITLE_SCREEN);

    //Color not final
    screens.push_back(Screen(renderer, PAUSE_SCREEN, width / 4, height / 4, width / 2, height / 2, RGB(100, 100, 255)));
    pause_screen.Text.AddLine("title", pause_screen.CENTERED, 20, "lato/bold", 80, BLACK, "PAUSED");
    pause_screen.Text.AddLine("desc", pause_screen.CENTERED, pause_screen.Text["title"].GetRect().h + 20, "lato/regular", 24, BLACK, "Press ESC to resume.");

    pause_screen.Button.SetDefaultBorder(10, BLACK);
    pause_screen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    pause_screen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    pause_screen.Button.AddButton("quit", pause_screen.CENTERED, pause_screen.GetRect().h - 120, 400, 100, GREY, "QUIT", GotoTitle);
    DebugOutput(debug, "  Created pause screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    screens.push_back(Screen(renderer, TITLE_SCREEN, 0, 0, width, height, DARK_GREY));
    title_screen.Text.AddLine("title", title_screen.CENTERED, 100, "lato/bold", 120, WHITE, "Dissension");

    title_screen.Button.SetDefaultBorder(10, BLACK);
    title_screen.Button.SetDefaultTextAttrib(60, BLACK, "lato/bold");
    title_screen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);

    title_screen.Button.AddButton("start", title_screen.CENTERED, 400, 400, 100, RGB(100, 255, 100), "START", GotoGame);
    title_screen.Button.AddButton("options", title_screen.CENTERED, 550, 400, 100, GREY, "OPTIONS", GotoOptions);
    title_screen.Button.AddButton("credits", title_screen.CENTERED, 700, 400, 100, GREY, "CREDITS", GotoCredits);
    title_screen.Button.AddButton("quit", title_screen.CENTERED, 850, 400, 100, RGB(255, 100, 100), "QUIT", StopGame);
    DebugOutput(debug, "  Created title screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    Tile bgtile = Tile(TileType::Roof, renderer);
    Color bgcolor = bgtile.GetColor();

    screens.push_back(Screen(renderer, GAME_SCREEN, 0, 0, width, height, bgcolor, true));
    game_screen.CreateBounds(200, 200, 200, 200); // relative (this is 200 px out in all directions);
    game_screen.Level.AddLevel("default", GenerateRandomLevel(16, 9)); // AddLevel() will bind renderer later
    game_screen.Level.SetCurrent("default");

    game_screen.Creature.AddCreature("player", TileType::Brick, game_screen.CENTERED, game_screen.CENTERED, width / 16, height / 9);
    game_screen.Creature["player"].Speed.x = 10;
    game_screen.Creature["player"].Speed.y = 10;
    DebugOutput(debug, "  Created game screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    screens.push_back(Screen(renderer, OPTIONS_SCREEN, 0, 0, width, height, WHITE));
    options_screen.Button.SetDefaultBorder(4, BLACK);
    options_screen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    options_screen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    options_screen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);
    DebugOutput(debug, "  Created options screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    screens.push_back(Screen(renderer, CREDITS_SCREEN, 0, 0, width, height, WHITE));
    credits_screen.Button.SetDefaultBorder(4, BLACK);
    credits_screen.Button.SetDefaultTextAttrib(24, BLACK, "lato/regular");
    credits_screen.Button.SetDefaultHoverRoutine(DarkenButton, LightenButton);
    credits_screen.Button.AddButton("back", 200, 200, 150, 50, DARK_GREY, "BACK", GotoTitle);
    DebugOutput(debug, "  Created credits screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    screens.push_back(Screen(renderer, SAVE_SCREEN, 0, 0, width, height, DARK_GREY));
    save_screen.Text.AddLine("title", save_screen.CENTERED, 200, "lato/bold", 80, BLACK, "Select Save");
    save_screen.Button.SetDefaultBorder(10, BLACK);
    save_screen.Button.AddButton("save1", save_screen.CENTERED, 500, 800, 100, LIGHT_GREY, "New Save", nullptr);
    DebugOutput(debug, "  Created saves screen\n");

    UpdateLoadingBar(loading_screen, renderer, barSegment);

    return renderer;
}

void DestroyGame(vector<Screen>& screens, SDL_Renderer *renderer, SDL_Window *window, bool debug) {
    for (long long unsigned int i=0; i<screens.size(); i++) screens[i].Destroy();
    
    DebugOutput(debug, "  Destroyed screens\n");
    SDL_DestroyRenderer(renderer);
    DebugOutput(debug, "  Destroyed renderer\n");
    SDL_DestroyWindow(window);

    DebugOutput(debug, "  Destroyed window\n");
    TTF_Quit();
    IMG_Quit();
}
