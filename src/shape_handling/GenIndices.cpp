#include "GenIndices.h"
#include "GenVert.h"

std:: vector<unsigned int> generateIndices() {
    std::vector<unsigned int> indices;
    indices.reserve(NUM_BARS * 6);

    for (int i = 0; i < NUM_BARS; i++) {
        unsigned int base = i * 4;

        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);

        indices.push_back(base + 2);
        indices.push_back(base + 3);
        indices.push_back(base + 0);
    }

    return indices;
}
