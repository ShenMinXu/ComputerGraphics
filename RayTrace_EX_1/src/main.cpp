#include "primitive.h"
#include "object.h"
#include"camera.h"
#include"integrator.h"
#include <iostream>
#include "math.h"
using namespace dragon;
int main() {
	Scene scene;
	PerspectiveCamera c(Point3f(0, 0, -40), Point3f(0, 0, 0), 39, 1e-2f, 1000.f, 1400, 1400);
	PMaterial glass(new GlassMat(Vec3f(0.5, 0.5, 0.5), Vec3f(0.7, 0.7, 0.7), 1.6, 1.32));
	PMaterial red(new MatteMat(Vec3f(1.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f), 10));
	PMaterial green(new MatteMat(Vec3f(0.f, 1.f, 0.f), Vec3f(1.f, 1.f, 1.f), 10));
	PMaterial check(new CheckMat(Vec3f(0.f, 1.f, 0.f), Vec3f(1.f, 1.f, 1.f), Vec2f(0.2,0.2),10));
	PMaterial blue(new MatteMat(Vec3f(0.f, 0.f, 1.f), Vec3f(1.f, 1.f, 1.f), 10));
	PMaterial golden(new MetalMat(Vec3f(0.f, 0.f, 0.f), Vec3f(1, 0.782, 0.344), Ratio(1), 0.8,0.5));
	PMaterial colorful(new RandomMat());
	PLight L1(new DirectionLight(Vec3f(1, 1, 1), RGB(0.7, 0.7, 0.7)));
	PLight L2(new DirectionLight(Vec3f(-1, -1, -1), RGB(0.5, 0.5, 0.5)));
	PObject s1(new Sphere(Point3f(0, 0, -5), 5, glass));
	PObject s2(new Sphere(Point3f(10, 0, 0), 5, red));
	PObject s3(new Sphere(Point3f(-10, 0, 0), 5, green));
	PObject s4(new Sphere(Point3f(0, -6, 0), 5, blue));
	PObject s5(new Sphere(Point3f(0, 10, 0), 5, golden));
	PObject s6(new Sphere(Point3f(10, -10, 0), 5, colorful));
	//PObject s7(new RotatingParabolic(Point3f(0, 0, 0), Vec2f(1,1),Vec2f(0,1), colorful));
	PObject f(new Floor(Point3f(0, 0, 15), 40, 40, Vec3f(0, 0, 0), check));
	//PObject f1(new Floor(Point3f(0, -15, 5), 80, 80, Vec3f(-90, 0, 0), check));
	scene.objs.push_back(f);
	//scene.objs.push_back(f1);
	scene.lights.push_back(L1);
	scene.lights.push_back(L2);
	scene.objs.push_back(s1);
	scene.objs.push_back(s2);
	scene.objs.push_back(s3);
	scene.objs.push_back(s4);
	scene.objs.push_back(s5);
	//scene.objs.push_back(s6);
	//scene.objs.push_back(s7);
	PathIntegrator it(4);
	//PhongIntegrator it;
	//Point3f pos(-80, 0, -80);
	//for (int i = 0; i < 80;i++) {
	//	//c.position = RotateY(-i)(pos);
	//	c.position.y += i;
	//	c.ReBuild();
	//	it.Render(scene, c);
	//	c.film->Write(i);
	//}
	it.Render(scene, c);
	c.film->Write(556);
	return 0;
}