#pragma once
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat();
		WrongCat(WrongCat const &second);
		WrongCat &operator=(WrongCat const &second);
		virtual ~WrongCat();

		void makeSound() const;

};
