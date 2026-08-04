#pragma once
#include <glad/glad.h>
#include <string>

class ShaderLink {
public:
    ShaderLink(GLuint vertexShader, GLuint fragmentShader);
    ~ShaderLink();

    ShaderLink(const ShaderLink&) = delete;
    ShaderLink& operator=(const ShaderLink&) = delete;

    ShaderLink(ShaderLink&& other) noexcept : id(other.id) {
        other.id = 0;
    }
    ShaderLink& operator=(ShaderLink&& other) noexcept {
        if (this != &other) {
            glDeleteProgram(id);
            id = other.id;
            other.id = 0;
        }
        return *this;
    }

    static ShaderLink FromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    static ShaderLink Default();

    void use() const;

    void setVec4(const char* name, float r, float g, float b, float a) const {
        glUniform4f(glGetUniformLocation(id, name), r, g, b, a);
    }

private:
    GLuint id = 0;
};
