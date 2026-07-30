#pragma once
#include "Window.h"
#include <Windows.h>

class TitleBar {
    public:
        explicit TitleBar(Window& window);

        void Initialize();
    private:
    Window& window;
    HWND hwnd = nullptr;
};
