#include "constants.hpp"
#include "shader.hpp"
#include "camera.hpp"

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    GLFWwindow* window = glfwCreateWindow(defaultWidth, defaultHeight, "Minecraft Clone", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    Shader shader = Shader(vertexShaderPath, fragmentShaderPath);
    Camera camera = Camera(glm::vec3(0.f, 0.f, 3.f));
    
    // Setting up Triangle Vertex Object
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    while (!glfwWindowShouldClose(window)) {

        // Input
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //

        glClear(GL_COLOR_BUFFER_BIT); 
        camera.updateView();

        // Render
        shader.enable();
        shader.set("projection", camera.getProjection());
        shader.set("view", camera.getView());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    shader.free();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
