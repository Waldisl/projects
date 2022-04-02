#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	std::cout << "Default constructor DiamondTrap" << std::endl;
	this->HitPoints = this->FragTrap::hit;
	this->EnergyPoints = this->ScavTrap::en;
	this->AttackDamage = this->FragTrap::attacka;
	this->name = "DiamondTrap";
}

DiamondTrap::DiamondTrap(DiamondTrap const &second)
{
	std::cout << "Copy constructor DiamondTrap" << std::endl;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
}

DiamondTrap::DiamondTrap(std::string const &name)
{
	std::cout << "Constructor name DiamondTrap" << std::endl;
	this->name = name;
	ClapTrap::name = name + "_clap_name";
	this->HitPoints = this->FragTrap::hit;
	this->EnergyPoints = this->ScavTrap::en;
	this->AttackDamage = this->FragTrap::attacka;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "Destructor DiamondTrap" << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &second)
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

void DiamondTrap::attack(std::string const &target)
{
	this->ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap\t" << this->name << std::endl;
	std::cout << "ClapTrap\t" << ClapTrap::name << std::endl << std::endl;
}