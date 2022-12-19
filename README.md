![Ngine-Standalone](/Logo.png?raw=true "Ngine")

# Ngine-Standalone
My personal game engine that supports both Windows and GNU/Linux

## About project
Ngine is game engine that I'm building for my game. Engine supports 64-bit linux On for now engine uses OpenGL graphics library.
## Building on Windows
Currently we are dropping Windows support
Windows build will became separate repository

## Building on GNU/Linux
To build project on GNU/Linux make sure that:
- Your GPU supports OpenGL 4.1 or higher
- You have glfw3 glew installed
- You have C++ compiler that supports C++20
- You have CMake 3.12 or newer


After that download the project, unpack it, then on folder containing CMakeLists.txt open terminal there and type "cmake -B out" and cmake should build your
project files
