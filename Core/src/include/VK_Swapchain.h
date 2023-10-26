#pragma once

#include <vulkan\vulkan.h>
#include <vector>

namespace ptvk {

// What SwapChain::acquire produces: a swap chain image plus
// semaphores protecting it.
	struct SwapChainAcquireState
	{
		// The image and its view and index in the swap chain.
		VkImage     image;
		VkImageView view;
		uint32_t    index;
		// MUST wait on this semaphore before writing to the image. ("The
		// system" signals this semaphore when it's done presenting the
		// image and can safely be reused).
		VkSemaphore waitSem;
		// MUST signal this semaphore when done writing to the image, and
		// before presenting it. (The system waits for this before presenting).
		VkSemaphore signalSem;
	};

	class SwapChain
	{

	public:
		SwapChain(SwapChain const&) = delete;
		SwapChain& operator=(SwapChain const&) = delete;

		SwapChain() {}

		static constexpr VkImageUsageFlags s_defaultImageUsage =
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

		SwapChain(VkDevice          device,
			VkPhysicalDevice  physicalDevice,
			VkQueue           queue,
			uint32_t          queueFamilyIndex,
			VkSurfaceKHR      surface,
			VkFormat          format = VK_FORMAT_B8G8R8A8_UNORM,
			VkImageUsageFlags imageUsage = s_defaultImageUsage)
		{
			init(device, physicalDevice, queue, queueFamilyIndex, surface, format, imageUsage);
		}
		~SwapChain() { deinit(); }

		bool init(VkDevice          device,
			VkPhysicalDevice  physicalDevice,
			VkQueue           queue,
			uint32_t          queueFamilyIndex,
			VkSurfaceKHR      surface,
			VkFormat          format = VK_FORMAT_B8G8R8A8_UNORM,
			VkImageUsageFlags imageUsage = s_defaultImageUsage);

		// triggers queue/device wait idle
		void deinit();

		// update the swapchain configuration
		// (must be called at least once after init)
		// triggers queue/device wait idle
		// returns actual swapchain dimensions, which may differ from requested
		auto update(int width, int height, bool vsync) -> VkExtent2D;
		auto update(int width, int height) -> VkExtent2D { return update(width, height, m_vsync); }

		// Returns true on success.
		//
		// Sets active index to the next swap chain image to draw to.
		// The handles and semaphores for this image are optionally written to *pOut.
		//
		// `acquire` and `acquireAutoResize` use getActiveReadSemaphore();
		// `acquireCustom` allows you to provide your own semaphore.
		//
		// If the swap chain was invalidated (window resized, etc.), the
		// swap chain will be recreated, which triggers queue/device wait
		// idle.  If you are not calling `update` manually on window resize,
		// you must pass the new swap image size explicitly.
		//
		// WARNING: The actual swap image size might not match what is
		// requested; use getWidth/getHeight to check actual swap image
		// size.
		//
		// If the swap chain was recreated, *pRecreated is set to true (if
		// pRecreated != nullptr); otherwise, set to false.
		//
		// WARNING the swap chain could be spontaneously recreated, even if
		// you are calling `update` whenever the window is resized.
		bool acquire(bool* pRecreated = nullptr, SwapChainAcquireState* pOut = nullptr);
		bool acquireAutoResize(int width, int height, bool* pRecreated, SwapChainAcquireState* pOut = nullptr);

		// Can be made public if this functionality is needed again.
		bool acquireCustom(VkSemaphore semaphore, bool* pRecreated = nullptr, SwapChainAcquireState* pOut = nullptr);
		bool acquireCustom(VkSemaphore semaphore, int width, int height, bool* pRecreated, SwapChainAcquireState* pOut = nullptr);

		// all present functions bump semaphore cycle

		// present on provided queue
		void present(VkQueue queue);
		// present using a default queue from init time
		void present() { present(m_queue); }
		// present via a custom function
		// (e.g. when extending via VkDeviceGroupPresentInfoKHR)
		// fills in defaults for provided presentInfo
		// with getActiveImageIndex()
		// and getActiveWrittenSemaphore()
		void presentCustom(VkPresentInfoKHR& outPresentInfo);

