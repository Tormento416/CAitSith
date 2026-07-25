#pragma once

#include "Mesh.hpp"
#include <glm/glm.hpp>

namespace CAitSith {

enum class SculptTool {
    Clay,
    Grab,
    Smooth,
    Flatten,
    TrimPlane
};

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};

struct RayHit {
    bool hit{false};
    float distance{0.0f};
    glm::vec3 point{0.0f};
    glm::vec3 normal{0.0f};
    unsigned int triangleIndex{0};
};

class SculptEngine {
public:
    SculptEngine();

    // Sculpting Application Interface
    bool ApplyTool(Mesh& mesh, const Ray& ray, glm::vec3 grabDelta = glm::vec3(0.0f));

    // Raycast hit testing
    RayHit RaycastMesh(const Mesh& mesh, const Ray& ray) const;

    // Tool Settings
    void SetTool(SculptTool tool) { m_activeTool = tool; }
    SculptTool GetTool() const { return m_activeTool; }

    float GetRadius() const { return m_brushRadius; }
    void SetRadius(float r) { m_brushRadius = glm::clamp(r, 0.05f, 5.0f); }

    float GetStrength() const { return m_brushStrength; }
    void SetStrength(float s) { m_brushStrength = glm::clamp(s, 0.01f, 1.0f); }

private:
    void ApplyClayBrush(Mesh& mesh, const RayHit& hit);
    void ApplySmoothBrush(Mesh& mesh, const RayHit& hit);
    void ApplyFlattenBrush(Mesh& mesh, const RayHit& hit);
    void ApplyGrabBrush(Mesh& mesh, const RayHit& hit, glm::vec3 grabDelta);
    void ApplyTrimPlane(Mesh& mesh, const RayHit& hit);

    float CalculateFalloff(float distance) const;

    SculptTool m_activeTool{SculptTool::Clay};
    float m_brushRadius{0.5f};
    float m_brushStrength{0.2f};
};

} // namespace CAitSith
