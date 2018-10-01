#pragma once
#ifndef DRAGON_CORE_LIGHT
#define DRAGON_CORE_LIGHT
#include"primitive.h"
namespace dragon {
	class Light {
	public:
		Light() {};
		virtual ~Light() {};
		virtual Vec3f GetDir(const Point3f&pos)const = 0;
		virtual RGB GetSDF(const Point3f&pos)const = 0;
	};
	class DirectionLight :public Light {
	public:
		Vec3f dir;
		RGB SDF;
		DirectionLight(const Vec3f&dir,const RGB&color)
			:dir(dir),SDF(color){}
		Vec3f GetDir(const Point3f&pos)const override {
			return dir.GetNorm();
		}
		RGB GetSDF(const Point3f&pos)const override {
			return SDF;
		}
	};
	typedef ::std::shared_ptr<DirectionLight> PDirectionLight;
	typedef ::std::shared_ptr<Light>PLight;
}

#endif
