#include "Device.h"
#include "Instance.h"
#include "SwapChain.h"

Device::Device(Instance* instance, vk::Device vkDevice, Queues queues)
    : instance(instance), device(vkDevice), queues(queues) {
}

auto Device::GetInstance() const noexcept -> Instance* {
    return instance;
}

auto Device::GetVkDevice() const noexcept -> VkDevice {
    return device;
}

auto Device::GetQueue(QueueFlags flag) const noexcept -> VkQueue {
    return queues[flag];
}

auto Device::GetQueueIndex(QueueFlags flag) const noexcept -> unsigned int {
    return GetInstance()->GetQueueFamilyIndices()[flag];
}

auto Device::CreateSwapChain(VkSurfaceKHR surface, unsigned int numBuffers) -> SwapChain* {
    return new SwapChain(this, surface, numBuffers);
}

Device::~Device() {
    vkDestroyDevice(device, nullptr);
}
