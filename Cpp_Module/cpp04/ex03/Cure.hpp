#pragma once
#include "AMateria.hpp"

class Cure: public AMateria
{
	public:
		Cure();
		// Cure(Cure const &second);
		// Cure &operator=(Cure const &second);
		~Cure();

		AMateria *clone(void) const;
		void use(ICharacter &target);
};