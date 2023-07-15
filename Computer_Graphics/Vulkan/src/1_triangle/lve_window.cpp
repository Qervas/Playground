#include "1_triangle/lve_window.hpp"
#include <stdexcept>
namespace lve{
	LVEWindow::LVEWindow(int width, int height, std::string window_name)
				: _width(width), _height(height), _window_name(window_name){
					initWindow();
				}

	LVEWindow::~LVEWindow(){ 
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	bool LVEWindow::shouldClose(){
		return glfwWindowShouldClose(_window);
	}

	VkExtent2D LVEWindow::getExtent(){
		return {static_cast<uint32_t>(_width), static_cast<uint32_t>(_height)};
	}

	void LVEWindow::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(_width, _height, _window_name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
	}

	void LVEWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if(glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS){
			throw std::runtime_error("failed to create a window surface");
		}
		

	}
};