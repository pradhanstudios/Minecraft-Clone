#pragma once
#include "constants.hpp"

class Camera {
    glm::mat4 m_view;
    glm::mat4 m_projection;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_upAxis;
    glm::vec3 m_rightAxis;

    float m_yaw;
    float m_pitch;
    float m_sensitivity;
    float m_zoom;
    float m_fov;

    void updateVectors();
public:
    Camera(glm::vec3 position, float fov=cameraDefaultFOV, float yaw=cameraDefaultYaw, float pitch=cameraDefaultPitch, float sensitivity=cameraDefaultSensitivity, float zoom=cameraDefaultZoom);
    void processMouse(double offsetX, double offsetY);
    
    ~Camera() {
        std::cout << "Camera has been destroyed." << std::endl;
    }

    inline void updateView() {
        m_view = glm::lookAt(m_position, m_position + m_front, m_upAxis);
    }

    inline glm::mat4 getView() const {
        return m_view;
    }

    inline glm::mat4 getProjection() const {
        return m_projection;
    }

    inline glm::vec3 getPosition() const {
        return m_position;
    }

    inline glm::vec3 getFront() {
        return m_front;
    }

    inline glm::vec3 getRightAxis() {
        return m_rightAxis;
    }

    inline void setPosition(glm::vec3 pos) {
        m_position = pos;
    }


    inline float getZoom() const {
        return m_zoom;
    }

    inline void setZoom(float zoom) {
        m_zoom = zoom;
    }

    inline float getYaw() const {
        return m_yaw;
    }

    inline float getPitch() const {
        return m_pitch;
    }

    inline float getFOV() const {
        return m_fov;
    }
};
