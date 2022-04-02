#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &second)
{
	std::cout << "Copy constructor called" << std::endl;
	Fixed::operator=(second);
}

Fixed::Fixed(int const fix_point)
{
	std::cout << "Int constructor called" << std::endl;
	this->fix_point = (fix_point << Fixed::bit);

}

Fixed::Fixed(float const fix_point)
{
	std::cout << "Float constructor called" << std::endl;
	this->fix_point = roundf(fix_point * (1 << Fixed::bit));
}

Fixed &Fixed::operator=(Fixed const &second)
{
	std::cout << "Assignation operator called" << std::endl;
	this->fix_point = second.fix_point;
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
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
