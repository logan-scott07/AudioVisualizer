#include <glad/glad.h>
#include <string>
#include "ShaderLink.h"
#include "Shaders.h"
#include <iostream>
#include <ostream>

ShaderLink::ShaderLink(GLuint vertexShader, GLuint fragmentShader) {
    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    GLint linkStatus = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus) {
        GLint logLength = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, ' ');
        glGetProgramInfoLog(id, logLength, &logLength, infoLog.data());

        std::cout << "Link failed \n" << infoLog << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}

ShaderLink::~ShaderLink() {
    glDeleteProgram(id);
}

void ShaderLink::use() const {
    glUseProgram(id);
}

ShaderLink ShaderLink::FromFiles(const std::string &vertexPath, const std::string &fragmentPath) {

    const std::string vertex_source = get_shader_source(vertexPath);
    const std::string fragment_source = get_shader_source(fragmentPath);

    GLuint vertexShader = compile_shader(vertex_source, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);

    return ShaderLink(vertexShader, fragmentShader);
}

ShaderLink ShaderLink::Default() {
    return FromFiles(
        std::string(SHADER_DIR) + "/default.vert",
        std::string(SHADER_DIR) + "/default.frag"
    );
}
