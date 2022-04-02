#include "ScavTrap.hpp"

int main(void)
{
	ClapTrap ivan("Ivan");
	ivan.getInfo();
	ivan.attack("Oleg");
	ivan.getInfo();
	ivan.takeDamage(5);
	ivan.getInfo();
	ivan.beRepaired(30);
	ivan.getInfo();

	ScavTrap grom("Grom");

	grom.getInfo();
	grom.attack("UFD");
	grom.getInfo();
	grom.takeDamage(30);
	grom.getInfo();
	grom.beRepaired(50);
	grom.getInfo();
	grom.guardGate();

	ClapTrap *ivan1 = &grom;

	ivan1->getInfo();
	ivan1->takeDamage(100);
	ivan1->getInfo();
	ivan1->attack("ssad");
	ivan1->getInfo();

	return (0);
}
// 	ClapTrap ivan("Ivan");
// 	ClapTrap def;

// 	ivan.getInfo();
// 	ivan.attack("Oleg");
// 	ivan.getInfo();
// 	ivan.takeDamage(5);
// 	ivan.getInfo();
// 	ivan.beRepaired(30);
// 	ivan.getInfo();
// 	def.getInfo();
// 	def = ivan;
// 	def.getInfo();
// 	def.attack("Pil");
// 	def.attack("Pil");
// 	def.attack("Pil");
// 	def.attack("Pil");
// 	def.getInfo();
// 	def.attack("asd");
// 	return (0);
// }