# AudioVisualizer

A lightweight C++ audio visualization project using modern OpenGL.

## Overview

Project renders real-time audio visualizations using C++, OpenGL, and supporting libraries.  
The goal is to create a simple foundation for experimenting with graphics, audio processing, and shader-based visual effects.

## Tools and Technologies

- C++20  
- CMake  
- OpenGL (graphics)
- GLAD (OpenGL function loading)  
- Conan (dependency management)  
- MiniAudio (audio capture)

## Project Structure

AudioVisualizer/  
├── src/<br>
│   ├── audio/<br>
│   ├── gl_abstractions/<br>
│   ├── shape_handling/<br>
│   ├── window/<br>
│   └── main.cpp<br>
│── CMakeLists.txt<br> 
└── README.md  

## Features (Planned / Implemented)

- [x] Basic window creation  
- [x] OpenGL context setup  
- [x] Audio input capture  
- [ ] FFT processing  
- [x] Simple bar visualization  
- [ ] Shader-based effects  

## Tutorials and Resources Used

- LearnOpenGL (Joey de Vries) [https://learnopengl.com/book/book_pdf.pdf](https://learnopengl.com/book/book_pdf.pdf)
- Project Setup [https://www.youtube.com/@codingwithmat](https://www.youtube.com/@codingwithmat)
- MiniAudio documentation [https://miniaud.io/docs/manual/index.html](https://miniaud.io/docs/manual/index.html)
- GLFW documentation  
- CMake and Conan documentation  
- Shader examples from various graphics resources  


