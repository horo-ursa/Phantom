#pragma once

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

#define LOGGER_FORMAT "[%^%l%$] %v"
#define PROJECT_NAME "Phantom"

 // Mainly for IDEs
#ifndef ROOT_PATH_SIZE
#	define ROOT_PATH_SIZE 0
#endif

#define __FILENAME__ (static_cast<const char *>(__FILE__) + ROOT_PATH_SIZE)

#define LOGI(...) spdlog::info(__VA_ARGS__);
#define LOGW(...) spdlog::warn(__VA_ARGS__);
#define LOGE(...) spdlog::error("[{}:{}] {}", __FILENAME__, __LINE__, fmt::format(__VA_ARGS__));
#define LOGD(...) spdlog::debug(__VA_ARGS__);


#ifdef _DEBUG
#define VK_DEBUG 1
#define VK_VALIDATION_LAYERS 1
#else
#define VK_DEBUG 0
#define VK_VALIDATION_LAYERS 0
#endif

//
//std::string errorString(VkResult errorCode)
//{
//	switch (errorCode)
//	{
//#define STR(r) case VK_ ##r: return #r
//		STR(NOT_READY);
//		STR(TIMEOUT);
//		STR(EVENT_SET);
//		STR(EVENT_RESET);
//		STR(INCOMPLETE);
//		STR(ERROR_OUT_OF_HOST_MEMORY);
//		STR(ERROR_OUT_OF_DEVICE_MEMORY);
//		STR(ERROR_INITIALIZATION_FAILED);
//		STR(ERROR_DEVICE_LOST);
//		STR(ERROR_MEMORY_MAP_FAILED);
//		STR(ERROR_LAYER_NOT_PRESENT);
//		STR(ERROR_EXTENSION_NOT_PRESENT);
//		STR(ERROR_FEATURE_NOT_PRESENT);
//		STR(ERROR_INCOMPATIBLE_DRIVER);
//		STR(ERROR_TOO_MANY_OBJECTS);
//		STR(ERROR_FORMAT_NOT_SUPPORTED);
//		STR(ERROR_SURFACE_LOST_KHR);
//		STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
//		STR(SUBOPTIMAL_KHR);
//		STR(ERROR_OUT_OF_DATE_KHR);
//		STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
//		STR(ERROR_VALIDATION_FAILED_EXT);
//		STR(ERROR_INVALID_SHADER_NV);
//		STR(ERROR_INCOMPATIBLE_SHADER_BINARY_EXT);
//#undef STR
//	default:
//		return "UNKNOWN_ERROR";
//	}
//}
//
//std::string errorString(vk::Result errorCode)
//{
//    switch (errorCode)
//    {
//        // Using vk::Result enum class members directly
//    case vk::Result::eNotReady: return "NOT_READY";
//    case vk::Result::eTimeout: return "TIMEOUT";
//    case vk::Result::eEventSet: return "EVENT_SET";
//    case vk::Result::eEventReset: return "EVENT_RESET";
//    case vk::Result::eIncomplete: return "INCOMPLETE";
//    case vk::Result::eErrorOutOfHostMemory: return "ERROR_OUT_OF_HOST_MEMORY";
//    case vk::Result::eErrorOutOfDeviceMemory: return "ERROR_OUT_OF_DEVICE_MEMORY";
//    case vk::Result::eErrorInitializationFailed: return "ERROR_INITIALIZATION_FAILED";
//    case vk::Result::eErrorDeviceLost: return "ERROR_DEVICE_LOST";
//    case vk::Result::eErrorMemoryMapFailed: return "ERROR_MEMORY_MAP_FAILED";
//    case vk::Result::eErrorLayerNotPresent: return "ERROR_LAYER_NOT_PRESENT";
//    case vk::Result::eErrorExtensionNotPresent: return "ERROR_EXTENSION_NOT_PRESENT";
//    case vk::Result::eErrorFeatureNotPresent: return "ERROR_FEATURE_NOT_PRESENT";
//    case vk::Result::eErrorIncompatibleDriver: return "ERROR_INCOMPATIBLE_DRIVER";
//	default:
//		return "UNKNOWN_ERROR";
//    }
//}
//
//template<typename T>
//void checkResultImpl(T result, const char* file, int line);
//
//template<>
//void checkResultImpl<VkResult>(VkResult result, const char* file, int line) {
//	if (result != VK_SUCCESS) {
//		LOGE("Detected Vulkan error: {}", errorString(result));
//		assert(result == VK_SUCCESS);
//	}
//}
//
//template<>
//void checkResultImpl<vk::Result>(vk::Result result, const char* file, int line) {
//	if (result != vk::Result::eSuccess) {
//		LOGE("Detected Vulkan error: {}", errorString(result));
//		assert(result == vk::Result::eSuccess);
//	}
//}
//
//#define VK_CHECK_RESULT(f) checkResultImpl(f, __FILE__, __LINE__)