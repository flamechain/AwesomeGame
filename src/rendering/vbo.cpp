#include "vbo.h"

VBO::VBO(GLfloat * vertices, GLsizeiptr size) {
    // object count, reference
    glGenBuffers(1, &this->ID);

    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    // type, size, vertices, type (for performance)
        //  types: stream (changed once and read a few times)
        //         static (changed once and read many times)
        //         dynamic (changed multiple times, read many times)
        //   draw: vertices modified and used to draw
        //   read: read the vertices
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
    // unbind (bind to 0) vao and vbo so accidently changing it wont change the copy in openGL
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
    glDeleteBuffers(1, &this->ID);
}
