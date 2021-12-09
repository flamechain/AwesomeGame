#ifndef SHADER_H
#define SHADER_H

#include "utils.h"
#include <glad/glad.h>

std::string FileReadAllText(const char * filename);

class Shader {
public:
    GLuint ID;

    Shader() {}
    Shader(const char * vertexFilename, const char * fragmentFilename);

    void Activate();
    void Delete();
};

#endif
