#include "GenQuad.h"

QuadMesh generateQuad(float xMin, float yMin, float xMax, float yMax) {
    QuadMesh quad;
    quad.vertices = {
        xMax, yMax, 0.0f,
        xMax, yMin, 0.0f,
        xMin, yMin, 0.0f,
        xMin, yMax, 0.0f,
    };
    quad.indices = { 0, 1, 3, 1, 2, 3};
    return quad;
};