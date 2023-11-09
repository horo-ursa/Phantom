#include "Device.h"
#include "Instance.h"
#include "SwapChain.h"

namespace pt {
    Device::Device(PhysicalDevice& gpu,
        vk::SurfaceKHR                         surface,
        std::unordered_map<const char*, bool>  requested_extensions)
        : VulkanResource{ VK_NULL_HANDLE, this }
        , gpu{ gpu }
    {

    }
}