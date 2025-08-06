#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh {
public:
	Mesh(const float* vertices, size_t numFloats);
	~Mesh();

	void bind() const;
	void unbind() const;

	size_t getVertexCount() const { return m_vertexCount; }

private:
	GLuint m_VAO;          // Vertex Array Object ID
	GLuint m_VBO;          // Vertex Buffer Object ID
	size_t m_vertexCount;  // Number of vertices in the mesh

	void setupVertexAttributes();
};