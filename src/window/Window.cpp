#include "Window.h"
#include <glad/glad.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <iostream>
#include <stdexcept>


static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char *title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    HWND hwnd = glfwGetWin32Window(window);
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME);
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int fbWidth = 0, fbHeight = 0;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetGLFWWindow() const
{
    return window;
}

HWND Window::GetHWND() const {
    return glfwGetWin32Window(window);
}

void Window::BeginCaptionDrag() const {
    ReleaseCapture();
    SendMessage(GetHWND(), WM_NCLBUTTONDOWN, HTCAPTION, 0);
}
