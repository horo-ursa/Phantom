#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <algorithm>

#include <glm.hpp>
#include <GLFW/glfw3native.h>
#include <fstream>
#include <vulkan\vulkan.hpp>
#include <Device.h>
#include <memory>
#include <logging.h>
#include <Window.h>
#include <initializer.h>

class Application {
public:
	Application(pt::Window::Properties p);
	~Application();

	void									prepare();
	void									update();
	void									resize();
	void									cleanup();

	void									recordCommandBuffer(vk::CommandBuffer commandBuffer, uint32_t imageIndex);
	void									drawFrame();


	void									createSwapChain(vk::Format swapchainformat = vk::Format::eR8G8B8A8Srgb);
	void									createCommandPool();
	void									createRenderPass();
	vk::ShaderModule						createShaderModule(const std::string& code);
	void									createPipeline();
	void									createFramebuffers();
	void									createCommandBuffers();
	void									createSychronizationPrimitives();
	std::vector<const char*> const&			get_validation_layers() const;
	vk::SurfaceFormatKHR					chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& available_surface_formats,
															    const std::vector<vk::SurfaceFormatKHR>& surface_format_priority_list,
																const vk::Format requestFormat);
	/* Shader Creation */
	std::string								readFile(const std::string& filename);


protected:
	void initialWindow();
	void initialVulkan();
	void addInstanceExtension(const char* extension, bool optional = false) {
		instance_extensions[extension] = optional;
	}
	vk::Extent2D& createExtent2D(vk::SurfaceCapabilitiesKHR&);

	std::unique_ptr<pt::HPPInstance>	instance;
	std::unique_ptr<pt::HPPDevice>		device;
	vk::SurfaceKHR						surface;
	std::unique_ptr<pt::Window>			mainWindow;
	vk::CommandPool						commandPool;
	std::vector<vk::CommandBuffer>		drawCmdBuffers;
	vk::CommandBuffer					defaultBuffer;
	/* swapchain propertyies */
	struct SwapChainBuffer {
		vk::Image image;
		vk::ImageView view;
	};
	vk::Extent2D						extent;
	vk::Format							swapChainImageFormat;
	vk::SwapchainKHR					swapChain{ nullptr };
	// swapchain usage, default as color attachment, might be transfer dst for post-processing
	vk::ImageUsageFlagBits				image_usage{ vk::ImageUsageFlagBits::eColorAttachment };
	// composite alpha flag, default as opaque
	vk::CompositeAlphaFlagBitsKHR       alpha_bit{ vk::CompositeAlphaFlagBitsKHR::eOpaque };
	std::vector<vk::Image>				swapChainImages;
	uint32_t							imageCount;
	std::vector<SwapChainBuffer>		buffers;
	std::vector<vk::Framebuffer>		swapchainFramebuffers;
	vk::RenderPass						renderPass;
	vk::PipelineLayout					pipelineLayout;
	vk::Pipeline						graphicsPipeline;

	// Synchronization
	vk::Semaphore						imageAvailableSemaphore;
	vk::Semaphore						renderFinishedSemaphore;
	vk::Fence							inFlightFence;

	//Queues
	vk::Queue							graphicsQueue;
	vk::Queue							presentQueue;

	/** @brief Set of device extensions to be enabled for this example and whether they are optional (must be set in the derived constructor) */
	std::unordered_map<const char*, bool> required_device_extensions{ {VK_KHR_SWAPCHAIN_EXTENSION_NAME, false} };
	/** @brief Set of instance extensions to be enabled for this example and whether they are optional (must be set in the derived constructor) */
	std::unordered_map<const char*, bool> instance_extensions;
	/** @brief The Vulkan API version to request for this sample at instance creation time */
	uint32_t api_version = VK_API_VERSION_1_0;
};