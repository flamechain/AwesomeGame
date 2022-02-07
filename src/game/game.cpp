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
    vector<Screen> screens;

    InitializeEngine();

    SDL_Window * window;
    SDL_Renderer * renderer = InitializeGame(Title, Width, Height, Debug, screens, Flags, window);

    Screen& gameScreen = screens[GAME_SCREEN];
    Screen& pauseScreen = screens[PAUSE_SCREEN];
    Screen& optionsScreen = screens[OPTIONS_SCREEN];
    Screen& titleScreen = screens[TITLE_SCREEN];
    Screen& creditsScreen = screens[CREDITS_SCREEN];

    int samples;
    Mix_Chunk * chunks = InitializeAudio(&samples);

    Screen background = Screen(renderer, 0, 0, 0, Width, Height, gameScreen.GetColor());

    while (gameState.IsRunning()) {

        HandleSDLEvents(screens);

        SDL_RenderClear(renderer);
        background.TempShade(1);
        background.Render();

        switch (gameState.CurrentScreen()) {
            case GAME_SCREEN: {
                HandleGameScreen(gameScreen);
            } break;
            case TITLE_SCREEN: {
                HandleTitleScreen(titleScreen);
            } break;
            case PAUSE_SCREEN: {
                HandlePauseScreen(gameScreen, pauseScreen, background);
            } break;
            case CREDITS_SCREEN: {
                HandleCreditsScreen(creditsScreen);
            } break;
            case OPTIONS_SCREEN: {
                HandleOptionsScreen(optionsScreen);
            } break;
        }

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
  