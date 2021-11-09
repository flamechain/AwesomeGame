#include "game.h"

#include "display.h"

Game::Game(int width, int height, const char * title) {
    this->InitialWindowWidth = width;
    this->InitialWindowHeight = height;
    this->InitialWindowTitle = (char *)title;
}

void Game::Run() {
    this->Initalize();

    DisplayManager display;
    GameTime gameTime;

    if (!display.CreateWinC(InitialWindowWidth, InitialWindowHeight, InitialWindowTitle)) {
        glfwTerminate();
        printf("Failed to create window\n");
        return;
    }

    if (!this->LoadContent()) {
        display.CloseWinC();
        printf("Failed to load resources\n");
        return;
    }

    while (!glfwWindowShouldClose(display.window)) {
        gameTime.DeltaTime = glfwGetTime() - gameTime.TotalElapsedSeconds;
        gameTime.TotalElapsedSeconds = glfwGetTime();

        this->Update();
        this->Render(gameTime, display);

        glfwPollEvents();
    }

    this->vao.Delete();
    this->vbo.Delete();
    this->ebo.Delete();
    this->shaderProgram.Delete();

    display.CloseWinC();
}

void Game::Initalize() {
    // glewInit();
}

int Game::LoadContent() {
    // coordinates of vertices
    GLfloat vertices[] = {
        -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f, 0.8f, 0.3f, 0.02f, // lower left corner
        0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f, 0.8f, 0.3f, 0.02f, // lower right corner
        0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6, 0.32f, // upper corner

        -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f, 0.9f, 0.45f, 0.17f, // inner left corner
        0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f, 0.9f, 0.45f, 0.17f, // inner right corner
        0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f, 0.8f, 0.3f, 0.02f,  // inner down corner
    };

    GLuint indices[] = {
        0, 3, 5, // lower left triangle
        3, 2, 4, // lower right triangle
        5, 4, 1 // upper triangle
    };

    this->shaderProgram = Shader("default.vert", "default.frag");

    this->vao = VAO(true);
    this->vao.Bind();

    this->vbo = VBO(vertices, sizeof(vertices));
    this->ebo = EBO(indices, sizeof(indices));

    this->vao.LinkVBO(this->vbo, 0);
    this->vao.Unbind();
    this->vbo.Unbind();
    this->ebo.Unbind();

    return 1;
}

void Game::Update() {
}

void Game::Render(GameTime gameTime, DisplayManager display) {
    // r g b a (alpha/transparency)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->shaderProgram.Activate();
    this->vao.Bind();

    // primitive type, starting index of vertices, amount of vertices to draw
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // primitive type, amount of indices to draw, type of indices, index of indices
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    // screen has 2 frame buffers, so it can display one while writing to the other and switching
    glfwSwapBuffers(display.window);
}
