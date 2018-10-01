#pragma once
#ifndef DRAGON_CORE_INTEGRATOR
#define DRAGON_CORE_INTEGRATOR
#include"primitive.h"
#include"camera.h"
#include"object.h"
#include"scene.h"
#include <vector>
namespace dragon {
	class Integrator {
	public:
		virtual RGB Sample(const Scene&s, const Ray &eye) = 0;
		virtual void Render(const Scene&s, const Camera&cam){
			Ray r;
			for (int i = 0; i < cam.film->height; i++) {
				for (int j = 0; j < cam.film->width; j++) {
					cam.GenerateRay(Vec2i(j, i), &r);
					cam.film->film[i][j] = Sample(s, r);
				}
			}
		}
	};
	class PhongIntegrator:public Integrator {
	public:
		PhongIntegrator() {}
		//Phong����ģ��
		RGB Sample(const Scene &s, const Ray &eye)override {
			HitInfo nearp,tmp;
			nearp.hitp = Point3f(1e30, 1e30, 1e30);
			RGB pix = WHITE;
			//Ѱ�����������Ľ���
			bool find = false;
			for (auto obj : s.objs) {
				if (obj->Hit(eye, &tmp)) {
					if (tmp.hitp.Distance(eye.o) < nearp.hitp.Distance(eye.o)) {
						nearp = tmp;
						find = true;
					}
				}
			}
			if (!find)return BLACK;
			//����ֱ�ӹ�Դ
			for (auto light : s.lights) {
				bool shade = false;
				//for (auto obj : s.objs) {
				//	//����������Դ֮�������壬�������Ӱ
				//	if (obj->isHit(Ray(light->pos, nearp.hitp))) {
				//		shade = true;
				//		break;
				//	}
				//}
				if (!shade) {
					auto view = (eye.o - nearp.hitp).GetNorm();
					pix *= nearp.mat->ComputeColor(view, light->GetDir(nearp.hitp),
						nearp.n,light->GetSDF(nearp.hitp),nearp.uv);
				}
			}
			return pix;
		}
	};
	class PathIntegrator:public Integrator {
	private:
		int maxDepth;
		int curDepth;
	public:
		PathIntegrator(int depth = 2):maxDepth(depth){}
		void Render(const Scene&s, const Camera&cam)override{
			Ray r;
			for (int i = 0; i < cam.film->height; i++) {
				for (int j = 0; j < cam.film->width; j++) {
					cam.GenerateRay(Vec2i(j, i), &r);
					curDepth = 0;
					cam.film->film[i][j] = Sample(s, r);
				}
			}
		}
		RGB Sample(const Scene &s, const Ray &eye)override {
			HitInfo nearp, tmp;
			nearp.hitp = Point3f(INFINITE_LARGE, INFINITE_LARGE, INFINITE_LARGE);
			RGB pix = BLACK;
			//Ѱ�����������Ľ���
			bool find = false;
			for (auto obj : s.objs) {
				if (obj->Hit(eye, &tmp)) {
					if (tmp.hitp.Distance(eye.o) < nearp.hitp.Distance(eye.o)) {
						nearp = tmp;
						find = true;
					}
				}
			}
			if (!find) {
				return BLACK;
			}
			//����ֱ�ӹ�Դ
			for (auto light : s.lights) {
				bool shade = false;
				//����������Դ֮���в�͸�����壬�������Ӱ
				//for (auto obj : s.objs) {
				//	if (obj->isHit(Ray(light->pos, nearp.hitp))) {
				//		shade = true;
				//		break;
				//	}
				//}
				if (!shade) {
					pix += nearp.mat->ComputeColor(-eye.d, light->GetDir(nearp.hitp),
						nearp.n, light->GetSDF(nearp.hitp),nearp.uv);
				}
			}
			while (curDepth < maxDepth) {
				curDepth++;
				Float Kr;
				if(nearp.mat->isReflect() && nearp.mat->isRefract())
					Kr = Fresnel(eye.d, nearp.n, nearp.mat->eta);
				else Kr = 1;
				//���������Է���ͼ����ݹ�
				if (nearp.mat->isReflect() && nearp.n.Dot(-eye.d) > 0) {
					Ray newray = Ray(nearp.hitp, Reflect(eye.d, nearp.n));
					pix += (Sample(s, newray) * nearp.mat->gloss );
				}
				//������������������ݹ�
				if (nearp.mat->isRefract()) {
					Ray newray = Ray(nearp.hitp, Refract(eye.d, nearp.n, nearp.mat->eta));
					pix += (Sample(s, newray) );
				}
				else break;
			}
			return pix;
		}
	};
}
#endif
