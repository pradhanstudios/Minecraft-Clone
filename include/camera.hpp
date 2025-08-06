#pragma once
#include "constants.hpp"

class Camera {
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 direction;
public:
    Camera(glm::vec3 position);
    void updateView();
    
    ~Camera() {
        std::cout << "Camera has been destroyed." << std::endl;
    }
    inline glm::mat4 getView() const {
        return view;
    }

    inline glm::mat4 getProjection() const {
        return projection;
    }

    inline void setPosition(glm::vec3 nPos) {
        position = nPos;
    }

    inline glm::vec3 getPosition() {
        return position;
    }
};
