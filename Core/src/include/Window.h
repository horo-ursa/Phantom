#pragma once

#ifdef _WIN32
#pragma comment(linker, "/subsystem:console")
#define NOMINMAX
#include <windows.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <Instance.h>

namespace pt {
	

	class Window {
	public:
		struct Extent
		{
			uint32_t width;
			uint32_t height;
		};

		enum class Mode
		{
			Headless,
			Fullscreen,
			FullscreenBorderless,
			FullscreenStretch,
			Default
		};

		enum class Vsync
		{
			OFF,
			ON,
			Default
		};

		struct Properties
		{
			std::string title = "";
			Mode        mode = Mode::Default;
			bool        resizable = true;
			Vsync       vsync = Vsync::Default;
			Extent      extent = { 1280, 720 };
		};

		Window(Properties p)
			: width{p.extent.width}
			, height{p.extent.height}
			, name{ p.title} 
			, mode{p.mode}
			, vsync{p.vsync}
			, resizable{p.resizable}
			, property{p}
		{
			InitializeWindow();
		}

		~Window() {
			DestroyWindow();
		}


		void						InitializeWindow();
		bool						ShouldQuit();
		void						DestroyWindow();
		void						MainLoop();

		VkSurfaceKHR				createSurface(VkInstance& instance);
		VkSurfaceKHR				createSurface(pt::HPPInstance& instance);
		uint32_t					getWidth() const { return width; }
		uint32_t					getHeight() const { return height; }
		std::string					getName() const { return name; }
		std::vector<const char*>	getRequiredSurfaceExtensions() const;
		Properties                  getProperty() const { return property; }
		GLFWwindow*					get_handle() { return window; }

	private:
		GLFWwindow* window = nullptr;
		uint32_t width;
		uint32_t height;
		std::string name;
		bool resizable;
		Vsync vsync; 
		Mode mode;
		Properties property;
	};
};