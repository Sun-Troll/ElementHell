#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom)
	:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
}

RectF::RectF(const VecF& leftTop, const VecF& rightBottom)
	:
	RectF(leftTop.x, rightBottom.x, leftTop.y, rightBottom.y)
{
}

RectF::RectF(const VecF& leftTop, float width, float height)
	:
	RectF(leftTop, { leftTop.x + width, leftTop.y + height })
{
}
