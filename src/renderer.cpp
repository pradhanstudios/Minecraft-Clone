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

void Renderer::draw(const Mesh& mesh, Shader& shader, const Camera& camera) {
	shader.enable();
    shader.setm4("projection", glm::value_ptr(camera.getProjection()));
    shader.setm4("view", glm::value_ptr(camera.getView()));
	mesh.bind();
	// glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
	mesh.unbind();
	shader.disable();
}

void Renderer::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
