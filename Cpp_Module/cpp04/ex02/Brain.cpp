#include "Brain.hpp"
#include <string>
#include <sstream>

Brain::Brain()
{
	std::cout << "Brain: Constructor" << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		std::stringstream ss;
		ss << (i + 1);
		std::string index = ss.str();
		this->idea[i] = ("\tIdea #" + index + " XXXXXXX");
	}
	std::cout << this->idea[0] << std::endl;
	std::cout << "\t99 more ideas are hidden;)" << std::endl;
}

Brain::Brain(Brain const &second)
{
	std::cout << "Brain: Constructor copy" << std::endl;
	for (int i = 0; i < 100; ++i)
		this->idea[i] = second.idea[i];
}

Brain::Brain(std::string const &type)
{
	std::cout << "Brain: Constructor name" << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		std::stringstream ss;
		ss << (i + 1);
		std::string index = ss.str();
		this->idea[i] = ("\tIdea " + type + " #" + index + " XXXXXXX");
	}
	std::cout << this->idea[0] << std::endl;
	std::cout << "\t99 more ideas are hidden;)" << std::endl << std::endl;
}

Brain &Brain::operator=(Brain const &second)
{
	if (this != &second)
	{
		for (int i = 0; i < 100; ++i)
			this->idea[i] = second.idea[i];
	}
	return *this;
}

Brain::~Brain()
{
	std::cout << "Brain: Destructor" << std::endl;
}
