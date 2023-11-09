#pragma once
#include <vulkan\vulkan.hpp>
#include "QueueFlags.h"
#include "SwapChain.h"
#include "vk_mem_alloc.h"
#include "vulkan_resource.h"
#include "PhysicalDevice.h"
#include <unordered_map>

namespace pt {
	class Device : public VulkanResource<vk::Device>
	{
	public:

		Device(PhysicalDevice                         &gpu,
			   vk::SurfaceKHR                          surface,
			   std::unordered_map<const char*, bool>   requested_extensions = {});

		~Device();


	private:
		using Queues = std::array<VkQueue, sizeof(QueueFlags)>;
		Device() = delete;
		Device(Instance*, vk::Device, Queues);

		Instance* instance;
		VkDevice device;
		Queues queues;

		PhysicalDevice gpu;
		vk::UniqueSurfaceKHR surface;
		VmaAllocator memory_allocator{ VK_NULL_HANDLE };
		vk::UniqueDevice dv;


		std::vector<const char*> enabled_extensions{};
	
	};
}