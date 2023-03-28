#include "1_triangle/triangle.hpp"

#include<iostream>
#include<cstdlib>

int main(int argc, char** argv){
	lve::Triangle app{};

	try	{
		app.run();
	}
	catch(const std::exception& e)	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
	
}