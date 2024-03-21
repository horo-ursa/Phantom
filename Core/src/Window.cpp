#include <stdio.h>
#include "Window.h"

namespace pt {

    VkSurfaceKHR Window::createSurface(VkInstance& instance) {
        if (instance == VK_NULL_HANDLE || !window)
        {
            return VK_NULL_HANDLE;
        }

        VkSurfaceKHR surface;
        VkResult errCode = glfwCreateWindowSurface(instance, window, NULL, &surface);
        if (errCode != VK_SUCCESS)
        {
            return nullptr;
        }

        return surface;
    }

    VkSurfaceKHR Window::createSurface(pt::HPPInstance& instance) {
        if (instance.get_handle() == VK_NULL_HANDLE || !window)
        {
            return VK_NULL_HANDLE;
        }

        VkSurfaceKHR surface;
        VkResult errCode = glfwCreateWindowSurface(instance.get_handle(), window, NULL, &surface);
        if (errCode != VK_SUCCESS)
        {
            return nullptr;
        }

        return surface;
    }

    void Window::InitializeWindow() {
        if (!glfwInit()) {
            fprintf(stderr, "Failed to initialize GLFW\n");
            exit(EXIT_FAILURE);
        }

        if (!glfwVulkanSupported()) {
            fprintf(stderr, "Vulkan not supported\n");
            exit(EXIT_FAILURE);
        }

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (!window) {
            fprintf(stderr, "Failed to initialize GLFW window\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    }

    bool Window::ShouldQuit() {
        return !!glfwWindowShouldClose(window);
    }

    void Window::DestroyWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::MainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    std::vector<const char*> Window::getRequiredSurfaceExtensions() const {
        uint32_t     glfw_extension_count{ 0 };
        const char** names = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
        return { names, names + glfw_extension_count };
    }

}