#include "1_triangle/triangle.hpp"

#include<iostream>
#include<cstdlib>
#include <iostream>
#include<filesystem>
#include<string>
namespace fs = std::filesystem;
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