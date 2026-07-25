#include "Camera.hpp"
#include <algorithm>

namespace CAitSith {

Camera::Camera(glm::vec3 target, float distance)
    : m_target(target)
    , m_distance(distance)
    , m_yaw(-90.0f)
    , m_pitch(20.0f)
    , m_fov(45.0f)
    , m_up(0.0f, 1.0f, 0.0f)
{
    UpdatePosition();
}

void Camera::UpdatePosition() {
    float yawRad = glm::radians(m_yaw);
    float pitchRad = glm::radians(m_pitch);

    float x = m_target.x + m_distance * cos(pitchRad) * cos(yawRad);
    float y = m_target.y + m_distance * sin(pitchRad);
    float z = m_target.z + m_distance * cos(pitchRad) * sin(yawRad);

    m_position = glm::vec3(x, y, z);
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(m_fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::Rotate(float deltaYaw, float deltaPitch) {
    m_yaw += deltaYaw;
    m_pitch = glm::clamp(m_pitch + deltaPitch, -89.0f, 89.0f);
    UpdatePosition();
}

void Camera::Pan(float deltaX, float deltaY) {
    glm::vec3 forward = glm::normalize(m_target - m_position);
    glm::vec3 right = glm::normalize(glm::cross(forward, m_up));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    float panSpeed = m_distance * 0.002f;
    m_target += (-right * deltaX + up * deltaY) * panSpeed;
    UpdatePosition();
}

void Camera::Zoom(float deltaDistance) {
    m_distance = glm::clamp(m_distance - deltaDistance * 0.5f, 0.5f, 50.0f);
    UpdatePosition();
}

glm::vec3 Camera::GetPosition() const {
    return m_position;
}

} // namespace CAitSith
