#include "game.h"

#include "display.h"
#include <math.h>

void Game::Run() {  
    this->Initalize();

    DisplayManager display;
    GameTime gameTime;

    if (!display.CreateWindow(InitialWindowWidth, InitialWindowHeight, InitialWindowTitle)) {
        display.CloseWindow();
    }

    if (!this->LoadContent()) {
        display.CloseWindow();
    }

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

int Game::LoadContent() {
    string vertexShader;
    string ln;
    ifstream file ("./src/shaders/vertex.vert");

    if (file.is_open()) {
        while (std::getline(file, ln)) {
            vertexShader += ln.c_str();
            vertexShader += "\n";
        }

        file.close();
    } else {
        return 0;
    }

    delete(file);

    string fragmentShader;
    ifstream file ("./src/shaders/fragment.vert");

    if (file.is_open()) {
        while (std::getline(file, ln)) {
            fragmentShader += ln.c_str();
            fragmentShader += "\n";
        }

        file.close();
    } else {
        return 0;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float * vertices = {
        -0.5f, 0.5f, 1f, 0f, 0f, // top left
        0.5f, 0.5f, 0f, 1f, 0f,// top right
        -0.5f, -0.5f, 0f, 0f, 1f, // bottom left

        0.5f, 0.5f, 0f, 1f, 0f,// top right
        0.5f, -0.5f, 0f, 1f, 1f, // bottom right
        -0.5f, -0.5f, 0f, 0f, 1f, // bottom left
    };

    std::vector<float> v_vert = vertices

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v_vert.size(), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, flase, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 1;
}

void Game::Update() {
}

void Game::Render(GameTime gameTime, DisplayManager displayManager) {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glfwSwapBuffers(displayManager.Window);
}
