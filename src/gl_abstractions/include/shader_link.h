#ifndef SHADER_LINK_H
#define SHADER_LINK_H
#include <glad/gl.h>

class ShaderLink {
    public:
    ShaderLink(GLuint vertexShader, GLuint fragmentShader);
    ~ShaderLink();

    void use() const;
    GLuint getID() const {return id;};

    private:
        GLuint id;
};

#endif
