#pragma once

#include "constants.hpp"

class Shader {
	GLuint m_id;
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	inline GLuint getID() const {
		return m_id;
	}

	inline void enable() const {
		glUseProgram(m_id);
	}

	inline void disable() const {
		glUseProgram(0);
	}

	inline GLint getLocation(const char* parameter) const {
		return glGetUniformLocation(m_id, parameter);
	}

	inline void set(const char* parameter, int v) const {
		glUniform1i(getLocation(parameter), v);
	}

	inline void set(const char* parameter, float v) const {
		glUniform1f(getLocation(parameter), v);
	}

	inline void set(const char* parameter, float v1, float v2) const {
		glUniform2f(getLocation(parameter), v1, v2);
	}

	inline void set(const char* parameter, float v1, float v2, float v3) const {
		glUniform3f(getLocation(parameter), v1, v2, v3);
	}

	inline void set(const char* parameter, float v1, float v2, float v3, float v4) const {
		glUniform4f(getLocation(parameter), v1, v2, v3, v4);
	}

    inline void set(const char* parameter, float v1, float v2, float v3, float v4) {
        glUniform4f(getLocation(parameter), v1, v2, v3, v4);
    }

    inline void setm4(const char* parameter, const float* matrix, GLsizei count = 1, GLboolean transpose = GL_FALSE) {
        glUniformMatrix4fv(getLocation(parameter), count, transpose, matrix);
    }
};
