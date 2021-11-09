#include "vao.h"

VAO::VAO(bool init) {
    glGenVertexArrays(1, &this->ID); // has to generate before VBO
}

void VAO::LinkVBO(VBO vbo, GLuint layout) {
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(this->ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &this->ID);
}
