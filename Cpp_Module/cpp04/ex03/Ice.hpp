#include "AMateria.hpp"

class Ice: public AMateria
{
	public:
		Ice();
		// Ice(Ice const &second);
		// Ice &operator=(Ice const &second);
		~Ice();

		AMateria *clone(void) const;
		void use(ICharacter &target);
};