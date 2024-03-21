#pragma once

#include <vector>
#include <vulkan\vulkan.hpp>


namespace pt
{
	namespace initializers
	{

		inline vk::MemoryAllocateInfo memoryAllocateInfo()
		{
			vk::MemoryAllocateInfo memAllocInfo{};
			memAllocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
			return memAllocInfo;
		}

		inline vk::MappedMemoryRange mappedMemoryRange()
		{
			vk::MappedMemoryRange mappedMemoryRange{};
			mappedMemoryRange.sType = vk::StructureType::eMappedMemoryRange;
			return mappedMemoryRange;
		}

		inline vk::CommandBufferAllocateInfo commandBufferAllocateInfo(
			vk::CommandPool commandPool,
			vk::CommandBufferLevel level,
			uint32_t bufferCount)
		{
			vk::CommandBufferAllocateInfo commandBufferAllocateInfo{};
			commandBufferAllocateInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
			commandBufferAllocateInfo.commandPool = commandPool;
			commandBufferAllocateInfo.level = level;
			commandBufferAllocateInfo.commandBufferCount = bufferCount;
			return commandBufferAllocateInfo;
		}

		inline vk::CommandPoolCreateInfo commandPoolCreateInfo()
		{
			vk::CommandPoolCreateInfo cmdPoolCreateInfo{};
			cmdPoolCreateInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
			return cmdPoolCreateInfo;
		}

		inline vk::CommandBufferBeginInfo commandBufferBeginInfo()
		{
			vk::CommandBufferBeginInfo cmdBufferBeginInfo{};
			cmdBufferBeginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
			return cmdBufferBeginInfo;
		}

		inline vk::CommandBufferInheritanceInfo commandBufferInheritanceInfo()
		{
			vk::CommandBufferInheritanceInfo cmdBufferInheritanceInfo{};
			cmdBufferInheritanceInfo.sType = vk::StructureType::eCommandBufferInheritanceInfo;
			return cmdBufferInheritanceInfo;
		}

		inline vk::RenderPassBeginInfo renderPassBeginInfo()
		{
			vk::RenderPassBeginInfo renderPassBeginInfo{};
			renderPassBeginInfo.sType = vk::StructureType::eRenderPassBeginInfo;
			return renderPassBeginInfo;
		}

		inline vk::RenderPassCreateInfo renderPassCreateInfo()
		{
			vk::RenderPassCreateInfo renderPassCreateInfo{};
			renderPassCreateInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			return renderPassCreateInfo;
		}

		/** @brief Initialize an image memory barrier with no image transfer ownership */
		inline vk::ImageMemoryBarrier imageMemoryBarrier()
		{
			vk::ImageMemoryBarrier imageMemoryBarrier{};
			imageMemoryBarrier.sType = vk::StructureType::eImageMemoryBarrier;
			imageMemoryBarrier.srcQueueFamilyIndex = vk::QueueFamilyIgnored;
			imageMemoryBarrier.dstQueueFamilyIndex = vk::QueueFamilyIgnored;
			return imageMemoryBarrier;
		}

		/** @brief Initialize a buffer memory barrier with no image transfer ownership */
		inline vk::BufferMemoryBarrier bufferMemoryBarrier()
		{
			vk::BufferMemoryBarrier bufferMemoryBarrier{};
			bufferMemoryBarrier.sType = vk::StructureType::eImageMemoryBarrier;
			bufferMemoryBarrier.srcQueueFamilyIndex = vk::QueueFamilyIgnored;
			bufferMemoryBarrier.dstQueueFamilyIndex = vk::QueueFamilyIgnored;
			return bufferMemoryBarrier;
		}

		//inline vk::MemoryBarrier memoryBarrier()
		//{
		//	vk::MemoryBarrier memoryBarrier{};
		//	memoryBarrier.sType = vk::StructureType::eMemoryBarrier;
		//	return memoryBarrier;
		//}

		inline vk::ImageCreateInfo imageCreateInfo()
		{
			vk::ImageCreateInfo imageCreateInfo{};
			imageCreateInfo.sType = vk::StructureType::eImageCreateInfo;
			return imageCreateInfo;
		}

