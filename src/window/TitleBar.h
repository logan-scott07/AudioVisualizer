#pragma once
#include "Window.h"
#include <memory>
#include "Mesh.h"
#include "ShaderLink.h"
#include "GenQuad.h"
#include <Windows.h>

class TitleBar {
public:
    explicit TitleBar(Window& window, ShaderLink& shader, Cords cords, Color color);

    void Initialize();
    void Draw() const;
private:
    Window& window;
    ShaderLink& shader;
    HWND hwnd = nullptr;
    Cords cords;
    Color color;
    std::unique_ptr<Mesh> mesh;
};
