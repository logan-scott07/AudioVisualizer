add_executable(AudioVisualizer
        main.cpp
)

add_subdirectory(gl_abstractions)
add_subdirectory(window)

target_link_libraries(AudioVisualizer
        PRIVATE
        gl_abstractions
        window
        glfw
        opengl::opengl
        glad::glad)