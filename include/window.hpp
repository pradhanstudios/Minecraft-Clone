#pragma once
#include "constants.hpp"

class Window {
public:
	Window(int width, int height, const char* title);
	~Window();

	bool shouldClose() const;
	void swapBuffers();
	void pollEvents();
	bool isKeyPressed(int key) const;
	GLFWwindow* getGLFWwindow() const { return m_window; }

private:
	GLFWwindow* m_window; // Pointer to the GLFW window object
	int m_width;          // Window width
	int m_height;         // Window height
	const char* m_title;  // Window title

	void initGLFW();
	void createWindow();
	void initGLEW();
};
