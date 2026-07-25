add_library(shape_handling
        GenVert.cpp
        GenIndices.cpp)

target_include_directories(shape_handling PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include)