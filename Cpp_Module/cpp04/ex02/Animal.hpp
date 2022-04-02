#pragma once
#include <iostream>

class Animal
{
	protected:
		std::string	type;
		Animal(std::string type);
	public:
		Animal();
		Animal(Animal const &second);
		Animal &operator=(Animal const &second);
		virtual ~Animal();

		virtual void makeSound() const = 0;
		std::string const &getType() const;

};