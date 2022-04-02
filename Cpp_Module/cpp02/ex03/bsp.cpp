#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed point1 = (a.GetX() - point.GetX()) * (b.GetY() - a.GetY()) - (b.GetX() - a.GetX()) * (a.GetY() - point.GetY());

	Fixed point2 = (b.GetX() - point.GetX()) * (c.GetY() - b.GetY()) - (c.GetX() - b.GetX()) * (b.GetY() - point.GetY());

	Fixed point3 = (c.GetX() - point.GetX()) * (a.GetY() - c.GetY()) - (a.GetX() - c.GetX()) * (c.GetY() - point.GetY());

	return ((point1 > 0 && point2 > 0 && point3 > 0) || (point1 < 0 && point2 < 0 && point3 < 0));
}
