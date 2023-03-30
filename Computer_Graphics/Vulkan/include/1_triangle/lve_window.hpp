#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace lve{
	class LVEWindow{
		public:
			LVEWindow(int width, int height, std::string window_name);
			LVEWindow(const LVEWindow&) = delete;
			~LVEWindow();
			LVEWindow &operator=(const LVEWindow&)=delete;

			bool shouldClose();
			VkExtent2D getExtent();
			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
		private:
			GLFWwindow* _window;
			const int _width;
			const int _height;
			std::string _window_name;
			void initWindow();
	};
};