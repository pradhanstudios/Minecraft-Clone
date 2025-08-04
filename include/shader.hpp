#pragma once
#include "constants.hpp"

class Shader {
    uint id;
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    inline void free() {
        glDeleteProgram(id);
    }

    inline GLuint getID() {
        return id;
    }

    inline void enable() {
        glUseProgram(id);
    }

    inline void disable() {
        glUseProgram(0);
    }

    inline int getLocation(const char* parameter) {
        return glGetUniformLocation(id, parameter);
    }

    inline void set(const char* parameter, int v) {
        glUniform1i(getLocation(parameter), v);
    }

    inline void set(const char* parameter, float v) {
        glUniform1f(getLocation(parameter), v);
    }

    inline void set(const char* parameter, float v1, float v2) {
        glUniform2f(getLocation(parameter), v1, v2);
    }

    inline void set(const char* parameter, float v1, float v2, float v3) {
        glUniform3f(getLocation(parameter), v1, v2, v3);
    }

    inline void set(const char* parameter, float v1, float v2, float v3, float v4) {
        glUniform4f(getLocation(parameter), v1, v2, v3, v4);
    }

    inline void setm4(const char* parameter, const float* matrix, GLsizei count = 1, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4fv(getLocation(parameter), count, transpose, matrix);
    }
};
