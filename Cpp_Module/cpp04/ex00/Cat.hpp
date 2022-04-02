#pragma once
#include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		Cat(Cat const &second);
		Cat &operator=(Cat const &second);
		virtual ~Cat();

		void makeSound() const;

};
