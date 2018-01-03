#pragma once

#include "Engine/Exception.hpp"
#include "Engine/Types.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace le {

class Mesh {
public:
    Mesh() = default;
    Mesh(Mesh& model) = default;
    Mesh(const char* path);

    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec2> Uv;
    std::vector<glm::vec3> Normals;
    std::vector<ushort> Elements;

    enum class Error { UNKNOWN, FILE_NOT_FOUND };

    class MeshException : public Exception {
    public:
        MeshException(Error type) : Exception(), ErrorType(type) {}
        MeshException(Error type, const char* message) : Exception(message), ErrorType(type) {}

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
