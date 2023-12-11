#pragma once

#include "vec3.h"

class ray
{
private:
	point3 _origin;
	vec3 _dir;
public:
	ray();
	ray(const point3& origin, const vec3& direction):_origin(origin), _dir(direction){}
	~ray();

	point3 origin() const {return _origin;}
	vec3 direction() const {return _dir;}

	point3 at(double t) const{
		return _origin + t * _dir;
	}
};

ray::ray(/* args */)
{
}

ray::~ray()
{
}
