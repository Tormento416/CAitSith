#include "SculptEngine.hpp"
#include <algorithm>
#include <cmath>

namespace CAitSith {

SculptEngine::SculptEngine() {}

float SculptEngine::CalculateFalloff(float distance) const {
    if (distance >= m_brushRadius) return 0.0f;
    float t = distance / m_brushRadius;
    return std::cos(t * 1.57079632679f); // Cosine falloff
}

RayHit SculptEngine::RaycastMesh(const Mesh& mesh, const Ray& ray) const {
    RayHit bestHit;
    bestHit.hit = false;
    bestHit.distance = 1e9f;

    const auto& vertices = mesh.GetVertices();
    const auto& indices = mesh.GetIndices();

    for (size_t i = 0; i < indices.size(); i += 3) {
        glm::vec3 v0 = vertices[indices[i]].position;
        glm::vec3 v1 = vertices[indices[i + 1]].position;
        glm::vec3 v2 = vertices[indices[i + 2]].position;

        // Möller–Trumbore ray-triangle intersection algorithm
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 h = glm::cross(ray.direction, edge2);
        float a = glm::dot(edge1, h);

        if (a > -0.00001f && a < 0.00001f) continue; // Parallel ray

        float f = 1.0f / a;
        glm::vec3 s = ray.origin - v0;
        float u = f * glm::dot(s, h);

        if (u < 0.0f || u > 1.0f) continue;

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(ray.direction, q);

        if (v < 0.0f || u + v > 1.0f) continue;

        float t = f * glm::dot(edge2, q);
        if (t > 0.0001f && t < bestHit.distance) {
            bestHit.hit = true;
            bestHit.distance = t;
            bestHit.point = ray.origin + ray.direction * t;
            bestHit.normal = glm::normalize(glm::cross(edge1, edge2));
            bestHit.triangleIndex = static_cast<unsigned int>(i / 3);
        }
    }

    return bestHit;
}

bool SculptEngine::ApplyTool(Mesh& mesh, const Ray& ray, glm::vec3 grabDelta) {
    RayHit hit = RaycastMesh(mesh, ray);
    if (!hit.hit) return false;

    switch (m_activeTool) {
        case SculptTool::Clay:
            ApplyClayBrush(mesh, hit);
            break;
        case SculptTool::Smooth:
            ApplySmoothBrush(mesh, hit);
            break;
        case SculptTool::Flatten:
            ApplyFlattenBrush(mesh, hit);
            break;
        case SculptTool::Grab:
            ApplyGrabBrush(mesh, hit, grabDelta);
            break;
        case SculptTool::TrimPlane:
            ApplyTrimPlane(mesh, hit);
            break;
    }

    mesh.UpdateBuffers();
    return true;
}

void SculptEngine::ApplyClayBrush(Mesh& mesh, const RayHit& hit) {
    auto& vertices = mesh.GetVertices();
    for (auto& v : vertices) {
        float dist = glm::distance(v.position, hit.point);
        float falloff = CalculateFalloff(dist);
        if (falloff > 0.0f) {
            v.position += hit.normal * (m_brushStrength * falloff * 0.1f);
        }
    }
}

void SculptEngine::ApplySmoothBrush(Mesh& mesh, const RayHit& hit) {
    auto& vertices = mesh.GetVertices();
    const auto& indices = mesh.GetIndices();

    std::vector<glm::vec3> avgPositions(vertices.size(), glm::vec3(0.0f));
    std::vector<int> counts(vertices.size(), 0);

    for (size_t i = 0; i < indices.size(); i += 3) {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        glm::vec3 center = (vertices[i0].position + vertices[i1].position + vertices[i2].position) / 3.0f;

        avgPositions[i0] += center; counts[i0]++;
        avgPositions[i1] += center; counts[i1]++;
        avgPositions[i2] += center; counts[i2]++;
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        float dist = glm::distance(vertices[i].position, hit.point);
        float falloff = CalculateFalloff(dist);
        if (falloff > 0.0f && counts[i] > 0) {
            glm::vec3 targetPos = avgPositions[i] / static_cast<float>(counts[i]);
            vertices[i].position = glm::mix(vertices[i].position, targetPos, m_brushStrength * falloff);
        }
    }
}

void SculptEngine::ApplyFlattenBrush(Mesh& mesh, const RayHit& hit) {
    auto& vertices = mesh.GetVertices();
    glm::vec3 planePoint = hit.point;
    glm::vec3 planeNormal = hit.normal;

    for (auto& v : vertices) {
        float dist = glm::distance(v.position, planePoint);
        float falloff = CalculateFalloff(dist);
        if (falloff > 0.0f) {
            float distToPlane = glm::dot(v.position - planePoint, planeNormal);
            v.position -= planeNormal * (distToPlane * m_brushStrength * falloff);
        }
    }
}

void SculptEngine::ApplyGrabBrush(Mesh& mesh, const RayHit& hit, glm::vec3 grabDelta) {
    auto& vertices = mesh.GetVertices();
    for (auto& v : vertices) {
        float dist = glm::distance(v.position, hit.point);
        float falloff = CalculateFalloff(dist);
        if (falloff > 0.0f) {
            v.position += grabDelta * (m_brushStrength * falloff);
        }
    }
}

void SculptEngine::ApplyTrimPlane(Mesh& mesh, const RayHit& hit) {
    auto& vertices = mesh.GetVertices();
    glm::vec3 planePoint = hit.point;
    glm::vec3 planeNormal = hit.normal;

    for (auto& v : vertices) {
        float distToPlane = glm::dot(v.position - planePoint, planeNormal);
        if (distToPlane > 0.0f) {
            v.position -= planeNormal * distToPlane; // Project all vertices above trim plane down to plane surface
        }
    }
}

} // namespace CAitSith
