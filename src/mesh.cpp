#include "mesh.hpp"
#include <iostream>

// Constructor
Mesh::Mesh(const float* vertices, size_t numFloats)
	: m_VAO(0), m_VBO(0), m_vertexCount(numFloats / 3) {

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), vertices, GL_STATIC_DRAW);

	setupVertexAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout << "Mesh created with VAO: " << m_VAO << ", VBO: " << m_VBO << std::endl;
}

// Destructor
Mesh::~Mesh() {
	if (m_VAO != 0) {
		glDeleteVertexArrays(1, &m_VAO);
	}
	if (m_VBO != 0) {
		glDeleteBuffers(1, &m_VBO);
	}
	std::cout << "Mesh VAO and VBO deleted." << std::endl;
}

void Mesh::bind() const {
	glBindVertexArray(m_VAO);
}

void Mesh::unbind() const {
	glBindVertexArray(0);
}

void Mesh::setupVertexAttributes() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
