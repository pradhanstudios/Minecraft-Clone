#include "renderer.hpp"
#include <iostream>

// Constructor
Renderer::Renderer() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	std::cout << "Renderer initialized." << std::endl;
}

// Destructor
Renderer::~Renderer() {
	std::cout << "Renderer destroyed." << std::endl;
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Mesh& mesh, const Shader& shader) {
	shader.enable();
	mesh.bind();
	glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
	mesh.unbind();
	shader.disable();
}

void Renderer::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