		auto getActiveReadSemaphore() const -> VkSemaphore;
		auto getActiveWrittenSemaphore() const ->VkSemaphore;
		auto getActiveImage() const -> VkImage;
		auto getActiveImageView() const -> VkImageView;
		auto getActiveImageIndex() const -> uint32_t { return m_currentImage; }

		auto getImageCount() const -> uint32_t  { return m_imageCount; }
		auto getImage(uint32_t i) const -> VkImage;
		auto getImageView(uint32_t i) const -> VkImageView;
		auto getFormat() const -> VkFormat { return m_surfaceFormat; }

		// Get the actual size of the swap chain images.
		auto getWidth() const -> uint32_t { return m_extent.width; }
		auto getHeight() const -> uint32_t { return m_extent.height; }
		auto getExtent() const -> VkExtent2D { return m_extent; }

		// Get the requested size of the swap chain images. THIS IS RARELY USEFUL.
		auto getUpdateWidth() const -> uint32_t { return m_updateWidth; }
		auto getUpdateHeight() const -> uint32_t { return m_updateHeight; }

		bool getVsync() const { return m_vsync; }
		auto getSwapchain() const -> VkSwapchainKHR { return m_swapchain; }

		// does a vkCmdPipelineBarrier for VK_IMAGE_LAYOUT_UNDEFINED to VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		// must apply resource transitions after update calls
		void cmdUpdateBarriers(VkCommandBuffer cmd) const;

		auto getChangeID() const -> uint32_t;

		// Ordinarily, `SwapChain` calls vkDeviceWaitIdle before recreating
		// the swap chain. However, if setWaitQueue is called with a
		// non-null queue, we only wait for that queue instead of the whole
		// device.  This may be needed if you are using queues in other CPU
		// threads that are not synchronized to the render loop.
		void setWaitQueue(VkQueue waitQueue = VK_NULL_HANDLE) { m_waitQueue = waitQueue; }

		// typically either VK_PRESENT_MODE_MAILBOX_KHR or VK_PRESENT_MODE_IMMEDIATE_KHR
		void setPreferredVsyncOffMode(VkPresentModeKHR mode) { m_preferredVsyncOffMode = mode; }

	private:
		struct Entry
		{
			VkImage     image{};
			VkImageView imageView{};
			// be aware semaphore index may not match active image index
			VkSemaphore readSemaphore{};
			VkSemaphore writtenSemaphore{};
		};

		VkDevice         m_device = VK_NULL_HANDLE;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

		VkQueue  m_queue{};
		VkQueue  m_waitQueue{};  // See waitIdle and setWaitQueue.
		uint32_t m_queueFamilyIndex{ 0 };

		VkSurfaceKHR    m_surface{};
		VkFormat        m_surfaceFormat{};
		VkColorSpaceKHR m_surfaceColor{};

		uint32_t       m_imageCount{ 0 };
		VkSwapchainKHR m_swapchain{};

		std::vector<Entry>                m_entries;
		std::vector<VkImageMemoryBarrier> m_barriers;

		// index for current image, returned by vkAcquireNextImageKHR
		// vk spec: The order in which images are acquired is implementation-dependent,
		// and may be different than the order the images were presented
		uint32_t m_currentImage{ 0 };
		// index for current semaphore, incremented by `SwapChain::present`
		uint32_t m_currentSemaphore{ 0 };
		// incremented by `SwapChain::update`, use to update other resources or track changes
		uint32_t m_changeID{ 0 };
		// surface
		VkExtent2D m_extent{ 0, 0 };
		// requested on update
		uint32_t m_updateWidth{ 0 };
		uint32_t m_updateHeight{ 0 };
		// if the swap operation is sync'ed with monitor
		bool m_vsync = false;
		// if vsync is off which mode to prefer
		VkPresentModeKHR m_preferredVsyncOffMode = VK_PRESENT_MODE_MAILBOX_KHR;
		// usage flags for swapchain images
		VkImageUsageFlags m_imageUsage{};

		VkResult waitIdle()
		{
			if (m_waitQueue)
				return vkQueueWaitIdle(m_waitQueue);
			else
				return vkDeviceWaitIdle(m_device);
		}

		// triggers device/queue wait idle
		void deinitResources();
	};
} // namespace ptvk