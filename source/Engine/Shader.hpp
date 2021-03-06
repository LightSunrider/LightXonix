#pragma once

#include "Engine/Exception.hpp"
#include "Engine/Types.hpp"
#include "Texture.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace le {

class Shader {
public:
    typedef std::unordered_map<std::string, std::string> PreprocDefinitions;

    struct PreprocSettings {
        PreprocDefinitions Definitions;
        std::string IncludePath;
    };

    Shader(const char *vertexPath, const char *fragmentPath, const PreprocSettings &settings);
    void Use();

    uint &Id = m_ProgramId;

    void set(const char *name, int value);
    void set(const char *name, uint value);
    void set(const char *name, float value);
    void set(const char *name, glm::vec2 value);
    void set(const char *name, glm::vec3 value);
    void set(const char *name, glm::vec4 value);
    void set(const char *name, glm::mat3 value);
    void set(const char *name, glm::mat4 value);
    void set(const char *name, int block, Texture texture);

    enum class Error {
        UNKNOWN,
        FILE_NOT_SUCCESSFULLY_READ,
        COMPILATION_FAILED,
        LINKING_FAILED,
        INVALID_TYPE,
        PREPROCESSOR_NONE_DEFINITION,
        PREPROCESSOR_INVALID_INCLUDE
    };

    class ShaderException : public Exception {
    public:
        ShaderException(Error type) : Exception(), ErrorType(type) {}
        ShaderException(Error type, const char *message) : Exception(message), ErrorType(type) {}

        Error ErrorType = Error::UNKNOWN;
    };

private:
    enum Type { Vertex, Fragment };

    typedef std::unordered_map<std::string, bool> IncludeList;

    struct PreprocData {
        std::string currentPath;
        bool root = true;
        IncludeList included;

        PreprocData(std::string currentPath, bool root = true, IncludeList included = IncludeList())
            : currentPath(currentPath), root(root), included(included) {}
    };

    std::string loadShaderCode(const char *path);
    std::string customPreprocessor(std::string code, const PreprocSettings &settings, PreprocData data);
    uint compileShader(Type type, std::string code);
    inline uint makeShader(const char *path, Type type, const PreprocSettings &settings);
    uint getGlShaderType(Type t);

    uint m_ProgramId;
};
}
