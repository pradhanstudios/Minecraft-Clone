#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include <GL/glew.h>

class Renderer {
public:
	Renderer();
	~Renderer();

	void clear();

	void draw(const Mesh& mesh, Shader& shader, const Camera& camera);
	void setClearColor(float r, float g, float b, float a);

private:
	//
};
