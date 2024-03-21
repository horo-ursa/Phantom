#pragma once
#include <vulkan\vulkan.hpp>
#include <unordered_map>
#include <vector>
#include <optional>
#include <logging.h>

namespace pt {
    class HPPPhysicalDevice;
    class HPPInstance {

    public:
        /**
          * @brief Can be set from the GPU selection plugin to explicitly select a GPU instead
          */
        static std::optional<uint32_t> selected_gpu_index;

        HPPInstance(const std::string&                          application_name,
                const std::unordered_map<const char*, bool>&    required_extensions = {},
                const std::vector<const char*>&                 required_validation_layers = {},
                bool                                            headless = false,
                uint32_t                                        api_version = VK_API_VERSION_1_3);

        /**
        * @brief Queries the GPUs of a vk::Instance that is already created
        * @param instance A valid vk::Instance
        */
        HPPInstance(vk::Instance instance);

        HPPInstance(const HPPInstance&)            = delete;
        HPPInstance& operator=(const HPPInstance&) = delete;
        HPPInstance(HPPInstance&&)                 = delete;
        HPPInstance& operator=(HPPInstance&&)      = delete;
        ~HPPInstance();

        /**
         * @brief Checks if the given extension is enabled in the vk::Instance
         * @param extension An extension to check
         */
        bool is_enabled(const char* extension) const;
        
        /**
        * @brief Tries to find the first available discrete GPU
        * @returns A valid physical device
        */
        VULKAN_HPP_NODISCARD auto get_first_gpu() ->HPPPhysicalDevice&;
        VULKAN_HPP_NODISCARD auto get_handle() ->vk::Instance& { return handle; }
        VULKAN_HPP_NODISCARD auto get_extensions() -> const std::vector<const char*>& { return enabled_extensions; }
       
        /**
        * @brief Tries to find the first available discrete GPU that can render to the given surface
        * @param surface to test against
        * @returns A valid physical device
        */
        VULKAN_HPP_NODISCARD auto get_suitable_gpu(vk::SurfaceKHR) ->HPPPhysicalDevice&;
        

    private:
        /**
        * @brief Queries the instance for the physical devices on the machine
        */
        void query_gpus();
        
        vk::Instance                                    handle;
        std::vector<const char*>                        enabled_extensions;
#if defined(VK_DEBUG) || defined(VK_VALIDATION_LAYERS)
        /**
         * @brief Debug utils messenger callback for VK_EXT_Debug_Utils
         */
        vk::DebugUtilsMessengerEXT                      debug_utils_messenger;
        /**
         * @brief The debug report callback
         */
        vk::DebugReportCallbackEXT                      debug_report_callback;
#endif
        std::vector<std::unique_ptr<HPPPhysicalDevice>>    gpus;

    };
}
