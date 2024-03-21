#pragma once
#include <vulkan\vulkan.hpp>
#include "QueueFlags.h"
#include "vk_mem_alloc.h"
#include "PhysicalDevice.h"
#include <unordered_map>
#include "logging.h"
#include "initializer.h"

namespace pt {
	class HPPDevice
	{
	private:

		HPPPhysicalDevice						gpu;
		vk::SurfaceKHR							surface{ nullptr };
		//VmaAllocator							memory_allocator{ VK_NULL_HANDLE };
		vk::Device								device;
		std::vector<vk::ExtensionProperties>	device_extensions;
		std::vector<std::vector<vk::Queue>>		queues;
		std::vector<const char*>				enabled_extensions{};
		/** @brief Default command pool for the graphics queue family index */
		vk::CommandPool							commandPool;

	public:

		struct queueFamilyIndices {
			uint32_t eGraphics;
			uint32_t eCompute;
			uint32_t eTransfer;
		};

		explicit HPPDevice(HPPPhysicalDevice           &gpu,
			   vk::SurfaceKHR                          surface,
			   std::unordered_map<const char*, bool>   requested_extensions = {});

		~HPPDevice();

		/** @bridf get physical device */
		VULKAN_HPP_NODISCARD
		const pt::HPPPhysicalDevice		get_gpu() const {return gpu;}
		VULKAN_HPP_NODISCARD
		vk::Device						get_handle() const { return device; }
		/** @bridf get memory allocater */
		//const  VmaAllocator				get_memory_allocator() const  {return memory_allocator;}
		void							prepare_VMA();
		VkQueue const&					get_queue(uint32_t queue_family_index, uint32_t queue_index) const {return queues[queue_family_index][queue_index];}
		VkQueue const&					get_queue_by_flags(vk::QueueFlags required_queue_flags, uint32_t queue_index) const;
		VkQueue const&					get_queue_by_present(uint32_t queue_index) const;

		/**
		 * @brief Finds a suitable graphics queue to submit to
		 * @return The first present supported queue, otherwise just any graphics queue
		 */
		VkQueue const&					get_suitable_graphics_queue() const;
		bool							is_extension_supported(std::string const& extension);
		bool							is_enabled(std::string const& extension);
		uint32_t						get_queue_family_index(vk::QueueFlagBits queue_flag);
		vk::CommandPool					createCommandPool(uint32_t queueFamilyIndex, vk::CommandPoolCreateFlags createFlags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
		vk::CommandBuffer				createCommandBuffer(vk::CommandBufferLevel level, vk::CommandPool pool, bool begin = false);
		vk::CommandBuffer				createCommandBuffer(vk::CommandBufferLevel level, bool begin = false);
	};
}