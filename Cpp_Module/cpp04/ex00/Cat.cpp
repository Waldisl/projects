
#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
}

Cat::Cat(Cat const &second) : Animal(second)
{
}

Cat &Cat::operator=(Cat const &second)
{
	this->Animal::operator=(second);
	return *this;
}

Cat::~Cat()
{
}

void Cat::makeSound() const
{
	std::cout << "Cat: MEOW" << std::endl;
}