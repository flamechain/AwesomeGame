#include "vao.h"

VAO::VAO(bool init) {
    glGenVertexArrays(1, &this->ID); // has to generate before VBO
}

void VAO::LinkAttrib(VBO vbo, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void * offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
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
