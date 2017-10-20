#pragma once

#include <GL/gl3w.h>

namespace le {

class Shader {
public:
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
    void Use();

    GLuint &Id = m_ProgramId;

private:
    GLuint m_ProgramId;
};
}
