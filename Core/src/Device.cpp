#include "Device.h"
#include "Instance.h"
#include "SwapChain.h"

namespace pt {
    HPPDevice::HPPDevice(pt::HPPPhysicalDevice &gpu,
        vk::SurfaceKHR                         surface,
        std::unordered_map<const char*, bool>  requested_extensions) : gpu{gpu}
    {
        // Prepare the device queues
		std::vector<vk::QueueFamilyProperties> queue_family_properties = gpu.get_queue_family_properties();
		std::vector<vk::DeviceQueueCreateInfo> queue_create_infos(queue_family_properties.size());
		std::vector<std::vector<float>>        queue_priorities(queue_family_properties.size());
    
		for (uint32_t queue_family_index = 0U; queue_family_index < queue_family_properties.size(); ++queue_family_index)
		{
			const VkQueueFamilyProperties& queue_family_property = gpu.get_queue_family_properties()[queue_family_index];

			if (gpu.has_high_priority_graphics_queue())
			{
				uint32_t graphics_queue_family = get_queue_family_index(vk::QueueFlagBits::eGraphics);
				if (graphics_queue_family == queue_family_index)
				{
					queue_priorities[queue_family_index].reserve(queue_family_property.queueCount);
					queue_priorities[queue_family_index].push_back(1.0f);
					for (uint32_t i = 1; i < queue_family_property.queueCount; i++)
					{
						queue_priorities[queue_family_index].push_back(0.5f);
					}
				}
				else
				{
					queue_priorities[queue_family_index].resize(queue_family_property.queueCount, 0.5f);
				}
			}
			else
			{
				queue_priorities[queue_family_index].resize(queue_family_property.queueCount, 0.5f);
			}

			VkDeviceQueueCreateInfo& queue_create_info = queue_create_infos[queue_family_index];

			queue_create_info.queueFamilyIndex = queue_family_index;
			queue_create_info.queueCount = queue_family_property.queueCount;
			queue_create_info.pQueuePriorities = queue_priorities[queue_family_index].data();
		}

		// Check extensions to enable Vma Dedicated Allocation
		device_extensions = gpu.get_handle().enumerateDeviceExtensionProperties();

		// Display supported extensions
#ifdef VK_DEBUG
		if (device_extensions.size() > 0)
		{
			LOGI("HPPDevice supports the following extensions:");
			for (auto& extension : device_extensions)
			{
				LOGI("  \t{}", extension.extensionName.data());
			}
		}
		else {
			LOGI("HPPDevice extension is empty.");
		}
#endif


		//bool can_get_memory_requirements = is_extension_supported(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
		//bool has_dedicated_allocation = is_extension_supported(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);
		//if (can_get_memory_requirements && has_dedicated_allocation)
		//{
		//	enabled_extensions.push_back(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
		//	enabled_extensions.push_back(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);

		//	LOGI("Dedicated Allocation enabled");
		//}
		// For performance queries, we also use host query reset since queryPool resets cannot
		// live in the same command buffer as beginQuery
		//if (is_extension_supported(VK_KHR_PERFORMANCE_QUERY_EXTENSION_NAME) && is_extension_supported(VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME))
		//{
		//	auto perf_counter_features = gpu.request_extension_features<vk::PhysicalDevicePerformanceQueryFeaturesKHR>();
		//	auto host_query_reset_features = gpu.request_extension_features<vk::PhysicalDeviceHostQueryResetFeatures>();

		//	if (perf_counter_features.performanceCounterQueryPools && host_query_reset_features.hostQueryReset)
		//	{
		//		enabled_extensions.push_back(VK_KHR_PERFORMANCE_QUERY_EXTENSION_NAME);
		//		enabled_extensions.push_back(VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME);
		//		LOGI("Performance query enabled");
		//	}
		//}

		// Check that extensions are supported before trying to create the device
		LOGI("Requested extensions:");
		for (auto& extension : requested_extensions)
		{
			LOGI("  \t{}", extension.first);
		}

		std::vector<const char*> unsupported_extensions{};
		for (auto& extension : requested_extensions)
		{
			if (is_extension_supported(extension.first))
			{
				enabled_extensions.emplace_back(extension.first);
			}
			else
			{
				unsupported_extensions.emplace_back(extension.first);
			}
		}
#ifdef _DEBUG
		if (enabled_extensions.size() > 0)
		{
			LOGI("HPPDevice supports the following requested extensions:");
			for (auto& extension : enabled_extensions)
			{
				LOGI("  \t{}", extension);
			}
		}
#endif
		if (unsupported_extensions.size() > 0)
		{
			auto error = false;
			for (auto& extension : unsupported_extensions)
			{
				auto extension_is_optional = requested_extensions[extension];
				if (extension_is_optional)
				{
					LOGW("Optional device extension {} not available, some features may be disabled", extension);
				}
				else
				{
					LOGE("Required device extension {} not available, cannot run", extension);
					error = true;
				}
			}

			if (error)
			{
				throw std::runtime_error("Extensions not present");
			}
		}

		vk::DeviceCreateInfo create_info({}, queue_create_infos, {}, enabled_extensions, & gpu.get_mutable_requested_features());

		// Latest requested feature will have the pNext's all set up for device creation.
		create_info.pNext = gpu.get_extension_feature_chain();

		device = gpu.get_handle().createDevice(create_info);

		queues.resize(queue_family_properties.size());

		for (uint32_t queue_family_index = 0U; queue_family_index < queue_family_properties.size(); ++queue_family_index)
		{
			vk::QueueFamilyProperties const& queue_family_property = queue_family_properties[queue_family_index];

			vk::Bool32 present_supported = gpu.get_handle().getSurfaceSupportKHR(queue_family_index, surface);

			for (uint32_t queue_index = 0U; queue_index < queue_family_property.queueCount; ++queue_index)
			{
				vk::Queue queueHandle = device.getQueue(queue_family_index, queue_index);
				queues[queue_family_index].emplace_back(queueHandle);
			}
		}

		// Setting VMA
		//prepare_VMA();
		// Create a default command pool for graphics command buffers
		commandPool = createCommandPool(queueFamilyIndices.graphics);
    }


