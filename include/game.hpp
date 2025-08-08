#pragma once

#include "constants.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class RenderableObject {
public:
	Mesh* m_mesh;
	Shader* m_shader;

	RenderableObject(Mesh* mesh, Shader* shader)
		: m_mesh(mesh), m_shader(shader) {
	}

	~RenderableObject() {
		if (m_mesh) {
			delete m_mesh;
		}
		if (m_shader) {
			delete m_shader;
		}
	}

	void draw() const {
		if (m_mesh && m_shader) {
			m_shader->enable();
			m_mesh->bind();
			glDrawElements(GL_TRIANGLES, m_mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
			m_mesh->unbind();
		}
	}
};


class Game {
public:
	Game();
	~Game();

	void run();

private:
	Window* m_window;
	Renderer* m_renderer;

	std::vector<RenderableObject*> m_renderables;

	void init();
	void processInput();
	void update();
	void render();
};
