#pragma once

#include "ray.h"
#include "helper.h"
class material;

class hit_record{
public:
	point3 _p;
	vec3 _normal;
	double _t;
	bool _front_face;
	shared_ptr<material> _mat;
	/*
	outward_normal should be an unit vector
	*/
	void set_face_normal(const ray& r, const vec3& outward_normal){
		//hit record normal vector
		_front_face = dot(r.direction(), outward_normal) < 0;
		_normal = _front_face ? outward_normal : -outward_normal;
	}
};

class hittable{
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval&& ray_t, hit_record& rec) const = 0;
};
