#include "Button.h"
#include "GenQuad.h"
#include "ShaderLink.h"

Button::Button(ShaderLink &shader, Cords cords, Color color)
: shader(shader), cords(cords), color(color)
{
    QuadMesh quad = generateQuad(cords.xMin, cords.yMin, cords.xMax, cords.yMax);
    mesh = std::make_unique<Mesh>(quad.vertices, quad.indices);
}

bool Button::Contains(float ndcX, float ndcY) const {
    return ndcX >= cords.xMin && ndcX <= cords.xMax && ndcY >= cords.yMin && ndcY <= cords.yMax;
}

void Button::Draw() const {
    shader.setVec4("uColor", color.r, color.g, color.b, color.a);
    mesh->Draw();
}
