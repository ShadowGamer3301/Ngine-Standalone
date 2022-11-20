#include "Window.h"
#include <spdlog/spdlog.h>

#ifdef _WIN32

Ngine::Window::GLFWException::GLFWException(unsigned int line, std::string file, unsigned int code) : Exception(line, file), code(code)
{
}

const char* Ngine::Window::GLFWException::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception caught! \n"
		<< "[TYPE] " << GetType() << "\n"
		<< "[LINE] " << GetLine() << "\n"
		<< "[FILE] " << GetFile() << "\n"
		<< "[CODE] " << std::hex << GetCode() << std::dec << "\n";

	wBuffer = oss.str();
	return wBuffer.c_str();
}

const char* Ngine::Window::GLFWException::GetType() const noexcept
{
	return "GLFW Exception";
}

int Ngine::Window::GLFWException::GetCode() const noexcept
{
	return code;
}

Ngine::Window::Window(uint32_t width, uint32_t height, const char* title, bool fullscreen)
{
	spdlog::info("Using GLFW3: Copyright (c) 2002-2006 Marcus Geelnard, Copyright (c) 2006-2019 Camilla Lowy");

	if (glfwInit() == GL_FALSE)
		throw GLFWException(__LINE__, __FILE__, glfwGetError(nullptr));
	/*
		Disable OpenGL backwards compatibility
		Set OpenGL version to 4.1
	*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	if(!fullscreen)
		hWnd = glfwCreateWindow(width, height, title, nullptr, nullptr);
	else	
		hWnd = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);

	if(!hWnd)
		throw GLFWException(__LINE__, __FILE__, glfwGetError(nullptr));

	glfwMakeContextCurrent(hWnd);
}

Ngine::Window::~Window()
{
}

void Ngine::Window::StartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.6, 1.0);
	glfwPollEvents();
}

void Ngine::Window::EndFrame()
{
	glfwSwapBuffers(hWnd);
}

#elif __linux__

Ngine::Window::GLFWException::GLFWException(unsigned int line, std::string file, unsigned int code) : Exception(line, file), code(code)
{
}

const char* Ngine::Window::GLFWException::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception caught! \n"
		<< "[TYPE] " << GetType() << "\n"
		<< "[LINE] " << GetLine() << "\n"
		<< "[FILE] " << GetFile() << "\n"
		<< "[CODE] " << std::hex << GetCode() << std::dec << "\n";

	wBuffer = oss.str();
	return wBuffer.c_str();
}

const char* Ngine::Window::GLFWException::GetType() const noexcept
{
	return "GLFW Exception";
}

int Ngine::Window::GLFWException::GetCode() const noexcept
{
	return code;
}

Ngine::Window::Window(uint32_t width, uint32_t height, const char* title, bool fullscreen)
{
	spdlog::info("Using GLFW3: Copyright (c) 2002-2006 Marcus Geelnard, Copyright (c) 2006-2019 Camilla Löwy");

	if (glfwInit() == GL_FALSE)
		throw GLFWException(__LINE__, __FILE__, glfwGetError(nullptr));
	/*
		Disable OpenGL backwards compatibility
		Set OpenGL version to 4.1
	*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);

	if(!fullscreen)
		hWnd = glfwCreateWindow(width, height, title, nullptr, nullptr);
	else	
		hWnd = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);


}

Ngine::Window::~Window()
{
}

#endif