#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain *br;
	public:
		Cat();
		Cat(Cat const &second);
		Cat &operator=(Cat const &second);
		virtual ~Cat();

		void makeSound() const;
};
