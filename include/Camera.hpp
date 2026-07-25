#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CAitSith {

class Camera {
public:
    Camera(glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), float distance = 5.0f);

    // Camera Transformation Matrices
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    // Viewport Navigation Controls
    void Rotate(float deltaYaw, float deltaPitch);
    void Pan(float deltaX, float deltaY);
    void Zoom(float deltaDistance);

    // Getters & Setters
    glm::vec3 GetPosition() const;
    glm::vec3 GetTarget() const { return m_target; }
    float GetDistance() const { return m_distance; }

    void SetTarget(glm::vec3 target) { m_target = target; }
    void SetDistance(float distance) { m_distance = glm::clamp(distance, 0.5f, 100.0f); }

private:
    void UpdatePosition();

    glm::vec3 m_target;
    glm::vec3 m_position;
    glm::vec3 m_up;

    float m_yaw;        // In degrees
    float m_pitch;      // In degrees
    float m_distance;   // Zoom distance from target
    float m_fov;        // Field of view in degrees
};

} // namespace CAitSith
