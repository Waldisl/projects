#pragma once
#include "Weapon.hpp"

class HumanB
{
	public:
		HumanB();
		~HumanB();
		HumanB(std::string name);
		void	attack(void);
		void	setWeapon(const Weapon &gun);
	private:
		std::string		_name;
		const Weapon	*gun;
};
