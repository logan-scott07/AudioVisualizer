#include "include/GenVert.h"
std::vector<float> generateVertices() {
    std::vector<float> vertices;
    vertices.reserve(NUM_BARS * 4 * 2);

    float width = 0.04f;
    float gap = 0.02f;
    float stride = width + gap;

    for (int i = 0; i < NUM_BARS; i++) {

        float x = i * stride;

        float xRight = -0.9f + x;
        float xLeft = -0.95f + x;

        float top = -0.35f;
        float bottom = -1.0f;

        //Top Right
        vertices.push_back(xRight);
        vertices.push_back(top);
        vertices.push_back(0.0f);
        //Bot Right
        vertices.push_back(xRight);
        vertices.push_back(bottom);
        vertices.push_back(0.0f);
        //Bot Left
        vertices.push_back(xLeft);
        vertices.push_back(bottom);
        vertices.push_back(0.0f);
        //Top Left
        vertices.push_back(xLeft);
        vertices.push_back(top);
        vertices.push_back(0.0f);
    }
    return vertices;
}