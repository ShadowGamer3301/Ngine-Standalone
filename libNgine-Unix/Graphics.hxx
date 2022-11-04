#include "Window.hxx"
#include <vulkan/vulkan_core.h>

namespace Ngine {
    class Graphics {
    public:
        Graphics(Ngine::Window&);
        ~Graphics();
        Graphics(const Graphics&) = delete;
        Graphics operator=(const Graphics&) = delete;


    private:
        VkInstance m_vkinstance;
    };
}