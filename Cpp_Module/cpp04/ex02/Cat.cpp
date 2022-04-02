
#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	this->br = new Brain(this->type);
}

Cat::Cat(Cat const &second) : Animal(second)
{
	this->br = new Brain(*second.br);
}

Cat &Cat::operator=(Cat const &second)
{
	if (this != &second)
	{
		this->~Cat();
		this->br = new Brain(*second.br);
		this->Animal::operator=(second);
	}
	return *this;
}

Cat::~Cat()
{
	delete this->br;
}

void Cat::makeSound() const
{
	std::cout << "Cat: MEOW" << std::endl;
}
