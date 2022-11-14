#include "Graphics.hxx"
#include "Exception.hxx"
#include "Window.hxx"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <cstring>

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
    if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        //Message is importan enought to show
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    }
    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance inst, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(inst, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr)
        return func(inst, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance inst, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(inst, "vkDestroyDebugUtilsMessengerEXT");
    if(func != nullptr)
        func(inst, debugMessenger, pAllocator);
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

Ngine::Graphics::Graphics(Ngine::Window& wnd) {
    //Check if computer supports validation layers
    if(!CheckInstanceLayersSupport() && enableValidationLayers)
        throw Ngine::Exception(__LINE__, __FILE__, "This computer does not support validation layers!");

    //Define information about application
    VkApplicationInfo app_nfo = {};
    app_nfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_nfo.apiVersion = VK_API_VERSION_1_3;
    app_nfo.pApplicationName = "";
    app_nfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    app_nfo.pEngineName = "Ngine";
    app_nfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    
    //Get required insteance extensions
    auto extensions = GetRequiredExtensions();

    //Define information about Vulkan instance
    VkInstanceCreateInfo inst_nfo = {};
    inst_nfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_nfo.pApplicationInfo = &app_nfo;
    inst_nfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    inst_nfo.ppEnabledExtensionNames = extensions.data();

     //If we are in debug build enable all validation layers
    if(enableValidationLayers) {
        inst_nfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        inst_nfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        inst_nfo.enabledLayerCount = 0;
    }

    //Create instance with provided info
    //If vkCreateInstance fails throw an exception
    VkResult res = vkCreateInstance(&inst_nfo, nullptr, &m_vkinstance);
    if(res != VK_SUCCESS)
        throw Ngine::Exception(__LINE__, __FILE__, "Failed to create vulkan instance");

    if(enableValidationLayers) {
        //Setup debug messenger
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)debugCallback;

        if(CreateDebugUtilsMessengerEXT(m_vkinstance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
            throw Ngine::Exception(__LINE__, __FILE__, "Failed to set up debug messenger");

        
    }
}

Ngine::Graphics::~Graphics() {
    DestroyDebugUtilsMessengerEXT(m_vkinstance, m_debugMessenger, nullptr);
    vkDestroyInstance(m_vkinstance, nullptr);
}

bool Ngine::Graphics::CheckInstanceLayersSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> avaliableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

    for(const char* layerName : validationLayers) {
        bool layerFound = false;

        for(const auto& layerProp : avaliableLayers) {
            if(std::strcmp(layerName, layerProp.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if(!layerFound)
            return false;
    }

    return true;
}

std::vector<const char*> Ngine::Graphics::GetRequiredExtensions() {
    uint32_t extensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);

    if(enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

