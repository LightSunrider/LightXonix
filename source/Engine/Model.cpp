#include "Engine/Model.hpp"

#include <fstream>
#include <sstream>

namespace le {

Model::Model(const char *path) {
    std::ifstream fs;
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs = std::ifstream(path, std::ios::binary);

    if (fs.fail()) {
        throw ModelException(Error::FILE_NOT_FOUND);
    }

    std::vector<ushort> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices, tempNormals;
    std::vector<glm::vec2> tempUv;

    std::string line;
    while (getline(fs, line)) {
        if (line.substr(0, 2) == "v ") {
            std::stringstream s(line.substr(2));
            glm::vec3 v;

            s >> v.x >> v.y >> v.z;
            tempVertices.push_back(v);
        }
        else if (line.substr(0, 3) == "vt ") {
            std::stringstream s(line.substr(3));
            glm::vec2 u;

            s >> u.x >> u.y;
            u.y = -u.y;
            tempUv.push_back(u);
        }
        else if (line.substr(0, 3) == "vn ") {
            std::stringstream s(line.substr(3));
            glm::vec3 n;

            s >> n.x >> n.y >> n.z;
            tempNormals.push_back(n);
        }
        else if (line.substr(0, 2) == "f ") {
            std::stringstream s(line.substr(2));
            ushort vertexIndex[3], uvIndex[3], normalIndex[3];

            for (uint i = 0; i < 3; i++) {
                char dl;
                s >> vertexIndex[i] >> dl >> uvIndex[i] >> dl >> normalIndex[i];

                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
    }

    for (uint i = 0; i < vertexIndices.size(); i++) {
        Vertices.push_back(tempVertices[vertexIndices[i] - 1]);
        Uv.push_back(tempUv[uvIndices[i] - 1]);
        Normals.push_back(tempNormals[normalIndices[i] - 1]);
    }
}
}
