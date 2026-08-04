#pragma once
#include <glad/glad.h>
#include <string>

GLuint compile_shader(const std::string& shader_data, GLenum shaderType);
std::string get_shader_source(std::string const& shaderFile);
