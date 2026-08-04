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

using namespace std;

int main() {
    Window window;

    if (!window.Create(1200, 600, "AudioVisualizer")) {
        return -1;
    }
    SongSelect song;
    unique_ptr<AudioPlayer> player;
    optional<ShaderLink> shader;

    try {
        player = make_unique<AudioPlayer>(song.Open());
        shader.emplace(ShaderLink::Default());
    } catch (exception &e) {
        wcout << e.what() << endl;
        return -1;
    }


    TitleBar titleBar(window, (shader.value()),
        Cords{ -1.0f, 0.90f, 1.0f, 1.0f },
        Color{ .r = 0.15f, .g = 0.15f, .b = 0.2f, .a = 1.0f });

    titleBar.Initialize();

    vector<float> vertices = generateVertices();
    vector<unsigned int> indices = generateIndices();

    Mesh barMesh(vertices, indices);

    Button playPauseButton(shader.value(),
        Cords{ 0.80f, 0.80f, 0.95f, 0.95f },
        Color{ .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f });

    bool leftMouseWasDown = false;

    FFT fft(BUFFER_SIZE, NUM_BARS, SAMPLE_RATE);

    //render loop
    while (!window.ShouldClose()) {
        glClearColor(0.24f, 0.24f, 0.24f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int leftMouseState = glfwGetMouseButton(window.GetGLFWWindow(), GLFW_MOUSE_BUTTON_LEFT);
        bool leftMouseIsDown = (leftMouseState == GLFW_PRESS);

        if (leftMouseIsDown && !leftMouseWasDown && player) {
            double mouseX, mouseY;
            glfwGetCursorPos(window.GetGLFWWindow(), &mouseX, &mouseY);

            int width, height;
            glfwGetFramebufferSize(window.GetGLFWWindow(), &width, &height);

            float ndcX = static_cast<float>(mouseX) / width * 2.0f - 1.0f;
            float ndcY = 1.0f - static_cast<float>(mouseY) / height * 2.0f;

            if (playPauseButton.Contains(ndcX, ndcY)) {
                if (player->IsPlaying())
                    player->Pause();
                else
                    player->Resume();
            }

        }
        leftMouseWasDown = leftMouseIsDown;

        if (player) {
            vector<float> samples = player->getSamples();
            vector<float> barHeights = fft.process(samples);
            updateBarHeights(vertices, barHeights);
            barMesh.UpdateVertices(vertices);
        }

        shader->use();
        titleBar.Draw();
        barMesh.Draw();
        playPauseButton.Draw();

        window.SwapBuffers();
        window.PollEvents();
    }

    //clean-up
    window.Destroy();

    return 0;
}