	uint32_t HPPDevice::get_queue_family_index(vk::QueueFlagBits queue_flag)
	{
		const auto& queue_family_properties = gpu.get_queue_family_properties();

		// Dedicated queue for compute
		// Try to find a queue family index that supports compute but not graphics
		if (queue_flag & vk::QueueFlagBits::eCompute)
		{
			for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties.size()); i++)
			{
				if ((queue_family_properties[i].queueFlags & queue_flag) && !(queue_family_properties[i].queueFlags & vk::QueueFlagBits::eGraphics))
				{
					return i;
					break;
				}
			}
		}

		// Dedicated queue for transfer
		// Try to find a queue family index that supports transfer but not graphics and compute
		if (queue_flag & vk::QueueFlagBits::eTransfer)
		{
			for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties.size()); i++)
			{
				if ((queue_family_properties[i].queueFlags & queue_flag) && !(queue_family_properties[i].queueFlags & vk::QueueFlagBits::eGraphics) &&
					!(queue_family_properties[i].queueFlags & vk::QueueFlagBits::eCompute))
				{
					return i;
					break;
				}
			}
		}

		// For other queue types or if no separate compute queue is present, return the first one to support the requested
		// flags
		for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties.size()); i++)
		{
			if (queue_family_properties[i].queueFlags & queue_flag)
			{
				return i;
				break;
			}
		}

		throw std::runtime_error("Could not find a matching queue family index");
	}

	/*void HPPDevice::prepare_VMA() {
		bool can_get_memory_requirements = is_extension_supported(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
		bool has_dedicated_allocation = is_extension_supported(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);
		VmaVulkanFunctions vma_vulkan_func{};
		vma_vulkan_func.vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(device.getProcAddr("vkAllocateMemory"));
		vma_vulkan_func.vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(device.getProcAddr("vkBindBufferMemory"));
		vma_vulkan_func.vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(device.getProcAddr("vkBindImageMemory"));
		vma_vulkan_func.vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(device.getProcAddr("vkCreateBuffer"));
		vma_vulkan_func.vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(device.getProcAddr("vkCreateImage"));
		vma_vulkan_func.vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(device.getProcAddr("vkDestroyBuffer"));
		vma_vulkan_func.vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(device.getProcAddr("vkDestroyImage"));
		vma_vulkan_func.vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(device.getProcAddr("vkFlushMappedMemoryRanges"));
		vma_vulkan_func.vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(device.getProcAddr("vkFreeMemory"));
		vma_vulkan_func.vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(device.getProcAddr("vkGetBufferMemoryRequirements"));
		vma_vulkan_func.vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(device.getProcAddr("vkGetImageMemoryRequirements"));
		vma_vulkan_func.vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(device.getProcAddr("vkGetPhysicalDeviceMemoryProperties"));
		vma_vulkan_func.vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(device.getProcAddr("vkGetPhysicalDeviceProperties"));
		vma_vulkan_func.vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(device.getProcAddr("vkInvalidateMappedMemoryRanges"));
		vma_vulkan_func.vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(device.getProcAddr("vkMapMemory"));
		vma_vulkan_func.vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(device.getProcAddr("vkUnmapMemory"));
		vma_vulkan_func.vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(device.getProcAddr("vkCmdCopyBuffer"));

		VmaAllocatorCreateInfo allocator_info{};
		allocator_info.physicalDevice = static_cast<VkPhysicalDevice>(gpu.get_handle());
		allocator_info.device = static_cast<VkDevice>(device);
		allocator_info.instance = static_cast<VkInstance>(gpu.get_instance().get_handle());

		if (can_get_memory_requirements && has_dedicated_allocation)
		{
			allocator_info.flags |= VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT;
			vma_vulkan_func.vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2KHR;
			vma_vulkan_func.vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2KHR;
		}

		if (is_extension_supported(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME) && is_enabled(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
		{
			allocator_info.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
		}

		allocator_info.pVulkanFunctions = &vma_vulkan_func;

		VkResult result = vmaCreateAllocator(&allocator_info, &memory_allocator);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("failed to setup VMA");
		}
	}*/

	bool HPPDevice::is_extension_supported(const std::string& requested_extension) {
		for (vk::ExtensionProperties& ext : device_extensions) {
			const char* name = ext.extensionName.data();
			if (strcmp(name, requested_extension.c_str()) == 0) return true;
		}
		return false;

		//return std::find_if(device_extensions.begin(), device_extensions.end(), 
		//	[requested_extension](auto& device_extension) {
		//		return std::strcmp(requested_extension.c_str(), device_extension.extensionName) == 0;
		//	}) != device_extensions.end();
	}

	bool HPPDevice::is_enabled(std::string const& extension) {
		for (auto& ext : enabled_extensions) {
			if (strcmp(ext, extension.c_str()) == 0) return true;
		}
		return false;
		//return std::find_if(enabled_extensions.begin(), enabled_extensions.end(),
		//	[extension](auto& ext) {
		//		return std::strcmp(extension.c_str(), ext.extensionName) == 0;
		//	}) != enabled_extensions.end();
	}


	vk::CommandPool HPPDevice::createCommandPool(uint32_t queueFamilyIndex, vk::CommandPoolCreateFlags createFlags) {
		vk::CommandPoolCreateInfo cmdPoolInfo = {};
		cmdPoolInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
		cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
		cmdPoolInfo.flags = createFlags;
		vk::CommandPool cmdPool = device.createCommandPool(cmdPoolInfo);
		return cmdPool;
	}

	vk::CommandBuffer  HPPDevice::createCommandBuffer(vk::CommandBufferLevel level, vk::CommandPool pool, bool begin)
	{
		vk::CommandBuffer command_buffer = get_handle().allocateCommandBuffers({ pool, level, 1 }).front();
		if (begin) {
			command_buffer.begin(vk::CommandBufferBeginInfo());
		}
		return command_buffer;
	}
	vk::CommandBuffer  HPPDevice::createCommandBuffer(vk::CommandBufferLevel level, bool begin) {
		return createCommandBuffer(level, commandPool, begin);
	}

	HPPDevice::~HPPDevice() {
		//if (memory_allocator != VK_NULL_HANDLE)
		//{
		//	VmaTotalStatistics stats;
		//	vmaCalculateStatistics(memory_allocator, &stats);

		//	LOGI("Total device memory leaked: {} bytes.", stats.total.statistics.allocationBytes);

		//	vmaDestroyAllocator(memory_allocator);
		//}

		if (device)
		{
			device.destroy();
		}
	}
}