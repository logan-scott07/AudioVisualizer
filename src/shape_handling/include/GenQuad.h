#pragma once
#include <vector>

struct Cords {float xMin, yMin, xMax, yMax;};
struct Color {float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;};

struct QuadMesh {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

QuadMesh generateQuad(float xMin, float yMin, float xMax, float yMax);
QuadMesh generateTextureQuad(float xMin, float yMin, float xMax, float yMax);
