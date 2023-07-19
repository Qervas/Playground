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

	void LVEWindow::setWidth(int width){
		_width = width;
	}

	void LVEWindow::setHeight(int height){
		_height = height;
	}

	void LVEWindow::setWindowResizedFlag(bool flag){
		_framebuffer_resized = flag;
	}


	VkExtent2D LVEWindow::getExtent(){
		return {static_cast<uint32_t>(_width), static_cast<uint32_t>(_height)};
	}

	GLFWwindow* LVEWindow::getWindow() const{
		return _window;
	}

	bool LVEWindow::shouldClose(){
		return glfwWindowShouldClose(_window);
	}

	bool LVEWindow::isWindowResized(){
		return _framebuffer_resized;
	}

	void LVEWindow::resetWindowResizedFlag(){
		_framebuffer_resized = false;
	}


	void LVEWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height){
		auto lve_window = reinterpret_cast<LVEWindow*>(glfwGetWindowUserPointer(window));
		lve_window->setWidth(width);
		lve_window->setHeight(height);
		lve_window->setWindowResizedFlag(true);
	}

	void LVEWindow::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		_window = glfwCreateWindow(_width, _height, _window_name.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(_window, this);
		glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);
		glfwMakeContextCurrent(_window);
	}


	void LVEWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if(glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS){
			throw std::runtime_error("failed to create a window surface");
		}
		

	}

};