#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "window.h"

int main() {

    GLFWwindow* window = create_window(800, 800, "AudioVisualizer");


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

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLint success = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        GLint logLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, ' ');
        glGetProgramInfoLog(shaderProgram, logLength, nullptr, infoLog.data());

        std::cout << "Program linking failed:\n" << infoLog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] =
    {
        //Square
        0.5f, 0.5f, 0.0f, // Top Right
        0.5f, -0.5f, 0.0f, // Bottom right
        -0.5f, -0.5f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f //Top Left
    };
    GLint indices[] =
        {
        0, 1, 3,
        1, 2, 3,
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}