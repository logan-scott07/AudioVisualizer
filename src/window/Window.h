#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Windows.h>

class Window {
    public:
    bool Create(int width, int height, const char *title);
        void Destroy();

        void SwapBuffers();
        void PollEvents();
        bool ShouldClose();

        GLFWwindow* GetGLFWWindow() const;
        HWND GetHWND() const;

    private:
        GLFWwindow* window = nullptr;
};