		inline vk::SamplerCreateInfo samplerCreateInfo()
		{
			vk::SamplerCreateInfo samplerCreateInfo{};
			samplerCreateInfo.sType = vk::StructureType::eSamplerCreateInfo;
			samplerCreateInfo.maxAnisotropy = 1.0f;
			return samplerCreateInfo;
		}

		inline vk::ImageViewCreateInfo imageViewCreateInfo()
		{
			vk::ImageViewCreateInfo imageViewCreateInfo{};
			imageViewCreateInfo.sType = vk::StructureType::eImageViewCreateInfo;
			return imageViewCreateInfo;
		}

		inline vk::FramebufferCreateInfo framebufferCreateInfo()
		{
			vk::FramebufferCreateInfo framebufferCreateInfo{};
			framebufferCreateInfo.sType = vk::StructureType::eFramebufferCreateInfo;
			return framebufferCreateInfo;
		}

		inline vk::SemaphoreCreateInfo semaphoreCreateInfo()
		{
			vk::SemaphoreCreateInfo semaphoreCreateInfo{};
			semaphoreCreateInfo.sType = vk::StructureType::eSemaphoreCreateInfo;
			return semaphoreCreateInfo;
		}

		inline vk::FenceCreateInfo fenceCreateInfo(vk::FenceCreateFlags flags = {})
		{
			vk::FenceCreateInfo fenceCreateInfo{};
			fenceCreateInfo.sType = vk::StructureType::eFenceCreateInfo;
			fenceCreateInfo.flags = flags;
			return fenceCreateInfo;
		}

		inline vk::EventCreateInfo eventCreateInfo()
		{
			vk::EventCreateInfo eventCreateInfo{};
			eventCreateInfo.sType = vk::StructureType::eEventCreateInfo;
			return eventCreateInfo;
		}

		inline vk::SubmitInfo submitInfo()
		{
			vk::SubmitInfo submitInfo{};
			submitInfo.sType = vk::StructureType::eSubmitInfo;
			return submitInfo;
		}

		inline vk::Viewport viewport(
			float width,
			float height,
			float minDepth,
			float maxDepth)
		{
			vk::Viewport viewport{};
			viewport.width = width;
			viewport.height = height;
			viewport.minDepth = minDepth;
			viewport.maxDepth = maxDepth;
			return viewport;
		}

		inline vk::Rect2D rect2D(
			int32_t width,
			int32_t height,
			int32_t offsetX,
			int32_t offsetY)
		{
			vk::Rect2D rect2D{};
			rect2D.extent.width = width;
			rect2D.extent.height = height;
			rect2D.offset.x = offsetX;
			rect2D.offset.y = offsetY;
			return rect2D;
		}

		inline vk::BufferCreateInfo bufferCreateInfo()
		{
			vk::BufferCreateInfo bufCreateInfo{};
			bufCreateInfo.sType = vk::StructureType::eBufferCreateInfo;
			return bufCreateInfo;
		}

		inline vk::BufferCreateInfo bufferCreateInfo(
			vk::BufferUsageFlags usage,
			vk::DeviceSize size)
		{
			vk::BufferCreateInfo bufCreateInfo{};
			bufCreateInfo.sType = vk::StructureType::eBufferCreateInfo;
			bufCreateInfo.usage = usage;
			bufCreateInfo.size = size;
			return bufCreateInfo;
		}

		inline vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo(
			uint32_t poolSizeCount,
			vk::DescriptorPoolSize* pPoolSizes,
			uint32_t maxSets)
		{
			vk::DescriptorPoolCreateInfo descriptorPoolInfo{};
			descriptorPoolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
			descriptorPoolInfo.poolSizeCount = poolSizeCount;
			descriptorPoolInfo.pPoolSizes = pPoolSizes;
			descriptorPoolInfo.maxSets = maxSets;
			return descriptorPoolInfo;
		}

		inline vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo(
			const std::vector<vk::DescriptorPoolSize>& poolSizes,
			uint32_t maxSets)
		{
			vk::DescriptorPoolCreateInfo descriptorPoolInfo{};
			descriptorPoolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
			descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
			descriptorPoolInfo.pPoolSizes = poolSizes.data();
			descriptorPoolInfo.maxSets = maxSets;
			return descriptorPoolInfo;
		}

