#include "game.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Constructor
Game::Game()
	: m_window(nullptr), m_renderer(nullptr) {
	init();
	std::cout << "Game initialized." << std::endl;
}

// Destructor
Game::~Game() {
	for (RenderableObject* obj : m_renderables) {
		delete obj;
	}
	m_renderables.clear();

	if (m_renderer) {
		delete m_renderer;
		m_renderer = nullptr;
	}
	if (m_window) {
		delete m_window;
		m_window = nullptr;
	}
	std::cout << "Game components cleaned up." << std::endl;
}

void Game::init() {
	m_window = new Window(defaultWidth, defaultHeight, "Minecraft Clone");
	m_renderer = new Renderer();

	//// triangle vertices
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};
	//m_triangleMesh = new Mesh(vertices, sizeof(vertices) / sizeof(float));

	// cube vertices
	float cubeVertices[] = {
		// front
		-0.5f, -0.5f,  0.5f, // 0
		 0.5f, -0.5f,  0.5f, // 1
		 0.5f,  0.5f,  0.5f, // 2
		-0.5f,  0.5f,  0.5f, // 3
		// back
		-0.5f, -0.5f, -0.5f, // 4
		 0.5f, -0.5f, -0.5f, // 5
		 0.5f,  0.5f, -0.5f, // 6
		-0.5f,  0.5f, -0.5f, // 7
	};
	// 12 triangles
	uint cubeIndices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// top
		3, 2, 6,
		6, 7, 3,
		// bottom
		4, 5, 1,
		1, 0, 4,
	};

	Mesh* cubeMesh = new Mesh(cubeVertices, sizeof(cubeVertices) / sizeof(float), cubeIndices, sizeof(cubeIndices) / sizeof(uint));
	Shader* cubeShader = new Shader(vertexShaderPath, fragmentShaderPath);
	if (cubeShader->getID() == 0) {
		std::cerr << "ERROR: Cube Shader program failed to create. Exiting." << std::endl;
		exit(EXIT_FAILURE);
	}

	m_renderables.push_back(new RenderableObject(cubeMesh, cubeShader));

	std::cout << "Game initialization complete." << std::endl;
}

// Main loop
void Game::run() {
	std::cout << "Game running..." << std::endl;
	while (!m_window->shouldClose()) {
		processInput();	// User input
		update();		// Game state update
		render();       // Draw frame

		m_window->swapBuffers();
		m_window->pollEvents();
	}
	std::cout << "Game loop finished." << std::endl;
}

void Game::processInput() {
	if (m_window->isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(m_window->getGLFWwindow(), true);
	}
	// Input handling
}

void Game::update() {
	// Movement, physics, AI, animation, updates, etc
}

void Game::render() {
	m_renderer->clear();

	for (RenderableObject* obj : m_renderables) {
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)defaultWidth / (float)defaultHeight, 0.1f, 100.0f);

		obj->m_shader->setm4("model", glm::value_ptr(model));
		obj->m_shader->setm4("view", glm::value_ptr(view));
		obj->m_shader->setm4("projection", glm::value_ptr(projection));

		obj->draw();
	}
}
