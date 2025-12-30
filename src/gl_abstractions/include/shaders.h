#ifndef AUDIOVISUALIZER_SHADERS_H
#define AUDIOVISUALIZER_SHADERS_H
#include <string>
#include <glad/gl.h>

bool compile_shader(std::string const& shader_data, GLenum shader_type);
std::string get_shader_source(std::string const& shader_file);

#endif //AUDIOVISUALIZER_SHADERS_H