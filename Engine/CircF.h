#pragma once

#include "VecF.h"

class CircF
{
public:
	CircF(const VecF& pos, float radius);
	bool Coliding(const CircF& circ) const;
	bool ContainsCenter(const CircF& circ) const;
	bool ContainsCirc(const CircF& circ) const;
public:
	VecF pos;
	float radius;
};