#pragma once
#include "constants.hpp"

class Camera {
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
public:
    Camera(glm::vec3 position);
    void updateView();
    

    inline glm::mat4& getView() {
        return view;
    }

    inline glm::mat4& getProjection() {
        return projection;
    }

    inline void setPosition(glm::vec3 nPos) {
        position = nPos;
    }
};
