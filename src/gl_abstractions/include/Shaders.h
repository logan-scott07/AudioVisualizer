#ifndef AUDIOVISUALIZER_SHADERS_H
#define AUDIOVISUALIZER_SHADERS_H
#include <glad/glad.h>
#include <string>


bool compile_shader(GLuint& shader_id, std::string const& shader_data, GLenum shader_type);
std::string get_shader_source(std::string const& shader_file);

#endif