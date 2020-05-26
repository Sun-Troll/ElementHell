#pragma once

#include "Vec.h"

template<typename T>
class Rect_
{
public:
	Rect_(T left, T right, T top, T bottom)
		:
		left(left),
		right(right),
		top(top),
		bottom(bottom)
	{}
	Rect_(const Vec_<T>& leftTop, const Vec_<T>& rightBottom)
		:
		Rect_(leftTop.x, rightBottom.x, leftTop.y, rightBottom.y)
	{}
	Rect_(const Vec_<T>& leftTop, T width, T height)
		:
		Rect_(leftTop, { leftTop.x + width, leftTop.y + height })
	{}
	bool isContained(const Rect_& container) const
	{
		return left > container.left && right < container.right
			&& top > container.top && bottom < container.bottom;
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};
typedef Rect_<float> RectF;
typedef Rect_<int> RectI;