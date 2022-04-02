#include "HumanA.hpp"

HumanA::~HumanA()
{
}

HumanA::HumanA(std::string const &_name, const Weapon &gun): _name(_name), gun(gun)
{
}

void	HumanA::attack()
{
	std::cout << this->_name << " attacks with his ";
	std::cout << this->gun.getType() << std::endl;
}