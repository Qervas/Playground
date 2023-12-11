#include "helper.h"
#include "color.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <iostream>
#include <fstream> // Include the fstream header
#include <random>



int main() {



	//World
	hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.4));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<metal>(color(0.5, 0.6, 0.4), 0.0);
	auto material_behind = make_shared<lambertian>(color(0.3,0.3,0.3));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-2.0,    1.0, -1.0),   1.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
	world.add(make_shared<sphere>(point3(0.0,	  0.0, -2.3),  0.5, material_behind));

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
    cam.image_width  = 800;
	cam.samples_per_pixel = 15;
	cam.max_depth = 100;
	cam.render(world);
    // Close the file when done
    ppmFile.close();

    return 0;
}
