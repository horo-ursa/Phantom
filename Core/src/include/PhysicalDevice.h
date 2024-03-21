#pragma once

#include "Instance.h"
#include <map>
#include <vulkan\vulkan.hpp>

namespace pt {
	class HPPInstance;

	struct DriverVersion
	{
		uint16_t major;
		uint16_t minor;
		uint16_t patch;
	};


	class HPPPhysicalDevice
	{
	public:

		HPPPhysicalDevice(pt::HPPInstance&, vk::PhysicalDevice);
		//HPPPhysicalDevice(const HPPPhysicalDevice&) = delete;
		//HPPPhysicalDevice& operator=(const HPPPhysicalDevice&) = delete;
		/*HPPPhysicalDevice(HPPPhysicalDevice&&) = delete;
		HPPPhysicalDevice& operator=(HPPPhysicalDevice&&) = delete;*/

		/**
		* @return The version of the driver
		*/
		DriverVersion get_driver_version() const;

		/**
		* @brief Used at logical device creation to pass the extensions feature chain to vkCreateDevice
		* @returns A void pointer to the start of the extension linked list
		*/
		auto get_extension_feature_chain() const -> void*;
		auto get_features() const -> const vk::PhysicalDeviceFeatures&;
		auto get_handle() const ->vk::PhysicalDevice;
		auto get_instance() const ->pt::HPPInstance&;
		auto get_memory_properties() const -> const vk::PhysicalDeviceMemoryProperties&;
	

		/**
		* @brief Checks that a given memory type is supported by the GPU
		* @param bits The memory requirement type bits
		* @param properties The memory property to search for
		* @param memory_type_found True if found, false if not found
		* @returns The memory type index of the found memory type
		*/
		auto get_memory_type(uint32_t bits, vk::MemoryPropertyFlags properties, vk::Bool32* memory_type_found = nullptr) const ->uint32_t;
		auto get_properties() const -> const vk::PhysicalDeviceProperties&;
		auto get_queue_family_properties() const -> const std::vector<vk::QueueFamilyProperties>&;
		auto get_requested_features() const -> const vk::PhysicalDeviceFeatures;
		auto get_mutable_requested_features() ->vk::PhysicalDeviceFeatures&;

		/**
		* @brief Returns high priority graphics queue state.
		* @return High priority state.
		*/
		bool has_high_priority_graphics_queue() const
		{
			return high_priority_graphics_queue;
		}

		/**
		 * @brief Requests a third party extension to be used by the framework
		 *
		 *        To have the features enabled, this function must be called before the logical device
		 *        is created. To do this request sample specific features inside
		 *        VulkanSample::request_gpu_features(vkb::HPPPhysicalDevice &gpu).
		 *
		 *        If the feature extension requires you to ask for certain features to be enabled, you can
		 *        modify the struct returned by this function, it will propagate the changes to the logical
		 *        device.
		 * @returns The extension feature struct
		 */
		template <typename HPPStructureType>
		HPPStructureType& request_extension_features()
		{
			// We cannot request extension features if the physical device properties 2 instance extension isn't enabled
			if (!instance.is_enabled(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
			{
				throw std::runtime_error("Couldn't request feature from device as " + std::string(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME) + " isn't enabled!");
			}

			// If the type already exists in the map, return a casted pointer to get the extension feature struct
			vk::StructureType structureType = HPPStructureType::structureType;        // need to instantiate this value to be usable in find()!
			auto              extension_features_it = extension_features.find(structureType);
			if (extension_features_it != extension_features.end())
			{
				return *static_cast<HPPStructureType*>(extension_features_it->second.get());
			}

			// Get the extension feature
			vk::StructureChain<vk::PhysicalDeviceFeatures2KHR, HPPStructureType> featureChain = handle.getFeatures2KHR<vk::PhysicalDeviceFeatures2KHR, HPPStructureType>();

			// Insert the extension feature into the extension feature map so its ownership is held
			extension_features.insert({ structureType, std::make_shared<HPPStructureType>(featureChain.template get<HPPStructureType>()) });

			// Pull out the dereferenced void pointer, we can assume its type based on the template
			auto* extension_ptr = static_cast<HPPStructureType*>(extension_features.find(structureType)->second.get());

			// If an extension feature has already been requested, we shift the linked list down by one
			// Making this current extension the new base pointer
			if (last_requested_extension_feature)
			{
				extension_ptr->pNext = last_requested_extension_feature;
			}
			last_requested_extension_feature = extension_ptr;

			return *extension_ptr;
		}

	private:
		// Handle to the Vulkan instance
		pt::HPPInstance& instance;

		// Handle to the Vulkan physical device
		vk::PhysicalDevice handle{ nullptr };

		// The features that this GPU supports
		vk::PhysicalDeviceFeatures features;

		// The GPU properties
		vk::PhysicalDeviceProperties properties;

		// The GPU memory properties
		vk::PhysicalDeviceMemoryProperties memory_properties;

		// The GPU queue family properties
		std::vector<vk::QueueFamilyProperties> queue_family_properties;

		// The features that will be requested to be enabled in the logical device
		vk::PhysicalDeviceFeatures requested_features;

		// The extension feature pointer
		void* last_requested_extension_feature{ nullptr };

		// Holds the extension feature structures, we use a map to retain an order of requested structures
		std::map<vk::StructureType, std::shared_ptr<void>> extension_features;

		bool high_priority_graphics_queue{ false };
	};
}
