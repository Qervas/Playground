#pragma once
#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable{
public:
	std::vector<shared_ptr<hittable>>  _objects;
	
	hittable_list(){}
	hittable_list(shared_ptr<hittable> objects){

	}

	void clear(){ _objects.clear();}
	void add(shared_ptr<hittable> object){
		_objects.emplace_back(object);
	}
	virtual  bool hit(const ray& r, interval&& ray_t, hit_record& rec) const override{
		hit_record tmp_rec;
		bool is_hit_anything = false;
		auto closest_so_far = ray_t.max;

		for(const auto& obj: _objects){
			if(obj->hit(r, interval(ray_t.min, closest_so_far), tmp_rec)){//set tmax as closest plane
				is_hit_anything = true;
				closest_so_far = tmp_rec.t;
				rec = tmp_rec;
			}
		}
		return is_hit_anything;
	}
};