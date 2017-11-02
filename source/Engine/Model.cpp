#include "Engine/Model.hpp"

#include <cstring>
#include <fstream>
#include <map>
#include <sstream>

namespace le {

Model::Model(const char *path) {
    ObjRawData rawObj = loadObj(path);
    ObjData obj = indexVertices(rawObj);
    obj = indexFragments(obj);

    Vertices = obj.Vertices;
    Uv = obj.Uv;
    Normals = obj.Normals;
    Elements = obj.Elements;
}

Model::ObjRawData Model::loadObj(const char *path) {
    ObjRawData data;
    std::ifstream fs;

    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs = std::ifstream(path, std::ios::binary);
    if (fs.fail()) {
        throw ModelException(Error::FILE_NOT_FOUND);
    }

    std::string line;
    while (getline(fs, line)) {
        if (line.substr(0, 2) == "v ") {
            std::stringstream s(line.substr(2));
            glm::vec3 v;

            s >> v.x >> v.y >> v.z;
            data.v.push_back(v);
        }
        else if (line.substr(0, 3) == "vt ") {
            std::stringstream s(line.substr(3));
            glm::vec2 u;

            s >> u.x >> u.y;
            u.y = -u.y;
            data.vt.push_back(u);
        }
        else if (line.substr(0, 3) == "vn ") {
            std::stringstream s(line.substr(3));
            glm::vec3 n;

            s >> n.x >> n.y >> n.z;
            data.vn.push_back(n);
        }
        else if (line.substr(0, 2) == "f ") {
            std::stringstream s(line.substr(2));
            ushort vertexIndex[3], uvIndex[3], normalIndex[3];

            for (uint i = 0; i < 3; i++) {
                char dl;
                s >> vertexIndex[i] >> dl >> uvIndex[i] >> dl >> normalIndex[i];

                data.fv.push_back(vertexIndex[i]);
                data.ft.push_back(uvIndex[i]);
                data.fn.push_back(normalIndex[i]);
            }
        }
    }

    return data;
}

Model::ObjData Model::indexVertices(ObjRawData &obj) {
    ObjData data;

    for (uint i = 0; i < obj.fv.size(); i++) {
        uint vertexIndex = obj.fv[i];
        uint uvIndex = obj.ft[i];
        uint normalIndex = obj.fn[i];

        glm::vec3 vertex = obj.v[vertexIndex - 1];
        glm::vec2 uv = obj.vt[uvIndex - 1];
        glm::vec3 normal = obj.vn[normalIndex - 1];

        data.Vertices.push_back(vertex);
        data.Uv.push_back(uv);
        data.Normals.push_back(normal);
    }

    return data;
}

Model::ObjData Model::indexFragments(ObjData &obj) {
    struct VertexData {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        bool operator<(const VertexData that) const {
            return memcmp((void *) this, (void *) &that, sizeof(VertexData)) > 0;
        };
    };
    ObjData data;

    std::map<VertexData, ushort> VertexToOutIndex;

    for (uint i = 0; i < obj.Vertices.size(); i++) {
        VertexData packed = {obj.Vertices[i], obj.Uv[i], obj.Normals[i]};

        auto it = VertexToOutIndex.find(packed);
        if (it == VertexToOutIndex.end()) {
            data.Vertices.push_back(obj.Vertices[i]);
            data.Uv.push_back(obj.Uv[i]);
            data.Normals.push_back(obj.Normals[i]);

            ushort newindex = (ushort) data.Vertices.size() - 1;
            data.Elements.push_back(newindex);
            VertexToOutIndex[packed] = newindex;
        }
        else {
            data.Elements.push_back(it->second);
        }
    }

    return data;
}
}
