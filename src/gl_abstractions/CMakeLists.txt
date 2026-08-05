find_package(glad REQUIRED)
find_package(stb REQUIRED)

add_library(gl_abstractions
        Shaders.cpp
        Mesh.cpp
        ShaderLink.cpp
        StbImage.cpp
        include/Texture.h
)
target_include_directories(gl_abstractions PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(gl_abstractions PUBLIC
        SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(gl_abstractions
        PRIVATE
        glad::glad
        shape_handling
)
target_link_libraries(gl_abstractions
        PUBLIC
        stb::stb
)