#include "Zombie.hpp"

Zombie::Zombie()
{
}

Zombie::Zombie(std::string name)
{
	Zombie::_name = name;
}

Zombie::~Zombie()
{
	std::cout << _name << "\t" <<"is died" << std::endl;
}

void Zombie::announce(void) 
{
	std::cout << _name << "\t" << "BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::SetName(std::string name)
{
	Zombie::_name = name;
}
