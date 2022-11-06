cmake_minimum_required(VERSION 3.1)

#Make libNgine project
#For Windows project will produce .lib and .dll file
#For Linux and Unix systems project will produce .lib and .so file

project(libNgine VERSION 1.0)
if(WIN32)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
	add_compile_definitions(_DLL UNICODE)
	add_library(libNgine SHARED "libNgine-Win32/Exception.cxx" "libNgine-Win32/Window.cxx" "libNgine-Win32/Graphics.cxx")
	find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(libNgine PRIVATE spdlog::spdlog_header_only "dxgi.lib" "d3d11.lib")
elseif(UNIX)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
	add_library(linNgine SHARED "libNgine-Unix/Exception.cxx" "libNgine-Unix/Window.cxx" "libNgine-Unix/Graphics.cxx")
	find_package(glfw3 CONFIG REQUIRED)
	find_package(Vulkan REQUIRED)
    target_link_libraries(linNgine PRIVATE glfw Vulkan::Vulkan)
endif()

project(testApp VERSION 1.0)
if(WIN32)
	add_executable(testApp  "testApp-Win32/main.cpp")
	target_include_directories(testApp PUBLIC "libNgine-Win32")
	target_link_libraries(testApp "libNgine.lib")
elseif(UNIX)
	add_executable(testApp "testApp-Unix/main.cpp")
	target_include_directories(testApp PUBLIC "libNgine-Unix")
	target_link_directories(testApp PUBLIC "out")
	target_link_libraries(testApp "liblinNgine.so")
endif()