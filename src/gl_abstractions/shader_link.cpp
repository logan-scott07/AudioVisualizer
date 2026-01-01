#include <glad/gl.h>
#include <string>
#include "shader_link.h"

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
