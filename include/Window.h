#pragma once
#include "Macro.h"
#include "Exception.h"

#ifdef _WIN32
#include <GLFW/glfw3.h>

namespace Ngine
{
	class NAPI Window
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

		void StartFrame();
		void EndFrame();

		inline bool KillWindow() { return glfwWindowShouldClose(hWnd); }

	private:
		GLFWwindow* hWnd;
	};
}
#elif defined __linux__
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


#endif