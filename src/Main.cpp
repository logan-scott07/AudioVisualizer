//Standard
#include <iostream>
#include <memory>
#include <optional>
// OpenGL / Window Rendering
#include "Shaders.h"
#include "Window.h"
#include "Mesh.h"
#include "ShaderLink.h"
#include "GenVert.h"
#include "GenIndices.h"
#include "Button.h"
#include "TitleBar.h"
// Audio
#include "AudioCapture.h"
#include "SongSelect.h"
#include "FFT.h"


int main() {
    Window window(1200, 600, "AudioVisualizer");

    SongSelect song;
    std::unique_ptr<AudioPlayer> player;
    std::optional<ShaderLink> shader;

    try {
        player = std::make_unique<AudioPlayer>(song.Open());
        shader.emplace(ShaderLink::Default());
    } catch (std::exception &e) {
        std::wcout << e.what() << std::endl;
        return -1;
    }

    TitleBar titleBar(window, (shader.value()),
        Cords{ -1.0f, 0.90f, 1.0f, 1.0f },
        Color{ .r = 0.15f, .g = 0.15f, .b = 0.2f, .a = 1.0f },
        player.get());

    std::vector<float> vertices = generateVertices();
    std::vector<unsigned int> indices = generateIndices();

    Mesh barMesh(vertices, indices);

    bool leftMouseWasDown = false;

    FFT fft(FFT_SIZE, NUM_BARS, SAMPLE_RATE);

    //render loop
    while (!window.ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (player) {
            std::vector<float> samples = player->getSamples();
            std::vector<float> barHeights = fft.process(samples);
            updateBarHeights(vertices, barHeights);
            barMesh.UpdateVertices(vertices);
        }

        titleBar.Draw();
        shader->use();
        shader->setVec4("uColor", 0.45f, 0.42f, 0.55f, 1.0f);
        barMesh.Draw();

        window.SwapBuffers();
        window.PollEvents();

        int fbWidth, fbHeight;
        glfwGetWindowSize(window.GetGLFWWindow(), &fbWidth, &fbHeight);
        double mouseX, mouseY;
        glfwGetCursorPos(window.GetGLFWWindow(), &mouseX, &mouseY);
        bool leftMouseIsDown = glfwGetMouseButton(window.GetGLFWWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        if (leftMouseIsDown && !leftMouseWasDown && fbWidth > 0 && fbHeight > 0) {
            float ndcX = static_cast<float>(mouseX) / static_cast<float>(fbWidth) * 2.0f - 1.0f;
            float ndcY = 1.0f - static_cast<float>(mouseY) / static_cast<float>(fbHeight) * 2.0f;
            titleBar.HandleClick(ndcX, ndcY);
        }
        leftMouseWasDown = leftMouseIsDown;
    }

    return 0;
}