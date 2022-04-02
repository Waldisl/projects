#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap ivan("Ivan");
	ClapTrap def;

	ivan.getInfo();
	ivan.attack("Oleg");
	ivan.getInfo();
	ivan.takeDamage(5);
	ivan.getInfo();
	ivan.beRepaired(30);
	ivan.getInfo();
	def.getInfo();
	def = ivan;
	def.getInfo();
	def.attack("Pil");
	def.attack("Pil");
	def.attack("Pil");
	def.attack("Pil");
	def.getInfo();
	def.attack("asd");
	return (0);
}