#include "HumanB.hpp"

HumanB::~HumanB()
{
}

HumanB::HumanB(std::string const _name): _name(_name), gun(NULL)
{
}

void	HumanB::attack(void)
{
	if (this->gun)
	{
		if (this->gun->getType() == "")
			std::cout << this->_name << " without weapons." << std::endl;
		else
		{
			std::cout << this->_name << " attacks with his ";
			std::cout << this->gun->getType() << std::endl;
		}
	}
	else
		std::cout << this->_name << " without weapons." << std::endl;
}

void HumanB::setWeapon(const Weapon &gun)
{
	this->gun = &gun;
}
