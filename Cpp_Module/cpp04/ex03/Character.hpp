#pragma once
#include <iostream>
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {}
		virtual std::string const & getName() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

class Character: public ICharacter
{
	private:
		Character();
		std::string name;
		AMateria *materia[4];
		int n_materia;

	public:
		Character(std::string const &name);
		Character(Character const &second);
		Character &operator=(Character const &second);
		virtual ~Character();

		std::string const & getName() const;

		void equip(AMateria* m);
		void use(int idx, ICharacter& target);
		void unequip(int idx);
};