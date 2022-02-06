#include "keyboard.h"

void HandleSDLEvents(vector<Screen*>& screens) {
    printf(" e 1\n");
    SDL_Event event;
    SDL_GetMouseState(&gameState.mouse.x, &gameState.mouse.y);
    printf(" e 2\n");

    Screen * gameScreen = screens[GAME_SCREEN];
    Screen * pauseScreen = screens[PAUSE_SCREEN];
    Screen * optionsScreen = screens[OPTIONS_SCREEN];
    Screen * titleScreen = screens[TITLE_SCREEN];
    Screen * creditsScreen = screens[CREDITS_SCREEN];
    printf(" e 3\n");
    printf("%d\n", titleScreen->GetFollow());

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gameState.StopGame();
                break;

            case SDL_KEYDOWN:
            printf(" kd\n");
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
                        if (gameState.CurrentScreen() == gameScreen->GetId()) {
                            gameState.SetScreen(pauseScreen->GetId());
                            // fadeInLevel = 1;
                        } else if (gameState.CurrentScreen() == pauseScreen->GetId()) {
                            gameState.SetScreen(gameScreen->GetId());
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
            printf(" ku\n");
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
            printf(" md\n");
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        switch (gameState.CurrentScreen()) {
                            case PAUSE_SCREEN: pauseScreen->Button.Click(gameState.mouse); break;
                            case TITLE_SCREEN: titleScreen->Button.Click(gameState.mouse); break;
                            case OPTIONS_SCREEN: optionsScreen->Button.Click(gameState.mouse); break;
                            case CREDITS_SCREEN: creditsScreen->Button.Click(gameState.mouse); break;
                            case GAME_SCREEN: gameScreen->Button.Click(gameState.mouse); break;
                            default: break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (gameState.CurrentScreen()) {
                    case PAUSE_SCREEN: printf(" mm1\n"); pauseScreen->Button.Hover(gameState.mouse); break;
                    case TITLE_SCREEN: printf(" mm2\n"); titleScreen->Button.Hover(gameState.mouse); break;
                    case OPTIONS_SCREEN: printf(" mm3\n"); optionsScreen->Button.Hover(gameState.mouse); break;
                    case CREDITS_SCREEN: printf(" mm4\n"); creditsScreen->Button.Hover(gameState.mouse); break;
                    case GAME_SCREEN: printf(" mm5\n"); gameScreen->Button.Hover(gameState.mouse); break;
                    default: printf(" mm0\n"); break;
                }
                break;
            default:
                break;
        }
    }
    printf(" e f\n");
}
