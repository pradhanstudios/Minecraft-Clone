#include "camera.hpp"

Camera::Camera(glm::vec3 position) {
    this->position = position;
    direction = glm::vec3(0.f, 0.f, 0.f);
    projection = glm::perspective(glm::radians(45.f), float(defaultWidth) / float(defaultHeight), 0.1f, 100.f);
    updateView();
}

// glm::mat4 Camera::getView() {
//     glm::vec3 direction = glm::normalize(position - target);
//     glm::vec3 rightAxis = glm::normalize(glm::cross(
//         glm::vec3(0.f, 1.f, 0.f), // up vector
//         direction
//     ))
//
//     glm::vec3 upAxis = glm::cross(direction, rightAxis);
//
//     return glm::lookAt(position, target, )
// }
//
//

void Camera::updateView() {
    view = glm::lookAt(position, position + direction + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
}
