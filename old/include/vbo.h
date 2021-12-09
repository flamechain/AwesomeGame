#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

// vertex buffer object (collection of things for GPU to draw)
class VBO {
public:
    GLuint ID;

    VBO() {}
    VBO(GLfloat * vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
