#pragma once
#include "VecI.h"

class VecF
{
public:
	VecF(float x, float y);
	VecF operator+(const VecF& rhs) const;
	VecF& operator+=(const VecF& rhs);
	VecF operator-(const VecF& rhs) const;
	VecF& operator-=(const VecF& rhs);
	VecF operator*(float rhs) const;
	VecF& operator*=(float rhs);
	VecF operator/(float rhs) const;
	VecF& operator/=(float rhs);
	operator VecI() const;
	float GetLengthSq() const;
	float GetLength() const;
	VecF GetNormalized() const;
	VecF& Normalize();
public:
	float x;
	float y;
};