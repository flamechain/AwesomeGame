#include "shader.h"

std::string FileReadAllText(const char * filename) {
    std::ifstream in (filename, std::ios::binary);

    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);

        in.read(&contents[0], contents.size());

        in.close();
        return contents;
    }

    throw errno;
}

Shader::Shader(const char * vertexFilename, const char * fragmentFilename) {

    char path[512];
    getcwd(path, 512);
    std::string vertexPath;
    std::string fragmentPath;

    std::string vertexCode, fragmentCode;

    try {
        vertexCode = FileReadAllText(vertexFilename);
        fragmentCode = FileReadAllText(fragmentFilename);
    } catch (...) {
        try {
            vertexPath = (std::string)path + vertexFilename;
            fragmentPath = (std::string)path + fragmentFilename;
            vertexCode = FileReadAllText(vertexPath.c_str());
            fragmentCode = FileReadAllText(fragmentPath.c_str());
        } catch (...) {
            try {
                vertexPath = (std::string)path + (std::string)"/src/rendering/shaders/" + vertexFilename;
                fragmentPath = (std::string)path + (std::string)"/src/rendering/shaders/" + fragmentFilename;
                printf("vertex: %s\n", vertexPath.c_str());
                printf("fragment: %s\n", fragmentPath.c_str());
                vertexCode = FileReadAllText(vertexPath.c_str());
                fragmentCode = FileReadAllText(fragmentPath.c_str());
            } catch (...) {
                printf("Shader: Failed to find shaders\n");
                throw errno;
            }
        }
    }

    const char * vertexSource = vertexCode.c_str();
    const char * fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // reference, screen count, source, extra
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);

    glLinkProgram(this->ID);

    // cleans stuff up, shader is stored in the program so this wont affect it
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(this->ID);
}

void Shader::Delete() {
    glDeleteProgram(this->ID);
}
