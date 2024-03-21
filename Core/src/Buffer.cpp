//#include "Buffer.h"
//#include "logging.h"
//
//namespace pt
//{
//	HPPBuffer::HPPBuffer(pt::HPPDevice& device,
//		vk::DeviceSize               size_,
//		vk::BufferUsageFlags         buffer_usage,
//		VmaMemoryUsage               memory_usage,
//		VmaAllocationCreateFlags     flags,
//		const std::vector<uint32_t>& queue_family_indices) : device{device}
//	{
//		persistent = (flags & VMA_ALLOCATION_CREATE_MAPPED_BIT) != 0;
//
//		vk::BufferCreateInfo buffer_create_info({}, size, buffer_usage);
//		if (queue_family_indices.size() >= 2)
//		{
//			buffer_create_info.sharingMode = vk::SharingMode::eConcurrent;
//			buffer_create_info.queueFamilyIndexCount = static_cast<uint32_t>(queue_family_indices.size());
//			buffer_create_info.pQueueFamilyIndices = queue_family_indices.data();
//		}
//
//		VmaAllocationCreateInfo memory_info{};
//		memory_info.flags = flags;
//		memory_info.usage = memory_usage;
//
//		VmaAllocationInfo allocation_info{};
//		auto              result = vmaCreateBuffer(device.get_memory_allocator(),
//			reinterpret_cast<VkBufferCreateInfo*>(&buffer_create_info), &memory_info,
//			reinterpret_cast<VkBuffer*>(&get_handle()), &allocation,
//			&allocation_info);
//
//		if (result != VK_SUCCESS)
//		{
//			throw std::runtime_error("Cannot create HPPBuffer");
//		}
//
//		memory = static_cast<vk::DeviceMemory>(allocation_info.deviceMemory);
//
//		if (persistent)
//		{
//			mapped_data = static_cast<uint8_t*>(allocation_info.pMappedData);
//		}
//	}
//
//	HPPBuffer::~HPPBuffer()
//	{
//		if (device.get_handle() && (allocation != VK_NULL_HANDLE))
//		{
//			unmap();
//			vmaDestroyBuffer(device.get_memory_allocator(), static_cast<VkBuffer>(get_handle()), allocation);
//		}
//	}
//
//	VmaAllocation HPPBuffer::get_allocation() const
//	{
//		return allocation;
//	}
//
//	vk::DeviceMemory HPPBuffer::get_memory() const
//	{
//		return memory;
//	}
//
//	vk::DeviceSize HPPBuffer::get_size() const
//	{
//		return size;
//	}
//
//	const uint8_t* HPPBuffer::get_data() const
//	{
//		return mapped_data;
//	}
//
//	uint8_t* HPPBuffer::map()
//	{
//		if (!mapped && !mapped_data)
//		{
//			vmaMapMemory(device.get_memory_allocator(), allocation, reinterpret_cast<void**>(&mapped_data));
//			mapped = true;
//		}
//		return mapped_data;
//	}
//
//	void HPPBuffer::unmap()
//	{
//		if (mapped)
//		{
//			vmaUnmapMemory(device.get_memory_allocator(), allocation);
//			mapped_data = nullptr;
//			mapped = false;
//		}
//	}
//
//	void HPPBuffer::flush()
//	{
//		vmaFlushAllocation(device.get_memory_allocator(), allocation, 0, size);
//	}
//
//	void HPPBuffer::update(const std::vector<uint8_t>& data, size_t offset)
//	{
//		update(data.data(), data.size(), offset);
//	}
//
//	uint64_t HPPBuffer::get_device_address() const
//	{
//		return device.get_handle().getBufferAddressKHR({ get_handle() });
//	}
//
//	void HPPBuffer::update(void const* data, size_t size, size_t offset)
//	{
//		update(reinterpret_cast<const uint8_t*>(data), size, offset);
//	}
//
//	void HPPBuffer::update(const uint8_t* data, const size_t size, const size_t offset)
//	{
//		if (persistent)
//		{
//			std::copy(data, data + size, mapped_data + offset);
//			flush();
//		}
//		else
//		{
//			map();
//			std::copy(data, data + size, mapped_data + offset);
//			flush();
//			unmap();
//		}
//	}
//
//	vk::Buffer HPPBuffer::get_handle() const {
//		return handle;
//	}
//}        // namespace pt
