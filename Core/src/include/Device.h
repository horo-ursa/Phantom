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

		/**
		* @bridf get physical device
		*/
		VULKAN_HPP_NODISCARD
		auto get_gpu() const -> const pt::PhysicalDevice;

		/**
		* @bridf get memory allocater
		*/
		VULKAN_HPP_NODISCARD
		auto get_memory_allocator() const -> const  VmaAllocator;


	private:

		PhysicalDevice gpu;
		vk::UniqueSurfaceKHR surface;
		VmaAllocator memory_allocator{ VK_NULL_HANDLE };
		vk::UniqueDevice dv;


		std::vector<const char*> enabled_extensions{};
	
	};
}