cmake_minimum_required(VERSION 4.1)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(AudioVisualizer main.cpp)

target_link_libraries(AudioVisualizer
        PRIVATE
        glfw
        GLEW::GLEW
        fmt::fmt
        opengl::opengl
        glad::glad)