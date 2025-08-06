#include "shader.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>


char* readFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		std::cerr << "ERROR: Failed to open file '" << filename << "'\n";
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	rewind(file);

	char* content = static_cast<char*>(malloc(fsize + 1));
	if (!content) {
		std::cerr << "ERROR: Failed to allocate memory for file '" << filename << "'\n";
		fclose(file);
		return nullptr;
	}

	size_t bytesRead = fread(content, 1, fsize, file);
	fclose(file);

	content[bytesRead] = '\0';

	if (bytesRead != fsize) {
		std::cerr << "WARNING: Mismatch in file size and bytes read for '" << filename << "'\n";
	}

	return content;
}

GLuint compileShader(GLenum shaderType, const char* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::string shaderTypeString = (shaderType == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
		std::cerr << "ERROR: " << shaderTypeString << " Shader Compilation Failed:\n" << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR: Shader Program Linking Failed:\n" << infoLog << std::endl;
		glDeleteProgram(shaderProgram);
		return 0;
	}

	return shaderProgram;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	char* vertexShaderSource = readFile(vertexShaderPath);
	char* fragmentShaderSource = readFile(fragmentShaderPath);

	if (!vertexShaderSource || !fragmentShaderSource) {
		if (vertexShaderSource) free(vertexShaderSource);
		if (fragmentShaderSource) free(fragmentShaderSource);
		m_id = 0;
		return;
	}

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	free(vertexShaderSource);
	free(fragmentShaderSource);

	if (vertexShader == 0 || fragmentShader == 0) {
		if (vertexShader != 0) glDeleteShader(vertexShader);
		if (fragmentShader != 0) glDeleteShader(fragmentShader);
		m_id = 0;
		return;
	}

	m_id = createShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	if (m_id != 0) {
		glDeleteProgram(m_id);
		std::cout << "Shader program " << m_id << " deleted by destructor." << std::endl;
	}
}