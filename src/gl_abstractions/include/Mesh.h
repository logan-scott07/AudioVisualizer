#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, bool hasUV = false);
    ~Mesh();

    void Draw() const;
    void UpdateVertices(const std::vector<float>& vertices) const;

private:
    GLuint VAO, VBO, EBO;
    GLuint indexCount;
};
