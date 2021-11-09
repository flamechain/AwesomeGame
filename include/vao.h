#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "vbo.h"

// vertex array object (collection of vbo's)
class VAO {
public:
    GLuint ID;

    VAO() {}
    VAO(bool init);

    void LinkVBO(VBO vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
