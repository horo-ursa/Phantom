#pragma once
#include <vulkan\vulkan.hpp>
#include <bitset>
#include <vector>
#include <vulkan/vulkan.h>
#include "QueueFlags.h"
#include "Device.h"



extern const bool ENABLE_VALIDATION;

class Instance {

public:
    Instance() = delete;
    Instance(const char* applicationName, unsigned int additionalExtensionCount = 0, const char** additionalExtensions = nullptr);

    auto GetVkInstance() const noexcept -> VkInstance;
    auto GetPhysicalDevice() const noexcept -> VkPhysicalDevice;
    auto GetQueueFamilyIndices() const -> const QueueFamilyIndices&;
    auto GetSurfaceCapabilities() const -> const VkSurfaceCapabilitiesKHR&;
    auto GetSurfaceFormats() const -> const std::vector<VkSurfaceFormatKHR>&;
    auto GetPresentModes() const -> const std::vector<VkPresentModeKHR>&;

    auto GetMemoryTypeIndex(uint32_t types, VkMemoryPropertyFlags properties) const ->uint32_t;
    auto GetSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const ->VkFormat;

    void PickPhysicalDevice(std::vector<const char*> deviceExtensions, QueueFlagBits requiredQueues, VkSurfaceKHR surface = VK_NULL_HANDLE);

    auto CreateDevice(QueueFlagBits requiredQueues, VkPhysicalDeviceFeatures deviceFeatures) ->Device*;

    ~Instance();

private:

    void initDebugReport();

    VkInstance instance;
    VkDebugReportCallbackEXT debugReportCallback;
    std::vector<const char*> deviceExtensions;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    QueueFamilyIndices queueFamilyIndices;
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> surfaceFormats;
    std::vector<VkPresentModeKHR> presentModes;
    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
};