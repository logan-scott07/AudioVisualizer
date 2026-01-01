find_package(glad REQUIRED)

add_library(gl_abstractions
        shaders.cpp
        mesh.cpp
        shader_link.cpp
)

target_include_directories(gl_abstractions
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gl_abstractions
        PRIVATE
            glad::glad
)