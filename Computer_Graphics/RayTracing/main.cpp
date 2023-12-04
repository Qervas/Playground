#include "helper.h"
#include "color.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
#include <fstream> // Include the fstream header
#include <random>



int main() {



	//World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0.0,0.0,-1.0), 0.5));
	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100));
	

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);


    // Open a file for writing
    std::ofstream ppmFile("output.ppm");

    // Check if the file is open successfully
    if (!ppmFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return 1;
    }

	camera cam(ppmFile);

	
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 2000;
	cam.samples_per_pixel = 100;
	cam.render(world);
    // Close the file when done
    ppmFile.close();

    return 0;
}
