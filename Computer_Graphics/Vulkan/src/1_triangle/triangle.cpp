#include "1_triangle/triangle.hpp"

namespace lve{
	Triangle::Triangle(){
		

	}
	
	void Triangle::run(){
		while(!_lve_window.shouldClose()){
			glfwPollEvents();
		}
	}
};