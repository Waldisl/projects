#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	int		size = 4;
	Animal *Ans[size];
	for (int i = 0; i < size; ++i)
	{
		if (i % 2 == 1)
			Ans[i] = new Dog();
		else
			Ans[i] = new Cat();
	}

	for (int i = 0; i < size; ++i)
	{
		delete Ans[i];
	}

	Animal ds;
	ds = Cat();
}