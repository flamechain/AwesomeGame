#include "game.h"

#include "display.h"

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

        glfwPollEvents();

        this->Render(gameTime, display);
    }

    // cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    display.CloseWinC();
}

void Game::Initalize() {
    // glewInit();
}

int Game::LoadContent() {
// shader handling
    const char * const vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";

    const char * const fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // reference, screen count, source, extra
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // cleans stuff up, shader is stored in the program so this wont affect it
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

// VAO and VBO
    // vbo = vertex buffer object (collection of things for GPU to draw)
    // vao = vertex array object (collection of vbo's)

    // coordinates of vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // upper corner
    };

    // object count, reference
    glGenVertexArrays(1, &this->VAO); // has to generate before VBO
    glGenBuffers(1, &this->VBO);
    // attachs buffer/vertex-array to be read and changed
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    // type, size, vertices, type (for performance)
        //  types: stream (changed once and read a few times)
        //         static (changed once and read many times)
        //         dynamic (changed multiple times, read many times)
        //   draw: vertices modified and used to draw
        //   read: read the vertices
        //   copy: copy the vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // gives info about the vertex to the shader
    // index of vertex, amount of values for that vertex, value type,
    //  integer stuff, size, offset of vertex where the data starts
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind (bind to 0) vao and vbo so accidently changing it wont change the copy in openGL
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 1;
}

void Game::Update() {
}

void Game::Render(GameTime gameTime, DisplayManager display) {
    // r g b a (alpha/transparency)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(this->shaderProgram);
    glBindVertexArray(this->VAO);
    // primitive type, starting index of vertices, amount of vertices to draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // screen has 2 frame buffers, so it can display one while writing to the other and switching
    glfwSwapBuffers(display.window);
}
