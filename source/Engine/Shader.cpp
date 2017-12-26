#include "Engine/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace le {

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    uint vertex = loadShader(Type::Vertex, vertexPath);
    uint fragment = loadShader(Type::Fragment, fragmentPath);

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vertex);
    glAttachShader(m_ProgramId, fragment);
    glLinkProgram(m_ProgramId);

    int success;
    glGetProgramiv(this->m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(this->m_ProgramId, 512, NULL, infoLog);
        throw ShaderException(Error::LINKING_FAILED, infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use() {
    glUseProgram(this->m_ProgramId);
}

void Shader::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::setInt(const char *name, uint value) {
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::setFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(Id, name), value);
}

void Shader::setVec2(const char *name, glm::vec2 value) {
    glUniform2fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setVec3(const char *name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setVec4(const char *name, glm::vec4 value) {
    glUniform4fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setMat3(const char *name, glm::mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const char *name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setTexture(int block, const char *name, Texture texture) {
    glActiveTexture(GL_TEXTURE0 + block);
    glBindTexture(GL_TEXTURE_2D, texture.Id);
    setInt(name, block);
}

uint Shader::loadShader(Shader::Type type, const char *path) {
    std::string inputSourceCode;
    std::ifstream file;
    uint shaderId;

    file.exceptions(std::ifstream::failbit);
    try {
        file.open(path);
        std::stringstream s;
        s << file.rdbuf();
        file.close();
        inputSourceCode = s.str();
    }
    catch (std::ifstream::failure) {
        throw ShaderException(Error::FILE_NOT_SUCCESSFULLY_READ);
    }

    const char *sourceCode = inputSourceCode.c_str();
    shaderId = glCreateShader(getGlShaderType(type));
    glShaderSource(shaderId, 1, &sourceCode, nullptr);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        throw ShaderException(Error::COMPILATION_FAILED, infoLog);
    }

    return shaderId;
}

uint Shader::getGlShaderType(Shader::Type t) {
    switch (t) {
    case Vertex:
        return GL_VERTEX_SHADER;
    case Fragment:
        return GL_FRAGMENT_SHADER;
    default:
        throw ShaderException(Error::INVALID_TYPE);
    }
}
}
