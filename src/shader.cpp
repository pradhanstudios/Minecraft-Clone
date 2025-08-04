#include "shader.hpp"

char* readFile(const char* filename) {
    char* content;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file '%s'\n", filename);
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    content = ( char* ) (malloc(fsize + 1 * sizeof(char)));
    if (!content) {
        printf("Failed to allocate memory for file '%s'\n", filename); 
        return nullptr;
    }

    size_t bytesRead = fread(content, 1, fsize, file);
    fclose(file);

    content[bytesRead] = '\0';

    return content;
}

uint compileShader(GLenum shaderType, const char* shaderSource) {
    uint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string shaderTypeString = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
        std::cout << shaderTypeString << " Shader Compilation Failed in uint compileShader(GLenum, const char*)\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

uint createShaderProgram(uint vertexShader, uint fragmentShader) {
    uint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "uint createShaderProgram(uint, uint) failed\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    uint vertexShader = compileShader(GL_VERTEX_SHADER, readFile(vertexShaderPath));
    uint fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentShaderPath));
    id = createShaderProgram(vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
