#include "game.hpp"
#include <iostream>

// Constructor
Game::Game(uint fps)
	: m_window(nullptr), m_renderer(nullptr), m_shader(nullptr), m_cubeMesh(nullptr), m_fps(fps) {
	init();
	std::cout << "Game initialized." << std::endl;
}

// Destructor
Game::~Game() {
	if (m_cubeMesh) {
		delete m_cubeMesh;
		m_cubeMesh = nullptr;
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
    m_camera = new Camera(glm::vec3(0.f, 0.f, 10.f));

    glfwSetWindowUserPointer(m_window->getGLFWwindow(), this);
    glfwSetCursorPos(m_window->getGLFWwindow(), 0, 0);
    glfwSetInputMode(m_window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window->getGLFWwindow(), mouseCallback);

	if (m_shader->getID() == 0) {
		std::cerr << "ERROR: Shader program failed to create. Exiting." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Triangle vertices
	// float vertices[] = {
	// 	-0.5f, -0.5f, 0.0f,
	// 	 0.5f, -0.5f, 0.0f,
	// 	 0.0f,  0.5f, 0.0f
	// };

	// m_triangleMesh = new Mesh(vertices, sizeof(vertices) / sizeof(float));


    float vertices[] = {
        // front
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // back
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0
    };

    uint elements[] = {
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
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

    m_cubeMesh = new Mesh(&vertices[0], sizeof(vertices) / sizeof(float), &elements[0], sizeof(elements) / sizeof(uint));

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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / m_fps));
	}
	std::cout << "Game loop finished." << std::endl;
}

void Game::processInput() {
	if (m_window->isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(m_window->getGLFWwindow(), true);
	}

	if (m_window->isKeyPressed(GLFW_KEY_W)) {
	    m_camera->setPosition(m_camera->getPosition() + m_camera->getFront() * cameraDefaultSpeed);	
	}

	if (m_window->isKeyPressed(GLFW_KEY_S)) {
	    m_camera->setPosition(m_camera->getPosition() - m_camera->getFront() * cameraDefaultSpeed);	
	}

    if (m_window->isKeyPressed(GLFW_KEY_A)) {
	    m_camera->setPosition(m_camera->getPosition() - m_camera->getRightAxis() * cameraDefaultSpeed);
	}

    if (m_window->isKeyPressed(GLFW_KEY_D)) {
	    m_camera->setPosition(m_camera->getPosition() + m_camera->getRightAxis() * cameraDefaultSpeed);	
	}

    if (m_window->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        m_camera->setPosition(m_camera->getPosition() - glm::vec3(0.f, 1.f, 0.f) * cameraDefaultSpeed);
    }
    if (m_window->isKeyPressed(GLFW_KEY_SPACE)) {
        m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.f, 1.f, 0.f) * cameraDefaultSpeed);
    }
    if (m_window->isKeyPressed(GLFW_KEY_F)) {
        m_renderer->toggleWireframeDraw();
    }
}

void Game::mouseCallback(GLFWwindow* window, double posX, double posY) {
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

    double offsetX = game->m_mousePosX - posX;
    double offsetY = game->m_mousePosY - posY;
    game->m_mousePosX = posX;
    game->m_mousePosY = posY; 
    game->m_camera->processMouse(offsetX, offsetY);
}

void Game::update() {
	// Movement, physics, AI, animation, updates, etc
    m_camera->updateView();
}

void Game::render() {
	m_renderer->clear();

	m_renderer->draw(*m_cubeMesh, *m_shader, *m_camera);
}
