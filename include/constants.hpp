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
constexpr float cameraDefaultSensitivity = 5.f;
constexpr float cameraDefaultZoom = 30.f;
constexpr float cameraDefaultFOV = 90.f;
constexpr float cameraDefaultSpeed = 5.f;
// Front face (z = 1)
constexpr float cubeVerticesFront[] = {
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

// Back face (z = 0)
constexpr float cubeVerticesBack[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

// Left face (x = 0)
constexpr float cubeVerticesLeft[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f
};

// Right face (x = 1)
constexpr float cubeVerticesRight[] = {
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f
};

// Top face (y = 1)
constexpr float cubeVerticesTop[] = {
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f
};

// Bottom face (y = 0)
constexpr float cubeVerticesBottom[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f
};

constexpr int blockOffsets[] = {
    0, 0, 1, // front
    0, 0, -1, // behind
    -1, 0, 0, // left
    1, 0, 0, // right
    0, 1, 0, // up
    0, -1, 0 // down
};

inline std::reference_wrapper<const float[18]> blockFaces[] = {
    std::ref(cubeVerticesFront),
    std::ref(cubeVerticesBack),
    std::ref(cubeVerticesLeft),
    std::ref(cubeVerticesRight),
    std::ref(cubeVerticesTop),
    std::ref(cubeVerticesBottom)
};

constexpr uint CHUNK_SIZE_X = 16;
constexpr uint CHUNK_SIZE_Y = 16;
constexpr uint CHUNK_SIZE_Z = 16;
constexpr uint CHUNK_ARRAY_LENGTH = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;
