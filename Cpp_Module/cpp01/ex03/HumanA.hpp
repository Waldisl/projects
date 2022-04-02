#pragma once
#include "Weapon.hpp"

class HumanA
{
	public:
		HumanA();
		~HumanA();
		HumanA(std::string const &name, const Weapon &gun);
		void	attack();
	private:
		std::string		_name;
		const Weapon	&gun;
};