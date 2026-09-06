# AudioVisualizer

AudioVisualizer is a real-time audio visualization application written in modern C++. The project uses OpenGL for rendering, performs FFT-based audio analysis, and is being developed as a modular graphics application with reusable rendering and UI components.

## Overview

The project captures live audio, performs frequency analysis using Fast Fourier Transform (FFT), and renders the results with a modern OpenGL pipeline. Development has expanded beyond a basic visualizer to include reusable graphics abstractions, texture support, and a foundation for interactive UI elements.

https://github.com/user-attachments/assets/c3ce08ab-dc3c-46b8-a825-7954e1313b5d

<video src="C:\Users\Logan\Downloads\ProjectExample.mp4" width="420" height="340" controls></video>

## Technologies

- C++20
- CMake
- Conan 2.x
- OpenGL 3.3
- GLFW
- GLAD
- MiniAudio
- KissFFT
- stb_image

## Project Structure

```
AudioVisualizer/
├── CMakeLists.txt
├── CMakePresets.json
├── conandata.yml
├── conanfile.py
├── README.md
├── assets/
│   └── icons/
│       ├── CloseIcon.png
│       ├── FileSelect.png
│       ├── PauseIcon.png
│       ├── PlayIcon.png
│       └── TitleText.png
└── src/
    ├── Main.cpp
    ├── audio/
    │   ├── AudioCapture.cpp
    │   ├── FFT.cpp
    │   ├── SongSelect.cpp
    │   └── include/
    │       ├── AudioCapture.h
    │       ├── FFT.h
    │       └── SongSelect.h
    ├── gl_abstractions/
    │   ├── Mesh.cpp
    │   ├── ShaderLink.cpp
    │   ├── Shaders.cpp
    │   ├── StbImage.cpp
    │   └── include/
    │       ├── Button.h
    │       ├── Mesh.h
    │       ├── ShaderLink.h
    │       ├── Shaders.h
    │       ├── Texture.h
    │       ├── default.frag
    │       ├── default.vert
    │       ├── texture.frag
    │       └── texture.vert
    ├── shape_handling/
    │   ├── GenIndices.cpp
    │   ├── GenQuad.cpp
    │   ├── GenVert.cpp
    │   └── include/
    │       ├── GenIndices.h
    │       ├── GenQuad.h
    │       └── GenVert.h
    └── window/
        ├── TitleBar.cpp
        ├── Window.cpp
        └── include/
            ├── TitleBar.h
            └── Window.h
```

## Current Features

- Real-time audio capture
- FFT-based frequency analysis
- OpenGL rendering pipeline
- Dynamic audio bar visualization
- Modular shader management
- Mesh abstraction layer
- Texture loading using stb_image
- Interactive button framework
- Custom window and title bar classes
- Modular project architecture

## Current Status

The project is currently focused on expanding the rendering framework while improving the user interface and overall architecture. Recent work has centered around separating rendering logic into reusable components, adding texture support, and building a foundation for interactive UI elements.

## Planned Improvements

- UI polish and interaction improvements
- Configurable application settings
- Additional shader effects
- Performance optimization

## Building

> **Note:** Currently Windows-only due to WIN32-specific code (cross-platform support planned).

### Prerequisites

1. **Visual Studio 2022 Build Tools** with the "Desktop development with C++" workload
   (provides the MSVC compiler required by this project's Conan profile)
2. **CMake** (v3.23 or higher)
3. **Conan 2.x** (`pip install conan`)
4. **Ninja** — bundled with VS Build Tools' "C++ CMake tools for Windows" component,
   or install standalone: `pip install ninja`

### Step 1: Detect Conan Profile (first-time setup only)

    conan profile detect --force

Open the generated profile at `%USERPROFILE%\.conan2\profiles\default` and confirm
`compiler=msvc` is set (Conan usually detects this correctly on Windows by default).

### Step 2: Install Dependencies

Run once per build type you want to use:

    conan install . --output-folder=conan --build=missing -s build_type=Debug
    conan install . --output-folder=conan --build=missing -s build_type=Release

This builds/downloads all dependencies and writes a Conan toolchain file
that `CMakePresets.json` (committed in this repo) already knows how to find.

### Step 3: Configure, Build, and Run

#### Option A: Command Line

    cmake --preset conan-debug
    cmake --build --preset conan-debug

Run: `.\cmake-build-debug\AudioVisualizer.exe`

#### Option B: IDE (CLion, Visual Studio 2022, VS Code)

Open the project root folder — your IDE should auto-detect `CMakePresets.json`
and offer `conan-debug` / `conan-release` as selectable configurations.
No IDE plugin or extra setup required beyond Step 1–2 above.
## Goals

This project serves as an opportunity to deepen experience in:

- Modern C++
- Graphics programming
- OpenGL
- Digital signal processing
- Software architecture
- Real-time rendering
- Interactive application development
