#pragma once
#include "constants.hpp"

inline float deltaTime = 0.0f;
inline float _lastFrameTime = 0.0f;

inline void updateDeltaTime() {
    float currentFrameTime = float(glfwGetTime());
    deltaTime = currentFrameTime - _lastFrameTime;
    _lastFrameTime = currentFrameTime;
    // std::cout << deltaTime << std::endl;
}
