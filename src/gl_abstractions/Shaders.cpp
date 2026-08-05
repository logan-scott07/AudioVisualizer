#include <Shaders.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string get_shader_source(std::string const& shaderFile) {
    std::ifstream file(shaderFile);
    if (!file.is_open()) {
        std::cout << "Failed to open " << shaderFile << "\n";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compile_shader(std::string const& shader_data, GLenum shaderType) {
    GLuint shader_id = glCreateShader(shaderType);
    if (shader_id == 0) {
        throw std::runtime_error("Failed to create shader");
    }

    const GLchar* source = shader_data.c_str();
    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    GLint success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE) {
        glDeleteShader(shader_id);
        throw std::runtime_error("Failed to compile shader");
    }
    return shader_id;
}
