add_executable(AudioVisualizer
        main.cpp
)

add_subdirectory(gl_abstractions)
add_subdirectory(window)
add_subdirectory(shape_handling)
add_subdirectory(audio)

target_link_libraries(AudioVisualizer
        PRIVATE
        gl_abstractions
        window
        shape_handling
        audio
        glfw
        opengl::opengl
        glad::glad
        miniaudio::miniaudio
        kissfft::kissfft)