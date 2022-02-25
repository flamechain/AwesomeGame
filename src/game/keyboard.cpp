#include "keyboard.h"

GAME_START

void HandleSDLEvents(vector<Screen>& screens) {
    SDL_Event event;
    SDL_GetMouseState(&game_state.mouse.x, &game_state.mouse.y);

    Screen& game_screen = screens[GAME_SCREEN];
    Screen& pause_screen = screens[PAUSE_SCREEN];
    Screen& options_screen = screens[OPTIONS_SCREEN];
    Screen& title_screen = screens[TITLE_SCREEN];
    Screen& credits_screen = screens[CREDITS_SCREEN];

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game_state.StopGame();
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        game_state.keyboard['w'] = true;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        game_state.keyboard['a'] = true;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        game_state.keyboard['s'] = true;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        game_state.keyboard['d'] = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        if (game_state.CurrentScreen() == game_screen.GetId()) {
                            game_state.SetScreen(pause_screen.GetId());
                            // fadeInLevel = 1;
                        } else if (game_state.CurrentScreen() == pause_screen.GetId()) {
                            game_state.SetScreen(game_screen.GetId());
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
                        game_state.keyboard['w'] = false;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        game_state.keyboard['a'] = false;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        game_state.keyboard['s'] = false;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        game_state.keyboard['d'] = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        switch (game_state.CurrentScreen()) {
                            case PAUSE_SCREEN: pause_screen.Button.Click(game_state.mouse); break;
                            case TITLE_SCREEN: title_screen.Button.Click(game_state.mouse); break;
                            case OPTIONS_SCREEN: options_screen.Button.Click(game_state.mouse); break;
                            case CREDITS_SCREEN: credits_screen.Button.Click(game_state.mouse); break;
                            case GAME_SCREEN: game_screen.Button.Click(game_state.mouse); break;
                            default: break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (game_state.CurrentScreen()) {
                    case PAUSE_SCREEN: pause_screen.Button.Hover(game_state.mouse); break;
                    case TITLE_SCREEN: title_screen.Button.Hover(game_state.mouse); break;
                    case OPTIONS_SCREEN: options_screen.Button.Hover(game_state.mouse); break;
                    case CREDITS_SCREEN: credits_screen.Button.Hover(game_state.mouse); break;
                    case GAME_SCREEN: game_screen.Button.Hover(game_state.mouse); break;
                    default: break;
                }
                break;
            default:
                break;
        }
    }
}

GAME_END
