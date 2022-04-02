#pragma once
#include "Fixed.hpp"

class Point
{
	private:
		Fixed const x;
		Fixed const y;

	public:
		Point();
		Point(Point const &second);
		Point(float const x, float const y);
		Point	&operator=(Point const &second);
		~Point();
		
		Fixed GetX() const;
		Fixed GetY() const;

};

std::ostream &operator<<(std::ostream &cout, Point const &clas);
bool bsp(Point const a, Point const b, Point const c, Point const point);
