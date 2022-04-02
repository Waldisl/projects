#include "Point.hpp"

Point::Point() : x(0), y(0)
{
}

Point::Point(Point const &second) : x(second.x), y(second.y)
{
}

Point::Point(float const x, float const y) : x(x), y(y)
{
}


Point &Point::operator=(Point const &second)
{
	if (this == &second)
		return *this;
	*(const_cast<Fixed*>(&x)) = second.x;
	*(const_cast<Fixed*>(&y)) = second.y;
	return *this;
}

Fixed Point::GetX() const
{
	return Fixed(x);
}
Fixed Point::GetY() const
{
	return Fixed(y);
}

Point::~Point()
{
}

std::ostream &operator<<(std::ostream &cout, Point const &clas)
{
	cout << clas.GetX() << ", " << clas.GetY();
	return cout;
}