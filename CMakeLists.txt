cmake_minimum_required(VERSION 4.1)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
    message(FATAL_ERROR "This project currently only supports Windows.")
endif()

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

add_executable(AudioVisualizer ${SOURCES})

find_package(glfw3 REQUIRED)
find_package(opengl_system REQUIRED)
find_package(glad REQUIRED)
find_package(miniaudio REQUIRED)
find_package(kissfft REQUIRED)
find_package(stb REQUIRED)

target_link_libraries(AudioVisualizer
        PRIVATE
        glfw
        opengl::opengl
        glad::glad
        miniaudio::miniaudio
        kissfft::kissfft
        stb::stb
)

target_include_directories(AudioVisualizer PRIVATE
        src/audio/include
        src/gl_abstractions/include
        src/shape_handling/include
        src/window/include
)

target_compile_definitions(AudioVisualizer PRIVATE UNICODE _UNICODE)
target_compile_definitions(AudioVisualizer PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/src/gl_abstractions/include")

add_custom_command(TARGET AudioVisualizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:AudioVisualizer>/assets
)

