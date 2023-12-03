#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream> // Include the fstream header
#include <random>

color ray_color(const ray& r){
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);
	return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	
}


int main() {
    // Image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 1800;
	int image_height = static_cast<int>(image_width/ aspect_ratio);

	//Camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
	auto camera_center = point3(0,0,0);
	

	//Image height

	//viewport vectrors along the viewport edges
	auto viewport_u = vec3(viewport_width, 0,0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	//delta vectors of pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	//upper left pixel location
	auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	//Render

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

    // Write the P3 PPM header
    ppmFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
            write_color(ppmFile, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

    // Close the file when done
    ppmFile.close();

    return 0;
}
