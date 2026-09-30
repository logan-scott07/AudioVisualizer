#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Windows.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void SwapBuffers() const;
    void PollEvents() const;
    bool ShouldClose() const;

    GLFWwindow* GetGLFWWindow() const;
    HWND GetHWND() const;
    void BeginCaptionDrag() const;

private:
    GLFWwindow* window = nullptr;
};
