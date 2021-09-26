// #define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// #include "GL/glew.h"
// #include <GL/GL.h>
// #include <GL/GLU.h>
// #include <GL/glut.h>
// #include "GL/freeglut.h"

int main() {
    GLFWwindow* window;

    if (!glfwInit()) return 1;

    window = glfwCreateWindow(640, 480, "Awesome Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
