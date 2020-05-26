#pragma once

#include "Vec.h"

class CircF
{
public:
	CircF(const VecF& pos, float radius);
	bool Coliding(const CircF& circ) const;
	bool ContainsCirc(const CircF& circ) const;
	bool ContainsPoint(const VecF& point) const;
public:
	VecF pos;
	float radius;
};