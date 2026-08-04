#pragma once
#include <memory>
#include "Mesh.h"
#include "GenQuad.h"
#include "ShaderLink.h"

class Button {
public:

    Button(ShaderLink& shader, Cords cords, Color color);

    bool Contains(float ndcX, float ndcY) const;
    void Draw() const;

private:
    ShaderLink& shader;
    Cords cords;
    Color color;
    std::unique_ptr<Mesh> mesh;
};
