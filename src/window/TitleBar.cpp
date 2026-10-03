#include "Window.h"
#include "TitleBar.h"
#include "AudioCapture.h"
#include "SongSelect.h"

TitleBar::TitleBar(Window& window, ShaderLink& shader, Cords cords, Color color, AudioPlayer* player)
    : window(window), shader(shader), textureShader(ShaderLink::Texture()), cords(cords), color(color), player(player)
{
    QuadMesh quad = generateQuad(cords.xMin, cords.yMin, cords.xMax, cords.yMax);
    mesh = std::make_unique<Mesh>(quad.vertices, quad.indices);

    buttons.emplace_back(
        Cords{-0.99f, 0.92f, -0.70f, 0.99f},
        Texture("assets/icons/TitleText.png"),
        []() {},
        false
    );

    buttons.emplace_back(
        Cords{0.95f, 0.91f, 0.99f, 0.99f},
        Texture("assets/icons/CloseIcon.png"),
        [&window]() { glfwSetWindowShouldClose(window.GetGLFWWindow(), GLFW_TRUE); }
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

    buttons.emplace_back(
        Cords{0.80f, 0.91f, 0.84f, 0.99f},
        Texture("assets/icons/FileSelect.png"),
        [player, this]() {
            player->Pause();
            try {
                std::string filepath = song.Open();
                player->ChangeSong(filepath);
                player->Resume();
            } catch (std::exception&) {
                player->Resume();
            }
        }
    );

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
        if (button.IsInteractive() && button.HitTest(x, y)) {
            button.Click();
            return;
        }
    }

    if (x >= cords.xMin && x <= cords.xMax &&
        y >= cords.yMin && y <= cords.yMax) {
        if (player) player->Pause();
        window.BeginCaptionDrag();
    }
}
