#pragma once
#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() {}
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};

class MateriaSource: public IMateriaSource
{
	private:
		AMateria *materia_source[4];
		int n_materia;
	public:
		MateriaSource();
		MateriaSource(MateriaSource const &second);
		MateriaSource &operator=(MateriaSource const &second);
		~MateriaSource();

		void learnMateria(AMateria *m);
		AMateria* createMateria(std::string const &type);
};