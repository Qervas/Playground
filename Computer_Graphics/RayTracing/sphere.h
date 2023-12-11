#pragma once

#include"hittable.h"
#include "vec3.h"

class sphere: public hittable{
public:
	sphere() = default;
	~sphere() = default;
	sphere(point3 center, double radius, shared_ptr<material> mat)
			: _center(center), _radius(radius), _mat(mat){}

	virtual bool hit(const ray& r, interval&& ray_t, hit_record& rec) const override{
		vec3 oc = r.origin() - _center;
	    auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - _radius*_radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

		//find nearst root
		auto root = (-half_b - sqrtd) / a;
		if(!ray_t.surrounds(root)){
			root = (-half_b + sqrtd) / a;
			if(!ray_t.surrounds(root)){
				return false;
			}
		}
		rec._t = root;
		rec._p = r.at(rec._t);
		vec3 outward_normal = (rec._p - _center) / _radius;
		rec.set_face_normal(r, outward_normal);
		rec._mat = _mat;


		return true;

	}

private:
	point3 _center;
	double _radius;
	shared_ptr<material> _mat;
};