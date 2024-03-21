#pragma once
#include <vulkan\vulkan.hpp>

namespace pt
{
	class HPPDevice;
	class HPPInstance;
	class HPPCommandBuffer;

	class HPPQueue
	{
	public:
		HPPQueue(HPPDevice& device, uint32_t family_index, vk::QueueFamilyProperties properties, vk::Bool32 can_present, uint32_t index);

		HPPQueue(const HPPQueue&) = default;

		HPPQueue(HPPQueue&& other);

		HPPQueue& operator=(const HPPQueue&) = delete;
		HPPQueue& operator=(HPPQueue&&) = delete;

		auto get_device() const -> const HPPDevice&;
		auto get_handle() const ->vk::Queue;
		auto get_family_index() const ->uint32_t;
		auto get_index() const ->uint32_t;
		auto get_properties() const -> const vk::QueueFamilyProperties&;
		auto support_present() const ->vk::Bool32;
		void submit(const HPPCommandBuffer& command_buffer, vk::Fence fence) const;
		auto present(const vk::PresentInfoKHR& present_infos) const -> vk::Result;

	private:
		HPPDevice& device;

		vk::Queue handle;

		uint32_t family_index{ 0 };

		uint32_t index{ 0 };

		vk::Bool32 can_present = false;

		vk::QueueFamilyProperties properties{};
	};
}