#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;
    void UpdateVertices(const std::vector<float>& vertices);

private:
    GLuint VAO, VBO, EBO;
    GLuint indexCount;
};
