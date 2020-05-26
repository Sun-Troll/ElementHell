#pragma once

#include <cmath>

template<typename T>
class Vec_
{
public:
	Vec_(T x, T y)
		:
		x(x),
		y(y)
	{}
	Vec_ operator+(const Vec_& rhs) const
	{
		return Vec_(x + rhs.x, y + rhs.y);
	}
	Vec_& operator+=(const Vec_& rhs)
	{
		return *this = *this + rhs;
	}
	Vec_ operator-(const Vec_& rhs) const
	{
		return Vec_(x - rhs.x, y - rhs.y);
	}
	Vec_& operator-=(const Vec_& rhs)
	{
		return *this = *this - rhs;
	}
	Vec_ operator*(T rhs) const
	{
		return Vec_(x * rhs, y * rhs);
	}
	Vec_& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vec_ operator/(T rhs) const
	{
		return Vec_(x / rhs, y / rhs);
	}
	Vec_& operator/=(T rhs)
	{
		return *this = *this / rhs;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength() const
	{
		return std::sqrt(GetLengthSq());
	}
	Vec_ GetNormalized() const
	{
		const T length = GetLength();
		if (length != 0.0f)
		{
			return *this / length;
		}
		return *this;
	}
	Vec_& Normalize()
	{
		return *this = GetNormalized();
	}
public:
	T x;
	T y;
};
typedef Vec_<float> VecF;
typedef Vec_<int> VecI;