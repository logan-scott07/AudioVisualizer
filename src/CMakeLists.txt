add_executable(AudioVisualizer main.cpp)

target_link_libraries(AudioVisualizer
        PRIVATE
        glfw
        opengl::opengl
        glad::glad)