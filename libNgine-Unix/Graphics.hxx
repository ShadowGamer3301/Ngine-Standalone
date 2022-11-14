#include "Window.hxx"
#include <vector>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

namespace Ngine {
    class Graphics {
    public:
        Graphics(Ngine::Window&);
        ~Graphics();
        Graphics(const Graphics&) = delete;
        Graphics operator=(const Graphics&) = delete;

    private:
        //Class members
        VkInstance m_vkinstance;
        VkDevice m_device;
        VkDebugUtilsMessengerEXT m_debugMessenger;

        //Class methods
        bool CheckInstanceLayersSupport();
        std::vector<const char*> GetRequiredExtensions();
    };
}