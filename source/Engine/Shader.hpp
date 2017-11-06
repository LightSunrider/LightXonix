#pragma once

#include "Engine/Exception.hpp"
#include "Engine/Types.hpp"
#include "Texture.hpp"

#include <GL/gl3w.h>
#include <glm/glm.hpp>

namespace le {

class Shader {
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    void Use();

    uint &Id = m_ProgramId;

    void setInt(const char *name, int value);
    void setInt(const char *name, uint value);
    void setFloat(const char *name, float value);
    void setVec2(const char *name, glm::vec2 value);
    void setVec3(const char *name, glm::vec3 value);
    void setVec4(const char *name, glm::vec4 value);
    void setMat3(const char *name, glm::mat3 value);
    void setMat4(const char *name, glm::mat4 value);
    void setTexture(int block, const char *name, Texture texture);

    enum class Error { UNKNOWN, FILE_NOT_SUCCESSFULLY_READ, COMPILATION_FAILED, LINKING_FAILED, INVALID_TYPE };

    class ShaderException : public Exception {
    public:
        ShaderException(Error type) : Exception(), ErrorType(type) {}
        ShaderException(Error type, const char *message) : Exception(message), ErrorType(type) {}

        Error ErrorType = Error::UNKNOWN;
    };

private:
    enum Type { Vertex, Fragment };

    uint loadShader(Type type, const char *path);
    uint getGlShaderType(Type t);

    uint m_ProgramId;
};
}
