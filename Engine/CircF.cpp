#include "CircF.h"

CircF::CircF(const VecF& pos, float radius)
	:
	pos(pos),
	radius(radius)
{
}

bool CircF::Coliding(const CircF& circ) const
{
	return (pos - circ.pos).GetLengthSq() < (radius + circ.radius) * (radius + circ.radius);
}

bool CircF::ContainsCenter(const CircF & circ) const
{
	return (pos - circ.pos).GetLengthSq() < radius * radius;
}

bool CircF::ContainsCirc(const CircF& circ) const
{
	return (pos - circ.pos).GetLength() + circ.radius < radius;
}
