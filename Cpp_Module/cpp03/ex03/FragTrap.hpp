#pragma once
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
	public:
		FragTrap();
		FragTrap(FragTrap const &second);
		FragTrap(std::string const &name);
		FragTrap &operator=(FragTrap const &second);
		~FragTrap();

		void highFivesGuys(void);

	protected:
		unsigned int hit;
		unsigned int attacka;
};