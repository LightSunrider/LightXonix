#pragma once

#include <GL/glew.h>

class Shader {
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();

private:
    GLuint m_ProgramId;
};
