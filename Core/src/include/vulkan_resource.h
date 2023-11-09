#pragma once
#include <utility>
#include <vulkan\vulkan.hpp>

namespace pt {
	class Device;

	template <typename HPPHandle, typename VKBDevice = pt::Device>
	class VulkanResource
	{
	public:

		VulkanResource(HPPHandle handle = nullptr, VKBDevice* device = nullptr) :
			handle{ handle }, device{ device }
		{
		}

		VulkanResource(const VulkanResource&) = delete;
		VulkanResource& operator=(const VulkanResource&) = delete;

		VulkanResource(VulkanResource&& other)
			: handle{ std::exchange(other.handle, {}) }
			, device{ std::exchange(other.device, {}) }
		{

		}

		VulkanResource& operator=(VulkanResource&& other) {
			handle = std::exchange(other.handle, {});
			device = std::exchange(other.device, {});
			return *this;
		}

		virtual ~VulkanResource() = default;

		// requires HPPHandle be vk::type
		VULKAN_HPP_NODISCARD
			auto get_object_type() const -> vk::ObjectType {
			return HPPHandle::NaiveType;
		}

		VULKAN_HPP_NODISCARD
			auto get_device() -> VKBDevice& {
			assert(device, "VKBDevice not created");
			return *device;
		}

		VULKAN_HPP_NODISCARD
			auto get_handle() -> HPPHandle& {
			return handle;
		}

		void set_handle(HPPHandle hdl) {
			handle = hdl;
		}

	private:
		HPPHandle handle;
		VKBDevice* device;
	};
}