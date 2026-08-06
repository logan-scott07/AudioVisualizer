#pragma once
#include "Window.h"
#include <memory>
#include "Mesh.h"
#include "ShaderLink.h"
#include "GenQuad.h"
#include <Windows.h>
#include "Button.h"
#include "SongSelect.h"

class AudioPlayer;

class TitleBar {
public:
    explicit TitleBar(Window& window, ShaderLink& shader, Cords cords, Color color, AudioPlayer* player = nullptr);
    void Initialize();
    void Draw() const;
    void HandleClick(float x, float y);
private:
    Window& window;
    ShaderLink& shader;
    ShaderLink textureShader;
    SongSelect song;
    HWND hwnd = nullptr;
    Cords cords;
    Color color;
    std::unique_ptr<Mesh> mesh;
    std::vector<Button> buttons;
};
