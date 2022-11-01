# Ngine-Standalone
My personal game engine that supports both Windows and GNU/Linux

## About project
Ngine is game engine that I'm building for my game. Engine supports both 64-bit windows and 64-bit linux (although windows is my priority for now so 
updates for linux might be delayed). On windows Ngine uses DirectX 12 API and VulkanAPI for Linux.

## Building on Windows
To build project on Windows make sure that:
- Your GPU supports DirectX 12
- You have installed vcpkg
- You have Visual Studio 2022 (might also work with any other IDEs but these instructions are only for this IDE)
- You have Windows 10 or newer
- You have CMake 3.1 or newer

Then download following packages from vcpkg
- d3dx12:x64-windows

After that download the project, unpack it, then on folder containing CMakeLists.txt click with right mouse button then select open in Visual Studio and then press 
Ctrl+Shift+B and project should start compiling
