#pragma once
#include <memory>
#include "Mesh.h"

class Button {
public:

    Button(float xMin, float yMin, float xMax, float yMax);

    bool Contains(float ndcX, float ndcY) const;
    void Draw() const;

private:
    float xMin, yMin, xMax, yMax;
    std::unique_ptr<Mesh> mesh;
};
