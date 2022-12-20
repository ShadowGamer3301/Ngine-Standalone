#pragma once
#include "Exception.h"
#include <GLFW/glfw3.h>

namespace Ngine
{
	class Window
	{
	public:
		class GLFWException : public Ngine::Exception
		{
		public:
			GLFWException(unsigned int line, std::string file, unsigned int code);
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			int GetCode() const noexcept;

		private:
			unsigned int code;
		};

	public:
		Window(uint32_t width, uint32_t height, const char* title, bool fullscreen);
		~Window();

		inline bool KillWindow() const noexcept { return glfwWindowShouldClose(hWnd); }

	private:
		GLFWwindow* hWnd;
	};
}
