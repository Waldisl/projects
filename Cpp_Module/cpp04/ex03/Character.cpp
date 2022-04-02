#include "Character.hpp"

Character::Character(std::string const &name) : name(name), n_materia(0)
{
	for (int i = 0; i < 4; i++)
		this->materia[i] = NULL;
}

Character::Character(Character const &second)
{
	this->name = second.name;
	this->n_materia = 0;
	for (int i = 0; i < second.n_materia; i++)
		this->equip(second.materia[i]->clone());
	for (int i = this->n_materia; i < 4; i++)
		this->materia[i] = NULL;
}

Character &Character::operator=(Character const &second)
{
	this->name = second.name;
	for (int i = 0; i < this->n_materia; i++)
		delete this->materia[i];
	this->n_materia = 0;
	for (int i = 0; i < second.n_materia; i++)
		this->equip(second.materia[i]->clone());
	for (int i = this->n_materia; i < 4; i++)
		this->materia[i] = NULL;
	return *this;
}

Character::~Character()
{
	for (int i = 0; i < this->n_materia; i++)
		delete this->materia[i];
}

std::string const & Character::getName() const
{
	return this->name;
}

void Character::equip(AMateria* m)
{
	if (this->n_materia >= 4 || !m)
		return ;
	this->materia[this->n_materia++] = m;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= this->n_materia || idx < 0 || !this->materia[idx])
		return ;
	this->materia[idx]->use(target);
}

void Character::unequip(int idx)
{
	if (idx >= this->n_materia || idx < 0 || !this->materia[idx])
		return ;
	for (int i = idx; i < 3; i++)
	{
		this->materia[i] = this->materia[i + 1];
		this->materia[i + 1] = NULL;
	}
	this->n_materia--;
}