#pragma once

#ifndef DRAGON_CORE_CAMERA
#define DRAGON_CORE_CAMERA
#include"primitive.h"
#include"transform.h"
#pragma warning(disable:4996)
namespace dragon {
	struct Film {
		RGB **film;
		int width, height;
		Film(int height, int width) :width(width), height(height) {
			film = new RGB*[height];
			for (int i = 0; i < height; i++) {
				film[i] = new RGB[width];
			}
		}
		~Film() {
			for (int i = 0; i < height; i++) {
				delete[]film[i];
			}
			delete[]film;
		}
		void Write(int c) {
			::std::string s = "image" + ::std::to_string(c) + ".ppm";
			FILE *f = fopen(s.c_str(), "w");
			fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					int r = film[i][j].r.ToFloat() * 254;
					int g = film[i][j].g.ToFloat() * 254;
					int b = film[i][j].b.ToFloat() * 254;
					fprintf(f, "%d %d %d ", r, g, b);
				}
			}
			fclose(f);
		}
	};
	class Camera {
	public:
		Film *film;
		Point3f position;
		Camera(const Point3f&position, const Point3f&target,int width,int height) :
			position(position), target(target) {
			forward = (target - position).GetNorm();
			right =  (Vec3f(0, 1, 0) * forward).GetNorm();
			up = (forward * right).GetNorm();
			Transform WorldToCam;
			WorldToCam *= Translate(position.x, position.y, position.z);
			WorldToCam *= Transform(right, up, forward);
			//CamToWorld = Inverse(WorldToCam);
			CamToWorld = WorldToCam;
			film = new Film(width, height);
		}
		void ReBuild() {
			forward = (target - position).GetNorm();
			right = (Vec3f(0, 1, 0) * forward).GetNorm();
			up = (forward * right).GetNorm();
			Transform WorldToCam;
			WorldToCam *= Translate(position.x, position.y, position.z);
			WorldToCam *= Transform(right, up, forward);
			CamToWorld = WorldToCam;
		}
		Vec3f GetViewDir(const Point3f&pos)const {
			return (position - pos).GetNorm();
		}
		virtual void GenerateRay(const Vec2i &pix,Ray *r)const = 0;
		virtual ~Camera() {
			/*delete CamToWorld;*/
		};	
	protected:
		Vec3f up;
		Vec3f forward;
		Vec3f right;
		Point3f target;
		Transform CamToWorld;
	};
	class PerspectiveCamera :public Camera {
	private:
		Float fov, far, near;
		Transform RasterToCam;
	public:
		PerspectiveCamera(const Point3f&position, const Point3f&target,
			Float fov,Float near,Float far,int height,int width)
			:Camera(position, target,width,height) {
			Transform CameraToScreen = Perspective(fov, near, far, (Float)film->width / (Float)film->height);
			Transform ScreenToRaster = Scale(0.5f, -0.5f, 1.f) *
				Scale(film->width, film->height, 1.f) * Translate(Vec3f(1.f, -1.f, 0.f));
			RasterToCam = Inverse(CameraToScreen) * Inverse(ScreenToRaster);
		};

		void GenerateRay(const Vec2i&pix,Ray *r)const override {
			Point3f hit = RasterToCam(Point3f(pix.x,pix.y,0));
			r->d = Vec3f(hit.x, hit.y, hit.z).GetNorm();
			r->o = Point3f(0, 0, 0);
			CamToWorld(r);
		}
	};
}
#endif
