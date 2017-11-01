#pragma once

#include "Engine/Exception.hpp"
#include "Engine/Types.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace le {

class Model {
public:
    Model(const char* path);

    enum class Error { UNKNOWN, FILE_NOT_FOUND };

    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec2> Uv;
    std::vector<glm::vec3> Normals;
    std::vector<ushort> Fragments;

    class ModelException : public Exception {
    public:
        ModelException(Error type) : Exception(), ErrorType(type) {}
        ModelException(Error type, const char* message) : Exception(message), ErrorType(type) {}

        Error ErrorType = Error::UNKNOWN;
    };

private:
};
}
