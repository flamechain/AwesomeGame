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

extern GameState game_state;

int RunGame(int width, int height, string title, bool debug, int flags) {
    game_state = GameState();
    vector<Screen> screens;

    InitializeEngine();

    SDL_Window *window;
    DebugOutput(debug, "Initializing game\n");
    SDL_Renderer *renderer = InitializeGame(title, width, height, debug, screens, flags, window);

    Screen& game_screen = screens[GAME_SCREEN];
    Screen& pause_screen = screens[PAUSE_SCREEN];
    Screen& options_screen = screens[OPTIONS_SCREEN];
    Screen& title_screen = screens[TITLE_SCREEN];
    Screen& credits_screen = screens[CREDITS_SCREEN];

    long long unsigned int samples;
    vector<Mix_Chunk> chunks;
    InitializeAudio(samples, chunks);

    Screen background = Screen(renderer, 0, 0, 0, width, height, game_screen.GetColor());

    // TODO This should be moved to the pause_screen class eventually
    double fade_level = 1;

    while (game_state.IsRunning()) {

        HandleSDLEvents(screens);

        SDL_RenderClear(renderer);
        background.TempShade(1);
        background.Render();

        switch (game_state.CurrentScreen()) {
            case GAME_SCREEN: {
                HandleGameScreen(game_screen);
                fade_level = 1;
            } break;
            case TITLE_SCREEN: {
                HandleTitleScreen(title_screen);
            } break;
            case PAUSE_SCREEN: {
                HandlePauseScreen(game_screen, pause_screen, background, fade_level);
            } break;
            case CREDITS_SCREEN: {
                HandleCreditsScreen(credits_screen);
            } break;
            case OPTIONS_SCREEN: {
                HandleOptionsScreen(options_screen);
            } break;
        }

        // triggers the double buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FRAMERATE);
    }

    DebugOutput(debug, "Game destruction\n");
    DestroyGame(screens, renderer, window, debug);
    background.Destroy();

    SDL_Quit();

    DebugOutput(debug, "Audio destruction\n");
    DestroyAudio(chunks, samples);

    return errno;
}
