#pragma once

#include "VecF.h"

class RectF
{
public:
	RectF(float left, float right, float top, float bottom);
	RectF(const VecF& leftTop, const VecF& rightBottom);
	RectF(const VecF& leftTop, float width, float height);
	bool isContained(const RectF& container) const;
public:
	float left;
	float right;
	float top;
	float bottom;
};