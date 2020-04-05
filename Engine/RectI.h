#pragma once

#include "VecI.h"

class RectI
{
public:
	RectI(int left, int right, int top, int bottom);
	RectI(const VecI& leftTop, const VecI& rightBottom);
	RectI(const VecI& leftTop, int width, int height);
public:
	int left;
	int right;
	int top;
	int bottom;
};