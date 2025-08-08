#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>
typedef unsigned int uint;
inline const char *vertexShaderPath = "assets/shader.vert";
inline const char *fragmentShaderPath = "assets/shader.frag";
constexpr uint defaultWidth = 1280;
constexpr uint defaultHeight = 720;
constexpr uint defaultFPS = 60;
constexpr float cameraDefaultYaw = -90.f;
constexpr float cameraDefaultPitch = 0.f;
constexpr float cameraDefaultSensitivity = 0.05f;
constexpr float cameraDefaultZoom = 45.f;
constexpr float cameraDefaultFOV = 45.f;
constexpr float cameraDefaultSpeed = 0.1f;
