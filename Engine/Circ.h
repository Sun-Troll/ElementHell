#pragma once

#include "Vec.h"

template<typename T>
class Circ_
{
public:
	Circ_(const Vec_<T>& pos, T radius)
		:
		pos(pos),
		radius(radius)
	{}
	bool Coliding(const Circ_& circ) const
	{
		return (pos - circ.pos).GetLengthSq() < (radius + circ.radius) * (radius + circ.radius);
	}
	bool ContainsCirc(const Circ_& circ) const
	{
		return (pos - circ.pos).GetLength() + circ.radius < radius;
	}
	bool ContainsPoint(const Vec_<T>& point) const
	{
		return (pos - point).GetLengthSq() < radius * radius;
	}
public:
	Vec_<T> pos;
	T radius;
};
typedef Circ_<float> CircF;
typedef Circ_<int> CircI;