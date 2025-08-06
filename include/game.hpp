#pragma once

#include "constants.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

class Game {
public:
	// Constructor: Initializes the Game components.
	Game();

	// Destructor: Cleans up Game components.
	~Game();

	// Runs the main game loop.
	void run();

private:
	Window* m_window;   // Pointer to the Window object
	Renderer* m_renderer; // Pointer to the Renderer object
	Shader* m_shader;   // Pointer to the Shader object
	Mesh* m_triangleMesh; // Pointer to the Mesh object for the triangle

	// Private helper function to initialize all components
	void init();

	// Private helper function to handle input
	void processInput();

	// Private helper function to update game state (empty for now)
	void update();

	// Private helper function to render the scene
	void render();
};
