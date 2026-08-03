//Standard
#include <iostream>
#include <memory>
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

    //Create window
    Window window;

    if (!window.Create(1200, 500, "AudioVisualizer")) {
        return -1;
    }

    TitleBar titleBar(window, 0.0f, 0.95f, 1.0f, 1.0f);

    titleBar.Initialize();

    //Song Selection/MiniAudio player creation
    SongSelect song;
    unique_ptr<AUDIO_PLAYER> player;

    if (song.Open()) {
        player = make_unique<AUDIO_PLAYER>(song.GetFilePath());
    } else {
        wcout << L"File Selection Closed or Failed.";
        return -1;
    }


    //Shader Setup
    GLuint vertexShader;
    GLuint fragmentShader;

    string vertex_source = get_shader_source(string(SHADER_DIR) + "/default.vert");
    string fragment_source = get_shader_source(string(SHADER_DIR) + "/default.frag");

    if (!(compile_shader(vertexShader, vertex_source, GL_VERTEX_SHADER))) {
        cout << "Vertex shader compilation failed." << endl;
        return -1;
    }

    if (!(compile_shader(fragmentShader, fragment_source, GL_FRAGMENT_SHADER))) {
        cout << "Fragment shader compilation failed." << endl;
        return -1;
    }

    ShaderLink shader_link(vertexShader, fragmentShader);

    vector<float> vertices = generateVertices();
    vector<unsigned int> indices = generateIndices();

    Mesh barMesh(vertices, indices);

    Button playPauseButton(0.80f, 0.80f, 0.95f, 0.95f);

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

        shader_link.use();
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