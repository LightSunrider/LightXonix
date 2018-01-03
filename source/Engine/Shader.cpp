#include "Engine/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\f\v\n\r");

    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\f\v\n\r");

    return str.substr(first, (last - first + 1));
}

inline bool findDirective(const string &str, const string &directive) {
    return str.find(directive) != string::npos;
}

namespace le {

Shader::Shader(const char *vertexPath, const char *fragmentPath, const PreprocSettings &settings) {
    uint vertex = makeShader(vertexPath, Type::Vertex, settings);
    uint fragment = makeShader(fragmentPath, Type::Fragment, settings);

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

string Shader::loadShaderCode(const char *path) {
    ifstream file;
    stringstream s;

    file.exceptions(ifstream::failbit);
    try {
        file.open(path);
        s << file.rdbuf();
        file.close();
    }
    catch (ifstream::failure e) {
        throw ShaderException(Error::FILE_NOT_SUCCESSFULLY_READ, e.what());
    }

    return s.str();
}

std::string Shader::customPreprocessor(std::string code, const PreprocSettings &settings, PreprocData data) {
    istringstream inCode(code);
    ostringstream outCode;

    if (data.included[data.currentPath]) {
        return outCode.str();
    }

    string s;
    while (!inCode.eof()) {
        getline(inCode, s);
        s = trim(s);

        if (findDirective(s, "#version")) {
            if (data.root) {
                outCode << s;
            }
        }
        else if (findDirective(s, "#getdefine")) {
            string defName = trim(s.substr(10));

            if (settings.Definitions.find(defName) == settings.Definitions.end()) {
                throw ShaderException(Error::PREPROCESSOR_NONE_DEFINITION, defName.c_str());
            }
            else {
                outCode << "#define " << defName << ' ' << settings.Definitions.at(defName);
            }
        }
        else if (findDirective(s, "#include")) {
            string include = trim(s.substr(8));

            if (include.length() < 3) {
                throw ShaderException(Error::PREPROCESSOR_INVALID_INCLUDE);
            }
            if (include.at(0) == '\"') {
                include.erase(0, 1);
            }
            if (include.at(include.length() - 1) == '\"') {
                include.erase(include.length() - 1);
            }

            string includeCode;
            includeCode = loadShaderCode((settings.IncludePath + include).c_str());
            includeCode = customPreprocessor(includeCode, settings, PreprocData(include, false, data.included));

            outCode << includeCode;
        }
        else if (findDirective(s, "#pragma once")) {
            data.included[data.currentPath] = true;
        }
        else {
            outCode << s;
        }

        outCode << endl;
    }

    return outCode.str();
}

uint Shader::compileShader(Type type, string code) {
    uint shaderId;
    const char *sourceCode = code.c_str();

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

inline uint Shader::makeShader(const char *path, Type type, const PreprocSettings &settings) {
    return compileShader(type, customPreprocessor(loadShaderCode(path), settings, PreprocData(path)));
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
