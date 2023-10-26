#pragma once
#include <vulkan\vulkan.hpp>
#include <vulkan\vulkan.h>
#include <vector>
#include "Device.h"

class Device;
class SwapChain {
    friend class Device;

public:
    auto GetVkSwapChain() const -> VkSwapchainKHR;
    auto GetVkImageFormat() const ->VkFormat;
    auto GetVkExtent() const ->VkExtent2D;
    auto GetIndex() const -> uint32_t;
    auto GetCount() const ->uint32_t;
    auto GetVkImage(uint32_t index) const -> VkImage;
    auto GetImageAvailableVkSemaphore() const ->VkSemaphore;
    auto GetRenderFinishedVkSemaphore() const ->VkSemaphore;

    void Recreate();
    bool Acquire();
    bool Present();
    ~SwapChain();

private:
    SwapChain(Device* device, VkSurfaceKHR vkSurface, unsigned int numBuffers);
    void Create();
    void Destroy();

    Device* device;
    VkSurfaceKHR vkSurface;
    unsigned int numBuffers;
    VkSwapchainKHR vkSwapChain;
    std::vector<VkImage> vkSwapChainImages;
    VkFormat vkSwapChainImageFormat;
    VkExtent2D vkSwapChainExtent;
    uint32_t imageIndex = 0;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
};
