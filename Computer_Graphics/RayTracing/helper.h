#pragma once

#include<cmath>
#include<random>
#include<limits>
#include<memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constants
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);


//utility functions

inline double degrees_to_radians(double degrees){
	return degrees*pi/180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return dis(gen);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * dis(gen);
}

#include "interval.h"
#include "ray.h"
#include "vec3.h"