#include "1_triangle/triangle.hpp"

namespace lve{
	Triangle::Triangle(){
		

	}
	
	void Triangle::run(){
		while(!lve_window.shouldClose()){
			glfwPollEvents();
		}
	}
};