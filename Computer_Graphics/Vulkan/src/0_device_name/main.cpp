#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#define VkCheck(x) if(VK_SUCCESS != x){return VK_ERROR_UNKNOWN;}
int main()
{
    VkInstance instance;
    VkInstanceCreateInfo createInfo = {};
    VkCheck(vkCreateInstance(&createInfo, nullptr, &instance));

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        std::cerr << "No Vulkan-compatible devices found" << std::endl;
        return 1;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties deviceProps;
        vkGetPhysicalDeviceProperties(device, &deviceProps);
        std::cout << "Device Name: " << deviceProps.deviceName << std::endl;
        std::cout << "Device Type: " << deviceProps.deviceType << std::endl;
    }

    vkDestroyInstance(instance, nullptr);

    return 0;
}