#pragma once
#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int fix_point = 0;
		static const int bit = 8;

	public:
		Fixed();
		Fixed(Fixed const &second);
		Fixed(int const fix_point);
		Fixed(float const fix_point);
		Fixed &operator=(Fixed const &second);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		int		toInt(void) const;
		float	toFloat(void) const;
};

std::ostream &operator<<(std::ostream &cout, Fixed const &clas);
