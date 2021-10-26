#include "game.h"

#include "display.h"
#include <math.h>
#include <stdio.h>

void Game::Run() {
    this->Initalize();

    DisplayManager display;
    GameTime gameTime;

    if (!display.CreateWinC(InitialWindowWidth, InitialWindowHeight, InitialWindowTitle)) {
        display.CloseWinC();
    }

    if (!this->LoadContent()) {
        display.CloseWinC();
    }

    // here
    while (!glfwWindowShouldClose(display.Window)) {
        gameTime.DeltaTime = glfwGetTime() - gameTime.TotalElapsedSeconds;
        gameTime.TotalElapsedSeconds = glfwGetTime();

        this->Update();

        glfwPollEvents();

        this->Render(gameTime, display);
    }
    // here

    display.CloseWinC();
}

void Game::Initalize() {
    // glewInit();
}

int Game::LoadContent() {
    printf("finding shaders\n");
    char vertexShader[] = "#version 330 core\n"
                          "layout (location = 0) in vec2 aPosition;\n"
                          "layout (location = 1) in vec3 aColor;\n"
                          "out vec4 vertexColor;\n"
                          "void main() {\n"
                          "vertexColor = vec4(aColor.rgb, 1.0);\n"
                          "gl_Position = vec4(aPosition.xy, 0, 1.0);}\n";

    char fragmentShader[] = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "in vec4 vertexColor;\n"
                            "void main() {\n"
                            "FragColor = vertexColor;}\n";

    printf("defining shaders\n");
    const char * v = vertexShader;
    const char * f = fragmentShader;

    printf("creating shaders\n");
    // create shaders
    // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vs, 1, &v, NULL);
    // glCompileShader(vs);

    // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fs, 1, &f, NULL);
    // glCompileShader(fs);

//     printf("attaching shaders\n");
//     // link shaders
//     this->shader = glCreateProgram();
//     glAttachShader(shader, vs);
//     glAttachShader(shader, fs);

//     printf("linking shaders\n");
//     glLinkProgram(shader);

//     printf("creating vao\n");
//     // create vao and vbo
//     glGenVertexArrays(1, &this->vao);
//     glGenBuffers(1, &this->vbo);

//     glBindVertexArray(this->vao);
//     glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

//     std::vector<float> vertices = {
//         -0.5, 0.5, 1, 0, 0, // top left
//         0.5, 0.5, 0, 1, 0,// top right
//         -0.5, -0.5, 0, 0, 1, // bottom left

//         0.5, 0.5, 0, 1, 0,// top right
//         0.5, -0.5, 0, 1, 1, // bottom right
//         -0.5, -0.5, 0, 0, 1, // bottom left
//     };

//     printf("finishing vao\n");
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);

//     glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void *)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

    return 1;
}

void Game::Update() {
}

void Game::Render(GameTime gameTime, DisplayManager displayManager) {
//     glClearColor(0, 0, 0, 0);
//     glClear(GL_COLOR_BUFFER_BIT);

//     glUseProgram(this->shader);

//     glBindVertexArray(this->vao);
//     glDrawArrays(GL_TRIANGLES, 0, 6);
//     glBindVertexArray(0);

//     glfwSwapBuffers(displayManager.Window);
}
