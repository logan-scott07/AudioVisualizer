#ifndef AUDIOVISUALIZER_WINDOW_H
#define AUDIOVISUALIZER_WINDOW_H
#include <glfw/glfw3.h>

//Handle window creation with one function
GLFWwindow* create_window(int width, int height, const char* title);

#endif //AUDIOVISUALIZER_WINDOW_H