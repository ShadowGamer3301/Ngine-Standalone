#include "Graphics.hxx"
#include "Exception.hxx"
#include "Window.hxx"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <vulkan/vulkan_core.h>

Ngine::Graphics::Graphics(Ngine::Window& wnd) {

    VkApplicationInfo app_nfo = {};
    app_nfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_nfo.apiVersion = VK_API_VERSION_1_1;
    app_nfo.pApplicationName = "";
    app_nfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    app_nfo.pEngineName = "Ngine";
    app_nfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    
    uint32_t glfwExtensionCount = 0;
    const char** extensionNames;
    extensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo inst_nfo = {};
    inst_nfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_nfo.pApplicationInfo = &app_nfo;
    inst_nfo.enabledExtensionCount = glfwExtensionCount;
    inst_nfo.ppEnabledExtensionNames = extensionNames;
    inst_nfo.enabledLayerCount = 0; //This will be changed later

    VkResult res = vkCreateInstance(&inst_nfo, nullptr, &m_vkinstance);
    if(res != VK_SUCCESS)
        throw Ngine::Exception(__LINE__, __FILE__, "Failed to create vulkan instance");
}

Ngine::Graphics::~Graphics() {
    vkDestroyInstance(m_vkinstance, nullptr);
}