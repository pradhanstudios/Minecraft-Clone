#include "camera.hpp"

Camera::Camera(glm::vec3 position, float fov, float yaw, float pitch, float sensitivity, float zoom) {
    m_position = position;
    m_fov = fov;
    m_yaw = yaw;
    m_pitch = pitch;
    m_sensitivity = sensitivity;
    m_zoom = zoom;
    m_projection = glm::perspective(glm::radians(m_fov), float(defaultWidth) / float(defaultHeight), 0.1f, 100.f);
    updateVectors();
    updateView();
}

void Camera::processMouse(double offsetX, double offsetY) {
    offsetX *= m_sensitivity;
    offsetY *= m_sensitivity;

    m_yaw -= offsetX;
    m_pitch += offsetY;
    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    m_rightAxis = glm::normalize(glm::cross(m_front, glm::vec3(0.f, 1.f, 0.f)));
    m_upAxis = glm::normalize(glm::cross(m_rightAxis, m_front));
} 
