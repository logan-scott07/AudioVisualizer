cmake_minimum_required(VERSION 4.1)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(fmt REQUIRED)
find_package(opengl_system REQUIRED)
find_package(glad REQUIRED)


add_subdirectory(src)
