#include "game.hpp"
#include <iostream>

// Constructor
Game::Game()
	: m_window(nullptr), m_renderer(nullptr), m_shader(nullptr), m_triangleMesh(nullptr) {
	init();
	std::cout << "Game initialized." << std::endl;
}

// Destructor
Game::~Game() {
	if (m_triangleMesh) {
		delete m_triangleMesh;
		m_triangleMesh = nullptr;
	}
	if (m_shader) {
		delete m_shader;
		m_shader = nullptr;
	}
	if (m_renderer) {
		delete m_renderer;
		m_renderer = nullptr;
	}
	if (m_window) {
		delete m_window;
		m_window = nullptr;
	}
    if (m_camera) {
        delete m_camera;
        m_camera = nullptr;
    }
	std::cout << "Game components cleaned up." << std::endl;
}

void Game::init() {
	m_window = new Window(defaultWidth, defaultHeight, "Minecraft Clone");
	m_renderer = new Renderer();
	m_shader = new Shader(vertexShaderPath, fragmentShaderPath);
    m_camera = new Camera(glm::vec3(0.f, 0.f, 3.f));
	if (m_shader->getID() == 0) {
		std::cerr << "ERROR: Shader program failed to create. Exiting." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Triangle vertices
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	m_triangleMesh = new Mesh(vertices, sizeof(vertices) / sizeof(float));

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

	m_renderer->draw(*m_triangleMesh, *m_shader, *m_camera);
}
