#include "Button.h"
#include <vector>

Button::Button(float xMin, float yMin, float xMax, float yMax)
    : xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax) {

    std::vector<float> vertices {
        xMax, yMax, 0.0f,  // top right
        xMax, yMin, 0.0f,  // bottom right
        xMin, yMin, 0.0f,  // bottom left
        xMin, yMax, 0.0f,  // top left
    };
    std::vector<unsigned int> indices { 0, 1, 3, 1, 2, 3};

    mesh = std::make_unique<Mesh>(vertices, indices);
}

bool Button::Contains(float ndcX, float ndcY) const {
    return ndcX >= xMin && ndcX <= xMax && ndcY >= yMin && ndcY <= yMax;
}

void Button::Draw() const {
    mesh->Draw();
}
