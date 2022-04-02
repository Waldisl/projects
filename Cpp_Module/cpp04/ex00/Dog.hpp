#pragma once
#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		Dog(Dog const &second);
		Dog &operator=(Dog const &second);
		virtual ~Dog();

		void makeSound() const;

};