		inline vk::DescriptorPoolSize descriptorPoolSize(
			vk::DescriptorType type,
			uint32_t descriptorCount)
		{
			vk::DescriptorPoolSize descriptorPoolSize{};
			descriptorPoolSize.type = type;
			descriptorPoolSize.descriptorCount = descriptorCount;
			return descriptorPoolSize;
		}

		inline vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding(
			vk::DescriptorType type,
			vk::ShaderStageFlags stageFlags,
			uint32_t binding,
			uint32_t descriptorCount = 1)
		{
			vk::DescriptorSetLayoutBinding setLayoutBinding{};
			setLayoutBinding.descriptorType = type;
			setLayoutBinding.stageFlags = stageFlags;
			setLayoutBinding.binding = binding;
			setLayoutBinding.descriptorCount = descriptorCount;
			return setLayoutBinding;
		}

		inline vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(
			const vk::DescriptorSetLayoutBinding* pBindings,
			uint32_t bindingCount)
		{
			vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
			descriptorSetLayoutCreateInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
			descriptorSetLayoutCreateInfo.pBindings = pBindings;
			descriptorSetLayoutCreateInfo.bindingCount = bindingCount;
			return descriptorSetLayoutCreateInfo;
		}

		inline vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(
			const std::vector<vk::DescriptorSetLayoutBinding>& bindings)
		{
			vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
			descriptorSetLayoutCreateInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
			descriptorSetLayoutCreateInfo.pBindings = bindings.data();
			descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
			return descriptorSetLayoutCreateInfo;
		}

		inline vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo(
			const vk::DescriptorSetLayout* pSetLayouts,
			uint32_t setLayoutCount = 1)
		{
			vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
			pipelineLayoutCreateInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
			pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
			pipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
			return pipelineLayoutCreateInfo;
		}

		inline vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo(
			uint32_t setLayoutCount = 1)
		{
			vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
			pipelineLayoutCreateInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
			pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
			return pipelineLayoutCreateInfo;
		}

		inline vk::DescriptorSetAllocateInfo descriptorSetAllocateInfo(
			vk::DescriptorPool descriptorPool,
			const vk::DescriptorSetLayout* pSetLayouts,
			uint32_t descriptorSetCount)
		{
			vk::DescriptorSetAllocateInfo descriptorSetAllocateInfo{};
			descriptorSetAllocateInfo.sType = vk::StructureType::eDescriptorSetAllocateInfo;
			descriptorSetAllocateInfo.descriptorPool = descriptorPool;
			descriptorSetAllocateInfo.pSetLayouts = pSetLayouts;
			descriptorSetAllocateInfo.descriptorSetCount = descriptorSetCount;
			return descriptorSetAllocateInfo;
		}

		inline vk::DescriptorImageInfo descriptorImageInfo(vk::Sampler sampler, vk::ImageView imageView, vk::ImageLayout imageLayout)
		{
			vk::DescriptorImageInfo descriptorImageInfo{};
			descriptorImageInfo.sampler = sampler;
			descriptorImageInfo.imageView = imageView;
			descriptorImageInfo.imageLayout = imageLayout;
			return descriptorImageInfo;
		}

		inline vk::WriteDescriptorSet writeDescriptorSet(
			vk::DescriptorSet dstSet,
			vk::DescriptorType type,
			uint32_t binding,
			vk::DescriptorBufferInfo* bufferInfo,
			uint32_t descriptorCount = 1)
		{
			vk::WriteDescriptorSet writeDescriptorSet{};
			writeDescriptorSet.sType = vk::StructureType::eWriteDescriptorSet;
			writeDescriptorSet.dstSet = dstSet;
			writeDescriptorSet.descriptorType = type;
			writeDescriptorSet.dstBinding = binding;
			writeDescriptorSet.pBufferInfo = bufferInfo;
			writeDescriptorSet.descriptorCount = descriptorCount;
			return writeDescriptorSet;
		}

