add_executable(AudioVisualizer
        main.cpp
)

add_subdirectory(gl_abstractions)

target_link_libraries(AudioVisualizer
        PRIVATE
        gl_abstractions
        glfw
        opengl::opengl
        glad::glad)