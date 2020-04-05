#include "VecF.h"
#include <cmath>

VecF::VecF(float x, float y)
	:
	x(x),
	y(y)
{
}

VecF VecF::operator+(const VecF& rhs) const
{
	return VecF(x + rhs.x, y + rhs.y);
}

VecF& VecF::operator+=(const VecF& rhs)
{
	return *this = *this + rhs;
}
VecF VecF::operator-(const VecF& rhs) const
{
	return VecF(x - rhs.x, y - rhs.y);
}

VecF& VecF::operator-=(const VecF& rhs)
{
	return *this = *this - rhs;
}

VecF VecF::operator*(float rhs) const
{
	return VecF(x * rhs, y * rhs);
}

VecF& VecF::operator*=(float rhs)
{
	return *this = *this * rhs;
}

VecF VecF::operator/(float rhs) const
{
	return VecF(x / rhs, y / rhs);
}

VecF& VecF::operator/=(float rhs)
{
	return *this = *this / rhs;
}

VecF::operator VecI() const
{
	return { int(x), int(y) };
}

float VecF::GetLengthSq() const
{
	return x * x + y * y;
}

float VecF::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

VecF VecF::GetNormalized() const
{
	const float length = GetLength();
	if (length != 0.0f)
	{
		return *this / length;
	}
	return *this;
}

VecF& VecF::Normalize()
{
	return *this = GetNormalized();
}