		inline vk::WriteDescriptorSet writeDescriptorSet(
			vk::DescriptorSet dstSet,
			vk::DescriptorType type,
			uint32_t binding,
			vk::DescriptorImageInfo* imageInfo,
			uint32_t descriptorCount = 1)
		{
			vk::WriteDescriptorSet writeDescriptorSet{};
			writeDescriptorSet.sType = vk::StructureType::eWriteDescriptorSet;
			writeDescriptorSet.dstSet = dstSet;
			writeDescriptorSet.descriptorType = type;
			writeDescriptorSet.dstBinding = binding;
			writeDescriptorSet.pImageInfo = imageInfo;
			writeDescriptorSet.descriptorCount = descriptorCount;
			return writeDescriptorSet;
		}

		inline vk::VertexInputBindingDescription vertexInputBindingDescription(
			uint32_t binding,
			uint32_t stride,
			vk::VertexInputRate inputRate)
		{
			vk::VertexInputBindingDescription vInputBindDescription{};
			vInputBindDescription.binding = binding;
			vInputBindDescription.stride = stride;
			vInputBindDescription.inputRate = inputRate;
			return vInputBindDescription;
		}

		inline vk::VertexInputAttributeDescription vertexInputAttributeDescription(
			uint32_t binding,
			uint32_t location,
			vk::Format format,
			uint32_t offset)
		{
			vk::VertexInputAttributeDescription vInputAttribDescription{};
			vInputAttribDescription.location = location;
			vInputAttribDescription.binding = binding;
			vInputAttribDescription.format = format;
			vInputAttribDescription.offset = offset;
			return vInputAttribDescription;
		}

		inline vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo()
		{
			vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
			pipelineVertexInputStateCreateInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
			return pipelineVertexInputStateCreateInfo;
		}

