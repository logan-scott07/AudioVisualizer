#include "Window.h"
#include <glad/glad.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <iostream>


static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool Window::Create(int width, int height, const char *title) {

    if (!glfwInit()) {
        std::cout << "Failed to create GLFW window";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void Window::Destroy() {
    glfwDestroyWindow(window);
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
