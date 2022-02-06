#include "game.h"
#include "utils.h"
#include "init.h"
#include "callbacks.h"
#include "keyboard.h"
#include "audio.h"
#include "game_screen.h"
#include "options_screen.h"
#include "credits_screen.h"
#include "title_screen.h"
#include "pause_screen.h"

extern GameState gameState;

int RunGame(int Width, int Height, const char * Title, bool Debug, int Flags) {
    gameState = GameState();
    vector<Screen*> screens;

    InitializeEngine();

    SDL_Window * window;
    SDL_Renderer * renderer = InitializeGame(Title, Width, Height, Debug, screens, Flags, window);
    printf("init game 1\n");
    Screen * gameScreen = screens[GAME_SCREEN];
    Screen * pauseScreen = screens[PAUSE_SCREEN];
    Screen * optionsScreen = screens[OPTIONS_SCREEN];
    Screen * titleScreen = screens[TITLE_SCREEN];
    Screen * creditsScreen = screens[CREDITS_SCREEN];
    printf("init game 2\n");

    int samples;
    Mix_Chunk * chunks = InitializeAudio(&samples);
    printf("init game 3\n");

    Screen background = Screen(renderer, 0, 0, 0, Width, Height, gameScreen->GetColor());
    printf("init game 4\n");

    while (gameState.IsRunning()) {

        printf("events 1\n");
        printf("%i\n", screens[TITLE_SCREEN]->GetFollow());
        printf("events 1.1\n");
        HandleSDLEvents(screens);
        printf("events 2\n");

        SDL_RenderClear(renderer);
        background.Render();
        printf("events 3\n");

        switch (gameState.CurrentScreen()) {
            case GAME_SCREEN: {
                printf("game handler\n");
                HandleGameScreen(gameScreen);
            } break;
            case TITLE_SCREEN: {
                printf("title handler\n");
                HandleTitleScreen(titleScreen);
            } break;
            case PAUSE_SCREEN: {
                printf("pause handler\n");
                HandlePauseScreen(gameScreen, pauseScreen);
            } break;
            case CREDITS_SCREEN: {
                printf("credits handler\n");
                HandleCreditsScreen(creditsScreen);
            } break;
            case OPTIONS_SCREEN: {
                printf("options handler\n");
                HandleOptionsScreen(optionsScreen);
            } break;
        }
        printf("handled\n");

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FRAMERATE);
    }

    DestroyAudio(chunks, samples);
    DestroyGame(screens, renderer, window);
    background.Destroy();

    SDL_Quit();

    return 0;
}
