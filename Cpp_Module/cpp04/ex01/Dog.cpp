#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	this->br = new Brain(this->type);
}

Dog::Dog(Dog const &second) : Animal(second)
{
	this->br = new Brain(*second.br);
}

Dog &Dog::operator=(Dog const &second)
{
	if (this != &second)
	{
		this->~Dog();
		this->br = new Brain(*second.br);
		this->Animal::operator=(second);
	}
	return *this;
}

Dog::~Dog()
{
	delete this->br;
}

void Dog::makeSound() const
{
	std::cout << "Dog: GAF" << std::endl;
}
