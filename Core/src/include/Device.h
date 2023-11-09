#pragma once
#include <vulkan\vulkan.hpp>
#include "QueueFlags.h"
#include "SwapChain.h"

class SwapChain;
class Instance;
class Device
{
	friend class Instance;
public:
	VULKAN_HPP_NODISCARD auto CreateSwapChain(VkSurfaceKHR surface, unsigned int numBuffers) ->SwapChain*;
	VULKAN_HPP_NODISCARD auto GetInstance() const noexcept-> Instance*;
	VULKAN_HPP_NODISCARD auto GetVkDevice() const noexcept-> VkDevice;
	VULKAN_HPP_NODISCARD auto GetQueue(QueueFlags flag) const noexcept->VkQueue;
	VULKAN_HPP_NODISCARD auto GetQueueIndex(QueueFlags flag) const noexcept -> unsigned int;
	
	
	auto CreatePhysicalDevice()->vk::PhysicalDevice*;

	~Device();


private:
	using Queues = std::array<VkQueue, sizeof(QueueFlags)>;
	Device() = delete;
	Device(Instance*, vk::Device, Queues);

	Instance* instance;
	VkDevice device;
	Queues queues;

	vk::PhysicalDevice& gpu;
	vk::UniqueSurfaceKHR surface;
	
};