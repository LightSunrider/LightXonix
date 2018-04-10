#pragma once

#include "Engine/Camera.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Material.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Types.hpp"

namespace le {

class IRenderable {
public:
    virtual void Draw(GameObject* object, Camera* camera) = 0;

    virtual ~IRenderable() = default;
};

class Model : public IRenderable {
public:
    Model(Mesh& mesh, Shader shader, IMaterial* material) : m_Shader(shader), m_Material(material) {
        glGenVertexArrays(1, &m_VBO);
        glBindVertexArray(m_VBO);

        glGenBuffers(1, &m_Vertex);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vertex);
        glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * sizeof(glm::vec3), &mesh.Vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_Uv);
        glBindBuffer(GL_ARRAY_BUFFER, m_Uv);
        glBufferData(GL_ARRAY_BUFFER, mesh.Uv.size() * sizeof(glm::vec2), &mesh.Uv[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_Normal);
        glBindBuffer(GL_ARRAY_BUFFER, m_Normal);
        glBufferData(GL_ARRAY_BUFFER, mesh.Normals.size() * sizeof(glm::vec3), &mesh.Normals[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_Element);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Element);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Elements.size() * sizeof(ushort), &mesh.Elements[0], GL_STATIC_DRAW);

        m_ElementsCount = mesh.Elements.size();
    }

    void Draw(GameObject* object, Camera* camera) override {
        m_Shader.Use();
        m_Shader.set("projection", camera->ProjectionMatrix);
        m_Shader.set("view", camera->ViewMatrix);
        m_Shader.set("cameraPosition", camera->transform.position);

        m_Material->Use(m_Shader);

        glm::mat4 model;
        model = glm::translate(model, object->transform.position);
        model = model * glm::mat4_cast(object->transform.rotation);
        model = glm::scale(model, object->transform.scale);

        m_Shader.set("model", model);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vertex);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_Uv);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, m_Normal);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Element);

        glDrawElements(GL_TRIANGLES, m_ElementsCount, GL_UNSIGNED_SHORT, nullptr);
    }

private:
    uint m_VBO = 0;
    uint m_Vertex = 0;
    uint m_Uv = 0;
    uint m_Normal = 0;
    uint m_Element = 0;

    uint m_ElementsCount;

    Shader m_Shader;
    IMaterial* m_Material;
};
}
