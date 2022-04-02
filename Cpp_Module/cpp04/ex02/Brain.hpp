#pragma once
#include <iostream>

class Brain
{
	private:
		std::string idea[100];

	public:
		Brain();
		Brain(Brain const &second);
		Brain(std::string const &type);
		Brain &operator=(Brain const &second);
		~Brain();
};