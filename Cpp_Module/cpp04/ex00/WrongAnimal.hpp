#pragma once
#include <iostream>

class WrongAnimal
{
	protected:
		std::string	type;

	public:
		WrongAnimal();
		WrongAnimal(std::string	type);
		WrongAnimal(WrongAnimal const &second);
		WrongAnimal &operator=(WrongAnimal const &second);
		virtual ~WrongAnimal();

		virtual void makeSound() const;
		std::string const &getType() const;

};