#include "window.hpp"

// Constructor
Window::Window(int width, int height, const char* title)
	: m_width(width), m_height(height), m_title(title), m_window(nullptr) {

	initGLFW();     // Initialize GLFW
	createWindow(); // Create the GLFW window
	initGLEW();     // Initialize GLEW after context is current
}

// Destructor
Window::~Window() {
	if (m_window) {
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
	std::cout << "Window and GLFW terminated." << std::endl;
}

void Window::initGLFW() {
	if (!glfwInit()) {
		std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	std::cout << "GLFW initialized." << std::endl;
}

void Window::createWindow() {
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!m_window) {
		std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	std::cout << "GLFW window created." << std::endl;
}

void Window::initGLEW() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "ERROR: Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
		glfwDestroyWindow(m_window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	std::cout << "GLEW initialized. OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::isKeyPressed(int key) const {
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}
