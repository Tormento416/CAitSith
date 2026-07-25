#include "Mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace CAitSith {

Mesh::Mesh() {}

Mesh::~Mesh() {
    // GPU Buffer Cleanup skeleton (would delete OpenGL buffers when glad context is initialized)
}

void Mesh::SetupBuffers() {
    // OpenGL VAO/VBO setup is executed dynamically when OpenGL context is initialized
    m_initializedBuffers = true;
}

void Mesh::UpdateBuffers() {
    RecalculateNormals();
}

void Mesh::RecalculateNormals() {
    for (auto& v : m_vertices) {
        v.normal = glm::vec3(0.0f);
    }

    for (size_t i = 0; i < m_indices.size(); i += 3) {
        unsigned int idx0 = m_indices[i];
        unsigned int idx1 = m_indices[i + 1];
        unsigned int idx2 = m_indices[i + 2];

        glm::vec3 p0 = m_vertices[idx0].position;
        glm::vec3 p1 = m_vertices[idx1].position;
        glm::vec3 p2 = m_vertices[idx2].position;

        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;
        glm::vec3 faceNormal = glm::cross(edge1, edge2);

        m_vertices[idx0].normal += faceNormal;
        m_vertices[idx1].normal += faceNormal;
        m_vertices[idx2].normal += faceNormal;
    }

    for (auto& v : m_vertices) {
        if (glm::length(v.normal) > 0.0001f) {
            v.normal = glm::normalize(v.normal);
        }
    }
}

Mesh Mesh::CreateSphere(float radius, unsigned int rings, unsigned int sectors) {
    Mesh mesh;
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);

    mesh.m_vertices.reserve(rings * sectors);
    for (unsigned int r = 0; r < rings; ++r) {
        for (unsigned int s = 0; s < sectors; ++s) {
            float const y = sin(-M_PI / 2.0f + M_PI * r * R);
            float const x = cos(2.0f * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2.0f * M_PI * s * S) * sin(M_PI * r * R);

            Vertex v;
            v.position = glm::vec3(x, y, z) * radius;
            v.normal = glm::vec3(x, y, z);
            v.texCoords = glm::vec2(s * S, r * R);
            mesh.m_vertices.push_back(v);
        }
    }

    mesh.m_indices.reserve(rings * sectors * 6);
    for (unsigned int r = 0; r < rings - 1; ++r) {
        for (unsigned int s = 0; s < sectors - 1; ++s) {
            mesh.m_indices.push_back(r * sectors + s);
            mesh.m_indices.push_back(r * sectors + (s + 1));
            mesh.m_indices.push_back((r + 1) * sectors + (s + 1));

            mesh.m_indices.push_back(r * sectors + s);
            mesh.m_indices.push_back((r + 1) * sectors + (s + 1));
            mesh.m_indices.push_back((r + 1) * sectors + s);
        }
    }

    mesh.RecalculateNormals();
    return mesh;
}

Mesh Mesh::CreateCube(float size) {
    Mesh mesh;
    float half = size * 0.5f;

    glm::vec3 positions[] = {
        {-half, -half,  half}, { half, -half,  half}, { half,  half,  half}, {-half,  half,  half}, // Front
        {-half, -half, -half}, {-half,  half, -half}, { half,  half, -half}, { half, -half, -half}  // Back
    };

    for (int i = 0; i < 8; ++i) {
        Vertex v;
        v.position = positions[i];
        v.normal = glm::normalize(positions[i]);
        v.texCoords = glm::vec2(0.0f);
        mesh.m_vertices.push_back(v);
    }

    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3, // Front
        4, 5, 6, 4, 6, 7, // Back
        3, 2, 6, 3, 6, 5, // Top
        4, 7, 1, 4, 1, 0, // Bottom
        1, 7, 6, 1, 6, 2, // Right
        4, 0, 3, 4, 3, 5  // Left
    };

    for (unsigned int idx : indices) {
        mesh.m_indices.push_back(idx);
    }

    mesh.RecalculateNormals();
    return mesh;
}

bool Mesh::LoadFromOBJ(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;

    m_vertices.clear();
    m_indices.clear();

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        } else if (type == "vn") {
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        } else if (type == "f") {
            std::string v1, v2, v3;
            ss >> v1 >> v2 >> v3;

            auto parseIndex = [](const std::string& s) -> unsigned int {
                std::istringstream vss(s);
                std::string idxStr;
                std::getline(vss, idxStr, '/');
                return std::stoi(idxStr) - 1;
            };

            m_indices.push_back(parseIndex(v1));
            m_indices.push_back(parseIndex(v2));
            m_indices.push_back(parseIndex(v3));
        }
    }

    for (const auto& pos : positions) {
        Vertex v;
        v.position = pos;
        v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        v.texCoords = glm::vec2(0.0f);
        m_vertices.push_back(v);
    }

    RecalculateNormals();
    return true;
}

bool Mesh::SaveToOBJ(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) return false;

    file << "# CAitSith 3D Mesh Export\n";
    file << "# Vertices: " << m_vertices.size() << "\n\n";

    for (const auto& v : m_vertices) {
        file << "v " << v.position.x << " " << v.position.y << " " << v.position.z << "\n";
    }

    for (const auto& v : m_vertices) {
        file << "vn " << v.normal.x << " " << v.normal.y << " " << v.normal.z << "\n";
    }

    for (size_t i = 0; i < m_indices.size(); i += 3) {
        file << "f " << (m_indices[i] + 1) << "//" << (m_indices[i] + 1) << " "
             << (m_indices[i + 1] + 1) << "//" << (m_indices[i + 1] + 1) << " "
             << (m_indices[i + 2] + 1) << "//" << (m_indices[i + 2] + 1) << "\n";
    }

    return true;
}

bool Mesh::SaveToSTL(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) return false;

    file << "solid CAitSithMesh\n";
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        const auto& v0 = m_vertices[m_indices[i]];
        const auto& v1 = m_vertices[m_indices[i + 1]];
        const auto& v2 = m_vertices[m_indices[i + 2]];

        glm::vec3 n = glm::normalize(glm::cross(v1.position - v0.position, v2.position - v0.position));

        file << "  facet normal " << n.x << " " << n.y << " " << n.z << "\n";
        file << "    outer loop\n";
        file << "      vertex " << v0.position.x << " " << v0.position.y << " " << v0.position.z << "\n";
        file << "      vertex " << v1.position.x << " " << v1.position.y << " " << v1.position.z << "\n";
        file << "      vertex " << v2.position.x << " " << v2.position.y << " " << v2.position.z << "\n";
        file << "    endloop\n";
        file << "  endfacet\n";
    }
    file << "endsolid CAitSithMesh\n";
    return true;
}

void Mesh::Render() const {
    // Drawing execution placeholder when GPU VAO/VBOs are bound
}

} // namespace CAitSith
