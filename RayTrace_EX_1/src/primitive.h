#pragma once
#ifndef DRAGON_CORE_PRIMITIVE_H
#define DRAGON_CORE_PRIMITIVE_H
#include <iterator>
#include <algorithm>
#include <iostream>
#include"utility.h"
#include"math.h"
namespace dragon {
	class Normal;
	template <typename T>
	class Vec3;
	template <typename T>
	class Vec2 {
	public:
		T x, y;
		Vec2() { x = y = 0; }
		Vec2(T xx,T yy):x(xx),y(yy){}
		bool HasNaNs()const { return isNaN(x) || isNaN(y); }
		Vec2(const Vec2<T>&v){
			x = v.x;
			y = v.y;
		}
		Vec2<T> &operator=(const Vec2<T>&v) {
			x = v.x;
			y = v.y;
			return *this;
		}
		Vec2<T> operator+(const Vec2<T>&v)const {
			return Vec2(x + v.x, y + v.y);
		}
		Vec2<T> &operator+=(const Vec2<T>&v) {
			x += v.x;
			y += v.y;
			return *this;
		}
		Vec2<T> operator-(const Vec2<T>&v)const {
			return Vec2(x - v.x, y - v.y);
		}
		Vec2<T> &operator-=(const Vec2<T>&v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		bool operator==(const Vec2<T>&v)const { return x == v.x && y == v.y; }
		bool operator!=(const Vec2<T>&v)const { return x != v.x || y != v.y; }
		template <typename U>
		Vec2<T> operator*(U u)const {
			return Vec2<T>(x * u, y * u);
		}
		template <typename U>
		Vec2<T>& operator*=(U u) {
			x *= u;
			y *= u;
			return *this;
		}
		template <typename U>
		Vec2<T> operator/(U u)const {
			Float div = (Float)1 / u;
			return Vec2<T>(x * div, y * div);
		}
		template <typename U>
		Vec2<T>& operator/=(U u) {
			Float div = (Float)1 / u;
			x *= div;
			y *= div;
			return *this;
		}
		Vec2<T> operator-()const {
			return Vec2(-x, -y);
		}
		void Normalize() {
			double l = Length();
			x /= l;
			y /= l;
		}
		T Dot(const Vec2<T>&v)const {
			return x * v.x + y * v.y;
		}
		T operator[](int i) const{
			if (i == 0)return x;
			else return y;
		}
		Float LengthSquared()const { return x * x + y * y; }
		Float Length()const { return std::sqrt(LengthSquared()); }
	};
	template <typename T>
	class Vec3 {
	public:
		T x, y, z;
		Vec3() { x = y = z = 0; }
		Vec3(T xx, T yy,T zz) :x(xx), y(yy), z(zz) {}
		bool HasNaNs()const { return isNaN(x) || isNaN(y) || isNaN(z); }
		Vec3(const Vec3<T>&v){
			x = v.x;
			y = v.y;
			z = v.z;
		}
		explicit Vec3(const Normal&n);
		Vec3<T>& operator=(const Vec3<T>&v) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
		Vec3<T> operator+(const Vec3<T>&v)const {
			return Vec3(x + v.x, y + v.y, z + v.z);
		}
		Vec3<T> operator+(const Normal&n)const;
		Vec3<T>& operator+=(const Vec3<T>&v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vec3<T> operator-(const Vec3<T>&v)const {
			return Vec3<T>(x - v.x, y - v.y, z - v.z);
		}
		Vec3<T> operator-(const Normal&n)const;
		Vec3<T> &operator-=(const Vec3<T>&v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		bool operator==(const Vec3<T>&v)const { return x == v.x && y == v.y && 	z == v.z; }
		bool operator!=(const Vec3<T>&v)const { return x != v.x || y != v.y || z != v.z; }
		template <typename U>
		Vec3<T> operator*(U u)const {
			return Vec3<T>(x * u, y * u, z * u);
		}
		template <typename U>
		Vec3<T>& operator*=(U u) {
			x *= u;
			y *= u;
			z *= u;
			return *this;
		}
		template <typename U>
		Vec3<T> operator/(U u)const {
			Float div = (Float)1 / u;
			return Vec3<T>(x * div, y * div, z * div);
		}
		template <typename U>
		Vec3<T>& operator/=(U u) {
			Float div = (Float)1 / u;
			x *= div;
			y *= div;
			z *= div;
			return *this;
		}
		Vec3<T> operator-()const {
			return Vec3(-x, -y, -z);
		}
		Vec3<T>& operator=(const Normal&n)const;
		Vec3<T> operator*(const Vec3<T>&v) {
			return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}
		void Normalize() {
			double l = Length();
			x /= l;
			y /= l;
			z /= l;
		}
		Vec3<T> GetNorm() const{
			double l = Length();
			return Vec3<T>(x / l, y / l, z / l);
		}
		T Dot(const Vec3<T>&v)const {
			return x * v.x + y * v.y + z * v.z;
		}
		T Dot(const Normal&n)const;
		T operator[](int i) const {
			if (i == 0)return x;
			else if(i == 1) return y;
			else return z;
		}
		Float LengthSquared()const { return x * x + y * y + z * z; }
		Float Length()const { return std::sqrt(LengthSquared()); }
	};
	template <typename T>
	class Point2 {
	public:
		T x, y;
		Point2() { x = y = 0; }
		Point2(T xx, T yy) :x(xx), y(yy) {};
		Point2(const Point2<T>&p){
			x = p.x;
			y = p.y;
		}
		Point2<T>& operator=(const Point2<T>&p) {
			x = p.x;
			y = p.y;
			return *this;
		}
		Point2<T> operator+(const Vec2<T>&v)const {
			return Point2<T>(x + v.x, y + v.y);
		}
		Point2<T> &operator+=(const Vec2<T>&v) {
			x += v.x;
			y += v.y;
			return *this;
		}
		Point2<T> operator-(const Vec2<T>&v)const {
			return Point2<T>(x - v.x, y - v.y);
		}
		Point2<T> &operator-=(const Vec2<T>&v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		Vec2<T> operator-(const Point2<T>&p)const {
			return Vec2<T>(x - p.x, y - p.y);
		}
		Vec2<T> &operator-=(const Point2<T>&p) {
			x -= p.x;
			y -= p.y;
			return *this;
		}
		bool operator==(const Point2<T>&p)const { return x == p.x && y == p.y; }
		bool operator!=(const Point2<T>&p)const { return x != p.x || y != p.y; }
		T operator[](int i) {
			if (i == 0)return x;
			else return y;
		}

	};
	template <typename T>
	class Point3 {
	public:
		T x, y, z;
		Point3() { x = y = z = 0; }
		Point3(T xx, T yy, T zz) :x(xx), y(yy),z(zz) {};
		Point3(const Point3<T>&p) {
			x = p.x;
			y = p.y;
			z = p.z;
		}
		Point3<T>& operator=(const Point3<T>&p) {
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}
		Point3<T> operator+(const Vec3<T>&v)const {
			return Point3<T>(x + v.x, y + v.y,z + v.z);
		}
		Point3<T> &operator+=(const Vec3<T>&v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Point3<T> operator-(const Vec3<T>&v)const {
			return Point3<T>(x - v.x, y - v.y, z - v.z);
		}
		Point3<T> &operator-=(const Vec3<T>&v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		Vec3<T> operator-(const Point3<T>&p)const {
			return Vec3<T>(x - p.x, y - p.y, z - p.z);
		}
		Vec3<T> &operator-=(const Point3<T>&p) {
			x -= p.x;
			y -= p.y;
			z -= p.z;
			return *this;
		}
		Float Distance(const Point3<T>&p)const {
			Float dx = p.x - x;
			Float dy = p.y - y;
			Float dz = p.z - z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
		Float DistTo0() {
			return std::sqrt(x * x, y * y, z * z);
		}
		Point3<T> operator/(Float s) {
			return Point3<T>(x / s, y / s, z / s);
		}
		Point3<T>&operator/=(Float s) {
			x /= s;
			y /= s;
			z /= s;
			return *this;
		}
		Point3<T> operator*(Float s) {
			return Point3<T>(x * s, y * s, z * s);
		}
		Point3<T>&operator*=(Float s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		bool operator==(const Point3<T>&p)const { return x == p.x && y == p.y && z == p.z; }
		bool operator!=(const Point3<T>&p)const { return x != p.x || y != p.y || z != p.z; }
		T operator[](int i) {
			if (i == 0)return x;
			else if(i == 1) return y;
			else return z;
		}
	};
	typedef Vec2<int> Vec2i;
	typedef Vec2<Float> Vec2f;
	typedef Vec3<int> Vec3i;
	typedef Vec3<Float> Vec3f;
	typedef Point2<int> Point2i;
	typedef Point2<Float> Point2f;
	typedef Point3<int> Point3i;
	typedef Point3<Float> Point3f;
	class Normal{
	public:
		Float x, y, z;
		Normal() { x = y = z = 0; }
		Normal(Float xx, Float yy, Float zz) :x(xx), y(yy), z(zz) {}
		Normal(const Normal&p) {
			x = p.x;
			y = p.y;
			z = p.z;
		}
		Normal(const Vec3f&v) :x(v.x), y(v.y), z(v.z) {}
		Normal operator+(const Vec3f &v)const {
			return Normal(x + v.x, y + v.y, z + v.z);
		}
		Normal& operator+=(const Normal &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Normal operator-(const Normal &v)const {
			return Normal(x - v.x, y - v.y, z - v.z);
		}
		Normal& operator-=(const Normal &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		bool operator==(const Normal &p)const { return x == p.x && y == p.y && z == p.z; }
		bool operator!=(const Normal &p)const { return x != p.x || y != p.y || z != p.z; }
		Float operator[](int i) {
			if (i == 0)return x;
			else if (i == 1) return y;
			else return z;
		}
		template <typename U>
		Normal operator*(U u)const {
			return Normal(x * u, y * u, z * u);
		}
		template <typename U>
		Normal& operator*=(U u) {
			x *= u;
			y *= u;
			z *= u;
			return *this;
		}
		template <typename U>
		Normal operator/(U u)const {
			Float div = (Float)1 / u;
			return Normal(x * div, y * div, z * div);
		}
		template <typename U>
		Normal& operator/=(U u) {
			Float div = (Float)1 / u;
			x *= div;
			y *= div;
			z *= div;
			return *this;
		}
		Normal operator-()const {
			return Normal(-x, -y, -z);
		}
		/*fixed:need double type to reduce the error*/
		Normal operator*(const Normal &v) {
			return Normal(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}
		void Normalize() {
			Float l = Length();
			if (l == 0)return;
			x /= l;
			y /= l;
			z /= l;
		}
		Normal GetNorm()const {
			return Normal(x/Length(), y / Length(), z / Length());
		}
		Float Dot(const Normal &v)const {
			return x * v.x + y * v.y + z * v.z;
		}
		Float LengthSquared()const { return x * x + y * y + z * z; }
		Float Length()const { return std::sqrt(LengthSquared()); }
	};
	class RGB {
	public:
		Ratio r, g, b;
		RGB() :r(0.), g(0.), b(0.) {};
		RGB(Float r, Float g, Float b) :r(r), g(g), b(b) {};
		RGB(Ratio r, Ratio g, Ratio b) :r(r), g(g), b(b) {};
		RGB operator*(const RGB&rgb)const {
			return RGB(r * rgb.r, g * rgb.g, b * rgb.b);
		}
		RGB& operator*=(const RGB&rgb){
			r *= rgb.r;
			g *= rgb.g;
			b *= rgb.b;
			return *this;
		}
		RGB operator*(const Vec3f&v)const {
			return RGB(r * v.x, g * v.y, b * v.z);
		}
		RGB operator*(Float s)const {
			return RGB(r * s, g * s, b * s);
		}
		RGB operator/(Float s)const {
			return RGB(r / s, g / s, b / s);
		}
		RGB operator+(const RGB&rgb)const {
			return RGB(r + rgb.r, g + rgb.g, b + rgb.b);
		}
		void operator=(const RGB&rgb) {
			r = rgb.r;
			g = rgb.g;
			b = rgb.b;
		}
		RGB& operator+=(const RGB&rgb) {
			r += rgb.r;
			g += rgb.g;
			b += rgb.b;
			return *this;
		}
		bool operator!= (const RGB&rgb) {
			if (r != rgb.r && g != rgb.g && b != rgb.b)return true;
			else return false;
		}
	};
	const RGB BLACK( 0.f,0.f,0.f );
	const RGB WHITE( 1.f,1.f,1.f );
	const RGB RED( 1.f,0.f,0.f );
	const RGB GREEN( 0.f,1.f,0.f );
	const RGB BLUE( 0.f,0.f,1.f );
	std::ostream &operator<<(std::ostream &os, const RGB&rgb) {
		os << "RGB:" << rgb.r << " " << rgb.g << " " << rgb.b << std::endl;
		return os;
	}
	template <typename T>
	class Bounds2 {
		Point2<T>pmin, pmax;
		Bounds2(const Point2<T>&p1, const Point2<T>&p2): pmin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
		pmax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}
		Bounds2() :pmin(0, 0), pmax(0, 0) {}
		Vec2<T> Diagonal() {
			return Vec2<T>(pmax.x - pmin.x, pmax.y - pmin.y);
		}
		T Area() {
			return (pmax.x - pmin.x) * (pmax.y - pmin.y);
		}

	};
	template <typename T>
	class Bounds3 {

	};
	class Ray {
	public:
		Point3f o;
		Vec3f d;
		Float t;
		Ray():t(INFINITE_LARGE){}
		Ray(const Point3f&p, const Vec3f&v,Float t = INFINITE_LARGE) :o(p), d(v.GetNorm()),t(t) {}
		Ray(const Point3f&p1, const Point3f&p2) :o(p1), d((p1 - p2).GetNorm()) {}
		Ray Scale(Float s) const{
			if (s < 0)Warning("ray's t can not be minus");
			return Ray(o, d, t * s);
		}
		Point3f operator()(Float t)const{
			return o + d * t;
		}
		Ray GetReflect(const Normal&n)const {
			if (n.Dot(this->d) > 0) {
				Warning("Ray inversed.");
			}
			Vec3f s(n * (-this->d).Dot(n));
			Vec3f p = s - d;

		}
	};
	template<typename T>
	inline Vec3<T>::Vec3(const Normal&n) :x(n.x), y(n.y), z(n.z) {};
	template <typename T>
	inline Vec3<T> Vec3<T>::operator+(const Normal&n)const {
		return Vec3f(x + n.x, y + n.y, z + n.z);
	}
	template <typename T>
	inline Vec3<T> Vec3<T>::operator-(const Normal&n)const {
		return Vec3f(x - n.x, y - n.y, z - n.z);
	}
	template <typename T>
	inline Vec3<T>& Vec3<T>::operator=(const Normal&n)const {
		x = n.x;
		y = n.y;
		z = n.z;
		return *this;
	}
	template <typename T>
	inline T Vec3<T>::Dot(const Normal&n)const {
		return x * n.x + y * n.y + z * n.z;
	}
	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec2<T>&v) {
		os << "[" << v.x << "," << v.y << "]"<< std::endl;
		return os;
	}
	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec3<T>&v) {
		os << "[" << v.x << "," << v.y << "," << v.z << "]" << std::endl;
		return os;
	}
	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Point2<T>&v) {
		os << "[" << v.x << "," << v.y << "]" << std::endl;
		return os;
	}
	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Point3<T>&v) {
		os << "[" << v.x << "," << v.y << "," << v.z << "]" << std::endl;
		return os;
	}
	inline std::ostream &operator<<(std::ostream &os, const Normal&v) {
		os << "[" << v.x << "," << v.y << "," << v.z << "]" << std::endl;
		return os;
	}
	inline std::ostream &operator<<(std::ostream &os, const Ray&r) {
		os << "start:" << r.o << " dir:" << r.d << std::endl;
		return os;
	}
	Vec3f Reflect(const Vec3f&R, const Normal&N) {
		Vec3f nr = -R;
		Normal nn = N.GetNorm();
		Float Ratio = nr.Dot(nn);
		if (Ratio <= 0)
			Warning("Check ");
		Vec3f s(nn * Ratio);
		Vec3f h = s - nr;
		return Vec3f(h * 2 - R).GetNorm();
	}
	Vec3f Refract(const Vec3f&I, const Normal&N, Float eta) {
		Vec3f i = I.GetNorm();
		Normal n = N;
		float cosi = n.Dot(i);
		if (cosi < 0) {
			cosi = -cosi;
			eta = 1 / eta;
		}
		else {
			n = -n;
		}
		float c2 = 1 - eta * eta * (1 - cosi * cosi);
		if (c2 < 0)
			return Reflect(I, n);
		else
			return (i * eta + n * (eta * cosi - std::sqrt(c2))).GetNorm();
	}
	float Fresnel(const Vec3f&I, const Normal&N, Float eta) {
		Vec3f i = I.GetNorm();
		Normal n = N;
		//假设条件在密度大的物体内入射
		Float etai = eta, etat = 1;
		Float cosi = i.Dot(n);
		//如果在密度小的物体入射
		if (cosi < 0)std::swap(etai, etat);
		Float sint = etai / etat * sqrt(1 - cosi * cosi);
		//全反射
		if (sint >= 1)
			return 1;
		Float cost = sqrt(1 - sint * sint);
		cosi = std::abs(cosi);
		Float fpar = (etat * cosi - etai * cost) / (etat * cosi + etai * cost);
		Float fper = (-etat * cosi + etai * cost) / (etat * cosi + etai * cost);
		fpar *= fpar;
		fper *= fper;
		return (fpar + fper) / 2;
	}
	template <typename T>
	inline Float Dot(const Vec3<T>&v1, const Vec3<T>&v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	template <typename T>
	inline Float Dot(const Vec3<T>&v1, const Normal&v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	template <typename T>
	inline Float Dot(const Normal&v1, const Vec3<T>&v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
}

#endif
