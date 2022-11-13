cmake_minimum_required(VERSION 3.12)

if(WIN32)
	add_compile_definitions(DLL_EXPORT)
endif()
project(LibNgine VERSION 1.0)
add_library(LibNgine SHARED "src/Exception.cxx")
target_include_directories(LibNgine PRIVATE "include")
