#pragma once

#include "helper.h"
#include "color.h"
#include "hittable.h"

class material {
public:
	virtual ~material() = default;

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const = 0;

};

class lambertian: public material{
public:
	lambertian(const color& a): _albedo(a){}
	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const override{
		auto scatter_direction = rec._normal + random_unit_vector();
		if(scatter_direction.near_zero()){
			scatter_direction = rec._normal;
		}
		scattered = ray(rec._p, scatter_direction);
		attenuation = _albedo;//can be albedo/(a possibility value)
		return true;
	}

private:
	color _albedo;
};

class metal: public material{
public:
	metal(const color a, double f): _albedo{a}, _fuzz{f < 1 ? f : 1}{}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    	const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec._normal);
        scattered = ray(rec._p, reflected + _fuzz * random_unit_vector());
        attenuation = _albedo;
        return (dot(scattered.direction(), rec._normal) > 0);
    }

private: 
	color _albedo;
	double _fuzz;
};