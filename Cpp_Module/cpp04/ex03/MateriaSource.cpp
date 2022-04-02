#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : n_materia(0)
{
	for (int i = 0; i < 4; i++)
		this->materia_source[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const &second)
{
	this->n_materia = 0;
	for (int i = 0; i < second.n_materia; i++)
		this->learnMateria(second.materia_source[i]->clone());
	for (int i = 0; i < 4; i++)
		this->materia_source[i] = NULL;
}

MateriaSource &MateriaSource::operator=(MateriaSource const &second)
{
	for (int i = 0; i < this->n_materia; i++)
		delete this->materia_source[i];
	this->n_materia = 0;
	for (int i = 0; i < second.n_materia; i++)
		this->learnMateria(second.materia_source[i]->clone());
	for (int i = 0; i < 4; i++)
		this->materia_source[i] = NULL;
	return *this;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < this->n_materia; i++)
		delete this->materia_source[i];
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (this->n_materia  == 4 || !m)
		return ;
	this->materia_source[this->n_materia++] = m;
}

AMateria* MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < this->n_materia; i++)
		if (this->materia_source[i]->getType() == type)
			return (this->materia_source[i]->clone());
	return (NULL);
}
