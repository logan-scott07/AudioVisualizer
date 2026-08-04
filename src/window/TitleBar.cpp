#include "TitleBar.h"

TitleBar::TitleBar(Window& window, ShaderLink& shader, Cords cords, Color color)
    : window(window), shader(shader), cords(cords), color(color)
{
    hwnd = window.GetHWND();
    QuadMesh quad = generateQuad(cords.xMin, cords.yMin, cords.xMax, cords.yMax);
    mesh = std::make_unique<Mesh>(quad.vertices, quad.indices);
}

void TitleBar::Initialize() {
    LONG style = GetWindowLong(hwnd, GWL_STYLE);

    style &= ~WS_CAPTION;
    style &= ~WS_THICKFRAME;

    SetWindowLong(hwnd, GWL_STYLE, style);

    SetWindowPos(
        hwnd,nullptr,
        0,0,
        0,0,SWP_NOMOVE | SWP_NOSIZE |
        SWP_NOZORDER | SWP_FRAMECHANGED);
}

void TitleBar::Draw() const {
    shader.use();
    shader.setVec4("uColor", color.r, color.g, color.b, color.a);
    mesh->Draw();
}
