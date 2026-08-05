# AudioVisualizer

AudioVisualizer is a real-time audio visualization application written in modern C++. The project uses OpenGL for rendering, performs FFT-based audio analysis, and is being developed as a modular graphics application with reusable rendering and UI components.

## Overview

The project captures live audio, performs frequency analysis using Fast Fourier Transform (FFT), and renders the results with a modern OpenGL pipeline. Development has expanded beyond a basic visualizer to include reusable graphics abstractions, texture support, and a foundation for interactive UI elements.

## Technologies

- C++20
- CMake
- OpenGL 3.3
- GLFW
- GLAD
- MiniAudio
- KissFFT
- stb_image

## Project Structure

```
AudioVisualizer/
├── src/
│   ├── audio/
│   │   ├── AudioCapture
│   │   ├── FFT
│   │   └── SongSelect
│   │
│   ├── gl_abstractions/
│   │   ├── ShaderLink
│   │   ├── Mesh
│   │   ├── Texture
│   │   └── Button
│   │
│   ├── shape_handling/
│   │   ├── GenQuad
│   │   ├── GenVert
│   │   └── GenIndices
│   │
│   ├── window/
│   │   ├── Window
│   │   └── TitleBar
│   │
│   └── Main.cpp
│
├── resources/
├── CMakeLists.txt
└── README.md
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

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Goals

This project serves as an opportunity to deepen experience in:

- Modern C++
- Graphics programming
- OpenGL
- Digital signal processing
- Software architecture
- Real-time rendering
- Interactive application development