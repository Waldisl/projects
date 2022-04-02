#include "Animal.hpp"

Animal::Animal()
{
	this->type = "Default animal";
	std::cout << this->type << ": Constructor" << std::endl;
}

Animal::Animal(std::string type)
{
	this->type = type;
	std::cout << this->type << ": Constructor" << std::endl;
}

Animal::Animal(Animal const &second)
{
	*this = second;
	std::cout << this->type << ": Constructor copy" << std::endl;
}

Animal &Animal::operator=(Animal const &second)
{
	this->type = second.getType();
	return *this;
}

Animal::~Animal()
{
	std::cout << this->type << ": Destructor" << std::endl;
}

std::string const &Animal::getType() const
{
	return this->type;
}

void Animal::makeSound() const
{
}

