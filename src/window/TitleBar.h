#pragma once
#include "Window.h"
#include <memory>
#include "Mesh.h"
#include <Windows.h>
#include "Shaders.h"

class TitleBar {
public:
    explicit TitleBar(Window& window,
        float xMin, float yMin,
        float xMax, float yMax);

    void Initialize();
    void Draw() const;
private:
    Window& window;
    HWND hwnd = nullptr;
    float xMin, yMin, xMax, yMax;
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Shaders> shader;
};
