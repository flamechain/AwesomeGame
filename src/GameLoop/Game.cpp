#include "Game.h"

#include "DisplayManager.h"
#include "GameTime.h"
#include <math.h>

void Game::Run() {  
    this->Initalize();

    DisplayManager display;
    GameTime gameTime;

    if (!display.CreateWindow(InitialWindowWidth, InitialWindowHeight, InitialWindowTitle)) {
        display.CloseWindow();
    }

    this->LoadContent();

    while (!glfwWindowShouldClose(display.Window)) {
        gameTime.DeltaTime = glfwGetTime() - gameTime.TotalElapsedSeconds;
        gameTime.TotalElapsedSeconds = glfwGetTime();

        this->Update();

        glfwPollEvents();

        this->Render(gameTime, display);
    }

    display.CloseWindow();
}

void Game::Initalize() {
}

void Game::LoadContent() {
}

void Game::Update() {
}

void Game::Render(GameTime gameTime, DisplayManager displayManager) {
    glClearColor(sin(gameTime.TotalElapsedSeconds), 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(displayManager.Window);
}
