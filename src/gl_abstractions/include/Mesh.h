#ifndef AUDIOVISUALIZER_MESH_H
#define AUDIOVISUALIZER_MESH_H
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;
    void updateVertices(const std::vector<float>& vertices);

private:
    GLuint VAO, VBO, EBO;
    GLuint indexCount;
};

#endif