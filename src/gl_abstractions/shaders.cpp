#include <shaders.h>
#include <glad/gl.h>
#include <string>
#include <fstream> //for std::fstream
#include <sstream>  //for std::stringstream
#include <iostream> //for std::string


std::string get_shader_source(std::string const& shader_file) {
    std::ifstream file(shader_file);
    if (!file.is_open()) {
        std::cout << "Failed to open " << shader_file << "\n";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool compile_shader(GLuint& shader_id, std::string const& shader_data, GLenum shader_type) {
    shader_id = glCreateShader(shader_type);
    if (shader_id == 0) {
        std::cout << "Failed to create shader " << shader_data << "\n";
        return false;
    }

    const GLchar* source = shader_data.c_str();
    glShaderSource(shader_id, 1, &source, nullptr);

    glCompileShader(shader_id);

    GLint success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE) {
        std::cout << "Failed to compile shader " << shader_data << "\n";
        return false;
    }
    return true;
}