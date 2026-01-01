#include <iostream>
#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "window.h"
#include "mesh.h"
#include "shader_link.h"

int main() {

    GLFWwindow* window = create_window(1000, 600, "AudioVisualizer");


    std::string vertex_source = get_shader_source("../../src/gl_abstractions/include/default.vert");
    GLuint vertexShader;
    if (!(compile_shader(vertexShader, vertex_source, GL_VERTEX_SHADER))) {
        std::cout << "Vertex shader compilation failed." << std::endl;
    }

    std::string fragment_source = get_shader_source("../../src/gl_abstractions/include/default.frag");
    GLuint fragmentShader;
    if (!(compile_shader(fragmentShader, fragment_source, GL_FRAGMENT_SHADER))) {
        std::cout << "Fragment shader compilation failed." << std::endl;
    }

    ShaderLink shader_link(vertexShader, fragmentShader);


    std::vector<float> vertices = {
        //Square
        -0.9f, -0.3f, 0.0f, // Top Right
        -0.9f, -1.0f, 0.0f, // Bottom right
        -0.95f, -1.0f, 0.0f, // Bottom Left
        -0.95f, -0.3f, 0.0f //Top Left
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3,
    };

    Mesh barMesh(vertices, indices);

    //render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.24f, 0.24f, 0.24f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_link.use();
        barMesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //clean-up
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}