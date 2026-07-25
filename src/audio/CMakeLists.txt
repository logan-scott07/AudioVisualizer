find_package(miniaudio REQUIRED)

add_library(audio
        AudioCapture.cpp
        include/SongSelect.h
        SongSelect.cpp
)

target_include_directories(audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(audio
        PRIVATE
        miniaudio::miniaudio
)

target_compile_definitions(audio PRIVATE UNICODE _UNICODE)