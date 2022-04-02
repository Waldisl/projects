#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	std::cout << "Default constructor" << std::endl;
	this->HitPoints = 20;
	this->EnergyPoints = 20;
	this->AttackDamage = 20;
	this->name = "Default";
}

ClapTrap::ClapTrap(ClapTrap const &second)
{
	std::cout << "Copy constructor" << std::endl;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
}

ClapTrap::ClapTrap(std::string const &name)
{
	std::cout << "Constructor name" << std::endl;
	this->HitPoints = 10;
	this->EnergyPoints = 10;
	this->AttackDamage = 0;
	this->name = name;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &second)
{
	std::cout << "Assignation operator" << std::endl;
	if (this == &second)
		return *this;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
	return *this;
}

void ClapTrap::getInfo()
{
	std::cout << std::endl;
	std::cout << "Name:\t\t" << this->name << std::endl;
	std::cout << "Hit Points:\t" << this->HitPoints << std::endl;
	std::cout << "Energy Points:\t" << this->EnergyPoints << std::endl;
	std::cout << "Attack Damage:\t" << this->AttackDamage << std::endl;
	std::cout << std::endl;
}

void ClapTrap::attack(std::string const &target)
{
	if (this->EnergyPoints <= 1)
	{
		std::cout << "ClapTrap: " << this->name << " lack of energy" << std::endl;
		this->energy = true;
	}
	else
	{
	std::cout << "ClapTrap: " << this->name << " spent 2 energy points..." << std::endl;
	std::cout << "ClapTrap: " << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage..." << std::endl;
	this->EnergyPoints -= 2;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->energy == false)
	{
		std::cout << "ClapTrap " << this->name << " take " << amount << " points of damage..." << std::endl;
		this->HitPoints < amount ? this->HitPoints = 0 : this->HitPoints -= amount;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "ClapTrap " << this->name << " be repaired " << amount << " hit points..." << std::endl;
	this->HitPoints += amount;
}