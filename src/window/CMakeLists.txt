find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_library(window
        Window.cpp
        TitleBar.cpp
)

target_include_directories(window PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(window
        PRIVATE
        glfw
        glad::glad
        gl_abstractions
        shape_handling
)