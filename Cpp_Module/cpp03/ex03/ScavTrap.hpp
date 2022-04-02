#pragma once
#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(ScavTrap const &second);
		ScavTrap(std::string const &name);
		ScavTrap &operator=(ScavTrap const &second);
		~ScavTrap();

		void attack(std::string const &target) override;
		void guardGate();

	protected:
		unsigned int en;
};