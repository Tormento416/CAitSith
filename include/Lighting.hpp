#pragma once

#include <glm/glm.hpp>

namespace CAitSith {

struct LightSource {
    glm::vec3 position{3.0f, 4.0f, 3.0f};
    glm::vec3 color{1.0f, 1.0f, 0.95f};
    float ambientIntensity{0.25f};
    float diffuseIntensity{0.8f};

    void RotateAroundOrigin(float angleDeltaDegrees) {
        float rad = glm::radians(angleDeltaDegrees);
        float x = position.x * cos(rad) - position.z * sin(rad);
        float z = position.x * sin(rad) + position.z * cos(rad);
        position.x = x;
        position.z = z;
    }
};

} // namespace CAitSith
