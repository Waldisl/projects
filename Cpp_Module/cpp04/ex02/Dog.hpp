#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *br;
	public:
		Dog();
		Dog(Dog const &second);
		Dog &operator=(Dog const &second);
		virtual ~Dog();

		void makeSound() const;
};