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

		bool operator==(Fixed const &second) const;
		bool operator!=(Fixed const &second) const;
		bool operator>(Fixed const &second) const;
		bool operator<(Fixed const &second) const;
		bool operator>=(Fixed const &second) const;
		bool operator<=(Fixed const &second) const;
		Fixed operator+(Fixed const &second);
		Fixed operator-(Fixed const &second);
		Fixed operator*(Fixed const &second);
		Fixed operator/(Fixed const &second);
		Fixed operator++();
		Fixed operator--();
		Fixed operator--(int);
		Fixed operator++(int);
		
		static Fixed &min(Fixed &a, Fixed &b);
		static Fixed &max(Fixed &a, Fixed &b);
		static Fixed const &min(Fixed const &a, Fixed const &b);
		static Fixed const &max(Fixed const &a, Fixed const &b);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		int		toInt(void) const;
		float	toFloat(void) const;
};

std::ostream &operator<<(std::ostream &cout, Fixed const &clas);
