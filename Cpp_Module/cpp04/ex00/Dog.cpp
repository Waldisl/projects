#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
}

Dog::Dog(Dog const &second) : Animal(second)
{
}

Dog &Dog::operator=(Dog const &second)
{
	this->Animal::operator=(second);
	return *this;
}

Dog::~Dog()
{
}

void Dog::makeSound() const
{
	std::cout << "Dog: GAF" << std::endl;
}