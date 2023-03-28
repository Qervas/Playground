#include "1_triangle/lve_window.hpp"

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

	void LVEWindow::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(_width, _height, _window_name.c_str(), nullptr, nullptr);

	}

	void LVEWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if(glfwCreateWindowSurface(instance, _window, nullptr, surface)){
			throw std::__throw_runtime_error("failed to create a window surface");
		}
		

	}
};