#pragma once
#ifndef DRAGON_CORE_MATH
#define DRAGON_CORE_MATH
#include<cmath>
#include<algorithm>
#define Float double
static Float PI = 3.141592741f;
static Float INFINITE_LARGE = 1e10f;
static Float INFINITE_SMALL = 1e-10f;
bool equal(Float v1, Float v2) {
	return std::abs(v1 - v2) > INFINITE_SMALL ? false : true;
}
template <typename T>
T Clamp(T v, T min, T max) {
	if (v > max)return max;
	if (v < min)return min;
	return v;
}
bool Quadratic(Float a, Float b, Float c, Float &r1, Float &r2) {
	Float discrim = b * b - 4 * a * c;
	if (discrim < 0.)return false;
	Float rootD = std::sqrt(discrim);
	r1 = (-1 * b + rootD) * 0.5f / a;
	r2 = (-1 * b - rootD) * 0.5f / a;
	if (r1 > r2)std::swap(r1, r2);
	return true;
}
struct Ratio {
public:
	Float x;
	explicit Ratio(Float xx) {
		x = Clamp(xx, Float(0.), Float(1.));
	}
	Float ToFloat()const {
		return x;
	}
	Ratio &operator=(const Ratio&r) {
		x = r.x;
		return *this;
	}
	Ratio& operator+=(const Ratio&r) {
		x = Clamp(x + r.x, Float(0.), Float(1.));
		return *this;
	}
	Ratio& operator*=(const Ratio &r) {
		x = Clamp(x * r.x, Float(0.), Float(1.));
		return *this;
	}
	Ratio operator+(const Ratio&r)const {
		return Ratio(Clamp(x + r.x, Float(0.), Float(1.)));
	}
	Ratio& operator-=(const Ratio&r) {
		x = Clamp(x - r.x, Float(0.), Float(1.));
		return *this;
	}
	Ratio operator-(const Ratio&r)const {
		return Ratio(Clamp(x - r.x, Float(0.), Float(1.)));
	}
	Ratio operator/(const Ratio&r)const {
		return Ratio(Clamp(x / r.x, Float(0.), Float(1.)));
	}
	Ratio operator/(Float s)const {
		return Ratio(Clamp(x / s, Float(0.), Float(1.)));
	}
	Ratio& operator/=(const Ratio&r) {
		x = Clamp(x / r.x, Float(0.), Float(1.));
		return *this;
	}
	Ratio operator*(const Ratio&r)const {
		return Ratio(Clamp(x * r.x, Float(0.), Float(1.)));
	}
	Ratio operator*(Float s)const {
		return Ratio(Clamp(x * s, Float(0.), Float(1.)));
	}
	bool operator!=(const Ratio&r)const {
		if (x != r.x)return true;
		else return false;
	}
};
inline ::std::ostream&operator<<(::std::ostream&os, const Ratio&r) {
	os << r.x;
	return os;
}
inline Float Radians(Float deg) {
	return (PI / 180) * deg;
}

#endif