#pragma once
#ifndef DRAGON_CORE_TRANSFORM
#define DRAGON_CORE_TRANSFORM
#include<iostream>
#include<cmath>
#include<cstring>
#include"primitive.h"
namespace dragon {
	struct Matrix44 {
		Matrix44() {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j)m[i][j] = 1;
					else
						m[i][j] = 0;
				}
				r[i] = i;
			}
		}
		Matrix44(Float t00, Float t01, Float t02, Float t03, Float t10,
			Float t11, Float t12, Float t13, Float t20, Float t21,
			Float t22, Float t23, Float t30, Float t31, Float t32,
			Float t33) {
			m[0][0] = t00;
			m[0][1] = t01;
			m[0][2] = t02;
			m[0][3] = t03;
			m[1][0] = t10;
			m[1][1] = t11;
			m[1][2] = t12;
			m[1][3] = t13;
			m[2][0] = t20;
			m[2][1] = t21;
			m[2][2] = t22;
			m[2][3] = t23;
			m[3][0] = t30;
			m[3][1] = t31;
			m[3][2] = t32;
			m[3][3] = t33;
			for (int i = 0; i < 4; i++) {
				r[i] = i;
			}
		}
		Matrix44(Float m44[4][4]) {
			memcpy(m, m44, 16 * sizeof(Float));
			for (int i = 0; i < 4; i++) {
				r[i] = i;
			}
		}
		Matrix44(const Matrix44 &x) {
			memcpy(m, x.m, 16 * sizeof(Float));
			memcpy(r, x.r, 4 * sizeof(char));
		}
		Matrix44(const Vec3f&xaxis, const Vec3f&yaxis, const Vec3f&zaxis) {
			for (int i = 0; i < 3; i++) {
				m[i][0] = xaxis[i];
				m[i][1] = yaxis[i];
				m[i][2] = zaxis[i];
				m[i][3] = 0;
				m[3][i] = 0;
				r[i] = i;
			}
			m[3][3] = 1;
			r[3] = 3;
		}
		Matrix44 Transpose() {
			return Matrix44(m[r[0]][0], m[r[1]][0], m[r[2]][0], m[r[3]][0], m[r[0]][1],
				m[r[1]][1], m[r[2]][1], m[r[3]][1], m[r[0]][2], m[r[1]][2],
				m[r[2]][2], m[r[3]][2], m[r[0]][3], m[r[1]][3], m[r[2]][3],
				m[r[3]][3]);
		}
		Matrix44 Mul(const Matrix44&m1)const {
			Matrix44 n;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					n.m[r[i]][j] = m[r[i]][0] * m1.m[r[0]][j] + m[r[i]][1] * m1.m[r[1]][j] +
						m[r[i]][2] * m1.m[r[2]][j] + m[r[i]][3] * m1.m[r[3]][j];
				}
			}
			return n;
		}
		Matrix44 Inverse() {
			Matrix44 n(m),x;
			for (int i = 0; i < 4; i++) {
				if (n.m[r[i]][i] <= INFINITE_SMALL) {
					bool invertable = false;
					for (int j = i + 1; j < 4; j++) {
						if (n.m[r[i]][j] > INFINITE_SMALL) {
							invertable = true;
							break;
						}
					}
					if (!invertable) {
						std::cout << "Matrix can not invert!" << std::endl;
						std::abort();
					}
				}
				auto s = n.m[r[i]][i];
				for (int j = 0; j < 4; j++) {
					n.m[r[i]][j] /= s;
					x.m[r[i]][j] /= s;
				}
				for (int j = 0; j < 4; j++) {
					if (j != i) {
						auto scale = n.m[r[j]][i];
						for (int k = 0; k < 4; k++) {
							 auto t = scale * n.m[r[i]][k];
							 n.m[r[j]][k] -= t;
							 auto tt = scale * x.m[r[i]][k];
							 x.m[r[j]][k] -= tt;
						}
					}
				}
			}
			return x;
		}
		Float m[4][4];
		char r[4];
	};
	::std::ostream &operator<<(::std::ostream&s,const Matrix44 &m) {
		std::cout << m.m[m.r[0]][0] << " " << m.m[m.r[0]][1] << " " << m.m[m.r[0]][2] << " " << m.m[m.r[0]][3] << std::endl;
		std::cout << m.m[m.r[1]][0] << " " << m.m[m.r[1]][1] << " " << m.m[m.r[1]][2] << " " << m.m[m.r[1]][3] << std::endl;
		std::cout << m.m[m.r[2]][0] << " " << m.m[m.r[2]][1] << " " << m.m[m.r[2]][2] << " " << m.m[m.r[2]][3] << std::endl;
		std::cout << m.m[m.r[3]][0] << " " << m.m[m.r[3]][1] << " " << m.m[m.r[3]][2] << " " << m.m[m.r[3]][3] << std::endl;
		return s;
	}
	class Transform{
	private:
		Matrix44 m, inv;
	public:
		Transform(const Matrix44 &x):m(x),inv(m.Inverse()) {}
		Transform(const Matrix44 &m, const Matrix44 &inv) :m(m), inv(inv) {};
		Transform() {};
		Transform(const Vec3f&xaxis, const Vec3f&yaxis, const Vec3f&zaxis) 
			:m(xaxis, yaxis, zaxis) {
			inv = m.Inverse();
		}
		template <typename T>
		Point3<T> operator()(const Point3<T>&p) const{
			T x = m.m[m.r[0]][0] * p.x + m.m[m.r[0]][1] * p.y + m.m[m.r[0]][2] * p.z + m.m[m.r[0]][3];
			T y = m.m[m.r[1]][0] * p.x + m.m[m.r[1]][1] * p.y + m.m[m.r[1]][2] * p.z + m.m[m.r[1]][3];
			T z = m.m[m.r[2]][0] * p.x + m.m[m.r[2]][1] * p.y + m.m[m.r[2]][2] * p.z + m.m[m.r[2]][3];
			T wp = m.m[m.r[3]][0] * p.x + m.m[m.r[3]][1] * p.y + m.m[m.r[3]][2] * p.z+ m.m[m.r[3]][3];
			if (wp == 1)return Point3<T>(x, y, z);
			else return Point3<T>(x / wp, y / wp, z / wp);
		}
		template <typename T>
		Vec3<T> operator()(const Vec3<T>&p) const{
			T x = m.m[m.r[0]][0] * p.x + m.m[m.r[0]][1] * p.y + m.m[m.r[0]][2] * p.z;
			T y = m.m[m.r[1]][0] * p.x + m.m[m.r[1]][1] * p.y + m.m[m.r[1]][2] * p.z;
			T z = m.m[m.r[2]][0] * p.x + m.m[m.r[2]][1] * p.y + m.m[m.r[2]][2] * p.z;
			return Vec3<T>(x, y, z);
		}
		template <typename T>
		Vec3<T> operator()(const Vec2<T>&p)const {

		}
		Normal operator()(const Normal&p) const{
			Float x = m.m[m.r[0]][0] * p.x + m.m[m.r[0]][1] * p.y + m.m[m.r[0]][2] * p.z;
			Float y = m.m[m.r[1]][0] * p.x + m.m[m.r[1]][1] * p.y + m.m[m.r[1]][2] * p.z;
			Float z = m.m[m.r[2]][0] * p.x + m.m[m.r[2]][1] * p.y + m.m[m.r[2]][2] * p.z;
			return Normal(x, y, z);
		}
		void operator()(Ray*p)const {
			Float ox = m.m[m.r[0]][0] * p->o.x + m.m[m.r[0]][1] * p->o.y + m.m[m.r[0]][2] * p->o.z + m.m[m.r[0]][3];
			Float oy = m.m[m.r[1]][0] * p->o.x + m.m[m.r[1]][1] * p->o.y + m.m[m.r[1]][2] * p->o.y + m.m[m.r[1]][3];
			Float oz = m.m[m.r[2]][0] * p->o.x + m.m[m.r[2]][1] * p->o.y + m.m[m.r[2]][2] * p->o.z + m.m[m.r[2]][3];
			Float wp = m.m[m.r[3]][0] * p->o.x + m.m[m.r[3]][1] * p->o.y + m.m[m.r[3]][2] * p->o.z + m.m[m.r[3]][3];
			Float dx = m.m[m.r[0]][0] * p->d.x + m.m[m.r[0]][1] * p->d.y + m.m[m.r[0]][2] * p->d.z;
			Float dy = m.m[m.r[1]][0] * p->d.x + m.m[m.r[1]][1] * p->d.y + m.m[m.r[1]][2] * p->d.z;
			Float dz = m.m[m.r[2]][0] * p->d.x + m.m[m.r[2]][1] * p->d.y + m.m[m.r[2]][2] * p->d.z;
			p->o.x = ox / wp;
			p->o.y = oy / wp;
			p->o.z = oz / wp;
			p->d.x = dx;
			p->d.y = dy;
			p->d.z = dz;
		}
		Ray operator()(const Ray&p)const {
			Ray ray;
			Float ox = m.m[m.r[0]][0] * p.o.x + m.m[m.r[0]][1] * p.o.y + m.m[m.r[0]][2] * p.o.z + m.m[m.r[0]][3];
			Float oy = m.m[m.r[1]][0] * p.o.x + m.m[m.r[1]][1] * p.o.y + m.m[m.r[1]][2] * p.o.y + m.m[m.r[1]][3];
			Float oz = m.m[m.r[2]][0] * p.o.x + m.m[m.r[2]][1] * p.o.y + m.m[m.r[2]][2] * p.o.z + m.m[m.r[2]][3];
			Float wp = m.m[m.r[3]][0] * p.o.x + m.m[m.r[3]][1] * p.o.y + m.m[m.r[3]][2] * p.o.z + m.m[m.r[3]][3];
			ray.d.x = m.m[m.r[0]][0] * p.d.x + m.m[m.r[0]][1] * p.d.y + m.m[m.r[0]][2] * p.d.z;
			ray.d.y = m.m[m.r[1]][0] * p.d.x + m.m[m.r[1]][1] * p.d.y + m.m[m.r[1]][2] * p.d.z;
			ray.d.z = m.m[m.r[2]][0] * p.d.x + m.m[m.r[2]][1] * p.d.y + m.m[m.r[2]][2] * p.d.z;
			ray.o.x = ox / wp;
			ray.o.y = oy / wp;
			ray.o.z = oz / wp;
			return ray;
		}
		Transform operator*(const Transform&t) {
			return Transform(m.Mul(t.m), t.inv.Mul(inv));
		}
		Transform &operator*=(const Transform&t) {
			m = m.Mul(t.m);
			inv = t.inv.Mul(inv);
			return *this;
		}
		friend Transform Inverse(const Transform&t) {
			return Transform(t.inv,t.m);
		}
		friend Transform NormalT(const Transform&t) {
			Transform tmp = Inverse(t);
			return Transform(tmp.m.Transpose(), tmp.inv.Transpose());
		}
	};
	Transform Scale(const Vec3f&v) {
		return Transform(
			Matrix44(
				v.x, 0, 0, 0,
				0, v.y, 0, 0,
				0, 0, v.z, 0,
				0, 0, 0, 1),
			Matrix44(
				1/v.x, 0, 0, 0,
				0, 1/v.y, 0, 0,
				0, 0, 1/v.z, 0,
				0, 0, 0, 1));
	}
	Transform Scale(Float x,Float y,Float z) {
		return Transform(
			Matrix44(
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1),
			Matrix44(
				1 / x, 0, 0, 0,
				0, 1 / y, 0, 0,
				0, 0, 1 / z, 0,
				0, 0, 0, 1));
	}
	Transform Translate(const Vec3f&v) {
		return Transform(
			Matrix44(
				1, 0, 0, v.x,
				0, 1, 0, v.y,
				0, 0, 1, v.z,
				0, 0, 0, 1),
			Matrix44(
				1, 0, 0, -v.x,
				0, 1, 0, -v.y,
				0, 0, 1, -v.z,
				0, 0, 0, 1));
	}
	Transform Translate(Float x,Float y,Float z) {
		return Transform(
			Matrix44(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1),
			Matrix44(
				1, 0, 0, -x,
				0, 1, 0, -y,
				0, 0, 1, -z,
				0, 0, 0, 1));
	}
	Transform RotateX(Float theta) {
		Float cost = std::cos(Radians(theta));
		Float sint = std::sin(Radians(theta));
		Matrix44 m(
			1, 0, 0, 0,
			0, cost, -sint, 0,
			0, sint, cost, 0,
			0, 0, 0, 1);
		return Transform(m, m.Transpose());
	}
	Transform RotateY(Float theta) {
		Float cost = std::cos(Radians(theta));
		Float sint = std::sin(Radians(theta));
		Matrix44 m(
			cost, 0, sint, 0,
			0, 1, 0, 0,
			-sint, 0, cost, 0,
			0, 0, 0, 1);
		return Transform(m, m.Transpose());
	}
	Transform RotateZ(Float theta) {
		Float cost = std::cos(Radians(theta));
		Float sint = std::sin(Radians(theta));
		Matrix44 m(
			cost, -sint, 0, 0,
			sint, cost, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		return Transform(m, m.Transpose());
	}
	Transform Perspective(Float fov,Float n,Float f,Float aspect) {
		Matrix44 m(1.f, 0.f, 0.f, 0.f,
			       0.f, 1.f, 0.f, 0.f,
				   0.f, 0.f, f / (f - n), -f * n / (f - n),
			       0.f, 0.f, 1.f, 0.f);
		Float invfov = 1 / std::tan(Radians(fov / 2));
		return Scale(Vec3f(invfov * aspect, invfov, 1)) * m;
	}
};

#endif
