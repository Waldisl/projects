#include "ScavTrap.hpp"
#include "FragTrap.hpp"

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

	ivan = grom;
	ivan.getInfo();
	ivan.takeDamage(100);
	ivan.getInfo();

	FragTrap tom("Tom");

	tom.getInfo();
	tom.takeDamage(80);
	tom.getInfo();
	tom.beRepaired(20);
	tom.getInfo();

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