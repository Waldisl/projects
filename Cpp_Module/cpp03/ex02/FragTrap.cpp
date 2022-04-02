#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << "Default constructor FragTrap" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
	this->name = "Flag";
}

FragTrap::FragTrap(FragTrap const &second)
{
	std::cout << "Copy constructor FragTrap" << std::endl;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
}

FragTrap::FragTrap(std::string const &name)
{
	std::cout << "Constructor name FragTrap" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
	this->name = name;
}

FragTrap::~FragTrap()
{
	std::cout << "Destructor FragTrap" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &second)
{
	std::cout << "Assignation operator FragTrap" << std::endl;
	if (this == &second)
		return *this;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
	return *this;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap: positive high fives" << std::endl;
}