#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	this->type = "Default WrongAnimal";
	std::cout << this->type << ": Constructor" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type)
{
	this->type = type;
	std::cout << this->type << ": Constructor" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &second)
{
	*this = second;
	std::cout << this->type << ": Constructor copy" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &second)
{
	this->type = second.getType();
	return *this;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << this->type << ": Destructor" << std::endl;
}

std::string const &WrongAnimal::getType() const
{
	return this->type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "Sound" << std::endl;
}
