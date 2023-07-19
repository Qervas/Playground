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

			void setWidth(int width);
			void setHeight(int height);
			void setWindowResizedFlag(bool flag);
			VkExtent2D getExtent();
			GLFWwindow* getWindow() const;
			bool shouldClose();
			bool isWindowResized();
			void resetWindowResizedFlag();
			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
			
			
		private:
			
			GLFWwindow* _window;
			int _width;
			int _height;
			bool _framebuffer_resized = false;
			std::string _window_name;
			
			
			static void framebufferResizeCallback(GLFWwindow* window, int width, int height); 
			void initWindow();
	};
};