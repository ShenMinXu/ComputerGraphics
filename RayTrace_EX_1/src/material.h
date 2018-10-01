#pragma once
#ifndef DRAGON_CORE_MATERIAL
#define DRAGON_CORE_MATERIAL
#include"primitive.h"
namespace dragon {
	class Texture {
		virtual RGB getColor(const Vec2f&uv) const = 0;
	};
	class CheckTex:public Texture {
	private:
		Vec2f res;
	public:
		CheckTex(const Vec2f&res):res(res){}
		RGB getColor(const Vec2f&uv) const override {
			int index = (int)(uv.x / res.x) + (int)(uv.y / res.y);
			if (index > 10) {
				int i = 1;
			}
			if ( index % 2) {
				return WHITE;
			}
			else return BLACK;
		}
	};
	class Material {
	public:
		Float eta;//折射率
		Float gloss;//反射光泽度
		Material(Float eta,Float gloss):eta(eta),gloss(gloss) {};
		virtual bool isReflect()const = 0;
		virtual bool isRefract()const = 0;
		virtual ~Material() {};
		virtual RGB ComputeColor(const Vec3f&view, const Vec3f&ray,const Normal&n,
			const RGB&light,const Vec2f&uv)const = 0;
	};
	class MatteMat :public Material {
	private:
		Float shininess;
		Vec3f Kd;
		Vec3f Ks;
	public:
		MatteMat(const Vec3f&Kd, const Vec3f&Ks, Float shininess) 
			:Kd(Kd), Ks(Ks), shininess(shininess),Material(0,0) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray,const Normal&n,
			const RGB&lightSDF,const Vec2f&uv)const override {
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = lightSDF * Kd * diffratio;	
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			return t;
		}
		bool isRefract()const override {
			return false;
		}
		bool isReflect()const override {
			return false;
		}
	};
	class GlassMat :public Material{
	private:
		Float shininess;
		Float glossiness;
		Vec3f Kd;
		Vec3f Ks;
	public:
		GlassMat(const Vec3f&Kd, const Vec3f&Ks, Float shininess, Float eta)
			:Kd(Kd), Ks(Ks), shininess(shininess),Material(eta,1) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n, 
			const RGB&lightSDF,const Vec2f&uv)const override{
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = BLACK;// lightSDF * Kd * diffratio;
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			return BLACK;
		}
		bool isReflect()const override {
			return true;
		}
		bool isRefract()const override {
			return true;
		}
	};
	class CheckMat:public Material {
	private:
		Float shininess;
		Vec3f Kd;
		Vec3f Ks;
		CheckTex tex;
	public:
		CheckMat(const Vec3f&Kd, const Vec3f&Ks, const Vec2f&grid, Float shininess)
			:Kd(Kd), Ks(Ks), shininess(shininess),tex(grid), Material(0,0) {}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n, 
			const RGB&lightSDF, const Vec2f&uv)const override {
			Float diffratio = (-ray).Dot(n);
			if (diffratio <= 0.f)return BLACK;
			RGB t = lightSDF * Kd * diffratio;
			Float sradio = Reflect(ray, n).Dot(view);
			if (sradio > 0) {
				Float spratio = powf(sradio, shininess);
				t += lightSDF * Ks * spratio;
			}
			t += tex.getColor(uv);
			return t;
		}
		bool isRefract()const override {
			return false;
		}
		bool isReflect()const override {
			return false;
		}
	};
	class MetalMat:public Material {
	private:
		Ratio metalness;
		Float shinness;
		Vec3f Kd;
		Vec3f Ks;
	public:
		MetalMat(const Vec3f&Kd, const Vec3f&Ks,Ratio metalness, Float shinness, Float gloss) :
			metalness(metalness), shinness(shinness), Kd(Kd), Ks(Ks),Material(0,gloss) {}
		virtual bool isReflect()const override{
			return true;
		}
		virtual bool isRefract()const {
			return false;
		}
		virtual RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n,
			const RGB&light, const Vec2f&uv)const override {
			RGB t = BLACK;
			Float diffr = Dot((-ray).GetNorm(), n);
			if (diffr < 0)return t;
			Float specr = Dot((view).GetNorm(), Reflect(ray, n));
			if (specr > 0)
				specr = pow(specr, shinness);
			else specr = 0;
			t += light * Kd * (1 - metalness.ToFloat()) * diffr + light * Ks * specr;
			return t;
		}
	};
	class RandomMat:public Material{
	public:
		RandomMat() :Material(0,0) {}
		bool isReflect()const override{
			return true;
		}
		bool isRefract()const override{
			return false;
		}
		RGB ComputeColor(const Vec3f&view, const Vec3f&ray, const Normal&n,
			const RGB&light, const Vec2f&uv)const override {
			return RGB(std::abs(n.x), std::abs(n.y), std::abs(n.z));
		}
	};
	typedef ::std::shared_ptr<MatteMat> PMatteMat;
	typedef ::std::shared_ptr<GlassMat> PGlassMat;
	typedef ::std::shared_ptr<Material> PMaterial;
}
#endif
