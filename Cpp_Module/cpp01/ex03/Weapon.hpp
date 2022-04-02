#pragma once
# include <iostream>
# include <string>

class Weapon
{
	public:
		Weapon();
		~Weapon();
		Weapon(std::string const &gun);
		const std::string	&getType() const;
		void				setType(const std::string &gun);
	private:
		std::string gun;
};
