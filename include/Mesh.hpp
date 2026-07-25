#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace CAitSith {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    // Mesh Primitives Generators
    static Mesh CreateSphere(float radius = 1.0f, unsigned int rings = 32, unsigned int sectors = 32);
    static Mesh CreateCube(float size = 1.0f);
    static Mesh CreateCylinder(float radius = 0.8f, float height = 2.0f, unsigned int sectors = 24);

    // Mesh Editing & Data Access
    std::vector<Vertex>& GetVertices() { return m_vertices; }
    const std::vector<Vertex>& GetVertices() const { return m_vertices; }
    std::vector<unsigned int>& GetIndices() { return m_indices; }
    const std::vector<unsigned int>& GetIndices() const { return m_indices; }

    void RecalculateNormals();
    void UpdateBuffers();

    // File I/O
    bool LoadFromOBJ(const std::string& filepath);
    bool SaveToOBJ(const std::string& filepath) const;
    bool SaveToSTL(const std::string& filepath) const;

    // OpenGL Rendering
    void Render() const;

private:
    void SetupBuffers();

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int m_VAO{0};
    unsigned int m_VBO{0};
    unsigned int m_EBO{0};
    bool m_initializedBuffers{false};
};

} // namespace CAitSith
