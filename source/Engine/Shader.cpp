#include "Engine/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace le {

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::failbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure) {
        throw ShaderException(Error::FILE_NOT_SUCCESSFULLY_READ);
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    glClear(GL_COLOR_BUFFER_BIT);
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        throw ShaderException(Error::VERTEX_COMPILATION_FAILED, infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        throw ShaderException(Error::FRAGMENT_COMPILATION_FAILED, infoLog);
    }

    this->m_ProgramId = glCreateProgram();
    glAttachShader(this->m_ProgramId, vertex);
    glAttachShader(this->m_ProgramId, fragment);
    glLinkProgram(this->m_ProgramId);

    glGetProgramiv(this->m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->m_ProgramId, 512, NULL, infoLog);
        throw ShaderException(Error::LINKING_FAILED, infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use() {
    glUseProgram(this->m_ProgramId);
}

void Shader::setInt(const char *name, int &value) {
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::setInt(const char *name, uint &value) {
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::setFloat(const char *name, float &value) {
    glUniform1f(glGetUniformLocation(Id, name), value);
}

void Shader::setVec2(const char *name, glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setVec3(const char *name, glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setVec4(const char *name, glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::setMat3(const char *name, glm::mat3 &value) {
    glUniformMatrix3fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const char *name, glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &value[0][0]);
}
}
