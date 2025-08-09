#pragma once

#include "constants.hpp"
#include <GL/glew.h>
#include <vector>

class Mesh {
public:
	Mesh(const float* vertices, size_t numVertices, const uint* indices, size_t numIndices);
	~Mesh();

	void bind() const;
	void unbind() const;

	size_t getVertexCount() const { return m_vertexCount; }
	size_t getIndexCount() const { return m_indexCount; }

private:
	GLuint m_VAO;			// Vertex Array Object ID
	GLuint m_VBO;			// Vertex Buffer Object ID
	GLuint m_EBO;			// Element Buffer Object ID
	size_t m_vertexCount;	// Number of vertices in the mesh
	size_t m_indexCount;	// Number of indices in the mesh

	void setupVertexAttributes();
};
