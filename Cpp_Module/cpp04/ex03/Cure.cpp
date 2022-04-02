#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
}

// Cure::Cure(Cure const &second)
// {
// 	*this = second;
// }

// Cure &Cure::operator=(Cure const &second)
// {
// 	*this = second;
// 	return *this;
// }

Cure::~Cure()
{
}

AMateria *Cure::clone(void) const
{
	return (new Cure(*this));
}

void Cure::use(ICharacter &target)
{
	AMateria::use(target);
	std::cout << "* heals " << target.getName() << "\'s wounds *" << std::endl;
}
