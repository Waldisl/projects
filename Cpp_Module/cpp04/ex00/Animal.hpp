#pragma once
#include <iostream>

class Animal
{
	protected:
		std::string	type;

	public:
		Animal();
		Animal(std::string	type);
		Animal(Animal const &second);
		Animal &operator=(Animal const &second);
		virtual ~Animal();

		virtual void makeSound() const;
		std::string const &getType() const;

};