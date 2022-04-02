#include "Fixed.hpp"
#include "Point.hpp"

void ch_bsp(Point const a, Point const b, Point const c, Point const point)
{
	std::cout << "A (x = " << a.GetX() << ", y = " << a.GetY() << ")" << std::endl;
	std::cout << "B (x = " << b.GetX() << ", y = " << b.GetY() << ")" << std::endl;
	std::cout << "C (x = " << c.GetX() << ", y = " << c.GetY() << ")" << std::endl;
	std::cout << "D (x = " << point.GetX() << ", y = " << point.GetY() << ")\t" ;
	if (bsp(a, b, c, point))
		std::cout << "inside" << std::endl << std::endl;
	else
		std::cout << "outside" << std::endl << std::endl;
	
}

int main(void)
{
	Point a(4, -1);
	Point b(6, 4);
	Point c(12, 2);

	Point d1(7, 2);
	Point d2(-3, 3);
	Point d3(0, 0);
	Point d4(5.0, 1.0);

	
	ch_bsp(a, b, c, d1);
	ch_bsp(a, b, c, d2);
	ch_bsp(a, b, c, d3);
	ch_bsp(a, b, c, d4);


	return 0;
}
