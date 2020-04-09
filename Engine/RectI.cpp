#include "RectI.h"

RectI::RectI(int left, int right, int top, int bottom)
	:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
}

RectI::RectI(const VecI& leftTop, const VecI& rightBottom)
	:
	RectI(leftTop.x, rightBottom.x, leftTop.y, rightBottom.y)
{
}

RectI::RectI(const VecI& leftTop, int width, int height)
	:
	RectI(leftTop, { leftTop.x + width, leftTop.y + height })
{
}

int RectI::GetWidth() const
{
	return right - left;
}

int RectI::GetHeight() const
{
	return bottom - top;
}
