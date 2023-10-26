#include <assert.h>
#include <stdexcept>
#include <cstdio>
#include <cstdarg>
#include <array>

#define VK_ASSERT(func_call) { \
    VkResult result = (func_call); \
    assert(!result); \
}

#define VK_CHECK_RESULT(func_call, error_msg)   \
    if ((func_call) != VK_SUCCESS) {            \
        throw std::runtime_error(error_msg);    \
    }

#define LOG(...) printf(__VA_ARGS__)

#define LOGE(...) \
    [&]() { \
        std::array<char, 512> errorMsg; \
        std::snprintf(errorMsg.data(), errorMsg.size(), __VA_ARGS__); \
        throw std::runtime_error(errorMsg.data()); \
    }()
