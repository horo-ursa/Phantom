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
        // Prepare the device queues
        uint32_t                             queue_family_properties_count = to_u32(gpu.get_queue_family_properties().size());
        std::vector<VkDeviceQueueCreateInfo> queue_create_infos(queue_family_properties_count, { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO });
        std::vector<std::vector<float>>      queue_priorities(queue_family_properties_count);
    
		for (uint32_t queue_family_index = 0U; queue_family_index < queue_family_properties_count; ++queue_family_index)
		{
			const VkQueueFamilyProperties& queue_family_property = gpu.get_queue_family_properties()[queue_family_index];

			if (gpu.has_high_priority_graphics_queue())
			{
				uint32_t graphics_queue_family = get_queue_family_index(VK_QUEUE_GRAPHICS_BIT);
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

    }
}