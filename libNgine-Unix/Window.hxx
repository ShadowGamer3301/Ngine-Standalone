#pragma once 
#include "Macro.hxx"
#include "Exception.hxx"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

namespace Ngine{
    class Window {
    public:
        Window(unsigned int width, unsigned int height, char* name);
        ~Window();
        Window(const Window&) = delete;
        Window operator=(const Window&) = delete;

        std::optional<int> ProcessMessage() noexcept;
    private:
        GLFWwindow* hWnd;
    };
}