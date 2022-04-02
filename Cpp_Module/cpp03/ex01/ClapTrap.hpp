#pragma once
#include <iostream>

class ClapTrap
{
	protected:
		std::string name;
		unsigned int AttackDamage;
		unsigned int HitPoints;
		unsigned int EnergyPoints;
		bool energy = false;

	public:
		ClapTrap();
		ClapTrap(ClapTrap const &second);
		ClapTrap(std::string const &name);
		ClapTrap &operator=(ClapTrap const &second);
		~ClapTrap();

		void getInfo();
		virtual void attack(std::string const &target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};
