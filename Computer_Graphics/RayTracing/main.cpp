#include "vec3.h"
#include "color.h"
#include <iostream>
#include <fstream> // Include the fstream header
#include <random>
int main() {
    // Image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = static_cast<int>(image_width/ aspect_ratio);

	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
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
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), dis(gen));
            write_color(ppmFile, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

    // Close the file when done
    ppmFile.close();

    return 0;
}
