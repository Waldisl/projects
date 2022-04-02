#include "Weapon.hpp"

Weapon::Weapon()
{
	gun = "";
}

Weapon::~Weapon()
{
}

Weapon::Weapon(std::string const &gun): gun(gun)
{
}

const	std::string	&Weapon::getType(void) const
{
	return this->gun;
}

void	Weapon::setType(const std::string &gun)
{
	this->gun = gun;
}