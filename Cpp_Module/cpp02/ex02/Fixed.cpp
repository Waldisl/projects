#include "Fixed.hpp"

Fixed::Fixed()
{
}

Fixed::Fixed(Fixed const &second)
{
	Fixed::operator=(second);
}

Fixed::Fixed(int const fix_point)
{
	this->fix_point = (fix_point << Fixed::bit);
}

Fixed::Fixed(float const fix_point)
{
	this->fix_point = roundf(fix_point * (1 << Fixed::bit));
}

Fixed &Fixed::operator=(Fixed const &second)
{
	this->fix_point = second.fix_point;
	return *this;
}

Fixed::~Fixed()
{
}

bool Fixed::operator==(Fixed const &second) const
{
	return (this->fix_point == second.fix_point);
}

bool Fixed::operator!=(Fixed const &second) const
{
	return (this->fix_point != second.fix_point);
}

bool Fixed::operator>(Fixed const &second) const
{
	return (this->fix_point > second.fix_point);
}

bool Fixed::operator<(Fixed const &second) const
{
	return (this->fix_point < second.fix_point);
}

bool Fixed::operator>=(Fixed const &second) const
{
	return (this->fix_point >= second.fix_point);
}

bool Fixed::operator<=(Fixed const &second) const
{
	return (this->fix_point <= second.fix_point);
}

Fixed Fixed::operator+(Fixed const &second)
{
	Fixed temp;
	temp.fix_point = this->fix_point + second.fix_point;
	return temp;
}

Fixed Fixed::operator-(Fixed const &second)
{
	Fixed temp;
	temp.fix_point = this->fix_point - second.fix_point;
	return temp;
}

Fixed Fixed::operator*(Fixed const &second)
{
	Fixed temp;
	long long a = ((long long)this->fix_point);
	long long b = ((long long)second.fix_point);
	temp.fix_point = (a * b) / (1 << Fixed::bit);
	return temp;
}

Fixed Fixed::operator/(Fixed const &second)
{
	if (second.fix_point == 0)
	{
		Fixed temp(-1);
		std::cout << "Division by zero" << std::endl;
		return temp;
	}
	else
	{
		Fixed temp;
		long long a = ((long long)this->fix_point);
		long long b = ((long long)second.fix_point);
		temp.fix_point = (a * (1 << Fixed::bit)) / b;
		return temp;
	}
}

Fixed Fixed::operator++()
{
	this->fix_point++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->fix_point++;
	return temp;
}

Fixed Fixed::operator--()
{
	this->fix_point--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->fix_point--;
	return temp;
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
	return (a > b ? b : a);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a > b ? b : a);
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
	return (a > b ? a : b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->fix_point;
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->fix_point = raw;
}

int Fixed::toInt(void) const
{
	return (this->fix_point >> Fixed::bit);
}

float Fixed::toFloat(void) const
{
	return ((float)this->fix_point / (float)(1 << Fixed::bit));
}

std::ostream &operator<<(std::ostream &cout, Fixed const &clas)
{
	cout << clas.toFloat();
	return cout;
}
