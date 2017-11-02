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
    std::vector<ushort> Elements;

    class ModelException : public Exception {
    public:
        ModelException(Error type) : Exception(), ErrorType(type) {}
        ModelException(Error type, const char* message) : Exception(message), ErrorType(type) {}

        Error ErrorType = Error::UNKNOWN;
    };

private:
    struct ObjRawData {
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;
        std::vector<ushort> fv, ft, fn;
    };

    struct ObjData {
        std::vector<glm::vec3> Vertices;
        std::vector<glm::vec2> Uv;
        std::vector<glm::vec3> Normals;
        std::vector<ushort> Elements;
    };

    ObjRawData loadObj(const char* path);
    ObjData indexVertices(ObjRawData& obj);
    ObjData indexFragments(ObjData& obj);
};
}
