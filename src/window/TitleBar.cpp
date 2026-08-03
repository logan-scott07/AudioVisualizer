#include "TitleBar.h"
#include "Shaders.h"

TitleBar::TitleBar(Window &window, float xMin, float yMin, float xMax, float yMax)
    : window(window),xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax) {
    hwnd = window.GetHWND();

    std::vector<float> vertices {
        xMax, yMax, 0.0f,  // top right
        xMax, yMin, 0.0f,  // bottom right
        xMin, yMin, 0.0f,  // bottom left
        xMin, yMax, 0.0f,  // top left
    };
    std::vector<unsigned int> indices { 0, 1, 3, 1, 2, 3};

    mesh = std::make_unique<Mesh>(vertices, indices);
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
    shader->use();
    shader->setVec4("color", 0.15f, 0.15f, 0.15f, 1.0f);
    mesh->Draw();
}
