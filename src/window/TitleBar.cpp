#include "TitleBar.h"
#include "AudioCapture.h"

TitleBar::TitleBar(Window& window, ShaderLink& shader, Cords cords, Color color, AudioPlayer* player)
    : window(window), shader(shader), textureShader(ShaderLink::Texture()), cords(cords), color(color)
{
    hwnd = window.GetHWND();
    QuadMesh quad = generateQuad(cords.xMin, cords.yMin, cords.xMax, cords.yMax);
    mesh = std::make_unique<Mesh>(quad.vertices, quad.indices);

    buttons.emplace_back(
        Cords{-0.99f, 0.92f, -0.70f, 0.99f},
        Texture("assets/icons/TitleText.png"),
        []() {}
    );

    buttons.emplace_back(
        Cords{0.95f, 0.91f, 0.99f, 0.99f},
        Texture("assets/icons/CloseIcon.png"),
        [window]() { glfwSetWindowShouldClose(window.GetGLFWWindow(), GLFW_TRUE); }
    );

    buttons.emplace_back(
        Cords{0.90f, 0.91f, 0.94f, 0.99f},
        Texture("assets/icons/PauseIcon.png"),
        [player]() { if (player) player->Pause(); }
    );

    buttons.emplace_back(
        Cords{0.85f, 0.91f, 0.89f, 0.99f},
        Texture("assets/icons/PlayIcon.png"),
        [player]() { if (player) player->Resume(); }
    );
    //ToDo
    buttons.emplace_back(
        Cords{0.80f, 0.91f, 0.84f, 0.99f},
        Texture("assets/icons/FileSelect.png"),
        []() {}
    );

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
    textureShader.use();

    for (auto& button : buttons) button.DrawButton(textureShader);
}

void TitleBar::HandleClick(float x, float y) {
    for (auto& button : buttons) {
        if (button.HitTest(x, y)) {
            button.Click();
            break;
        }
    }
}
