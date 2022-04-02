#pragma once
#include "Character.hpp"

class ICharacter;

class AMateria
{
	protected:
		AMateria();
		std::string type;
	public:
		AMateria(std::string const &type);
		AMateria(AMateria const &second);
		AMateria &operator=(AMateria const &second);
		virtual ~AMateria();

		std::string const & getType() const;

		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};