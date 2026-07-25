find_package(miniaudio REQUIRED)

add_library(audio
        AudioCapture.cpp
        SongSelect.cpp
        FFT.cpp
)

target_include_directories(audio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(audio
        PRIVATE
        miniaudio::miniaudio
        kissfft::kissfft
)

target_compile_definitions(audio PRIVATE UNICODE _UNICODE)