		inline vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
			const std::vector<vk::VertexInputBindingDescription>& vertexBindingDescriptions,
			const std::vector<vk::VertexInputAttributeDescription>& vertexAttributeDescriptions
		)
		{
			vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
			pipelineVertexInputStateCreateInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
			pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions.size());
			pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();
			pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributeDescriptions.size());
			pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();
			return pipelineVertexInputStateCreateInfo;
		}

		inline vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
			vk::PrimitiveTopology topology,
			vk::PipelineInputAssemblyStateCreateFlags flags,
			vk::Bool32 primitiveRestartEnable)
		{
			vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{};
			pipelineInputAssemblyStateCreateInfo.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
			pipelineInputAssemblyStateCreateInfo.topology = topology;
			pipelineInputAssemblyStateCreateInfo.flags = flags;
			pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = primitiveRestartEnable;
			return pipelineInputAssemblyStateCreateInfo;
		}

		inline vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
			vk::PolygonMode polygonMode,
			vk::CullModeFlags cullMode,
			vk::FrontFace frontFace,
			vk::PipelineRasterizationStateCreateFlags flags = {})
		{
			vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{};
			pipelineRasterizationStateCreateInfo.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
			pipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
			pipelineRasterizationStateCreateInfo.cullMode = cullMode;
			pipelineRasterizationStateCreateInfo.frontFace = frontFace;
			pipelineRasterizationStateCreateInfo.flags = flags;
			pipelineRasterizationStateCreateInfo.depthClampEnable = vk::False;
			pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
			return pipelineRasterizationStateCreateInfo;
		}

		inline vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
			vk::ColorComponentFlags colorWriteMask,
			vk::Bool32 blendEnable)
		{
			vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState{};
			pipelineColorBlendAttachmentState.colorWriteMask = colorWriteMask;
			pipelineColorBlendAttachmentState.blendEnable = blendEnable;
			return pipelineColorBlendAttachmentState;
		}

		inline vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
			uint32_t attachmentCount,
			const vk::PipelineColorBlendAttachmentState* pAttachments)
		{
			vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo{};
			pipelineColorBlendStateCreateInfo.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;
			pipelineColorBlendStateCreateInfo.attachmentCount = attachmentCount;
			pipelineColorBlendStateCreateInfo.pAttachments = pAttachments;
			return pipelineColorBlendStateCreateInfo;
		}

		inline vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
			vk::Bool32 depthTestEnable,
			vk::Bool32 depthWriteEnable,
			vk::CompareOp depthCompareOp)
		{
			vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo{};
			pipelineDepthStencilStateCreateInfo.sType = vk::StructureType::ePipelineDepthStencilStateCreateInfo;
			pipelineDepthStencilStateCreateInfo.depthTestEnable = depthTestEnable;
			pipelineDepthStencilStateCreateInfo.depthWriteEnable = depthWriteEnable;
			pipelineDepthStencilStateCreateInfo.depthCompareOp = depthCompareOp;
			pipelineDepthStencilStateCreateInfo.back.compareOp = vk::CompareOp::eAlways;
			return pipelineDepthStencilStateCreateInfo;
		}

		inline vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
			uint32_t viewportCount,
			uint32_t scissorCount,
			vk::PipelineViewportStateCreateFlags flags = {})
		{
			vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo{};
			pipelineViewportStateCreateInfo.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
			pipelineViewportStateCreateInfo.viewportCount = viewportCount;
			pipelineViewportStateCreateInfo.scissorCount = scissorCount;
			pipelineViewportStateCreateInfo.flags = flags;
			return pipelineViewportStateCreateInfo;
		}

		inline vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
			vk::SampleCountFlagBits rasterizationSamples,
			vk::PipelineMultisampleStateCreateFlags flags = {})
		{
			vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{};
			pipelineMultisampleStateCreateInfo.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
			pipelineMultisampleStateCreateInfo.rasterizationSamples = rasterizationSamples;
			pipelineMultisampleStateCreateInfo.flags = flags;
			return pipelineMultisampleStateCreateInfo;
		}

		inline vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
			const vk::DynamicState* pDynamicStates,
			uint32_t dynamicStateCount,
			vk::PipelineDynamicStateCreateFlags flags = {})
		{
			vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
			pipelineDynamicStateCreateInfo.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
			pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates;
			pipelineDynamicStateCreateInfo.dynamicStateCount = dynamicStateCount;
			pipelineDynamicStateCreateInfo.flags = flags;
			return pipelineDynamicStateCreateInfo;
		}

		inline vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
			const std::vector<vk::DynamicState>& pDynamicStates,
			vk::PipelineDynamicStateCreateFlags flags = {})
		{
			vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
			pipelineDynamicStateCreateInfo.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
			pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates.data();
			pipelineDynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(pDynamicStates.size());
			pipelineDynamicStateCreateInfo.flags = flags;
			return pipelineDynamicStateCreateInfo;
		}

		inline vk::PipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo(uint32_t patchControlPoints)
		{
			vk::PipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo{};
			pipelineTessellationStateCreateInfo.sType = vk::StructureType::ePipelineTessellationStateCreateInfo;
			pipelineTessellationStateCreateInfo.patchControlPoints = patchControlPoints;
			return pipelineTessellationStateCreateInfo;
		}

		inline vk::GraphicsPipelineCreateInfo pipelineCreateInfo(
			vk::PipelineLayout layout,
			vk::RenderPass renderPass,
			vk::PipelineCreateFlags flags = {})
		{
			vk::GraphicsPipelineCreateInfo pipelineCreateInfo{};
			pipelineCreateInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
			pipelineCreateInfo.layout = layout;
			pipelineCreateInfo.renderPass = renderPass;
			pipelineCreateInfo.flags = flags;
			pipelineCreateInfo.basePipelineIndex = -1;
			pipelineCreateInfo.basePipelineHandle = nullptr;
			return pipelineCreateInfo;
		}

		inline vk::GraphicsPipelineCreateInfo pipelineCreateInfo()
		{
			vk::GraphicsPipelineCreateInfo pipelineCreateInfo{};
			pipelineCreateInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
			pipelineCreateInfo.basePipelineIndex = -1;
			pipelineCreateInfo.basePipelineHandle = nullptr;
			return pipelineCreateInfo;
		}

		inline vk::ComputePipelineCreateInfo computePipelineCreateInfo(
			vk::PipelineLayout layout,
			vk::PipelineCreateFlags flags = {})
		{
			vk::ComputePipelineCreateInfo computePipelineCreateInfo{};
			computePipelineCreateInfo.sType = vk::StructureType::eComputePipelineCreateInfo;
			computePipelineCreateInfo.layout = layout;
			computePipelineCreateInfo.flags = flags;
			return computePipelineCreateInfo;
		}

		inline vk::PushConstantRange pushConstantRange(
			vk::ShaderStageFlags stageFlags,
			uint32_t size,
			uint32_t offset)
		{
			vk::PushConstantRange pushConstantRange{};
			pushConstantRange.stageFlags = stageFlags;
			pushConstantRange.offset = offset;
			pushConstantRange.size = size;
			return pushConstantRange;
		}

		inline vk::BindSparseInfo bindSparseInfo()
		{
			vk::BindSparseInfo bindSparseInfo{};
			bindSparseInfo.sType = vk::StructureType::eBindSparseInfo;
			return bindSparseInfo;
		}

		/** @brief Initialize a map entry for a shader specialization constant */
		inline vk::SpecializationMapEntry specializationMapEntry(uint32_t constantID, uint32_t offset, size_t size)
		{
			vk::SpecializationMapEntry specializationMapEntry{};
			specializationMapEntry.constantID = constantID;
			specializationMapEntry.offset = offset;
			specializationMapEntry.size = size;
			return specializationMapEntry;
		}

		/** @brief Initialize a specialization constant info structure to pass to a shader stage */
		inline vk::SpecializationInfo specializationInfo(uint32_t mapEntryCount, const vk::SpecializationMapEntry* mapEntries, size_t dataSize, const void* data)
		{
			vk::SpecializationInfo specializationInfo{};
			specializationInfo.mapEntryCount = mapEntryCount;
			specializationInfo.pMapEntries = mapEntries;
			specializationInfo.dataSize = dataSize;
			specializationInfo.pData = data;
			return specializationInfo;
		}

		/** @brief Initialize a specialization constant info structure to pass to a shader stage */
		inline vk::SpecializationInfo specializationInfo(const std::vector<vk::SpecializationMapEntry>& mapEntries, size_t dataSize, const void* data)
		{
			vk::SpecializationInfo specializationInfo{};
			specializationInfo.mapEntryCount = static_cast<uint32_t>(mapEntries.size());
			specializationInfo.pMapEntries = mapEntries.data();
			specializationInfo.dataSize = dataSize;
			specializationInfo.pData = data;
			return specializationInfo;
		}

		// Ray tracing related
		inline vk::AccelerationStructureGeometryKHR accelerationStructureGeometryKHR()
		{
			vk::AccelerationStructureGeometryKHR accelerationStructureGeometryKHR{};
			accelerationStructureGeometryKHR.sType = vk::StructureType::eAccelerationStructureGeometryKHR;
			return accelerationStructureGeometryKHR;
		}

		inline vk::AccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR()
		{
			vk::AccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{};
			accelerationStructureBuildGeometryInfoKHR.sType = vk::StructureType::eAccelerationStructureBuildGeometryInfoKHR;
			return accelerationStructureBuildGeometryInfoKHR;
		}

		inline vk::AccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR()
		{
			vk::AccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR{};
			accelerationStructureBuildSizesInfoKHR.sType = vk::StructureType::eAccelerationStructureBuildSizesInfoKHR;
			return accelerationStructureBuildSizesInfoKHR;
		}

		inline vk::RayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR()
		{
			vk::RayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR{};
			rayTracingShaderGroupCreateInfoKHR.sType = vk::StructureType::eRayTracingShaderGroupCreateInfoKHR;
			return rayTracingShaderGroupCreateInfoKHR;
		}

		inline vk::RayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR()
		{
			vk::RayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR{};
			rayTracingPipelineCreateInfoKHR.sType = vk::StructureType::eRayTracingPipelineCreateInfoKHR;
			return rayTracingPipelineCreateInfoKHR;
		}

		inline vk::WriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR()
		{
			vk::WriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR{};
			writeDescriptorSetAccelerationStructureKHR.sType = vk::StructureType::eWriteDescriptorSetAccelerationStructureKHR;
			return writeDescriptorSetAccelerationStructureKHR;
		}

	}
}