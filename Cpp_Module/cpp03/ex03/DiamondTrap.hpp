#pragma once
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
	private:
		std::string name;

	public:
		DiamondTrap();
		DiamondTrap(DiamondTrap const &second);
		DiamondTrap(std::string const &name);
		DiamondTrap &operator=(DiamondTrap const &second);
		~DiamondTrap();

		void attack(std::string const &target);
		void whoAmI();
};