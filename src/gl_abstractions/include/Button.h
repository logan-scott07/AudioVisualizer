// Button.h
#pragma once
#include "Texture.h"
#include "Mesh.h"
#include "ShaderLink.h"
#include <functional>
#include "GenQuad.h"
#include <memory>

class Button {
public:
    Button(Cords cords, Texture texture, std::function<void()> onClick, bool interactive = true)
        : cords(cords), texture(texture), onClick(std::move(onClick)), interactive(interactive) {
        QuadMesh quad = generateTextureQuad(cords.xMin, cords.yMin, cords.xMax, cords.yMax);
        mesh = std::make_unique<Mesh>(quad.vertices, quad.indices, /*hasUV=*/true);
    }

    void DrawButton(const ShaderLink& shader) const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        shader.setInt("uTexture", 0);
        mesh->Draw();
    }

    [[nodiscard]] bool HitTest(float x, float y) const {
        return x >= cords.xMin && x <= cords.xMax &&
               y >= cords.yMin && y <= cords.yMax;
    }

    void Click() const { if (onClick) onClick(); }

    [[nodiscard]] bool IsInteractive() const { return interactive; }

private:
    Cords cords;
    Texture texture;
    std::unique_ptr<Mesh> mesh;
    std::function<void()> onClick;
    bool interactive = true;
};