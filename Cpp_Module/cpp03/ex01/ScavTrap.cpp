#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "Default constructor SCAVTRAP" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 20;
	this->name = "Scav";
}

ScavTrap::ScavTrap(ScavTrap const &second)
{
	std::cout << "Copy constructor called SCAVTRAP" << std::endl;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
}

ScavTrap::ScavTrap(std::string const &name)
{
	std::cout << "Constructor name SCAVTRAP" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 20;
	this->name = name;
}

ScavTrap::~ScavTrap()
{
	std::cout << "Destructor SCAVTRAP" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &second)
{
	std::cout << "Assignation operator SCAVTRAP" << std::endl;
	if (this == &second)
		return *this;
	this->HitPoints = second.HitPoints;
	this->EnergyPoints = second.EnergyPoints;
	this->AttackDamage = second.AttackDamage;
	this->name = second.name;
	return *this;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap have entered in Gate keeper mode." << std::endl;
}

void ScavTrap::attack(std::string const &target)
{
	if (this->EnergyPoints < 0)
	{
		std::cout << "ScavTrap: " << this->name << " lack of energy" << std::endl;
		this->energy = true;
	}
	else
	{
	std::cout << "ScavTrap: " << this->name << " spent 1 energy points..." << std::endl;
	std::cout << "ScavTrap: " << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage..." << std::endl;
	this->EnergyPoints--;
	}
}
