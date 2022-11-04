#include "Window.hxx"
#include "Exception.hxx"
#include <GLFW/glfw3.h>

Ngine::Window::Window(unsigned int width, unsigned int height, char* name) {
    if(!glfwInit())
        throw Ngine::Exception(__LINE__, __FILE__, "Failed to initialize GLFW");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    hWnd = glfwCreateWindow(width, height, (const char*)name, nullptr, nullptr);

    if(!hWnd)
        throw Ngine::Exception(__LINE__, __FILE__, "Failed to create window");
}

Ngine::Window::~Window() {
    glfwDestroyWindow(hWnd);
    glfwTerminate();
}

std::optional<int> Ngine::Window::ProcessMessage() noexcept {
    glfwPollEvents();
    if(glfwWindowShouldClose(hWnd))
        return 0;

    return {};
}