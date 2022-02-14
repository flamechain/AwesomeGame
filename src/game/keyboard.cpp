#include "keyboard.h"

void HandleSDLEvents(vector<Screen>& screens) {
    SDL_Event event;
    SDL_GetMouseState(&gameState.mouse.x, &gameState.mouse.y);

    Screen& game_screen = screens[GAME_SCREEN];
    Screen& pause_screen = screens[PAUSE_SCREEN];
    Screen& options_screen = screens[OPTIONS_SCREEN];
    Screen& title_screen = screens[TITLE_SCREEN];
    Screen& credits_screen = screens[CREDITS_SCREEN];

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gameState.StopGame();
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        gameState.keyboard['w'] = true;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        gameState.keyboard['a'] = true;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        gameState.keyboard['s'] = true;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        gameState.keyboard['d'] = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        if (gameState.CurrentScreen() == game_screen.GetId()) {
                            gameState.SetScreen(pause_screen.GetId());
                            // fadeInLevel = 1;
                        } else if (gameState.CurrentScreen() == pause_screen.GetId()) {
                            gameState.SetScreen(game_screen.GetId());
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
                        gameState.keyboard['w'] = false;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        gameState.keyboard['a'] = false;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        gameState.keyboard['s'] = false;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        gameState.keyboard['d'] = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        switch (gameState.CurrentScreen()) {
                            case PAUSE_SCREEN: pause_screen.Button.Click(gameState.mouse); break;
                            case TITLE_SCREEN: title_screen.Button.Click(gameState.mouse); break;
                            case OPTIONS_SCREEN: options_screen.Button.Click(gameState.mouse); break;
                            case CREDITS_SCREEN: credits_screen.Button.Click(gameState.mouse); break;
                            case GAME_SCREEN: game_screen.Button.Click(gameState.mouse); break;
                            default: break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (gameState.CurrentScreen()) {
                    case PAUSE_SCREEN: pause_screen.Button.Hover(gameState.mouse); break;
                    case TITLE_SCREEN: title_screen.Button.Hover(gameState.mouse); break;
                    case OPTIONS_SCREEN: options_screen.Button.Hover(gameState.mouse); break;
                    case CREDITS_SCREEN: credits_screen.Button.Hover(gameState.mouse); break;
                    case GAME_SCREEN: game_screen.Button.Hover(gameState.mouse); break;
                    default: break;
                }
                break;
            default:
                break;
        }
    }
}
