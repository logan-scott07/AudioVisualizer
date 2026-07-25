#include "GenVert.h"
#include <algorithm>

std::vector<float> generateVertices()
{
    std::vector<float> vertices;
    vertices.reserve(NUM_BARS * 4 * 3);

    float stride = BAR_WIDTH + BAR_GAP;

    for (int i = 0; i < NUM_BARS; i++)
    {
        float x = i * stride;
        float xRight = -0.9f + x;
        float xLeft = -0.95f + x;
        float top = BASELINE + MIN_HEIGHT; // start nearly flat

        // Top Right
        vertices.push_back(xRight);
        vertices.push_back(top);
        vertices.push_back(0.0f);
        // Bot Right
        vertices.push_back(xRight);
        vertices.push_back(BASELINE);
        vertices.push_back(0.0f);
        // Bot Left
        vertices.push_back(xLeft);
        vertices.push_back(BASELINE);
        vertices.push_back(0.0f);
        // Top Left
        vertices.push_back(xLeft);
        vertices.push_back(top);
        vertices.push_back(0.0f);
    }
    return vertices;
}

void updateBarHeights(std::vector<float>& vertices, const std::vector<float>& barHeights)
{
    int count = std::min(NUM_BARS, static_cast<int>(barHeights.size()));

    for (int i = 0; i < count; ++i)
    {
        float height = std::clamp(barHeights[i], 0.0f, 1.0f);
        float top = BASELINE + MIN_HEIGHT + height * (MAX_TOP - BASELINE);

        int base = i * 12; // 4 vertices * 3 floats per bar

        vertices[base + 1] = top;      // Top Right y
        vertices[base + 10] = top;     // Top Left y
    }
}