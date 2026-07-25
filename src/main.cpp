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
// Audio
#include "AudioCapture.h"
#include "SongSelect.h"
#include "FFT.h"

int main() {

    SongSelect dlg;
    std::unique_ptr<AUDIO_PLAYER> player;

    if (dlg.Open()) {
        std::string path = dlg.GetFilePath();
        player = std::make_unique<AUDIO_PLAYER>(path);
    } else {
        std::wcout << L"Dialog cancelled or failed." << std::endl;
    }

    GLFWwindow* window = create_window(1200, 500, "AudioVisualizer");

    std::string vertex_source = get_shader_source(std::string(SHADER_DIR) + "/default.vert");
    GLuint vertexShader;
    if (!(compile_shader(vertexShader, vertex_source, GL_VERTEX_SHADER))) {
        std::cout << "Vertex shader compilation failed." << std::endl;
        return -1;
    }

    std::string fragment_source = get_shader_source(std::string(SHADER_DIR) + "/default.frag");
    GLuint fragmentShader;
    if (!(compile_shader(fragmentShader, fragment_source, GL_FRAGMENT_SHADER))) {
        std::cout << "Fragment shader compilation failed." << std::endl;
        return -1;
    }

    ShaderLink shader_link(vertexShader, fragmentShader);

    std::vector<float> vertices = generateVertices();
    std::vector<unsigned int> indices = generateIndices();
    Mesh barMesh(vertices, indices);

    FFT fft(BUFFER_SIZE, NUM_BARS, SAMPLE_RATE);

    //render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.24f, 0.24f, 0.24f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (player) {
            std::vector<float> samples = player->getSamples();
            std::vector<float> barHeights = fft.process(samples);
            updateBarHeights(vertices, barHeights);
            barMesh.updateVertices(vertices);
        }

        shader_link.use();
        barMesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //clean-up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}