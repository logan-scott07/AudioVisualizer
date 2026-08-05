cmake_minimum_required(VERSION 4.1)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(opengl_system REQUIRED)
find_package(glad REQUIRED)
find_package(miniaudio REQUIRED)
find_package(kissfft REQUIRED)
find_package(stb REQUIRED)

add_subdirectory(src)

