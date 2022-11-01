cmake_minimum_required(VERSION 3.1)

#Make libNgine project
#For Windows project will produce .lib and .dll file
#For Linux and Unix systems project will produce .lib and .so file

project(libNgine VERSION 1.0)
if(WIN32)
	add_compile_definitions(_DLL)
	add_library(libNgine SHARED "libNgine-Win32/Exception.cxx")
endif()