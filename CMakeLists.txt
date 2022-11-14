cmake_minimum_required(VERSION 3.12)

#Add project definitions
project(Ngine VERSION 1.0)

#Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Ngine SHARED "src/Exception.cxx" "src/Window.cxx"  "src/Timer.cxx")

if(WIN32)
	#Add required compile definitions for all platforms
	add_compile_definitions(DLL_EXPORT)
	#Add required libraries libraries
	#Vendor folder is for windows only since on GNU/Linux all libraries can be found in package manager :)
	target_include_directories(Ngine PRIVATE "include" "vendor/include")
	target_link_directories(Ngine PRIVATE "vendor/WIN-Lib")
	target_link_libraries(Ngine PRIVATE "glfw3.lib")
elseif(UNIX)
	target_include_directories(Ngine PRIVATE "include")
	target_link_libraries(Ngine PRIVATE "libglfw.so")
endif()


