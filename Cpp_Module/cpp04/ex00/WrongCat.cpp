
#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat")
{
}

WrongCat::WrongCat(WrongCat const &second) : WrongAnimal(second)
{
}

WrongCat &WrongCat::operator=(WrongCat const &second)
{
	this->WrongAnimal::operator=(second);
	return *this;
}

WrongCat::~WrongCat()
{
}

void WrongCat::makeSound() const
{
	std::cout << "WrongCat: MEOW" << std::endl;
}